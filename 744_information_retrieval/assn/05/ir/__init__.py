from pathlib import Path

from .files import CorpusFile
from .minhash import MinHash


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.filename: Path = filename
        self.docs: list[set[int]] = []
        self.clusters: list[set[int]] = []

    def ingest(self, ngrams: int = 2, normalize: bool = True) -> None:

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
        CorpusFile().dump_clusters(self.filename.stem, self.clusters)

    def score(self, golden_file: Path) -> tuple[int, int]:

        golden_data = CorpusFile().read_clusters(golden_file.stem)
        output = CorpusFile().read_clusters(self.filename.stem)

        gold_diff_out = golden_data.difference(output)
        out_diff_gold = output.difference(golden_data)

        return (len(gold_diff_out), len(out_diff_gold))
