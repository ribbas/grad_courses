from typing import Any

import numpy as np
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline

from .text import Normalizer


class Model:
    def __init__(self) -> None:

        self.clf: GridSearchCV
        self.train_features: list[str] = []
        self.train_target: list[int]
        self.test_features: list[str] = []
        self.test_target: list[int]

    def set_train_features(self, data: list[str], target: list[int]) -> None:

        self.train_features = data
        self.train_target = target

    def set_test_features(self, data: list[str], target: list[int]) -> None:

        self.test_features = data
        self.test_target = target

    def load_classifier(self, clf: GridSearchCV) -> None:

        self.clf = clf

    def get_classifier(self) -> GridSearchCV:

        return self.clf

    def grid_search(self) -> None:

        params = {}

        params = {
            "cv__tokenizer": [None, Normalizer()],
            # "clf__class_weight": [{1: i} for i in range(3, 31)],
        }
        clf = SGDClassifier(loss="hinge", random_state=0)

        pipe = Pipeline(
            [
                (
                    "cv",
                    CountVectorizer(stop_words=None, tokenizer=Normalizer()),
                ),
                # ("tfidf", TfidfTransformer()),
                ("clf", clf),
            ]
        )
        self.load_classifier(pipe)
        self.__train_classifier()

        # for param_name in params.keys():
        #     print(f"{param_name}: {self.clf.best_params_[param_name]}")

    def __train_classifier(self) -> None:

        self.clf.fit(self.train_features, self.train_target)
        predicted = self.clf.predict(self.test_features)
        print(predicted, self.test_target)
        print(np.mean(predicted == self.test_target))

    def get_cv_results(self) -> dict[str, Any]:

        return self.clf.cv_results_

    def predict(self) -> np.ndarray:

        return self.clf.predict(self.test_features)
