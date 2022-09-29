from pathlib import Path
import unittest

from ir import InformationRetrieval
from ir.files import IO


class TestHeadlines(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:

        super().__init__(methodName)
        self.golden_file = IO.read_json(Path(__file__).parent / "headlines")

        self.ir_obj = InformationRetrieval()
        self.ir_obj.set_filename(
            Path(__file__).parent.parent / "data" / "headlines.txt"
        )
        self.ir_obj.load_inverted_file()

    def test1(self):

        # print out the document frequency and postings list for terms:
        # "Heidelberg", "cesium", "Trondheim", "crustacean".
        # NOTE: the normalization stems "crustacean" to "crustacea"
        # and "crustaceans" to "crustacean"
        tokens1 = self.ir_obj.normalize_test_terms(
            ("Heidelberg", "cesium", "Trondheim", "crustaceans")
        )
        results1 = self.ir_obj.read_inverted_file(
            tokens1,
            ("term", "postings", "postings_len"),
        )
        for test in results1:
            for real in self.golden_file[0]:
                if test["term"] == real["term"]:
                    for k, v in test.items():
                        assert test[k] == v

    def test2(self):
        # give document frequency, but do not print postings for the words:
        # "Hopkins", "Stanford", "Brown", and "college"
        tokens2 = self.ir_obj.normalize_test_terms(
            ("Hopkins", "Stanford", "Brown", "college")
        )
        results2 = self.ir_obj.read_inverted_file(
            tokens2, ("term", "postings_len")
        )

        for test in results2:
            for real in self.golden_file[1]:
                if test["term"] == real["term"]:
                    for k, v in test.items():
                        assert test[k] == v

    def test3(self):

        # print out the docids for documents that have both "Elon" and "Musk"
        # in the text
        tokens3 = self.ir_obj.normalize_test_terms(("Elon", "Musks"))
        results3 = self.ir_obj.read_inverted_file(tokens3, ("postings",))
        elon, musk = results3
        elon_postings, musk_postings = set(elon["postings"]), set(
            musk["postings"]
        )
        elon_musk_postings = elon_postings & musk_postings
        assert elon_musk_postings == set(self.golden_file[2])
