from pathlib import Path
from pprint import pprint
import unittest


from ir import InformationRetrieval


class TestQuick(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:

        super().__init__(methodName)

        self.ir_obj = InformationRetrieval()
        self.ir_obj.set_filename(
            Path(__file__).parent.parent / "data" / "headlines.txt"
        )
        self.ir_obj.load_inverted_file()

    def test1(self):

        tokens1 = self.ir_obj.normalize_test_terms(("Elon", "Musks"))
        results1 = self.ir_obj.read_inverted_file(tokens1)
        pprint(results1)
