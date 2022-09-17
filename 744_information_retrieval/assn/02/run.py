from pathlib import Path

from src.io import IO
from src.normalize import Normalizer
from src.lexer import Lexer
from src.invertedfile import InvertedFile

if __name__ == "__main__":

    def process_document(filename: Path) -> None:

        prep = Normalizer()
        lex = Lexer()
        io = IO()

        io.set_preprocessor(prep)
        io.set_lexer(lex)

        io.ingest_data_file(filename)
        io.dump_term_doc_tf(f"tmp/{filename.stem}")
        io.dump_stats(f"stats/{filename.stem}")

        invf = InvertedFile()
        invf.vocabulary(lex.get_df(), lex.get_tf())
        invf.ingest(io.read_term_doc_tf_file(f"tmp/{filename.stem}"))
        inv_file = invf.get_inverted_file_raw()
        invf.set_byte_fmt(inv_file)
        data = invf.encode("i" * len(inv_file), inv_file)
        io.dump_bin(f"bin/{filename.stem}.if", data)
        io.dump_json(f"bin/{filename.stem}.dict", invf.get_dictionary())

    def read_inverted_file(filename: Path) -> None:

        io = IO()

        invf = InvertedFile()
        inv_file = io.read_bin(f"bin/{filename.stem}.if")
        dict_ = io.read_json(f"bin/{filename.stem}.dict")

        invf.set_inverted_file(inv_file)
        invf.set_dictionary(dict_)
        print(invf.lookup("fudg"))

    data_dir: Path = Path(__file__).parent.parent / "data"

    # process_document(data_dir / "test.txt")
    read_inverted_file(data_dir / "test.txt")
    # process_document(data_dir / "yelp.txt")
    # process_document(data_dir / "headlines.txt")
