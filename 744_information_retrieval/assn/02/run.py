from pathlib import Path
from typing import Any, Generator

from src.files import IO, Formatter, DataFile
from src.normalize import Normalizer
from src.lexer import Lexer
from src.invertedfile import InvertedFile
from src.packer import Packer


def process_document(filename: Path) -> None:

    prep = Normalizer()
    lex = Lexer()
    data = DataFile(filename)

    term_doc_tf: list[tuple[str, str, int]] = []
    num_docs = data.ingest(prep, lex, term_doc_tf)
    term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
    IO.dump(data.tdt_file_name, term_doc_tf_str)
    IO.dump_json(data.df_file_name, lex.get_df())
    IO.dump_json(data.tf_file_name, lex.get_tf())

    contents: str = Formatter.format_stats(lex, num_docs)
    IO.dump(data.stats_file_name, contents)

    invf = InvertedFile()
    invf.vocabulary(lex.get_df(), lex.get_tf())
    invf.ingest(IO.read(data.tdt_file_name))
    inv_file = invf.get_inverted_file_raw()
    if_data = Packer.encode(inv_file)
    IO.dump_bin(data.inv_file_name, if_data)
    IO.dump_json(data.dict_name, invf.get_dictionary())


def read_inverted_file(
    filename: Path, tokens: Generator[str, None, None], keys: tuple[str, ...]
):

    data = DataFile(filename)

    invf = InvertedFile()
    inv_file = IO.read_bin(data.inv_file_name)
    dict_ = IO.read_json(data.dict_name)

    invf.set_inverted_file(inv_file)
    invf.set_dictionary(dict_)

    for token in tokens:
        metadata = invf.lookup(token)
        yield tuple(metadata.get(key, -1) for key in keys)


def normalize_test_terms(terms: tuple[str, ...]) -> Generator[str, None, None]:

    prep = Normalizer()
    prep.set_document(" ".join(terms))
    prep.process()
    return prep.get_tokens()


if __name__ == "__main__":

    data_dir: Path = Path(__file__).parent.parent / "data"

    process_document(data_dir / "headlines.txt")

    tokens1 = normalize_test_terms(
        ("Heidelberg", "cesium", "Trondheim", "crustacean", "crustaceans")
    )
    results = read_inverted_file(
        data_dir / "headlines.txt",
        tokens1,
        ("term", "offset", "width", "postings", "postings_len"),
    )
    print(list(results))

    tokens2 = normalize_test_terms(("Hopkins", "Stanford", "Brown", "college"))
    results = read_inverted_file(
        data_dir / "headlines.txt", tokens2, ("term", "postings_len")
    )
    print(list(results))

    tokens3 = normalize_test_terms(("Elon", "Musks"))
    results = read_inverted_file(
        data_dir / "headlines.txt",
        tokens3,
        ("postings",),
    )
    elon_postings, musk_postings = results
    elon_postings, musk_postings = set(elon_postings[0]), set(musk_postings[0])
    elon_musk_postings = elon_postings & musk_postings
    print(len(elon_musk_postings))
    print(elon_musk_postings)
