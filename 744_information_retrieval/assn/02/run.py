from pathlib import Path

from src.io import IO
from src.normalize import Normalizer
from src.lexer import Lexer


if __name__ == "__main__":

    def process_document(filename: Path) -> None:

        prep = Normalizer()
        lex = Lexer()
        io = IO(filename, prep, lex)

        io.read_file()
        io.print_stats(f"stats/{filename.stem}")

    data_dir: Path = Path(__file__).parent.parent / "data"

    process_document(data_dir / "yelp.txt")
    process_document(data_dir / "headlines.txt")
