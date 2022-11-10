from pathlib import Path

from .normalize import Normalizer
from .shingle import Shingle

JHED = "sahmed80"


class CorpusFile:
    @staticmethod
    def ingest(filename: Path, n: int = 3) -> list[set[int]]:

        norm = Normalizer()
        shingle = Shingle(n)
        docs: list[set[int]] = []

        with open(filename) as fp:
            for line in fp:
                if line:
                    _, doc = line[:-1].split("\t")
                    normalized_doc = norm(doc)
                    doc_shingles = shingle(normalized_doc)
                    docs.append(doc_shingles)

        return docs

    @staticmethod
    def dump_clusters(filename: str, data: str) -> None:

        filepath = f"outputs/{JHED}-{filename}.txt"
        with open(filepath, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filepath}'")
