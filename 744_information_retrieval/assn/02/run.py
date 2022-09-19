from pathlib import Path

from ir.files import IO, Formatter, DataFile
from ir.invertedfile import InvertedFile
from ir.lexer import Lexer
from ir.normalize import Normalizer
from ir.packer import Packer


def process_document(filename: Path) -> None:

    prep = Normalizer()
    lex = Lexer()
    data = DataFile(filename)

    term_doc_tf: list[tuple[str, str, int]] = []
    data.ingest(prep, lex, term_doc_tf)
    term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
    IO.dump(data.tdt_file_name, term_doc_tf_str)
    IO.dump_json(data.df_file_name, lex.get_df())
    IO.dump_json(data.tf_file_name, lex.get_tf())

    contents: str = Formatter.format_stats(lex, data.num_docs)
    IO.dump(data.stats_file_name, contents)

    invf = InvertedFile()
    invf.build_dict(lex.get_df(), lex.get_tf())
    invf.ingest(IO.read(data.tdt_file_name))
    inv_file = invf.get_inverted_file_raw()
    if_data = Packer.encode(inv_file)
    IO.dump_bin(data.inv_file_name, if_data)
    IO.dump_json(data.dict_name, invf.get_dictionary())


if __name__ == "__main__":

    process_document(Path(__file__).parent.parent / "data" / "headlines.txt")
