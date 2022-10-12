from pathlib import Path
import unittest


from ir import InformationRetrieval


class TestQuick(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:

        super().__init__(methodName)
        dir_name = Path(__file__).parent.parent

        self.ir_obj = InformationRetrieval()
        self.ir_obj.set_filename(dir_name / "data" / "cord19.txt")
        self.ir_obj.load_inverted_file()
        self.ir_obj.load_retriever()
        self.ir_obj.set_query_filename(
            dir_name.parent / "data" / "cord19.topics.keyword.txt"
        )
        self.kw_queries = self.ir_obj.ingest_query_file()
        self.ir_obj.set_query_filename(
            dir_name.parent / "data" / "cord19.topics.question.txt"
        )
        self.question_queries = self.ir_obj.ingest_query_file()

    def test_keyword(self):

        rankings = {}
        self.ir_obj.decode_inverted_file()

        for doc_id, tokens in self.kw_queries.items():
            rankings[doc_id] = self.ir_obj.read_inverted_file(tokens)
            self.ir_obj.reset_retriever()

        self.ir_obj.ingest_rankings(rankings)
