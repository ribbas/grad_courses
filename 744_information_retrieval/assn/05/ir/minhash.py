import random

import numpy as np

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

        self.num_elems = int(self.n_docs * (self.n_docs - 1) / 2)
        self.sim = [0.0 for _ in range(self.num_elems)]

        # self.sim = [[0.0] * self.n_docs for _ in range(self.n_docs)]

    def get_triangle_index(self, i, j):

        if j < i:
            temp = i
            i = j
            j = temp

        k = int(i * (self.n_docs - (i + 1) / 2.0) + j - i) - 1

        return k

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

        # self.signatures = np.asarray(self.signatures)

    def compare_signatures(self):

        for first in range(self.n_docs):

            if not first % 1000:
                print(f"Documents: {first}/{self.n_docs}")

            for second in range(first + 1, self.n_docs):

                count = sum(
                    self.signatures[first][k] == self.signatures[second][k]
                    for k in range(self.n_hashes)
                )

                # self.sim[first][second] = count / self.n_hashes
                self.sim[self.get_triangle_index(first, second)] = (
                    count / self.n_hashes
                )

    def find_near_duplicates(self):

        clusters = []
        checked = set()
        for i in range(self.n_docs):

            if i + 1 not in checked:
                cluster = [i + 1]

                for j in range(i + 1, self.n_docs):

                    # sim = self.sim[i][j]
                    sim = self.sim[self.get_triangle_index(i, j)]

                    if sim > self.threshold:
                        checked.add(j + 1)
                        cluster.append(j + 1)

                clusters.append(cluster)

        return clusters
