from typing import Any, Generator
from struct import pack, unpack


class InvertedFile:
    def __init__(self, content: str, vocab: dict[str, int]) -> None:

        self.term_doc_tf = content
        self.vocab = vocab
        self.inv_file_data: Generator[list[str | int], None, None]
        self.mapped_values: list[tuple[int, str, int, int]] = []
        self.col_split_list: list[tuple[int, int, int]] = []
        self.byte_fmt: str = ""

    def convert_types(
        self, col_split_list: list[str]
    ) -> tuple[int, str, int, int]:
        return (
            self.vocab[col_split_list[0]],  # term
            col_split_list[0],  # term ID
            int(col_split_list[1]),  # doc ID
            int(col_split_list[2]),  # term count
        )

    def map_to_int(self) -> list[tuple[int, str, int, int]]:

        return [
            self.convert_types(i.split(" "))
            for i in self.term_doc_tf.split("\n")[:-1]
        ]

    def ingest(self) -> None:

        self.mapped_values = self.map_to_int()

        # builtin timsort implicitly performs radix sort
        self.mapped_values.sort()

    def encode(self) -> bytes:

        cur: int = self.mapped_values[0][0]
        offset: int = 0
        inverted_file: list[int] = []
        dictionary: list[int] = []
        print(cur, offset)
        for i in self.mapped_values:
            if cur != i[0]:
                cur = i[0]
                print(i[1], offset)
            offset += 2
            inverted_file.extend(i[2:])
            print(f"    {i[2:]}")

        print(inverted_file)
        yo = 0
        for i in inverted_file:
            yo += 1
            print(f" | {i}", end="")
            if yo == 10:
                print(" |")
                yo = 0
        print()

        self.byte_fmt: str = "i" * len(inverted_file)

        return pack(self.byte_fmt, *inverted_file)

    def decode(self, data: bytes) -> tuple[int, ...]:

        if self.byte_fmt:
            print(data)
            return unpack(self.byte_fmt, data)

        raise AttributeError(
            "No byte format provided, maybe data is not yet encoded?"
        )

    def dictionary(self) -> dict[str, tuple[int, int]]:

        return {}
