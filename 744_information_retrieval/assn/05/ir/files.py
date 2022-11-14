from pathlib import Path

from .text import Normalizer, Shingle

JHED = "sahmed80"


class CorpusFile:
    @staticmethod
    def ingest(filename: Path, ngram: int, normalize: bool) -> list[set[int]]:

        shingle = Shingle(ngram)
        norm = Normalizer()
        docs: list[set[int]] = []

        with open(filename) as fp:
            for line in fp:
                if line:
                    _, doc = line[:-1].split("\t")
                    if normalize:
                        doc = norm(doc)
                    else:
                        doc = doc.split(" ")
                    doc_shingles = shingle(doc)
                    docs.append(doc_shingles)

        return docs

    @staticmethod
    def dump_clusters(filename: str, data: list[set[int]]) -> None:

        filepath = f"outputs/{JHED}-{filename}.txt"
        with open(filepath, "w") as fp:
            output = ""
            for c in data:
                output += " ".join(str(i) for i in c) + "\n"
            fp.write(output)
        print(f"Dumped to '{filepath}'")

    @staticmethod
    def read_clusters(filename: str) -> set[frozenset[int]]:

        data: set[frozenset[int]] = set()
        filepath = f"outputs/{JHED}-{filename}.txt"
        with open(filepath) as fp:
            cluster = frozenset[int]
            for line in fp:
                if line:
                    cluster = line[:-1].split(" ")
                    cluster = frozenset(int(i) for i in cluster)
                    data.add(cluster)

        return data
