from collections import Counter
from typing import Generator
from struct import pack, unpack


class InvertedFile:
    def __init__(self) -> None:

        self.dictionary: dict[str, list[int]] = {}
        self.inv_file_data: Generator[list[str | int], None, None]
        self.mapped_values: list[tuple[int, int, int, str]] = []
        self.col_split_list: list[tuple[int, int, int]] = []
        self.inverted_file: list[int] = []
        self.byte_fmt: str = ""

    def vocabulary(
        self, df: Counter[str], tf: Counter[str]
    ) -> dict[str, list[int]]:

        for idx, term in enumerate(sorted(tf.keys())):
            self.dictionary[term] = [idx, 0, df[term], tf[term]]

        return self.dictionary

    def convert_inv_file_types(
        self, col_split_list: list[str]
    ) -> tuple[int, int, int, str]:
        return (
            self.dictionary[col_split_list[0]][0],  # term ID
            int(col_split_list[1]),  # doc ID
            int(col_split_list[2]),  # term count,
            col_split_list[0],  # term
        )

    def map_to_int(self, term_doc_tf: str) -> list[tuple[int, int, int, str]]:

        return [
            self.convert_inv_file_types(i.split(" "))
            for i in term_doc_tf.split("\n")[:-1]
        ]

    def ingest(self, term_doc_tf: str) -> None:

        self.mapped_values = self.map_to_int(term_doc_tf)

        # builtin timsort implicitly performs radix sort
        self.mapped_values.sort()

        cur: int = self.mapped_values[0][0]
        term_id_idx, offset_idx, tf_idx = (0, 1, 3)
        offset: int = 0

        print(cur, offset)
        for i in self.mapped_values:
            term_str: str = i[tf_idx]
            if cur != i[term_id_idx]:
                cur = i[term_id_idx]
                print(i[term_id_idx], offset)
                self.dictionary[term_str][offset_idx] = offset  # update offset
            offset += 2
            self.inverted_file.extend(i[offset_idx:tf_idx])
            print(f"    {i[offset_idx:tf_idx]}")

        print(self.dictionary)

    def get_inverted_file(self) -> list[int]:

        return self.inverted_file

    def set_byte_fmt(self, data: list[int]) -> None:

        self.byte_fmt = "i" * len(data)

    @staticmethod
    def encode(byte_fmt: str, data: list[int]) -> bytes:

        return pack(byte_fmt, *data)

    @staticmethod
    def decode(byte_fmt: str, data: bytes) -> tuple[int, ...]:

        print(data)
        return unpack(byte_fmt, data)
