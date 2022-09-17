import json
from pathlib import Path
import re
from typing import Any

# from pprint import pprint

from .lexer import Lexer
from .normalize import Normalizer


class IO:

    table_header: str = (
        f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n----------------------------\n"
    )

    def __init__(self) -> None:

        self.prep: Normalizer
        self.lex: Lexer
        self.doc_id_re = re.compile(r"\d+")

        self.line_num = 0
        self.num_docs = 0
        self.term_doc_tf: list[tuple[str, str, int]] = []

    def set_preprocessor(self, prep: Normalizer) -> None:
        self.prep: Normalizer = prep

    def set_lexer(self, lex: Lexer) -> None:
        self.lex: Lexer = lex

    @staticmethod
    def read_json(filename: str) -> Any:

        with open(f"{filename}.json") as fp:
            return json.loads(fp.read())

    @staticmethod
    def dump_json(filename: str, data: Any) -> None:

        with open(f"{filename}.json", "w") as fp:
            json.dump(data, fp)

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}\n"

    def ingest_data_file(self, filename: Path) -> None:

        doc_id: str = ""
        with open(filename) as fp:
            for line in fp:
                match self.line_num % 4:

                    # line containing DocID
                    case 0:
                        doc_id = next(self.doc_id_re.finditer(line)).group()
                        self.num_docs += 1

                    # line containing document
                    case 1:

                        # normalize document through the preprocessing pipeline
                        self.prep.set_document(line)
                        self.prep.process()

                        # add processed tokens to the lexer
                        self.lex.add(self.prep.tokens())

                        # save records of term-DocID-tf
                        self.term_doc_tf.extend(self.lex.term_doc_tf(doc_id))

                    # empty lines
                    case _:
                        pass

                self.line_num += 1

    def read_term_doc_tf_file(self, filename: str) -> str:

        with open(f"{filename}_if.txt") as fp:
            return fp.read()

    def read_bin(self, filename: str) -> Any:

        with open(f"{filename}.bin", "rb") as fp:
            return fp.read()

    def dump_bin(self, filename: str, data: Any) -> None:

        with open(f"{filename}.bin", "wb") as fp:
            fp.write(data)
        print(f"Dumped to {filename}")

    def dump_term_doc_tf(self, filename: str) -> None:

        print("Dumped term_doc_tf", self.num_docs, "documents.")

        with open(f"{filename}_if.txt", "w") as fp:
            for line in self.term_doc_tf:
                print(*line, file=fp)

    def dump_stats(self, filename: str) -> None:

        print("Processed", self.num_docs, "documents.")

        self.dump_json(filename + "_df", self.lex.get_df())
        self.dump_json(filename + "_df", self.lex.get_df())

        contents: str = ""

        contents += "----------------------------\n"
        contents += f"{self.num_docs} documents.\n"

        contents += "----------------------------\n"
        contents += f"Collections size: {self.lex.get_collection_size()}\n"
        contents += f"Vocabulary size: {self.lex.get_vocab_size()}\n"
        contents += "\n----------------------------\n"

        contents += "Top 100 most frequent words:\n"
        contents += self.table_header
        for term in self.lex.get_top_n_tf_df(100):
            contents += self.__format_tf_df(*term)

        contents += "\n----------------------------\n"
        contents += "500th word:\n"
        contents += self.table_header
        contents += self.__format_tf_df(*self.lex.get_nth_freq_term(500))

        contents += "\n----------------------------\n"
        contents += "1000th word:\n"
        contents += self.table_header
        contents += self.__format_tf_df(*self.lex.get_nth_freq_term(1000))

        contents += "\n----------------------------\n"
        contents += "5000th word:\n"
        contents += self.table_header
        contents += self.__format_tf_df(*self.lex.get_nth_freq_term(5000))

        contents += "\n----------------------------\n"
        single_occs: int = self.lex.get_single_occs()
        contents += "Number of words that occur in exactly one document:\n"
        contents += f"{single_occs} ({round(single_occs / self.lex.get_vocab_size() * 100, 2)}%)\n"

        with open(f"{filename}_stats.txt", "w") as fp:
            fp.write(contents)
