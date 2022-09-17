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
        invf.vocabulary(lex.get_tf(), lex.get_df())
        invf.ingest(io.read_term_doc_tf_file(f"tmp/{filename.stem}"))
        inv_file = invf.get_inverted_file()
        invf.set_byte_fmt(inv_file)
        data = invf.encode("i" * len(inv_file), inv_file)
        print(data)
        io.dump_bin(f"bin/{filename.stem}.if", data)

    def read_inverted_file(filename: Path) -> None:

        io = IO()

        data = io.read_bin(f"bin/{filename.stem}.if")
        invf = InvertedFile()
        print(invf.decode("i" * (len(data) // 4), data)[22:])

    data_dir: Path = Path(__file__).parent.parent / "data"

    process_document(data_dir / "test.txt")
    read_inverted_file(data_dir / "test.txt")
    # process_document(data_dir / "yelp.txt")
    # process_document(data_dir / "headlines.txt")
