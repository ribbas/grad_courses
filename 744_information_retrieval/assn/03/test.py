from pathlib import Path
from pprint import pprint

from ir import InformationRetrieval


if __name__ == "__main__":

    ir_obj = InformationRetrieval()
    ir_obj.set_filename(Path(__file__).parent.parent / "data" / "headlines.txt")
    ir_obj.load_inverted_file()

    # print out the document frequency and postings list for terms:
    # "Heidelberg", "cesium", "Trondheim", "crustacean".
    # NOTE: the normalization stems "crustacean" to "crustacea"
    # and "crustaceans" to "crustacean"
    tokens1 = ir_obj.normalize_test_terms(
        ("Heidelberg", "cesium", "Trondheim", "crustaceans")
    )
    results1 = ir_obj.read_inverted_file(
        tokens1,
        ("term", "postings", "postings_len"),
    )
    pprint(list(results1))

    # give document frequency, but do not print postings for the words:
    # "Hopkins", "Stanford", "Brown", and "college"
    tokens2 = ir_obj.normalize_test_terms(
        ("Hopkins", "Stanford", "Brown", "college")
    )
    results2 = ir_obj.read_inverted_file(tokens2, ("term", "postings_len"))
    pprint(list(results2))

    # Print out the docids for documents that have both "Elon" and "Musk" in the text.
    tokens3 = ir_obj.normalize_test_terms(("Elon", "Musks"))
    results3 = ir_obj.read_inverted_file(tokens3, ("postings",))
    elon, musk = results3
    elon_postings, musk_postings = set(elon["postings"]), set(musk["postings"])
    elon_musk_postings = elon_postings & musk_postings
    pprint(sorted(elon_musk_postings))
