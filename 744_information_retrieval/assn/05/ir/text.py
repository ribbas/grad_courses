from typing import Iterator

import nltk

# fmt: off
CONTRACTIONS = {
    "aren't": "are not", "ain't": "is not", "can't": "can not",
    "could've": "could have", "couldn't": "could not", "didn't": "did not",
    "doesn't": "does not", "don't": "do not", "hadn't": "had not",
    "hasn't": "has not", "haven't": "have not", "he'd": "he would",
    "he'll": "he will", "he's": "he is", "i'd": "i would",
    "i'll": "i will", "i'm": "i am", "i've": "i have", "isn't": "is not",
    "it'll": "it will", "it'd": "it would", "it's": "it is", "let's": "let us",
    "mightn't": "might not", "might've'": "might have", "mustn't": "must not",
    "must've'": "must have", "shan't": "sha not", "she'd": "she would",
    "she'll": "she will", "she's": "she is", "should've": "should have",
    "shouldn't": "should not", "that'll": "that will", "that's": "that is",
    "there's": "there is", "they'd": "they would", "they'll": "they will",
    "they're": "they are", "they've": "they have", "wasn't": "was not",
    "we'd": "we would", "we'll": "we will", "we're": "we are",
    "we've": "we have", "weren't": "were not", "what'll": "what will",
    "what're": "what are", "what's": "what is", "what've": "what have",
    "where's": "where is", "who'd": "who would", "who'll": "who will",
    "who're": "who are", "who's": "who is", "who've": "who have",
    "won't": "wo not", "wouldn't": "would not", "would've": "would have",
    "y'all": "you all", "you'd": "you would", "you'll": "you will",
    "you're": "you are", "you've": "you have",
}
# fmt: on


class Normalizer:
    def __init__(self) -> None:

        self.stem = nltk.stem.SnowballStemmer("english")
        self.punc_table: dict[int, int | None] = str.maketrans(
            "", "", """!"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"""
        )

    def __to_lower_case(self, document: str) -> str:

        return document.lower()

    def __split_document(self, document: str) -> list[str]:

        return document.split(" ")

    def __expand_contractions(self, tokens: list[str]) -> list[str]:

        temp_tokens: list[str] = []
        for token in tokens:
            if token in CONTRACTIONS:
                temp_tokens.extend(CONTRACTIONS[token].split(" "))
            else:
                temp_tokens.append(token)

        return temp_tokens

    def __remove_puncs(self, tokens: list[str]) -> list[str]:

        return [i.translate(self.punc_table) for i in tokens]

    def __stem(self, tokens: list[str]) -> list[str]:

        return [self.stem.stem(token) for token in tokens]

    def __call__(self, document: str) -> list[str]:

        # convert the entire document to lower-case
        doc_lc: str = self.__to_lower_case(document)

        # split the document on its whitespace
        tokens: list[str] = self.__split_document(doc_lc)

        # expand contraction words
        tokens = self.__expand_contractions(tokens)

        # remove punctuations
        tokens = self.__remove_puncs(tokens)

        # stem tokens
        tokens = self.__stem(tokens)

        return tokens


class Shingle:
    def __init__(self, ngram) -> None:
        self.ngram = ngram

    def __ngrams(self, input_list) -> Iterator[tuple[str, ...]]:
        return zip(*(input_list[i:] for i in range(self.ngram)))

    def __call__(self, doc: list[str]) -> set[int]:

        shingles: set[int] = set()
        for shingle in self.__ngrams(doc):

            hashed_shingle = hash(" ".join(shingle))
            shingles.add(hashed_shingle)

        return shingles
