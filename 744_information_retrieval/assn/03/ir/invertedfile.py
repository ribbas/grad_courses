from .const import IDX, CHUNK_SIZE
from .types import generator, counter


class InvertedFile:
    def __init__(self) -> None:

        self.dictionary: dict[str, list[int]] = {}
        self.inverted_file_raw: list[int] = []

    def build_dict(self, df: counter, tf: counter) -> dict[str, list[int]]:

        for idx, term in enumerate(sorted(tf.keys())):
            # term: [term index, offset, length, df, tf]
            self.dictionary[term] = [idx, 0, 0, df[term], tf[term]]

        return self.dictionary

    def __convert_tdt_types(
        self, col_split_list: list[str]
    ) -> tuple[int, int, int, str]:
        return (
            self.dictionary[col_split_list[IDX.TID]][IDX.TID],  # term ID
            int(col_split_list[IDX.INVF.DID]),  # doc ID
            int(col_split_list[IDX.INVF.TC]),  # term count,
            col_split_list[IDX.TID],  # term
        )

    def __map_to_int(
        self, term_doc_tf: str
    ) -> generator[tuple[int, int, int, str]]:

        return (
            self.__convert_tdt_types(i.split(" "))
            for i in term_doc_tf.split("\n")[:-1]
        )

    def sort_mapped_tdt(
        self, term_doc_tf: str
    ) -> generator[list[tuple[int, int, int, str]]]:

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
        self, mapped_values: generator[tuple[int, int, int, str]]
    ) -> None:

        cur: int = -1
        offset: int = 0

        for val in mapped_values:

            term_str: str = val[IDX.INVF.STR]

            if cur != val[IDX.TID]:

                cur = val[IDX.TID]

                # update offset
                self.dictionary[term_str][IDX.DICT.OF] = offset

                # update width between the current term and the next
                self.dictionary[term_str][IDX.DICT.LEN] = (
                    self.dictionary[term_str][IDX.DICT.DF] * 2
                )

            offset += 2
            self.inverted_file_raw.extend(val[IDX.INVF.DID : IDX.INVF.STR])

    def set_inverted_file_raw(self, inverted_file_raw: list[int]) -> None:

        self.inverted_file_raw = inverted_file_raw

    def get_inverted_file_raw(self) -> list[int]:

        return self.inverted_file_raw

    def set_inverted_file_bytes(self, inverted_file_bytes: bytes) -> None:

        self.inverted_file_bytes = inverted_file_bytes

    def get_inverted_file_bytes(self) -> bytes:

        return self.inverted_file_bytes

    def set_dictionary(self, dictionary: dict[str, list[int]]) -> None:

        self.dictionary = dictionary

    def get_dictionary(self) -> dict[str, list[int]]:

        return self.dictionary
