from collections import Counter
import re
from typing import Iterator, Generator

import nltk

CONTRACTIONS: dict[str, str] = {
    "aren't": "are not",
    "ain't": "is not",
    "can't": "cannot",
    "could've": "could have",
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
    "it'll": "it will",
    "it'd": "it would",
    "it's": "it is",
    "let's": "let us",
    "mightn't": "might not",
    "might've'": "might have",
    "mustn't": "must not",
    "must've'": "must have",
    "shan't": "shall not",
    "she'd": "she had",
    "she'll": "she will",
    "she's": "she is",
    "should've": "should have",
    "shouldn't": "should not",
    "that'll": "that will",
    "that's": "that is",
    "there's": "there is",
    "they'd": "they had",
    "they'll": "they will",
    "they're": "they are",
    "they've": "they have",
    "wasn't": "was not",
    "we'd": "we had",
    "we'll": "we will",
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
    "would've": "would have",
    "you'd": "you had",
    "you'll": "you will",
    "you're": "you are",
    "you've": "you have",
}


class Normalizer:
    def __init__(self) -> None:

        self.document: str = ""
        self.tokens: Generator[str, None, None]

        self.ws_re: re.Pattern[str] = re.compile(r"([A-Za-z]+'?[A-Za-z]+)")
        self.porter: nltk.stem.SnowballStemmer = nltk.stem.SnowballStemmer(
            "english"
        )
        self.stopwords_dict = Counter(nltk.corpus.stopwords.words("english"))

    def set_document(self, document: str) -> None:

        self.document = document[:-1]

    def __basic_stem(self, tokens: Iterator[str]) -> Generator[str, None, None]:

        return (self.porter.stem(token) for token in tokens)

    def __translate_contractions(self, token: str) -> str:

        return CONTRACTIONS.get(token, token)

    def __split_document(self, document: str) -> Generator[str, None, None]:

        return (x.group(0) for x in self.ws_re.finditer(document))

    def __to_lower_case(self, document: str) -> str:

        return document.lower()

    def __remove_stopwords(self, tokens: list[str]) -> str:
        return " ".join(
            word for word in tokens if word not in self.stopwords_dict
        )

    def get_tokens(self) -> Generator[str, None, None]:

        return self.tokens

    def process(self) -> None:

        self.document = self.__to_lower_case(self.document)
        self.tokens = self.__split_document(self.document)

        no_contr: list[str] = []
        for token in self.tokens:
            no_contr.append(self.__translate_contractions(token))

        no_sw: str = self.__remove_stopwords(no_contr)
        no_empty: Iterator[str] = filter(None, self.__split_document(no_sw))
        self.tokens = self.__basic_stem(no_empty)
