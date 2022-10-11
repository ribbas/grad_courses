from math import log2, sqrt

from .const import IDX, QUERY_DOC_ID
from .invertedfile import InvertedFile
from .packer import Packer
from .types import Any


class Retriever:
    def __init__(self, invf: InvertedFile, num_docs: int) -> None:

        self.invf = invf
        self.num_docs = num_docs

        self.partial_len: list[float] = [0.0] * (self.num_docs + 1)

        self.dictionary: dict[str, list[int]] = invf.get_dictionary()
        self.inverted_file: bytes = invf.get_inverted_file_bytes()
        self.decoded_inverted_file: tuple[int, ...]

        self.retrievals: dict[str, dict[str, Any]] = {}
        self.query_tfidfs: dict[str, float] = {}
        self.doc_ids: set[int] = set()

        self.metrics: list[tuple[int, float]] = []

    def decode_inverted_file(self):

        self.decoded_inverted_file = Packer.decode(self.inverted_file)

    def retrieve(self, term: str) -> dict[str, Any]:

        invf_data: dict[str, Any] = {"term": term}

        # term not in dictionary
        if term not in self.dictionary:
            return invf_data

        of: int = self.dictionary[term][IDX.DICT.OF]
        width: int = self.dictionary[term][IDX.DICT.WID]
        decoded_chunk: tuple[int, ...] = self.decoded_inverted_file[
            of : of + width + 1
        ]

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
            decoded_chunk = self.decoded_inverted_file[of : of + width + 1]

            postings: tuple[int, ...] = decoded_chunk[:width:2]
            tfs: tuple[int, ...] = decoded_chunk[1 : width + 1 : 2]

            df: int = len(postings)
            idf: float = log2(self.num_docs / df)
            tfidfs: tuple[float, ...] = tuple(tf * idf for tf in tfs)

            for doc_id, tfidf in zip(postings, tfidfs):
                self.partial_len[doc_id] += tfidf * tfidf

    def compute_lengths(self) -> None:

        for doc_id in range(1, len(self.partial_len)):
            self.partial_len[doc_id] = sqrt(self.partial_len[doc_id])

    def get_lengths(self) -> list[float]:

        return self.partial_len

    def set_lengths(self, lengths: list[float]) -> None:

        self.partial_len = lengths

    @staticmethod
    def get_term_tfidf(
        doc_id: int, postings: tuple[int], tfidfs: tuple[int]
    ) -> float:

        if doc_id in postings:
            return tfidfs[postings.index(doc_id)]

        return 0

    def get_query_tfs(self, query_terms: list[str]) -> dict[str, float]:

        tfs: dict[str, float] = {}
        self.partial_len[QUERY_DOC_ID] = 0.0
        for term in query_terms:
            tfs[term] = query_terms.count(term) * self.retrievals[term]["idf"]
            self.partial_len[QUERY_DOC_ID] += tfs[term] * tfs[term]

        self.partial_len[QUERY_DOC_ID] = sqrt(self.partial_len[QUERY_DOC_ID])
        return tfs

    def dot_product(self, document: dict[str, float]) -> float:

        return sum(
            self.query_tfidfs[term] * document[term]
            for term in self.query_tfidfs.keys()
        )

    def update_retrievals(self, terms: list[str]) -> None:

        self.retrievals = {term: self.retrieve(term) for term in terms}

    def get_retrievals(self) -> dict[str, dict[str, Any]]:

        return self.retrievals

    def get_metrics(self) -> list[tuple[int, float]]:
        return self.metrics

    def update_doc_ids(self) -> None:

        for retr in self.retrievals.values():
            for posting in retr["postings"]:
                if retr["idf"]:
                    self.doc_ids.add(posting)

    def generate_metrics(self, query_terms: list[str]) -> None:

        self.metrics = [None] * len(self.doc_ids)
        cur: int = 0

        for doc_id in self.doc_ids:
            tfidfs: dict[str, float] = {}
            for term in query_terms:
                if term not in tfidfs:
                    tfidfs[term] = self.get_term_tfidf(
                        doc_id,
                        self.retrievals[term]["postings"],
                        self.retrievals[term]["tfidf"],
                    )

            self.metrics[cur] = (doc_id, self.similarity(doc_id, tfidfs))
            cur += 1

    def similarity(self, doc_id: int, doc_weights: dict[str, float]) -> float:

        dot: float = self.dot_product(doc_weights)
        doc_len: float = self.partial_len[doc_id]
        return dot / (doc_len * self.partial_len[QUERY_DOC_ID])

    def query(self, query_terms: list[str]) -> None:

        print(f"Querying '{query_terms}'...")

        # decode inverted file into memory
        self.decode_inverted_file()
        print("Decoded inverted file...")

        # initialize retrievals with terms from query
        self.update_retrievals(query_terms)
        print("Initialized retrievals...")

        # initialize set of all documents with at least one query term
        self.update_doc_ids()
        print(f"Found {len(self.doc_ids)} relevant documents...")

        self.query_tfidfs = self.get_query_tfs(query_terms)
        print("Computed weights for query terms...")

        # table of docID mapped to maps of term-TFIDF
        self.generate_metrics(query_terms)
        print("Generated metrics...")

        self.retrievals.clear()
        print("Cleared unnecessary containers...")

    def get_rankings(self, top_n: int = 100) -> list[tuple[int, float]]:

        return sorted(
            (retrieval for retrieval in self.metrics),
            key=lambda x: x[1],
            reverse=True,
        )[:top_n]
