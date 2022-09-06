import json
from typing import Any

from .stats import Lexer

TABLE_HEADER: str = (
    f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n----------------------------"
)


def dump_json(filename: str, data: Any) -> None:

    with open(f"data/{filename}.json", "w") as fp:
        json.dump(data, fp)


def format_tf_df(term: str, tf: int, df: int) -> str:

    return f"{term:<12} | {tf:<6} | {df:<6}"


def print_stats(filename: str, num_docs: int, lex: Lexer) -> None:

    print("Processed", num_docs, "documents.")
    dump_json(filename + "_tf", lex.get_tf())
    dump_json(filename + "_df", lex.get_df())

    with open(f"data/{filename}_stats.txt", "w") as fp:

        print("----------------------------", file=fp)
        print(num_docs, "documents.", file=fp)

        print("----------------------------", file=fp)
        print("Collections size:", lex.get_collection_size(), file=fp)
        print("Vocabulary size:", lex.get_vocab_size(), file=fp)
        print("\n----------------------------", file=fp)

        print("Top 100 most frequent words:", file=fp)
        print(TABLE_HEADER, file=fp)
        for term in lex.get_top_n_tf_df(100):
            print(format_tf_df(*term), file=fp)

        print("\n----------------------------", file=fp)
        print("500th word:", file=fp)
        print(TABLE_HEADER, file=fp)
        print(format_tf_df(*lex.get_nth_freq_term(500)), file=fp)

        print("\n----------------------------", file=fp)
        print("1000th word:", file=fp)
        print(TABLE_HEADER, file=fp)
        print(format_tf_df(*lex.get_nth_freq_term(1000)), file=fp)

        print("\n----------------------------", file=fp)
        print("5000th word:", file=fp)
        print(TABLE_HEADER, file=fp)
        print(format_tf_df(*lex.get_nth_freq_term(5000)), file=fp)

        print("\n----------------------------", file=fp)
        single_occs: int = lex.get_single_occs()
        print("Number of words that occur in exactly one document:", file=fp)
        print(
            single_occs,
            f"({round(single_occs / lex.get_vocab_size() * 100, 2)}%)",
            file=fp,
        )
