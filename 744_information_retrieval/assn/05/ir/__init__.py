from pathlib import Path

from .files import CorpusFile
from .minhash import MinHash


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.filename = filename
        self.docs = []
        self.clusters = []

    def normalize(self) -> None:

        self.docs = CorpusFile().ingest(self.filename)

    def generate_signatures(self) -> None:

        min_hash = MinHash(self.docs)
        min_hash.generate_signatures()
        min_hash.compare_signatures()
        self.clusters = min_hash.find_near_duplicates()

    def dump_clusters(self) -> None:

        self.clusters.sort(key=len, reverse=True)

        output = ""
        for c in self.clusters:
            output += " ".join(str(i) for i in c) + "\n"

        CorpusFile().dump_clusters(self.filename, output)
