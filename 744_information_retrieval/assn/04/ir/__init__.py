from pathlib import Path

import numpy as np

from .const import FEATURE_FIELDS, TARGET_FIELD, LIST_FEATURE_FIELDS
from .files import CorpusFile, Formatter, IO
from .metrics import Metrics
from .vectorizer import Vectorizer


class InformationRetrieval:
    def __init__(self, train_filename: Path) -> None:

        self.train_corpus: CorpusFile = CorpusFile(train_filename)

        self.vec = Vectorizer()

        self.num_docs: int = 0
        self.model_loaded = False

    def extract_text_features(
        self, categories: tuple[str, ...], corpus: CorpusFile
    ) -> tuple[list[str], np.ndarray]:

        docs = corpus.ingest()
        target: np.ndarray = np.array([i[TARGET_FIELD] for i in docs])
        features: list[str] = []

        for row in docs:
            feature_list = []
            for feature in categories:
                if feature in LIST_FEATURE_FIELDS:
                    feature_list.extend(row[feature])

                else:
                    feature_list.append(row[feature])
            features.append(" ".join(feature_list))

        return features, target

    def extract_train_features(
        self, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        features, target = self.extract_text_features(
            categories, self.train_corpus
        )
        self.vec.set_training_features(features, target)
        print("train targets:", Metrics.describe(target))

    def grid_search(self):
        self.vec.grid_search()
        self.model_loaded = True

    def dump_classifier(self, phase: str):

        IO.dump_joblib(f"tmp/model-{phase}", self.vec.get_classifier())

    def load_classifier(self, phase: str):

        self.vec.load_classifier(IO.read_joblib(f"tmp/model-{phase}"))
        self.model_loaded = True

    def extract_test_features(
        self, test_filename: Path, categories: tuple[str, ...] = FEATURE_FIELDS
    ):

        if self.model_loaded:

            test_corpus = CorpusFile(test_filename)
            features, target = self.extract_text_features(
                categories, test_corpus
            )
            self.vec.set_test_features(features, target)
            print("test targets:", Metrics.describe(target))

        else:
            raise AttributeError("Classifier model not generated yet")

    def score(self) -> None:

        predicted = self.vec.predict()
        print("predicted targets:", Metrics.describe(predicted))
        print(Metrics.classification_report(self.vec.test_target, predicted))
