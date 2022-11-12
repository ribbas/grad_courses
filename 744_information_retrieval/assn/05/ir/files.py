from pathlib import Path

from .normalize import Normalizer
from .shingle import Shingle

JHED = "sahmed80"


class CorpusFile:
    @staticmethod
    def ingest(
        filename: Path, n: int = 3, normalize: bool = True
    ) -> list[set[int]]:

        shingle = Shingle(n)
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
    def dump_clusters(filename: str, data: str) -> None:

        filepath = f"outputs/{JHED}-{filename}.txt"
        with open(filepath, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filepath}'")
