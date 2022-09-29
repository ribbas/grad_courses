from collections import Counter
from typing import Any, Generator

from .const import CHUNK_SIZE
from .packer import Packer

# shared indices
TERM_ID_IDX = 0

# dictionary indices
OFFSET_IDX, LEN_IDX, DF_IDX, TF_IDX = (1, 2, 3, 4)

# inverted file indices
DOC_ID_IDX, TC_IDX, TERM_STR_IDX = (1, 2, 3)


class InvertedFile:
    def __init__(self) -> None:

        self.dictionary: dict[str, list[int]] = {}
        # self.mapped_values: Generator[tuple[int, int, int, str], None, None]
        # self.mapped_values_sorted: list[tuple[int, int, int, str]] = []
        self.inverted_file_raw: list[int] = []

    def build_dict(
        self, df: Counter[str], tf: Counter[str]
    ) -> dict[str, list[int]]:

        for idx, term in enumerate(sorted(tf.keys())):
            # term: [term index, offset, length, df, tf]
            self.dictionary[term] = [idx, 0, 0, df[term], tf[term]]

        return self.dictionary

    def __convert_tdt_types(
        self, col_split_list: list[str]
    ) -> tuple[int, int, int, str]:
        return (
            self.dictionary[col_split_list[TERM_ID_IDX]][
                TERM_ID_IDX
            ],  # term ID
            int(col_split_list[DOC_ID_IDX]),  # doc ID
            int(col_split_list[TC_IDX]),  # term count,
            col_split_list[TERM_ID_IDX],  # term
        )

    def __map_to_int(
        self, term_doc_tf: str
    ) -> Generator[tuple[int, int, int, str], None, None]:

        return (
            self.__convert_tdt_types(i.split(" "))
            for i in term_doc_tf.split("\n")[:-1]
        )

    def sort_mapped_tdt(
        self, term_doc_tf: str
    ) -> Generator[list[tuple[int, int, int, str]], None, None]:

        mapped_values = self.__map_to_int(term_doc_tf)

        chunk: list[tuple[int, int, int, str]] = []
        cur_cs: int = 0

        for mapped_value in mapped_values:
            cur_cs += 1
            chunk.append(mapped_value)
            if cur_cs % CHUNK_SIZE == 0:
                chunk.sort()
                yield chunk
                chunk = []

        if chunk:
            chunk.sort()
            yield chunk
            chunk = []

    def convert(
        self, mapped_values: Generator[tuple[int, int, int, str], None, None]
    ) -> None:

        cur: int = -1
        offset: int = 0

        for val in mapped_values:

            term_str: str = val[TERM_STR_IDX]

            if cur != val[TERM_ID_IDX]:

                cur = val[TERM_ID_IDX]

                # update offset
                self.dictionary[term_str][OFFSET_IDX] = offset

                # update width between the current term and the next
                self.dictionary[term_str][LEN_IDX] = (
                    self.dictionary[term_str][DF_IDX] * 2
                )

            offset += 2
            self.inverted_file_raw.extend(val[DOC_ID_IDX:TERM_STR_IDX])

    def set_inverted_file_raw(self, inverted_file_raw: list[int]) -> None:

        self.inverted_file_raw = inverted_file_raw

    def get_inverted_file_raw(self) -> list[int]:

        return self.inverted_file_raw

    def set_inverted_file(self, inverted_file: bytes) -> None:

        self.inverted_file = inverted_file

    def get_inverted_file(self) -> bytes:

        return self.inverted_file

    def set_dictionary(self, dictionary: dict[str, list[int]]) -> None:

        self.dictionary = dictionary

    def get_dictionary(self) -> dict[str, list[int]]:

        return self.dictionary

    def lookup(self, term: str) -> dict[str, Any]:

        metadata: dict[str, Any] = {"term": term}

        if term not in self.dictionary:
            return metadata

        of: int = self.dictionary[term][OFFSET_IDX]
        width: int = self.dictionary[term][LEN_IDX]
        postings: tuple[int, ...] = Packer.decode(self.inverted_file)[
            of : of + width : 2
        ]
        pos_len: int = len(postings)

        metadata["offset"] = of
        metadata["width"] = width
        metadata["postings"] = postings
        metadata["postings_len"] = pos_len

        return metadata
