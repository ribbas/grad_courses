import json
from pathlib import Path
import re
from typing import Any

# from pprint import pprint

from .lexer import Lexer
from .normalize import Normalizer


class IO:

    table_header: str = (
        f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n----------------------------"
    )

    def __init__(self, filename: Path, prep: Normalizer, lex: Lexer) -> None:

        self.filename = filename
        self.prep: Normalizer = prep
        self.lex: Lexer = lex
        self.doc_id_re = re.compile(r"\d+")

        self.line_num = 0
        self.num_docs = 0
        self.term_doc_tf: list[tuple[str, str, int]] = []

    @staticmethod
    def __dump_json(filename: str, data: Any) -> None:

        with open(f"{filename}.json", "w") as fp:
            json.dump(data, fp)

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}"

    def ingest_data_file(self) -> None:

        doc_id: str = ""
        with open(self.filename) as fp:
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
                        self.lex.add(self.prep.get_tokens())

                        # save records of term-DocID-tf
                        self.term_doc_tf.extend(self.lex.term_doc_tf(doc_id))

                    # empty lines
                    case _:
                        pass

                self.line_num += 1

    def read_term_doc_tf_file(self, filename: str) -> str:

        with open(f"{filename}_if.txt") as fp:
            return fp.read()

    def dump_all_to_txt(self, filename: str, data: Any) -> None:

        print("Dumped term_doc_tf", self.num_docs, "documents.")

        with open(f"{filename}.txt", "w") as fp:
            fp.write("\n".join(data))

    def dump_term_doc_tf(self, filename: str) -> None:

        print("Dumped term_doc_tf", self.num_docs, "documents.")

        with open(f"{filename}_if.txt", "w") as fp:
            for line in self.term_doc_tf:
                print(*line, file=fp)

    def print_stats(self, filename: str) -> None:

        print("Processed", self.num_docs, "documents.")

        self.__dump_json(filename + "_tf", self.lex.get_tf())
        self.__dump_json(filename + "_df", self.lex.get_df())

        with open(f"{filename}_stats.txt", "w") as fp:

            print("----------------------------", file=fp)
            print(self.num_docs, "documents.", file=fp)

            print("----------------------------", file=fp)
            print("Collections size:", self.lex.get_collection_size(), file=fp)
            print("Vocabulary size:", self.lex.get_vocab_size(), file=fp)
            print("\n----------------------------", file=fp)

            print("Top 100 most frequent words:", file=fp)
            print(self.table_header, file=fp)
            for term in self.lex.get_top_n_tf_df(100):
                print(self.__format_tf_df(*term), file=fp)

            print("\n----------------------------", file=fp)
            print("500th word:", file=fp)
            print(self.table_header, file=fp)
            print(
                self.__format_tf_df(*self.lex.get_nth_freq_term(500)), file=fp
            )

            print("\n----------------------------", file=fp)
            print("1000th word:", file=fp)
            print(self.table_header, file=fp)
            print(
                self.__format_tf_df(*self.lex.get_nth_freq_term(1000)), file=fp
            )

            print("\n----------------------------", file=fp)
            print("5000th word:", file=fp)
            print(self.table_header, file=fp)
            print(
                self.__format_tf_df(*self.lex.get_nth_freq_term(5000)), file=fp
            )

            print("\n----------------------------", file=fp)
            single_occs: int = self.lex.get_single_occs()
            print(
                "Number of words that occur in exactly one document:", file=fp
            )
            print(
                single_occs,
                f"({round(single_occs / self.lex.get_vocab_size() * 100, 2)}%)",
                file=fp,
            )
