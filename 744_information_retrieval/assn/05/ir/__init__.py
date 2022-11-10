from pathlib import Path

import numpy as np

from .files import CorpusFile, IO
from .minhash import MinHash
from .metrics import Metrics

JHED = "sahmed80"


class InformationRetrieval:
    def __init__(self) -> None:

        pass

    def read(self, filename: Path) -> None:

        docs = CorpusFile().ingest(filename)

        min_hash = MinHash(docs)
        min_hash.generate_signatures()
        min_hash.compare_signatures()
        clusters = min_hash.find_near_duplicates()

        from pprint import pprint

        pprint(clusters)
