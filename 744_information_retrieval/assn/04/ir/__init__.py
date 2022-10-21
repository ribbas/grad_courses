from pathlib import Path
from pprint import pprint

import numpy as np
import scipy
from sklearn.metrics import accuracy_score, confusion_matrix


from .const import FEATURE_FIELDS, TARGET_FIELD
from .files import CorpusFile, Formatter, IO
from .vectorizer import Vectorizer
from .types import Any


class InformationRetrieval:
    def __init__(self, train_filename: Path, test_filename: Path) -> None:

        self.train_corpus: CorpusFile = CorpusFile(train_filename)
        self.test_corpus: CorpusFile = CorpusFile(test_filename)
        self.vec = Vectorizer()

        self.num_docs: int = 0

    def describe(self, data):

        unique, counts = np.unique(data, return_counts=True)
        print(dict(zip(unique, counts)))
        print(scipy.stats.describe(data))

    def extract_features(
        self, categories: tuple[str, ...], corpus: CorpusFile
    ) -> tuple[Any, dict[str, list[int | str]]]:

        docs = corpus.ingest()
        target = np.array([i[TARGET_FIELD] for i in docs])
        features: dict[str, list[int | str]] = {}

        for feature in categories:
            feature_list = []
            for row in docs:
                feature_list.append(row[feature])
            features[feature] = feature_list

        return target, features

    def extract_train_features(
        self, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        target, features = self.extract_features(categories, self.train_corpus)
        self.describe(target)

        self.vec.tfidf_fit_transform(features["title"], target)

    def extract_test_features(
        self, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        target, features = self.extract_features(categories, self.test_corpus)
        predicted = self.vec.predict(features["title"])
        print("accuracy %s" % accuracy_score(predicted, target))

        print(self.describe(predicted))
        print(np.mean(predicted == target))
