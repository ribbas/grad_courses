import json
from pathlib import Path
from typing import Any

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

        self.line_num = 0
        self.num_docs = 0

    @staticmethod
    def __dump_json(filename: str, data: Any) -> None:

        with open(f"{filename}.json", "w") as fp:
            json.dump(data, fp)

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}"

    def read_file(self) -> None:

        with open(self.filename) as fp:
            for line in fp:
                match self.line_num % 4:
                    case 0:
                        self.num_docs += 1
                    case 1:
                        self.prep.set_document(line)
                        self.prep.process()
                        self.lex.add(self.prep.get_tokens())
                    case _:
                        pass
                self.line_num += 1

    def print_stats(self, filename: str) -> None:

        print("Processed", self.num_docs, "documents.")
        IO.__dump_json(filename + "_tf", self.lex.get_tf())
        IO.__dump_json(filename + "_df", self.lex.get_df())

        with open(f"{filename}_stats.txt", "w") as fp:

            print("----------------------------", file=fp)
            print(self.num_docs, "documents.", file=fp)

            print("----------------------------", file=fp)
            print("Collections size:", self.lex.get_collection_size(), file=fp)
            print("Vocabulary size:", self.lex.get_vocab_size(), file=fp)
            print("\n----------------------------", file=fp)

            print("Top 100 most frequent words:", file=fp)
            print(IO.table_header, file=fp)
            for term in self.lex.get_top_n_tf_df(100):
                print(IO.__format_tf_df(*term), file=fp)

            print("\n----------------------------", file=fp)
            print("500th word:", file=fp)
            print(IO.table_header, file=fp)
            print(IO.__format_tf_df(*self.lex.get_nth_freq_term(500)), file=fp)

            print("\n----------------------------", file=fp)
            print("1000th word:", file=fp)
            print(IO.table_header, file=fp)
            print(IO.__format_tf_df(*self.lex.get_nth_freq_term(1000)), file=fp)

            print("\n----------------------------", file=fp)
            print("5000th word:", file=fp)
            print(IO.table_header, file=fp)
            print(IO.__format_tf_df(*self.lex.get_nth_freq_term(5000)), file=fp)

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
