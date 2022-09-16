import re
from typing import Iterator, Generator

import nltk

CONTRACTIONS: dict[str, str] = {
    "aren't": "are not",
    "ain't": "is not",
    "can't": "cannot",
    "couldn't": "could not",
    "didn't": "did not",
    "doesn't": "does not",
    "don't": "do not",
    "hadn't": "had not",
    "hasn't": "has not",
    "haven't": "have not",
    "he'd": "he had",
    "he'll": "he will",
    "he's": "he is",
    "i'd": "i had",
    "i'll": "i will",
    "i'm": "i am",
    "i've": "i have",
    "isn't": "is not",
    "it's": "it is",
    "let's": "let us",
    "mightn't": "might not",
    "mustn't": "must not",
    "shan't": "shall not",
    "she'd": "she had",
    "she'll": "she will",
    "she's": "she is",
    "shouldn't": "should not",
    "that's": "that is",
    "there's": "there is",
    "they'd": "they had",
    "they'll": "they will",
    "they're": "they are",
    "they've": "they have",
    "wasn't": "was not",
    "we'd": "we had",
    "we're": "we are",
    "we've": "we have",
    "weren't": "were not",
    "what'll": "what will",
    "what're": "what are",
    "what's": "what is",
    "what've": "what have",
    "where's": "where is",
    "who'd": "who had",
    "who'll": "who will",
    "who're": "who are",
    "who's": "who is",
    "who've": "who have",
    "won't": "will not",
    "wouldn't": "would not",
    "you'd": "you had",
    "you'll": "you will",
    "you're": "you are",
    "you've": "you have",
}


class Normalizer:
    def __init__(self) -> None:

        self.document: str = ""
        self.__tokens: Generator[str, None, None]

        self.ws_re: re.Pattern[str] = re.compile(r"[A-Za-z']+")
        self.punc_re: re.Pattern[str] = re.compile(
            "['!\"#$%&()*+,-./:;<=>?@[\\]^_`{|}~]"
        )
        self.porter: nltk.stem.PorterStemmer = nltk.stem.PorterStemmer()

    def set_document(self, document: str) -> None:

        self.document = document[:-1]

    def __basic_stem(self, tokens: Iterator[str]) -> Generator[str, None, None]:

        return (self.porter.stem(token) for token in tokens)

    def __translate_contractions(self, token: str) -> str:

        return CONTRACTIONS.get(token, token)

    def __split_document(self, document: str) -> Generator[str, None, None]:

        return (x.group(0) for x in self.ws_re.finditer(document))

    def __remove_punc(self, tokens: str) -> list[str]:

        return self.punc_re.split(tokens)

    def __to_lower_case(self, document: str) -> str:

        return document.lower()

    def tokens(self) -> Generator[str, None, None]:

        return self.__tokens

    def process(self) -> None:

        self.document = self.__to_lower_case(self.document)
        self.__tokens = self.__split_document(self.document)

        temp_str: str = ""
        for token in self.__tokens:
            temp_str += self.__translate_contractions(token) + " "

        no_puncs: list[str] = self.__remove_punc(temp_str)
        no_empty: Iterator[str] = filter(
            None, self.__split_document(" ".join(no_puncs))
        )
        self.__tokens = self.__basic_stem(no_empty)
