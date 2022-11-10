import random

NEXT_PRIME = 4294967311
MAX_VAL = 2**32 - 1


class MinHash:
    def __init__(self, shingle_sets) -> None:

        random.seed(0)
        self.shingle_sets = shingle_sets
        self.n_docs = len(shingle_sets)
        self.n_hashes = 200

        self.perms = [
            (
                random.randint(0, MAX_VAL),
                random.randint(0, MAX_VAL),
            )
            for _ in range(self.n_hashes)
        ]

        self.signatures = []
        self.sim = [[0] * self.n_docs for _ in range(self.n_docs)]

    def generate_signatures(self):

        # For each document...
        for shingle_set in self.shingle_sets:

            signature = []

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

                # Add the smallest hash code value as component number 'i' of the signature.
                signature.append(min_hash_code)

            # Store the MinHash signature for this document.
            self.signatures.append(signature)

    def get_signatures(self):

        return self.signatures

    def compare_signatures(self):

        for i in range(self.n_docs):

            if not i % 1000:
                print("done with a thousand", i)

            for j in range(i + 1, self.n_docs):

                count = 0
                for k in range(self.n_hashes):
                    count += self.signatures[i][k] == self.signatures[j][k]

                self.sim[i][j] = count / self.n_hashes

    def find_near_duplicates(self):

        threshold = 0.5
        clusters = []
        for i in range(self.n_docs):
            cluster = [i + 1]
            for j in range(i + 1, self.n_docs):
                # Retrieve the estimated similarity value for this pair.
                # estJ = estJSim[getTriangleIndex(i, j)]
                estJ = self.sim[i][j]

                # If the similarity is above the threshold...
                if estJ > threshold:

                    cluster.append(j + 1)

                    # # Calculate the actual Jaccard similarity for validation.
                    # s1 = self.shingle_sets[i]
                    # s2 = self.shingle_sets[j]
                    # J = len(s1.intersection(s2)) / len(s1.union(s2))

                    # print(i + 1, end=" ")
                    # print(j + 1, end=" ")
                    # # Print out the match and similarity values with pretty spacing.
                    # # print(
                    # #     "  %5s --> %5s   %.5f     %.5f"
                    # #     % (i + 1, j + 1, estJ, J)
                    # # )
                    # print()
            clusters.append(cluster)

        return clusters
