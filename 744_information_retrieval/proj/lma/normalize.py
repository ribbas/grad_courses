import re

import nltk
from sklearn.feature_extraction import _stop_words

# fmt: off
STOPWORDS: frozenset[str] = frozenset({
    # contractions
    "aren't", "ain't", "can't", "could've", "couldn't", "didn't", "doesn't",
    "don't", "hadn't", "hasn't", "haven't", "he'd", "he'll", "he's",
    "i'd", "i'll", "i'm", "i've", "isn't", "it'll", "it'd",
    "it's", "let's", "mightn't", "might've'", "mustn't", "must've'", "shan't",
    "she'd", "she'll", "she's", "should've", "shouldn't", "that'll", "that's",
    "there's", "they'd", "they'll", "they're", "they've", "wasn't", "we'd",
    "we'll", "we're", "we've", "weren't", "what'll", "what're", "what's",
    "what've", "where's", "who'd", "who'll", "who're", "who's", "who've",
    "won't", "wouldn't", "would've", "y'all", "you'd", "you'll", "you're",
    "you've",
    # NLTK stopwords
    "a", "all", "am", "an", "and", "any",
    "are", "as", "at", "be", "because", "been", "being",
    "but", "by", "can", "cannot", "could", "did", "do",
    "does", "doing", "for", "from", "had", "has", "have",
    "having", "he", "her", "here", "hers", "herself", "him",
    "himself", "his", "how", "i", "if", "in", "is",
    "it", "its", "itself", "just", "let", "may", "me",
    "might", "must", "my", "myself", "need", "no", "nor",
    "not", "now", "o", "of", "off", "on", "once",
    "only", "or", "our", "ours", "ourselves", "shall", "she",
    "should", "so", "some", "such", "than", "that", "the",
    "their", "theirs", "them", "themselves", "then", "there", "these",
    "they", "this", "those", "to", "too", "very", "was",
    "we", "were", "what", "when", "where", "which", "who",
    "whom", "why", "will", "with", "would", "you", "your",
    "yours", "yourself", "yourselves",
})
# fmt: on


class Normalizer:
    def __init__(
        self, stemmer: str = "snowball", stopwords: str | None = None
    ) -> None:

        self.stemmer: str = stemmer
        self.chosen_stemmer: nltk.stem.PorterStemmer | nltk.stem.SnowballStemmer
        if self.stemmer == "snowball":
            self.chosen_stemmer = nltk.stem.SnowballStemmer("english")
        elif self.stemmer == "porter":
            self.chosen_stemmer = nltk.stem.PorterStemmer()

        self.stopwords: str = stopwords
        self.stopwords_list: frozenset[str]
        if self.stopwords == "custom":
            self.stopwords_list = STOPWORDS
        elif self.stopwords == "sklearn":
            self.stopwords_list = _stop_words.ENGLISH_STOP_WORDS

        self.ws_re: re.Pattern[str] = re.compile(r"([A-Za-z]+'?[A-Za-z]+)")

    def __repr__(self) -> str:

        return f"{self.__class__.__name__}/{self.stemmer}/{self.stopwords}"

    def __to_lower_case(self, document: str) -> str:

        return document.lower()

    def __split_document(self, document: str) -> list[str]:

        return [x.group(0) for x in self.ws_re.finditer(document)]

    def __remove_stopwords(self, tokens: list[str]) -> list[str]:
        return [word for word in tokens if word not in self.stopwords_list]

    def __stem(self, tokens: list[str]) -> list[str]:

        return [self.chosen_stemmer.stem(token) for token in tokens]

    def __call__(self, document: str) -> list[str]:

        # convert the entire document to lower-case
        doc_lc: str = self.__to_lower_case(document)

        # split the document on its whitespace
        tokens: list[str] = self.__split_document(doc_lc)

        # remove contractions and stopwords
        if self.stopwords:
            tokens = self.__remove_stopwords(tokens)

        # stem tokens
        tokens = self.__stem(tokens)

        return tokens
