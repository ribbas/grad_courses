from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.linear_model import SGDClassifier
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline

from .normalize import Normalizer


class Vectorizer:
    def __init__(self) -> None:

        self.clf: SGDClassifier
        self.train_features = []
        self.train_target = []
        self.test_features = []
        self.test_target = []

    def grid_search(self):

        parameters = {
            "cv__tokenizer": [Normalizer()],
        }

        pipe = Pipeline(
            [
                ("cv", CountVectorizer()),
                ("tfidf", TfidfTransformer()),
                (
                    "clf",
                    SGDClassifier(random_state=0, class_weight={1: 4}),
                ),
            ]
        )
        self.load_classifier(GridSearchCV(pipe, parameters, n_jobs=-1))
        self.train_classifier()

        # for param_name in sorted(parameters.keys()):
        #     print("%s: %r" % (param_name, self.clf.best_params_[param_name]))

    def set_training_features(self, data: list[str], target: list[int]):

        self.train_features = data
        self.train_target = target

    def set_test_features(self, data: list[str], target: list[int]):

        self.test_features = data
        self.test_target = target

    def load_classifier(self, clf) -> None:

        self.clf = clf

    def get_classifier(self):

        return self.clf

    def train_classifier(self):

        self.clf.fit(self.train_features, self.train_target)

    def predict(self):

        return self.clf.predict(self.test_features)
