from pathlib import Path

from src.io import IO
from src.normalize import Normalizer
from src.lexer import Lexer
from src.invertedfile import InvertedFile


if __name__ == "__main__":

    def process_document(filename: Path) -> None:

        prep = Normalizer()
        lex = Lexer()
        io = IO(filename, prep, lex)

        io.ingest_data_file()
        io.dump_term_doc_tf(f"tmp/{filename.stem}")
        io.print_stats(f"stats/{filename.stem}")

        # inv_if = InvertedFile(
        #     io.read_term_doc_tf_file(f"tmp/{filename.stem}"), lex.vocabulary()
        # )
        # inv_if.ingest()

    data_dir: Path = Path(__file__).parent.parent / "data"

    # process_document(data_dir / "test.txt")
    process_document(data_dir / "yelp.txt")
    # process_document(data_dir / "headlines.txt")
