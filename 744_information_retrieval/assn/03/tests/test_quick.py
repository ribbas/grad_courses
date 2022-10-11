from pathlib import Path
import unittest


from ir import InformationRetrieval


class TestQuick(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:

        super().__init__(methodName)

        self.ir_obj = InformationRetrieval()
        self.ir_obj.set_filename(
            Path(__file__).parent.parent / "data" / "test.txt"
        )
        self.ir_obj.load_inverted_file()
        self.ir_obj.load_retriever()

    def test1(self):

        self.ir_obj.decode_inverted_file()
        tokens = self.ir_obj.normalize_query("apple orange")
        rankings = self.ir_obj.read_inverted_file(tokens)

        self.ir_obj.ingest_rankings({1: rankings, 3: rankings})
