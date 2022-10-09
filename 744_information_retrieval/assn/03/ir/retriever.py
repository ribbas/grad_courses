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

        self.dictionary: dict[str, list[int]] = invf.get_dictionary()
        self.inverted_file: bytes = invf.get_inverted_file_bytes()

        self.retrievals: dict[str, dict[str, Any]] = {}
        self.all_terms: dict[int, Any] = {}
        self.doc_ids: set[int] = set()

        self.tfidf_table: dict[int, dict[str, float]] = {}
        self.metrics_table: dict[int, dict[str, float]] = {}

    def lookup(self, term: str) -> dict[str, Any]:

        invf_data: dict[str, Any] = {"term": term}

        # term not in dictionary
        if term not in self.dictionary:
            return invf_data

        of: int = self.dictionary[term][IDX.DICT.OF]
        width: int = self.dictionary[term][IDX.DICT.LEN]
        decoded_chunk: tuple[int, ...] = Packer.decode(self.inverted_file)

        postings: tuple[int, ...] = decoded_chunk[of : of + width : 2]
        tf: tuple[int, ...] = decoded_chunk[of + 1 : of + width + 1 : 2]
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

    def get_document_terms(self, doc_id: int) -> list[str | int]:
        return [self.tid[str(term)] for term in self.doc_terms[str(doc_id)]]

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
        for term in query_terms:
            tfs[term] = query_terms.count(term) * self.retrievals[term]["idf"]

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

        for term in terms:
            if term not in self.retrievals:
                self.retrievals[term] = self.lookup(term)

    def get_retrievals(self) -> dict[str, dict[str, Any]]:

        return self.retrievals

    def get_metrics_table(self) -> dict[int, dict[str, float]]:
        return self.metrics_table

    def update_doc_ids(self) -> None:

        for retr in self.retrievals.values():
            for posting in retr["postings"]:
                if retr["idf"]:
                    self.doc_ids.add(posting)

    def retrieve_all_terms(self) -> None:

        for doc_id in self.doc_ids:
            self.all_terms[doc_id] = self.get_document_terms(doc_id)
            self.update_retrievals(self.all_terms[doc_id])

    def map_tfidf_table(self) -> None:

        for doc_id, terms in self.all_terms.items():
            tfidfs: dict[str, float] = {}
            for term in terms:
                tfidfs[term] = self.get_term_tfidf(
                    doc_id,
                    self.retrievals[term]["postings"],
                    self.retrievals[term]["tfidf"],
                )
            self.tfidf_table[doc_id] = tfidfs

    def generate_metrics_table(self) -> None:

        self.metrics_table = {
            doc_id: {
                "doc_id": 0.0,
                "dot": 0.0,
                "sum_sq": 0.0,
                "len": 0.0,
                "sim": 0.0,
            }
            for doc_id in (QUERY_DOC_ID, *self.doc_ids)
        }

        for doc_id in (QUERY_DOC_ID, *self.doc_ids):
            tfidfs = self.tfidf_table[doc_id]
            self.metrics_table[doc_id]["doc_id"] = doc_id
            self.metrics_table[doc_id]["sum_sq"] = sum(
                tfidf * tfidf for tfidf in tfidfs.values()
            )
            self.metrics_table[doc_id]["len"] = sqrt(
                self.metrics_table[doc_id]["sum_sq"]
            )
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

        # initialize retrievals with terms from query
        self.update_retrievals(query_terms)

        # initialize set of all documents with at least one query term
        self.update_doc_ids()

        # update retrievals with terms from all retrieved documents
        self.retrieve_all_terms()

        # table of docID mapped to maps of term-TFIDF
        self.map_tfidf_table()
        self.tfidf_table[QUERY_DOC_ID] = self.get_query_tfs(query_terms)

        self.generate_metrics_table()

    def get_rankings(self, top_n: int = 5) -> list[dict[str, float]]:

        rankings = sorted(
            (
                retrieval
                for doc_id, retrieval in self.metrics_table.items()
                if doc_id != QUERY_DOC_ID
            ),
            key=lambda x: x["sim"],
            reverse=True,
        )
        return rankings[:top_n]
