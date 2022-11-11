from pathlib import Path

from .files import CorpusFile, JHED
from .metrics import Metrics
from .minhash import MinHash


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.filename = filename
        self.docs = []
        self.clusters = []

    def normalize(self) -> None:

        print("Normalizing documents...")
        self.docs = CorpusFile().ingest(self.filename, 3)

    def generate_signatures(self) -> None:

        min_hash = MinHash(self.docs)
        print("Generating signatures...")
        min_hash.generate_signatures()

        print("Comparing signatures...")
        min_hash.compare_signatures()

        print("Finding clusters...")
        self.clusters = min_hash.find_near_duplicates()

    def sort_clusters(self) -> None:
        self.clusters.sort(key=len, reverse=True)

    def dump_clusters(self) -> None:

        self.sort_clusters()
        output = ""
        for c in self.clusters:
            output += " ".join(str(i) for i in c) + "\n"

        CorpusFile().dump_clusters(self.filename.stem, output)

    def __read_cluster(self, filename) -> list[str]:

        data = []
        with open(filename) as fp:
            cluster = set()
            for line in fp:
                if line:
                    cluster = line[:-1].split(" ")
                    cluster = set(int(i) for i in cluster)
                    data.append(cluster)

        return data

    def score(self, golden_file):

        golden_data = self.__read_cluster(golden_file)
        output = self.__read_cluster(f"outputs/{JHED}-{self.filename.stem}.txt")

        metr = Metrics()
        metr.convert_ds(golden_data, output)
        metr.get_score()
