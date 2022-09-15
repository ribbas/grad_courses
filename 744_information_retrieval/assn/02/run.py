from pathlib import Path

from src.io import IO
from src.normalize import Normalizer
from src.lexer import Lexer


if __name__ == "__main__":

    def process_document(filename: Path) -> None:

        prep = Normalizer()
        lex = Lexer()
        io = IO()

        line_num = 0
        num_docs = 0

        with open(filename) as fp:
            for line in fp:
                match line_num % 4:
                    case 0:
                        num_docs += 1
                    case 1:
                        prep.set_document(line)
                        prep.process()
                        lex.add(prep.get_tokens())
                    case _:
                        pass
                line_num += 1

        io.print_stats(f"stats/{filename.stem}", num_docs, lex)

    data_dir: Path = Path(__file__).parent.parent / "data"

    process_document(data_dir / "yelp.txt")
    process_document(data_dir / "headlines.txt")
