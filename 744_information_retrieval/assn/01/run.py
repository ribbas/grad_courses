from src.io import print_stats
from src.normalize import Preprocessor
from src.stats import Lexer


def process_document(filename: str) -> None:

    prep = Preprocessor()
    lex = Lexer()

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

    print_stats(filename[:-4], num_docs, lex)


if __name__ == "__main__":

    process_document("yelp.txt")
    process_document("headlines.txt")
