from collections import Counter
import json


class Lexer:
    def __init__(self) -> None:

        self.__tf: Counter[str] = Counter()
        self.__df: Counter[str] = Counter()

    def add(self, tokens: list[str]) -> None:

        self.__tf.update(tokens)
        self.__df.update(set(tokens))

    def get_tf(self) -> Counter[str]:

        return self.__tf

    def get_df(self) -> Counter[str]:

        return self.__df

    def save_freq(self, filename: str) -> None:

        with open(f"data/{filename}_tf.json", "w") as fp:
            json.dump(self.__tf, fp)

        with open(f"data/{filename}_df.json", "w") as fp:
            json.dump(self.__df, fp)

    def get_collection_size(self) -> int:

        return self.__tf.total()

    def get_vocab_size(self) -> int:

        return len(self.__tf)

    def print_top_100_tf_df(self) -> None:

        top_100 = self.__tf.most_common(100)
        for i in top_100:
            term, freq = i
            print(term, "|", freq, "|", self.__df[term])

    def get_nth_freq_term(self, n: int) -> str:

        term, freq = self.__tf.most_common(n)[-1]
        return f"{n}th word: {term} | {freq} | {self.__df[term]}"
