from pathlib import Path

from src.files import IO, Formatter, DataFile
from src.normalize import Normalizer
from src.lexer import Lexer
from src.invertedfile import InvertedFile
from src.packer import Packer

if __name__ == "__main__":

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

    def read_inverted_file(filename: Path) -> None:

        data = DataFile(filename)

        invf = InvertedFile()
        inv_file = IO.read_bin(data.inv_file_name)
        dict_ = IO.read_json(data.dict_name)

        invf.set_inverted_file(inv_file)
        invf.set_dictionary(dict_)
        print(invf.lookup("fudg"))

    data_dir: Path = Path(__file__).parent.parent / "data"

    process_document(data_dir / "test.txt")
    read_inverted_file(data_dir / "test.txt")
    process_document(data_dir / "yelp.txt")
    read_inverted_file(data_dir / "yelp.txt")
    process_document(data_dir / "headlines.txt")
    read_inverted_file(data_dir / "headlines.txt")

"""
1. Print out the document frequency and postings list for terms: "Heidelberg", "cesium", "Trondheim”, "crustacean".
2. Give document frequency, but do not print postings for the words: "Hopkins", "Stanford", "Brown", and "college”
(these postings lists are longer -- I just want to see the counts).
3. Print out the docids for documents that have both "Elon" and "Musk" in the text. You can do this by finding the
postings list for each term, and then intersecting the two lists. For this test you do not need to use or supply frequency
information. Please print the docids in increasing order.
"""
