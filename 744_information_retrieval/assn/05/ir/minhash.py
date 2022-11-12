import random

import networkx as nx

NEXT_PRIME = 4294967311
MAX_VAL = 2**32 - 1


class MinHash:
    def __init__(self, shingle_sets: list[set[int]]) -> None:

        random.seed(0)
        self.shingle_sets = shingle_sets
        self.n_docs = len(shingle_sets)
        self.n_hashes = 200
        self.threshold = 0.5

        self.perms = [
            (
                random.randint(0, MAX_VAL),
                random.randint(0, MAX_VAL),
            )
            for _ in range(self.n_hashes)
        ]

        self.signatures: list[list[int]] = []
        self.sim = [[0.0] * self.n_docs for _ in range(self.n_docs)]

    def generate_signatures(self):

        for shingle_set in self.shingle_sets:

            signature: list[int] = []

            # For each of the random hash functions...
            for a, b in self.perms:

                min_hash_code = NEXT_PRIME + 1

                # For each shingle in the document...
                for shingle in shingle_set:
                    # Evaluate the hash function.
                    # a, b = self.perms[it]
                    hash_code = (a * shingle + b) % NEXT_PRIME

                    # Track the lowest hash code seen.
                    if hash_code < min_hash_code:
                        min_hash_code = hash_code

                # Add the smallest hash code value as component number
                # 'i' of the signature.
                signature.append(min_hash_code)

            # Store the MinHash signature for this document.
            self.signatures.append(signature)

    def compare_signatures(self):

        for first in range(self.n_docs):

            if first and not first % 1000:
                print(f"\t{first}/{self.n_docs}")

            for second in range(first + 1, self.n_docs):

                count = sum(
                    self.signatures[first][k] == self.signatures[second][k]
                    for k in range(self.n_hashes)
                )

                self.sim[first][second] = count / self.n_hashes

        print(f"\t{self.n_docs}/{self.n_docs}")
        self.signatures.clear()

    def find_near_duplicates(self) -> list[set[int]]:

        clusters = nx.utils.UnionFind(list(range(1, self.n_docs + 1)))
        for i in range(self.n_docs):

            for j in range(i + 1, self.n_docs):

                sim = self.sim[i][j]

                if sim > self.threshold:
                    clusters.union(i + 1, j + 1)

        return list(clusters.to_sets())
