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
        self.sim = [[0.0] * self.n_docs for _ in range(self.n_docs)]
        # self.sim = np.zeros((self.n_docs, self.n_docs))

    def generate_signatures(self):

        for shingle_set in self.shingle_sets:

            signature: list[int] = []

            # For each of the random hash functions...
            for i in range(self.n_hashes):

                min_hash_code = NEXT_PRIME + 1

                # For each shingle in the document...
                for shingle in shingle_set:
                    # Evaluate the hash function.
                    a, b = self.perms[i]
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

        for i in range(self.n_docs):

            if not i % 1000:
                print("done with a thousand", i)

            for j in range(i + 1, self.n_docs):

                count = sum(
                    self.signatures[i][k] == self.signatures[j][k]
                    for k in range(self.n_hashes)
                )

                self.sim[i][j] = count / self.n_hashes

    def find_near_duplicates(self):

        clusters = []
        checked = set()
        for i in range(self.n_docs):

            if i + 1 not in checked:
                cluster = [i + 1]

                for j in range(i + 1, self.n_docs):

                    sim = self.sim[i][j]

                    if sim > self.threshold:
                        checked.add(j + 1)
                        cluster.append(j + 1)

                clusters.append(cluster)

        return clusters
