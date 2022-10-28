from pathlib import Path

import numpy as np

from .const import TARGET_FIELD, LIST_FEATURE_FIELDS, JHED
from .files import CorpusFile, IO
from .metrics import Metrics
from .model import Model


class InformationRetrieval:
    def __init__(self, train_filename: Path) -> None:

        self.train_corpus: CorpusFile = CorpusFile(train_filename)

        self.clf: Model = Model()

        self.predicted: np.ndarray
        self.model_loaded = False

    def use_xgb(self) -> None:

        self.clf.use_xgb_flag = True

    def __extract_text_features(
        self, categories: tuple[str, ...], corpus: CorpusFile
    ) -> tuple[list[str], np.ndarray]:

        docs = corpus.ingest()
        target = np.array([i[TARGET_FIELD] for i in docs])
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

    def extract_train_features(self, categories: tuple[str, ...]) -> None:

        features, target = self.__extract_text_features(
            categories, self.train_corpus
        )
        self.clf.set_training_features(features, target)
        print("train targets:", Metrics.distribution(target))

    def extract_test_features(
        self, test_filename: Path, categories: tuple[str, ...]
    ) -> None:

        if self.model_loaded:

            test_corpus = CorpusFile(test_filename)
            features, target = self.__extract_text_features(
                categories, test_corpus
            )
            self.clf.set_test_features(features, target)
            print("test targets:", Metrics.distribution(target))

        else:
            raise AttributeError("Classifier model not generated yet")

    def grid_search(self) -> None:

        self.clf.grid_search()
        self.model_loaded = True

    def dump_classifier(self, phase: int) -> None:

        IO.dump_joblib(f"models/model-{phase}", self.clf.get_classifier())

    def load_classifier(self, phase: int) -> None:

        self.clf.load_classifier(IO.read_joblib(f"models/model-{phase}"))
        self.model_loaded = True

    def predict(self) -> None:

        self.predicted = self.clf.predict()

    def score(self) -> None:

        print("predicted targets:", Metrics.distribution(self.predicted))
        print(
            Metrics.classification_report(self.clf.test_target, self.predicted)
        )

    def dump_cv_results(self) -> None:

        cv_results = self.clf.get_cv_results()
        content_str = ""
        for param, score in zip(
            cv_results["params"], cv_results["mean_test_score"]
        ):
            content_str += f"{param['clf__class_weight'][1]},{param['cv__tokenizer']},{score}\n"

        print(content_str)
        IO.dump("outputs/cv", content_str)

    def dump_predict_vals(self, test_filename: Path) -> None:

        test_corpus = CorpusFile(test_filename)
        doc_ids, _ = self.__extract_text_features(("docid",), test_corpus)
        output_pairs = "\n".join(
            f"{doc_id}\t{p}" for doc_id, p in zip(doc_ids, self.predicted)
        )
        IO.dump(f"outputs/{JHED}", output_pairs)
