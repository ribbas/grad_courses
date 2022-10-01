from math import log2, sqrt

from .const import IDX
from .invertedfile import InvertedFile
from .packer import Packer
from .types import Any, generator


class Retriever:
    def __init__(
        self, invf: InvertedFile, num_docs: int, doc_vocabs: str
    ) -> None:

        self.invf = invf
        self.num_docs = num_docs
        self.doc_vocabs = doc_vocabs.split("\n")
        self.dictionary: dict[str, list[int]] = invf.get_dictionary()
        self.inverted_file: bytes = invf.get_inverted_file_bytes()

    def lookup(self, term: str) -> dict[str, Any]:

        metadata: dict[str, Any] = {"term": term}

        # term not in dictionary
        if term not in self.dictionary:
            return metadata

        of: int = self.dictionary[term][IDX.DICT.OF]
        width: int = self.dictionary[term][IDX.DICT.LEN]

        decoded_file: tuple[int, ...] = Packer.decode(self.inverted_file)
        postings: tuple[int, ...] = decoded_file[of : of + width : 2]
        df: int = len(postings)
        # print("num docs", self.num_docs)
        idf: float = log2(self.num_docs / df)

        tf: tuple[int, ...] = decoded_file[of + 1 : of + width + 1 : 2]
        total_term_count: int = sum(tf)

        tfidf: tuple[float] = tuple(tf * idf for tf in tf)

        metadata["offset"] = of
        metadata["width"] = width
        metadata["postings"] = postings
        metadata["df"] = df
        metadata["idf"] = idf
        metadata["tf"] = tf
        metadata["total_term_count"] = total_term_count
        metadata["tfidf"] = tfidf

        return metadata

    def get_document(self, doc_id: int) -> list[str]:
        return self.doc_vocabs[doc_id - 1].split(" ")

    @staticmethod
    def get_term_tfidf(
        doc_id: int, postings: tuple[int], tfidfs: tuple[int]
    ) -> float:

        for posting, term_count in zip(postings, tfidfs):
            if posting == doc_id:
                return term_count

        return 0

    def get_query_tfs(self, query_tokens: list[str]) -> dict[str, float]:

        tfs: dict[str, float] = {}
        for token in query_tokens:
            tfs[token] = query_tokens.count(token)

        return tfs

    def dot_product(
        self, document: dict[str, float], query: dict[str, float]
    ) -> float:

        dot: float = 0
        for term in query.keys():
            dot += query[term] * document[term]

        return dot

    def query(self, query_tokens: list[str]) -> list[dict[str, Any]]:

        retrievals: dict[str, dict[str, Any]] = {}
        doc_ids: set[int] = set()

        for token in query_tokens:
            retrievals[token] = self.lookup(token)

        for retr in retrievals.values():
            for posting in retr["postings"]:
                doc_ids.add(posting)

        print(doc_ids)

        all_tokens: set[str] = set()
        all_terms: dict[int, Any] = {}

        for i in doc_ids:
            all_terms[i] = self.get_document(i)
            for term in all_terms[i]:
                all_tokens.add(term)

        print(all_tokens)
        for token in all_tokens:
            if token not in retrievals:
                retrievals[token] = self.lookup(token)

        summary: dict[int, dict[str, float]] = {}

        for doc_id, terms in all_terms.items():
            tfidfs: dict[str, float] = {}
            for term in terms:
                tfidf: float = self.get_term_tfidf(
                    doc_id,
                    retrievals[term]["postings"],
                    retrievals[term]["tfidf"],
                )
                tfidfs[term] = tfidf
            summary[doc_id] = tfidfs

        query_tfs = self.get_query_tfs(query_tokens)
        for term in query_tokens:
            query_tfs[term] = query_tfs[term] * retrievals[term]["idf"]

        metrics: dict[int, dict[str, float]] = {
            doc_id: {"dot": 0.0, "sum_of_squares": 0.0, "len": 0.0, "sim": 0.0}
            for doc_id in (-1, *doc_ids)
        }

        summary[-1] = query_tfs

        for doc_id in (-1, *doc_ids):
            tfidfs = summary[doc_id]
            metrics[doc_id]["sum_of_squares"] = sum(
                tfidf * tfidf for tfidf in tfidfs.values()
            )
            metrics[doc_id]["len"] = sqrt(metrics[doc_id]["sum_of_squares"])
            metrics[doc_id]["dot"] = self.dot_product(tfidfs, summary[-1])
            metrics[doc_id]["sim"] = metrics[doc_id]["dot"] / (
                metrics[doc_id]["len"] * metrics[-1]["len"]
            )

        return retrievals
