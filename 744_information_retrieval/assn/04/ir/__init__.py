from pathlib import Path

import numpy as np
import scipy
from sklearn.metrics import accuracy_score, classification_report

from .const import FEATURE_FIELDS, TARGET_FIELD
from .files import CorpusFile, Formatter, IO
from .types import Any
from .vectorizer import Vectorizer


class InformationRetrieval:
    def __init__(self, train_filename: Path) -> None:

        self.train_corpus: CorpusFile = CorpusFile(train_filename)

        self.vec = Vectorizer()

        self.num_docs: int = 0
        self.loaded_clf = False

    def describe(self, data):

        unique, counts = np.unique(data, return_counts=True)
        print(dict(zip(unique, counts)))
        print(scipy.stats.describe(data))

    def extract_text_features(
        self, categories: tuple[str, ...], corpus: CorpusFile
    ) -> tuple[Any, list[str]]:

        docs = corpus.ingest()
        target = np.array([i[TARGET_FIELD] for i in docs])
        features: list[str] = []

        for row in docs:
            feature_list = []
            for feature in categories:
                feature_list.append(row[feature])
            features.append(" ".join(feature_list))

        return target, features

    def extract_train_features(
        self, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        target, features = self.extract_text_features(
            categories, self.train_corpus
        )
        self.vec.set_training_features(features, target)
        self.describe(target)

    def grid_search(self):
        self.vec.grid_search()
        self.loaded_clf = True

    def dump_classifier(self):

        IO.dump_joblib("tmp/clf", self.vec.get_classifier())

    def load_classifier(self):

        self.vec.load_classifier(IO.read_joblib("tmp/clf"))
        self.loaded_clf = True

    def extract_test_features(
        self, test_filename: Path, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        if self.loaded_clf:

            test_corpus = CorpusFile(test_filename)
            target, features = self.extract_text_features(
                categories, test_corpus
            )
            self.vec.set_test_features(features, target)

            predicted = self.vec.predict()
            print("accuracy %s" % accuracy_score(predicted, target))
            print(classification_report(predicted, target))

            self.describe(predicted)

        else:
            raise AttributeError("Corpus frequencies not generated yet")
