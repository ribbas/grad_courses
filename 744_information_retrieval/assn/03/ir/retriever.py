from .const import DICT_IDX
from .invertedfile import InvertedFile
from .packer import Packer
from .types import Any


class Retriever:
    def __init__(self, invf: InvertedFile) -> None:

        self.invf = invf
        self.dictionary: dict[str, list[int]] = invf.get_dictionary()
        self.inverted_file: bytes = invf.get_inverted_file()

    def lookup(self, term: str) -> dict[str, Any]:

        metadata: dict[str, Any] = {"term": term}

        if term not in self.dictionary:
            return metadata

        of: int = self.dictionary[term][DICT_IDX.OF]
        width: int = self.dictionary[term][DICT_IDX.LEN]
        decoded_file: tuple[int, ...] = Packer.decode(self.inverted_file)
        postings: tuple[int, ...] = decoded_file[of : of + width : 2]
        term_counts: tuple[int, ...] = decoded_file[of + 1 : of + width + 1 : 2]
        pos_len: int = len(postings)

        metadata["offset"] = of
        metadata["width"] = width
        metadata["postings"] = postings
        metadata["postings_len"] = pos_len
        metadata["term_counts"] = term_counts

        return metadata
