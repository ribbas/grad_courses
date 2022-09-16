from typing import Generator


class InvertedFile:
    def __init__(self, content: str, vocab: dict[str, int]) -> None:

        self.term_doc_tf = content
        self.vocab = vocab
        self.inv_file_data: Generator[list[str | int], None, None]
        self.mapped_values: list[tuple[int, int, int]] = []
        self.col_split_list: list[tuple[int, int, int]] = []

    def convert_types(self, col_split_list: list[str]) -> tuple[int, int, int]:
        return (
            self.vocab[col_split_list[0]],  # term ID
            int(col_split_list[1]),  # doc ID
            int(col_split_list[2]),  # term count
        )

    def map_to_int(self) -> list[tuple[int, int, int]]:

        return [
            self.convert_types(i.split(" "))
            for i in self.term_doc_tf.split("\n")[:-1]
        ]

    def ingest(self) -> None:

        self.mapped_values = self.map_to_int()
        # Python implicitly performs radix sort via timsort
        self.mapped_values.sort()

    def merge_postings(self) -> None:

        for i in self.mapped_values:
            print(f"{i[0]}={i[1:]}")
