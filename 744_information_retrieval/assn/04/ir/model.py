import numpy as np
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline

from .normalize import Normalizer, STOPWORDS


class Model:
    def __init__(self) -> None:

        self.clf: GridSearchCV
        self.train_features: list[str] = []
        self.train_target: np.ndarray
        self.test_features: list[str] = []
        self.test_target: np.ndarray

    def grid_search(self) -> None:

        params = {
            "cv__tokenizer": [None, Normalizer(), Normalizer(use_porter=True)],
            "cv__stop_words": [None, "english", STOPWORDS],
            "clf__class_weight": [{1: i} for i in range(3, 31)],
        }

        pipe = Pipeline(
            [
                ("cv", CountVectorizer()),
                ("tfidf", TfidfTransformer()),
                (
                    "clf",
                    SGDClassifier(loss="hinge", random_state=0),
                ),
            ]
        )
        self.load_classifier(
            GridSearchCV(
                pipe,
                params,
                n_jobs=-1,
                scoring=("f1", "recall", "precision"),
                refit="precision",
                verbose=10,
            )
        )
        self.train_classifier()

        for param_name in params.keys():
            print(f"{param_name}: {self.clf.best_params_[param_name]}")

    def set_training_features(
        self, data: list[str], target: np.ndarray
    ) -> None:

        self.train_features = data
        self.train_target = target

    def set_test_features(self, data: list[str], target: np.ndarray) -> None:

        self.test_features = data
        self.test_target = target

    def load_classifier(self, clf: GridSearchCV) -> None:

        self.clf = clf

    def get_classifier(self) -> GridSearchCV:

        return self.clf

    def train_classifier(self) -> None:

        self.clf.fit(self.train_features, self.train_target)

    def predict(self) -> np.ndarray:

        return self.clf.predict(self.test_features)
