import random

import networkx as nx

NEXT_PRIME = 4294967311
MAX_VAL = 4294967295


class MinHash:
    def __init__(self, shingle_sets: list[set[int]]) -> None:

        random.seed(0)
        self.shingle_sets = shingle_sets
        self.n_docs = len(shingle_sets)
        self.n_hashes = 200
        self.threshold = 0.5 * self.n_hashes

        self.signatures: list[list[int]] = []
        self.sim: list[list[int]] = [
            [0] * self.n_docs for _ in range(self.n_docs)
        ]

    def __hash_func_coeffs(self) -> list[tuple[int, int]]:

        return [
            (
                random.randint(0, MAX_VAL),
                random.randint(0, MAX_VAL),
            )
            for _ in range(self.n_hashes)
        ]

    def generate_signatures(self) -> None:

        hash_func_coeffs = self.__hash_func_coeffs()

        for shingle_set in self.shingle_sets:
            signature: list[int] = []

            for a, b in hash_func_coeffs:
                phi_s = NEXT_PRIME + 1
                for shingle in shingle_set:
                    hash_code = (a * shingle + b) % NEXT_PRIME

                    if hash_code < phi_s:
                        phi_s = hash_code

                signature.append(phi_s)

            self.signatures.append(signature)

        self.shingle_sets.clear()

    def compare_signatures(self) -> None:

        for first in range(self.n_docs):

            if not first % 1000:
                print(f"\t{first}/{self.n_docs}")

            for second in range(first + 1, self.n_docs):

                self.sim[first][second] = sum(
                    self.signatures[first][k] == self.signatures[second][k]
                    for k in range(self.n_hashes)
                )

        print(f"\t{self.n_docs}/{self.n_docs}")
        self.signatures.clear()

    def find_clusters(self) -> list[set[int]]:

        clusters = nx.utils.UnionFind(list(range(1, self.n_docs + 1)))

        for first in range(self.n_docs):
            for second in range(first + 1, self.n_docs):
                sim = self.sim[first][second]
                if sim > self.threshold:
                    clusters.union(first + 1, second + 1)

        return list(clusters.to_sets())
