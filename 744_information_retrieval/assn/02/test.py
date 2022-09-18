"""1. Print out the document frequency and postings list for terms: “Heidelberg", "cesium", “Trondheim”, “crustacean".
2. Give document frequency, but do not print postings for the words: "Hopkins", “Stanford", "Brown", and “college”
(these postings lists are longer -- I just want to see the counts).
3. Print out the docids for documents that have both "Elon" and "Musk" in the text. You can do this by finding the
postings list for each term, and then intersecting the two lists. For this test you do not need to use or supply frequency
information. Please print the docids in increasing order."""

from pathlib import Path
from typing import Generator

from ir.files import IO, DataFile
from ir.normalize import Normalizer
from ir.invertedfile import InvertedFile


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

    data = DataFile(Path(__file__).parent.parent / "data" / "headlines.txt")

    invf = InvertedFile()
    inv_file = IO.read_bin(data.inv_file_name)
    dict_ = IO.read_json(data.dict_name)

    invf.set_inverted_file(inv_file)
    invf.set_dictionary(dict_)

    prep = Normalizer()

    tokens1 = normalize_test_terms(
        prep, ("Heidelberg", "cesium", "Trondheim", "crustacean", "crustaceans")
    )
    results = read_inverted_file(
        invf,
        tokens1,
        ("term", "offset", "width", "postings", "postings_len"),
    )
    print(list(results))

    tokens2 = normalize_test_terms(
        prep, ("Hopkins", "Stanford", "Brown", "college")
    )
    results = read_inverted_file(invf, tokens2, ("term", "postings_len"))
    print(list(results))

    tokens3 = normalize_test_terms(prep, ("Elon", "Musks"))
    results = read_inverted_file(invf, tokens3, ("postings",))
    elon, musk = results
    elon_postings, musk_postings = set(elon["postings"]), set(musk["postings"])
    elon_musk_postings = elon_postings & musk_postings
    print(len(elon_musk_postings))
    print(sorted(elon_musk_postings))
