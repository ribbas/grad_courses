class Shingle:
    def __init__(self, n) -> None:
        self.n = n

    def __ngrams(self, input_list):
        return zip(*(input_list[i:] for i in range(self.n)))

    def __call__(self, doc: list[str]) -> set[int]:

        shingles: set[int] = set()
        for shingle in self.__ngrams(doc):

            hashed_shingle = hash(" ".join(shingle)) & 0xFFFFFFFF
            shingles.add(hashed_shingle)

        return shingles
