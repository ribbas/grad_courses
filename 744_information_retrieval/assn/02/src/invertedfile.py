from typing import Generator, Iterable


class InvertedFile:
    def __init__(self, content: str, vocab: dict[str, int]) -> None:

        self.term_doc_tf = content
        self.vocab = vocab
        self.inv_file_data: Generator[list[str | int], None, None] = []
        self.col_split_list: list[tuple[int, int, int]] = []

    def convert_types(self, col_split_list: list[str]) -> tuple[int, int, int]:
        return (
            self.vocab[col_split_list[0]],
            int(col_split_list[1]),
            int(col_split_list[2]),
        )

    def map_to_int(self) -> list[tuple[int, int, int]]:

        return [
            self.convert_types(i.split(" "))
            for i in self.term_doc_tf.split("\n")[:-1]
        ]

    def ingest(self) -> None:

        # Python implicitly performs radix sort via timsort
        mapped_values: list[tuple[int, int, int]] = self.map_to_int()
        mapped_values.sort()
        # self.col_split_list = sorted(mapped_values, key=lambda x: x[0])
        print(mapped_values)

    def merge_postings(self) -> None:
        pass
