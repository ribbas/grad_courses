import re
from typing import Iterator, Generator

import nltk

STOPWORDS: set[str] = {
    "a",
    "ain",
    "all",
    "am",
    "an",
    "and",
    "any",
    "are",
    "aren",
    "as",
    "at",
    "be",
    "because",
    "been",
    "being",
    "but",
    "by",
    "can",
    "cannot",
    "could",
    "couldn",
    "d",
    "did",
    "didn",
    "do",
    "does",
    "doesn",
    "doing",
    "don",
    "few",
    "for",
    "from",
    "had",
    "hadn",
    "has",
    "hasn",
    "have",
    "haven",
    "having",
    "he",
    "her",
    "here",
    "hers",
    "herself",
    "him",
    "himself",
    "his",
    "how",
    "i",
    "if",
    "in",
    "is",
    "isn",
    "it",
    "its",
    "itself",
    "just",
    "let",
    "ll",
    "m",
    "may",
    "me",
    "might",
    "mightn",
    "more",
    "most",
    "must",
    "mustn",
    "my",
    "myself",
    "need",
    "no",
    "nor",
    "not",
    "now",
    "o",
    "of",
    "off",
    "on",
    "once",
    "only",
    "or",
    "our",
    "ours",
    "ourselves",
    "re",
    "s",
    "shall",
    "shan",
    "she",
    "should",
    "shouldn",
    "so",
    "some",
    "such",
    "t",
    "than",
    "that",
    "the",
    "their",
    "theirs",
    "them",
    "themselves",
    "then",
    "there",
    "these",
    "they",
    "this",
    "those",
    "to",
    "too",
    "ve",
    "very",
    "was",
    "wasn",
    "we",
    "were",
    "weren",
    "what",
    "when",
    "where",
    "which",
    "who",
    "whom",
    "why",
    "will",
    "with",
    "won",
    "would",
    "wouldn",
    "you",
    "your",
    "yours",
    "yourself",
    "yourselves",
}


class Normalizer:
    def __init__(self) -> None:

        self.document: str = ""
        self.tokens: Generator[str, None, None]

        self.ws_re: re.Pattern[str] = re.compile(r"[A-Za-z]+")
        self.porter: nltk.stem.PorterStemmer = nltk.stem.PorterStemmer()

    def set_document(self, document: str) -> None:

        self.document = document[:-1]

    def __to_lower_case(self, document: str) -> str:

        return document.lower()

    def __split_document(self, document: str) -> Generator[str, None, None]:

        return (x.group(0) for x in self.ws_re.finditer(document))

    def __remove_stopwords(
        self, tokens: Generator[str, None, None]
    ) -> Generator[str, None, None]:
        return (word for word in tokens if word not in STOPWORDS)

    def __stem(self, tokens: Iterator[str]) -> Generator[str, None, None]:

        return (self.porter.stem(token) for token in tokens)

    def get_tokens(self) -> Generator[str, None, None]:

        return self.tokens

    def process(self) -> None:

        # convert the entire document to lower-case
        doc_lc: str = self.__to_lower_case(self.document)

        # split the document on its whitespace
        tokens: Generator[str, None, None] = self.__split_document(doc_lc)

        # remove contractions and stopwords
        no_sw: Generator[str, None, None] = self.__remove_stopwords(tokens)

        # stem tokens
        self.tokens = self.__stem(no_sw)
