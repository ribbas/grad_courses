from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn.pipeline import Pipeline
from sklearn.linear_model import SGDClassifier
from sklearn import svm

from sklearn.naive_bayes import MultinomialNB
from sklearn.model_selection import GridSearchCV

from .normalize import Normalizer


class Vectorizer:
    def __init__(self) -> None:

        self.parameters = {
            "cv__tokenizer": [Normalizer()],
            "clf__class_weight": ({1: 2}, {1: 3}, {1: 4}, {1: 15}, {1: 30}),
        }

        self.pipe = Pipeline(
            [
                ("cv", CountVectorizer()),
                ("tfidf", TfidfTransformer()),
                (
                    "clf",
                    SGDClassifier(random_state=0),
                ),
            ]
        )
        self.gs_clf = GridSearchCV(self.pipe, self.parameters, n_jobs=-1)

    def tfidf_fit_transform(self, data: list[str], target: list[int]):

        self.gs_clf.fit(data, target)

    def predict(self, data: list[str]):

        # print(self.pipe["cv"].vocabulary_)

        print(self.gs_clf.best_score_)

        for param_name in sorted(self.parameters.keys()):
            print("%s: %r" % (param_name, self.gs_clf.best_params_[param_name]))

        return self.gs_clf.predict(data)

    # def cross_validate(self):
