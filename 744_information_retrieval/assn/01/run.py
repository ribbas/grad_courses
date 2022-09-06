from src.normalize import Preprocessor
from src.stats import Lexer


def gen_freq(filename: str) -> None:

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
                    try:
                        prep.set_document(line)
                        prep.process()
                        lex.add(prep.get_tokens())
                    except Exception as e:
                        print(num_docs, e, line)
                        exit()
                case _:
                    pass
            line_num += 1

    print("Processed", num_docs, "documents.")
    lex.save_freq(filename[:-4])
    print("col size", lex.get_collection_size())
    print("voc size", lex.get_vocab_size())
    print("most common")
    lex.print_top_100_tf_df()
    print(lex.get_nth_freq_term(500))
    print(lex.get_nth_freq_term(1000))
    print(lex.get_nth_freq_term(5000))


if __name__ == "__main__":

    gen_freq("yelp.txt")
    gen_freq("headlines.txt")
