from math import log2, sqrt

from .const import IDX, QUERY_DOC_ID
from .invertedfile import InvertedFile
from .packer import Packer
from .types import Any


class Retriever:
    def __init__(
        self,
        invf: InvertedFile,
        num_docs: int,
        doc_terms: dict[str, list[int]],
        tid: dict[str, int | str],
    ) -> None:

        self.invf = invf
        self.num_docs = num_docs
        self.tid = tid
        self.doc_terms = doc_terms

        self.partial_len: dict[int | str, float] = {
            doc_id: 0.0 for doc_id in range(1, self.num_docs + 1)
        }

        self.dictionary: dict[str, list[int]] = invf.get_dictionary()
        self.inverted_file: bytes = invf.get_inverted_file_bytes()
        self.decoded_invf: tuple[int, ...]

        self.retrievals: dict[str, dict[str, Any]] = {}
        # self.all_terms: dict[int, Any] = {}
        self.doc_ids: set[int] = set()

        self.tfidf_table: dict[int, dict[str, float]] = {}
        self.metrics_table: dict[int, dict[str, float]] = {}

    def decode_inverted_file(self):

        self.decoded_invf = Packer.decode(self.inverted_file)

    def lookup_all(self, term: str) -> dict[str, Any]:

        invf_data: dict[str, Any] = {"term": term}

        # term not in dictionary
        if term not in self.dictionary:
            return invf_data

        of: int = self.dictionary[term][IDX.DICT.OF]
        width: int = self.dictionary[term][IDX.DICT.WID]
        decoded_chunk: tuple[int, ...] = self.decoded_invf[of : of + width + 1]

        postings: tuple[int, ...] = decoded_chunk[:width:2]
        tf: tuple[int, ...] = decoded_chunk[1 : width + 1 : 2]
        df: int = len(postings)
        idf: float = log2(self.num_docs / df)
        tfidf: tuple[float, ...] = tuple(i * idf for i in tf)

        invf_data["of"] = of
        invf_data["width"] = width

        invf_data["postings"] = postings
        invf_data["tf"] = tf

        invf_data["df"] = df
        invf_data["idf"] = idf
        invf_data["tfidf"] = tfidf

        return invf_data

    def lookup(self, term: str) -> dict[str, Any]:

        invf_data: dict[str, Any] = {"term": term}

        # term not in dictionary
        if term not in self.dictionary:
            return invf_data

        of: int = self.dictionary[term][IDX.DICT.OF]
        width: int = self.dictionary[term][IDX.DICT.WID]
        decoded_chunk: tuple[int, ...] = self.decoded_invf[of : of + width + 1]

        postings: tuple[int, ...] = decoded_chunk[:width:2]
        tf: tuple[int, ...] = decoded_chunk[1 : width + 1 : 2]
        df: int = len(postings)
        idf: float = log2(self.num_docs / df)
        tfidf: tuple[float, ...] = tuple(i * idf for i in tf)

        invf_data["postings"] = postings

        invf_data["idf"] = idf
        invf_data["tfidf"] = tfidf

        return invf_data

    def compute_sum_of_squares(self) -> None:

        for val in self.dictionary.values():
            of: int = val[IDX.DICT.OF]
            width: int = val[IDX.DICT.WID]
            decoded_chunk = self.decoded_invf[of : of + width + 1]

            postings: tuple[int, ...] = decoded_chunk[:width:2]
            tfs: tuple[int, ...] = decoded_chunk[1 : width + 1 : 2]

            df: int = len(postings)
            idf: float = log2(self.num_docs / df)
            tfidfs: tuple[float, ...] = tuple(tf * idf for tf in tfs)

            for doc_id, tfidf in zip(postings, tfidfs):
                self.partial_len[doc_id] += tfidf * tfidf

    def compute_lengths(self) -> None:

        for doc_id, sum_sq in self.partial_len.items():
            self.partial_len[doc_id] = sqrt(sum_sq)

    def get_lengths(self) -> dict[int | str, float]:

        return self.partial_len

    def set_lengths(self, lengths: dict[int | str, float]) -> None:

        self.partial_len = lengths

    @staticmethod
    def get_term_tfidf(
        doc_id: int, postings: tuple[int], tfidfs: tuple[int]
    ) -> float:

        for posting, term_count in zip(postings, tfidfs):
            if posting == doc_id:
                return term_count

        return 0

    def get_query_tfs(self, query_terms: list[str]) -> dict[str, float]:

        tfs: dict[str, float] = {}
        self.partial_len[QUERY_DOC_ID] = 0.0
        for term in query_terms:
            tfs[term] = query_terms.count(term) * self.retrievals[term]["idf"]
            self.partial_len[QUERY_DOC_ID] += tfs[term] * tfs[term]

        self.partial_len[QUERY_DOC_ID] = sqrt(self.partial_len[QUERY_DOC_ID])
        return tfs

    @staticmethod
    def dot_product(
        document: dict[str, float], query: dict[str, float]
    ) -> float:

        dot: float = 0
        for term in query.keys():
            dot += query[term] * document.get(term, 0)

        return dot

    def update_retrievals(self, terms: list[str]) -> None:

        self.retrievals = {term: self.lookup(term) for term in terms}

    def get_retrievals(self) -> dict[str, dict[str, Any]]:

        return self.retrievals

    def get_metrics_table(self) -> dict[int, dict[str, float]]:
        return self.metrics_table

    def update_doc_ids(self) -> None:

        for retr in self.retrievals.values():
            for posting in retr["postings"]:
                if retr["idf"]:
                    self.doc_ids.add(posting)

    def map_tfidf_table(self, query_terms: list[str]) -> None:

        for doc_id in self.doc_ids:
            tfidfs: dict[str, float] = {}
            for term in query_terms:
                tfidfs[term] = self.get_term_tfidf(
                    doc_id,
                    self.retrievals[term]["postings"],
                    self.retrievals[term]["tfidf"],
                )
            self.tfidf_table[doc_id] = tfidfs

    def generate_metrics_table(self) -> None:

        self.metrics_table = {
            doc_id: {
                "doc_id": 0,
                "dot": 0.0,
                "len": 0.0,
                "sim": 0.0,
            }
            for doc_id in (QUERY_DOC_ID, *self.doc_ids)
        }

        for doc_id in (QUERY_DOC_ID, *self.doc_ids):
            tfidfs = self.tfidf_table[doc_id]
            self.metrics_table[doc_id]["doc_id"] = doc_id
            self.metrics_table[doc_id]["len"] = self.partial_len[str(doc_id)]
            # self.metrics_table[doc_id]["len"] = sqrt(
            #     self.metrics_table[doc_id]["sum_sq"]
            # )
            self.metrics_table[doc_id]["dot"] = self.dot_product(
                tfidfs, self.tfidf_table[QUERY_DOC_ID]
            )
            self.metrics_table[doc_id]["sim"] = self.metrics_table[doc_id][
                "dot"
            ] / (
                self.metrics_table[doc_id]["len"]
                * self.metrics_table[QUERY_DOC_ID]["len"]
            )

    def query(self, query_terms: list[str]) -> None:

        self.decode_inverted_file()

        # initialize retrievals with terms from query
        self.update_retrievals(query_terms)

        # initialize set of all documents with at least one query term
        self.update_doc_ids()

        # table of docID mapped to maps of term-TFIDF
        self.map_tfidf_table(query_terms)
        self.tfidf_table[QUERY_DOC_ID] = self.get_query_tfs(query_terms)

        self.generate_metrics_table()

    def get_rankings(self, top_n: int = 5) -> list[dict[str, float]]:

        rankings = sorted(
            (
                retrieval
                for doc_id, retrieval in self.metrics_table.items()
                if str(doc_id) != QUERY_DOC_ID
            ),
            key=lambda x: x["sim"],
            reverse=True,
        )
        return rankings[:top_n]
