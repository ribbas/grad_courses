from string import punctuation
from collections import Counter
import json
from typing import Any

CONTRACTIONS: dict[str, list[str]] = {
    "aren't": ["are", "not"],
    "can't": ["cannot"],
    "couldn't": ["could", "not"],
    "didn't": ["did", "not"],
    "doesn't": ["does", "not"],
    "don't": ["do", "not"],
    "hadn't": ["had", "not"],
    "hasn't": ["has", "not"],
    "haven't": ["have", "not"],
    "he'd": ["he", "had"],
    "he'll": ["he", "will"],
    "he's": ["he", "is"],
    "I'd": ["I", "had"],
    "I'll": ["I", "will"],
    "I'm": ["I", "am"],
    "I've": ["I", "have"],
    "isn't": ["is", "not"],
    "let's": ["let", "us"],
    "mightn't": ["might", "not"],
    "mustn't": ["must", "not"],
    "shan't": ["shall", "not"],
    "she'd": ["she", "had"],
    "she'll": ["she", "will"],
    "she's": ["she", "is"],
    "shouldn't": ["should", "not"],
    "that's": ["that", "is"],
    "there's": ["there", "is"],
    "they'd": ["they", "had"],
    "they'll": ["they", "will"],
    "they're": ["they", "are"],
    "they've": ["they", "have"],
    "we'd": ["we", "had"],
    "we're": ["we", "are"],
    "we've": ["we", "have"],
    "weren't": ["were", "not"],
    "what'll": ["what", "will"],
    "what're": ["what", "are"],
    "what's": ["what", "is"],
    "what've": ["what", "have"],
    "where's": ["where", "is"],
    "who'd": ["who", "had"],
    "who'll": ["who", "will"],
    "who're": ["who", "are"],
    "who's": ["who", "is"],
    "who've": ["who", "have"],
    "won't": ["will", "not"],
    "wouldn't": ["would", "not"],
    "you'd": ["you", "had"],
    "you'll": ["you", "will"],
    "you're": ["you", "are"],
    "you've": ["you", "have"],
}


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


class Preprocessor:
    def __init__(self) -> None:

        self.document: str = ""
        self.__tokens: list[str] = []

    def set_document(self, document: str) -> None:

        self.document = document[:-1]

    def process(self) -> None:

        self.__to_lower_case()
        self.__split_document()
        for ix, token in enumerate(self.__tokens):
            temp = self.__translate_contractions(token)
            temp = self.__remove_punc(temp)
            self.__tokens[ix] = temp

        self.__tokens = [item for sublist in self.__tokens for item in sublist if item]

    def __translate_contractions(self, token: str) -> list[str]:

        if token in CONTRACTIONS:
            return CONTRACTIONS[token]

        return [token]

    def __split_document(self) -> None:

        self.__tokens = self.document.split(" ")

    def __remove_punc(self, tokens: list[str]) -> list[str]:

        for p in punctuation:
            for ix, token in enumerate(tokens):
                tokens[ix] = token.replace(p, "")

        return tokens

    def __to_lower_case(self) -> None:

        self.document = self.document.lower()

    def get_tokens(self) -> list[str]:

        return self.__tokens


def save_freq(filename: str, data: Any) -> None:

    with open(filename, "w") as fp:
        json.dump(data, fp)


def gen_freq(filename: str) -> tuple[Counter[str], Counter[str]]:

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

    print("Processed", num_docs, "documents.")
    return lex.get_tf(), lex.get_df()


# def gen_freq(filename:str)->None:


if __name__ == "__main__":

    tf, df = gen_freq("yelp.txt")
    save_freq("yelp_tf.json", tf)
    save_freq("yelp_df.json", df)
