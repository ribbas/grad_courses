from pathlib import Path
from pprint import pprint
from typing import Generator

from ir.files import IO, DataFile
from ir.invertedfile import InvertedFile
from ir.normalize import Normalizer


def read_inverted_file(
    invf: InvertedFile,
    tokens: Generator[str, None, None],
    keys: tuple[str, ...],
) -> Generator[dict[str, int | tuple[int, ...]], None, None]:

    for token in tokens:
        metadata = invf.lookup(token)
        yield {key: metadata.get(key, -1) for key in keys}


def normalize_test_terms(
    prep: Normalizer, terms: tuple[str, ...]
) -> Generator[str, None, None]:

    prep.set_document(" ".join(terms))
    prep.process()
    return prep.get_tokens()


if __name__ == "__main__":

    data = DataFile(Path(__file__).parent.parent / "data" / "cord19.txt")

    invf = InvertedFile()
    inv_file = IO.read_bin(data.inv_file_name)
    dict_ = IO.read_json(data.dict_name)

    invf.set_inverted_file(inv_file)
    invf.set_dictionary(dict_)

    prep = Normalizer()

    # print out the document frequency and postings list for terms:
    # "Heidelberg", "cesium", "Trondheim", "crustacean".
    # NOTE: the normalization stems "crustacean" to "crustacea"
    # and "crustaceans" to "crustacean"
    tokens1 = normalize_test_terms(
        prep, ("Heidelberg", "cesium", "Trondheim", "crustaceans")
    )
    results1 = read_inverted_file(
        invf,
        tokens1,
        ("term", "postings", "postings_len"),
    )
    pprint(list(results1))

    # give document frequency, but do not print postings for the words:
    # "Hopkins", "Stanford", "Brown", and "college"
    tokens2 = normalize_test_terms(
        prep, ("Hopkins", "Stanford", "Brown", "college")
    )
    results2 = read_inverted_file(invf, tokens2, ("term", "postings_len"))
    pprint(list(results2))

    # Print out the docids for documents that have both "Elon" and "Musk" in the text.
    tokens3 = normalize_test_terms(prep, ("Elon", "Musks"))
    results3 = read_inverted_file(invf, tokens3, ("postings",))
    elon, musk = results3
    elon_postings, musk_postings = set(elon["postings"]), set(musk["postings"])
    elon_musk_postings = elon_postings & musk_postings
    pprint(sorted(elon_musk_postings))
