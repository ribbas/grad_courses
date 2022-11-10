from pathlib import Path

from .files import CorpusFile
from .minhash import MinHash


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.filename = filename
        self.docs = []
        self.clusters = []

    def normalize(self) -> None:

        print("Normalizing documents...")
        self.docs = CorpusFile().ingest(self.filename)

    def generate_signatures(self) -> None:

        min_hash = MinHash(self.docs)
        print("Generating signatures...")
        min_hash.generate_signatures()
        print("Comparing signatures...")
        min_hash.compare_signatures()
        print("Finding clusters...")
        self.clusters = min_hash.find_near_duplicates()

    def dump_clusters(self) -> None:

        self.clusters.sort(key=len, reverse=True)

        output = ""
        for c in self.clusters:
            output += " ".join(str(i) for i in c) + "\n"

        CorpusFile().dump_clusters(self.filename.stem, output)
