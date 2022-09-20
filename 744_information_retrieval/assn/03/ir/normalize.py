import re
from typing import Generator

import nltk

# fmt: off
STOPWORDS: set[str] = {
    # contractions
    "aren't", "ain't", "can't", "could've", "couldn't", "didn't", "doesn't", "don't",
    "hadn't", "hasn't", "haven't", "he'd", "he'll", "he's", "i'd", "i'll",
    "i'm", "i've", "isn't", "it'll", "it'd", "it's", "let's", "mightn't",
    "might've'", "mustn't", "must've'", "shan't", "she'd", "she'll", "she's", "should've",
    "shouldn't", "that'll", "that's", "there's", "they'd", "they'll", "they're", "they've",
    "wasn't", "we'd", "we'll", "we're", "we've", "weren't", "what'll", "what're",
    "what's", "what've", "where's", "who'd", "who'll", "who're", "who's", "who've",
    "won't", "wouldn't", "would've", "y'all", "you'd", "you'll", "you're", "you've",
    # NLTK stopwords
    "a", "all", "am", "an", "and", "any", "are", "as",
    "at", "be", "because", "been", "being", "but", "by", "can",
    "cannot", "could", "did", "do", "does", "doing", "for", "from",
    "had", "has", "have", "having", "he", "her", "here", "hers",
    "herself", "him", "himself", "his", "how", "i", "if", "in",
    "is", "it", "its", "itself", "just", "let", "may", "me", 
    "might", "must", "my", "myself", "need", "no", "nor", "not", 
    "now", "o", "of", "off", "on", "once", "only", "or", 
    "our", "ours", "ourselves", "shall", "she", "should", "so", "some", 
    "such", "than", "that", "the", "their", "theirs", "them", "themselves", 
    "then", "there", "these", "they", "this", "those", "to", "too", 
    "very", "was", "we", "were", "what", "when", "where", "which", 
    "who", "whom", "why", "will", "with", "would", "you", "your", 
    "yours", "yourself", "yourselves",
}
# fmt: on


class Normalizer:
    def __init__(self) -> None:

        self.document: str = ""
        self.tokens: Generator[str, None, None]

        self.ws_re: re.Pattern[str] = re.compile(r"([A-Za-z]+'?[A-Za-z]+)")
        self.snow: nltk.stem.SnowballStemmer = nltk.stem.SnowballStemmer(
            "english"
        )

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

    def __stem(
        self, tokens: Generator[str, None, None]
    ) -> Generator[str, None, None]:

        return (self.snow.stem(token) for token in tokens)

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