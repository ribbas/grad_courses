from typing import Generator


class InvertedFile:
    def __init__(self, content: str, vocab: dict[str, int]) -> None:

        self.term_doc_tf = content
        self.vocab = vocab
        self.inv_file_data: Generator[list[str | int], None, None] = []

    def convert_types(self, col_split_list: list[str]) -> tuple[int, int, int]:
        return (
            self.vocab[col_split_list[0]],
            int(col_split_list[1]),
            int(col_split_list[2]),
        )

    def ingest(self) -> None:

        col_split_list: list[tuple[int, int, int]] = sorted(
            (
                self.convert_types(i.split(" "))
                for i in self.term_doc_tf.split("\n")[:-1]
            ),
            key=lambda x: x[1],
        )
        col_split_list = sorted(col_split_list, key=lambda x: x[0])
        print(col_split_list)
