import joblib
from pathlib import Path
from typing import Any

from .normalize import Normalizer


class CorpusFile:

    field_delim = "\t"
    norm = Normalizer()

    @staticmethod
    def __ngrams(input_list, n=3):
        return zip(*[input_list[i:] for i in range(n)])

    @staticmethod
    def __make_shingles(doc: list[str]) -> set[int]:

        shingles: set[int] = set()
        for shingle in CorpusFile.__ngrams(doc):

            crc = hash(" ".join(shingle)) & 0xFFFFFFFF
            shingles.add(crc)

        return shingles

    @staticmethod
    def __split(line: str) -> list[str]:

        return line.split(CorpusFile.field_delim)

    @staticmethod
    def ingest(filename: Path) -> list[set[int]]:

        docs: list[set[int]] = []

        with open(filename) as fp:
            for line in fp:
                if line:
                    _, doc = CorpusFile.__split(line[:-1])
                    normalized_doc = CorpusFile.norm(doc)
                    doc_shingles = CorpusFile.__make_shingles(normalized_doc)
                    docs.append(doc_shingles)

        return docs


class IO:
    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(filename, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}'")

    @staticmethod
    def read_joblib(filename: str) -> Any:

        return joblib.load(f"{filename}.joblib")

    @staticmethod
    def dump_joblib(filename: str, clf: Any) -> None:

        joblib.dump(clf, f"{filename}.joblib")
        print(f"Dumped model to '{filename}.joblib'")
