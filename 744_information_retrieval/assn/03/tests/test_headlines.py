from pathlib import Path
from pprint import pprint
import unittest


from ir import InformationRetrieval


class TestQuick(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:

        super().__init__(methodName)

        self.ir_obj = InformationRetrieval()
        self.ir_obj.set_filename(
            Path(__file__).parent.parent / "data" / "cord19.txt"
        )
        self.ir_obj.load_inverted_file()

    def test1(self):

        # takes 193.823s
        tokens1 = self.ir_obj.normalize_query(
            "How has the COVID-19 pandemic impacted mental health?"
        )
        # # takes 186.949s
        # tokens1 = self.ir_obj.normalize_query(
        #     "which SARS-CoV-2 proteins-human proteins interactions indicate potential for drug targets. Are there approved drugs that can be repurposed based on this information?"
        # )
        results1 = self.ir_obj.read_inverted_file(tokens1)
        pprint(results1)
