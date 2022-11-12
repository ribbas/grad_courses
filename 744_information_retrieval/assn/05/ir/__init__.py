from pathlib import Path

from .files import CorpusFile, JHED
from .metrics import Metrics
from .minhash import MinHash


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.filename = filename
        self.docs = []
        self.clusters = []

    def ingest(self, ngrams: int, normalize: bool) -> None:

        print(
            f"Shingling documents with {ngrams}-grams and normalization={normalize}..."
        )
        self.docs = CorpusFile().ingest(self.filename, ngrams, normalize)

    def generate_signatures(self) -> None:

        min_hash = MinHash(self.docs)
        print("Generating signatures...")
        min_hash.generate_signatures()

        print("Comparing signatures...")
        min_hash.compare_signatures()

        print("Finding clusters...")
        self.clusters = min_hash.find_clusters()

    def sort_clusters(self) -> None:
        self.clusters.sort(key=len, reverse=True)

    def dump_clusters(self) -> None:

        self.sort_clusters()
        output = ""
        for c in self.clusters:
            output += " ".join(str(i) for i in c) + "\n"

        CorpusFile().dump_clusters(self.filename.stem, output)

    def __read_cluster(self, filename) -> set[frozenset[int]]:

        data: set[frozenset[int]] = set()
        with open(filename) as fp:
            cluster = frozenset[int]
            for line in fp:
                if line:
                    cluster = line[:-1].split(" ")
                    cluster = frozenset(int(i) for i in cluster)
                    data.add(cluster)

        return data

    def score(self, golden_file) -> tuple[int, int]:

        golden_data = self.__read_cluster(golden_file)
        output = self.__read_cluster(f"outputs/{JHED}-{self.filename.stem}.txt")

        gold_diff_out = golden_data.difference(output)
        out_diff_gold = output.difference(golden_data)

        return (len(gold_diff_out), len(out_diff_gold))
