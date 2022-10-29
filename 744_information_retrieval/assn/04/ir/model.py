from typing import Any

import numpy as np
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline
from xgboost import XGBClassifier
from sklearn.preprocessing import LabelEncoder

from .normalize import Normalizer


class Model:
    def __init__(self) -> None:

        self.clf: GridSearchCV
        self.train_features: list[str] = []
        self.train_target: np.ndarray
        self.test_features: list[str] = []
        self.test_target: np.ndarray

        self.use_xgb_flag = False

    def set_train_features(self, data: list[str], target: np.ndarray) -> None:

        self.train_features = data
        self.train_target = target

    def set_test_features(self, data: list[str], target: np.ndarray) -> None:

        self.test_features = data
        self.test_target = target

    def load_classifier(self, clf: GridSearchCV) -> None:

        self.clf = clf

    def get_classifier(self) -> GridSearchCV:

        return self.clf

    def grid_search(self) -> None:

        params = {}
        clf = None

        if not self.use_xgb_flag:
            params = {
                "cv__tokenizer": [
                    None,
                    Normalizer(stemmer="snowball", stopwords=None),
                    Normalizer(stemmer="porter", stopwords=None),
                    Normalizer(stemmer="snowball", stopwords="custom"),
                    Normalizer(stemmer="porter", stopwords="custom"),
                    Normalizer(stemmer="snowball", stopwords="sklearn"),
                    Normalizer(stemmer="porter", stopwords="sklearn"),
                ],
                "clf__class_weight": [{1: i} for i in range(3, 31)],
            }
            clf = SGDClassifier(loss="hinge", random_state=0)

        else:
            params = {
                "cv__tokenizer": [
                    None,
                    Normalizer(stemmer="snowball", stopwords=None),
                    Normalizer(stemmer="porter", stopwords=None),
                    Normalizer(stemmer="snowball", stopwords="custom"),
                    Normalizer(stemmer="porter", stopwords="custom"),
                    Normalizer(stemmer="snowball", stopwords="sklearn"),
                    Normalizer(stemmer="porter", stopwords="sklearn"),
                ],
                "clf__scale_pos_weight": range(3, 31),
                "clf__max_depth": range(3, 10),
                "clf__min_child_weight": range(1, 10),
            }
            clf = XGBClassifier(
                objective="binary:logistic",
                random_state=0,
                learning_rate=0.2,
                n_estimators=100,
            )

        pipe = Pipeline(
            [
                ("cv", CountVectorizer(stop_words=None)),
                ("tfidf", TfidfTransformer()),
                ("clf", clf),
            ]
        )
        self.load_classifier(
            GridSearchCV(
                pipe,
                params,
                n_jobs=-1,
                scoring="f1",
                verbose=10,
            )
        )
        self.__train_classifier()

        for param_name in params.keys():
            print(f"{param_name}: {self.clf.best_params_[param_name]}")

    def __train_classifier(self) -> None:

        if self.use_xgb_flag:
            le = LabelEncoder()
            self.train_target = le.fit_transform(self.train_target)

        self.clf.fit(self.train_features, self.train_target)

    def get_cv_results(self) -> dict[str, Any]:

        return self.clf.cv_results_

    def predict(self) -> np.ndarray:

        return self.clf.predict(self.test_features)
