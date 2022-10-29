from pathlib import Path

import numpy as np

from .files import CorpusFile, IO, TARGET_FIELD, LIST_FEATURE_FIELDS
from .metrics import Metrics
from .model import Model

JHED = "sahmed80"


class InformationRetrieval:
    def __init__(self) -> None:

        self.clf: Model = Model()

        self.predicted: np.ndarray
        self.model_loaded = False

    def use_xgb(self) -> None:

        self.clf.use_xgb_flag = True

    def __extract_text_features(
        self, filename: Path, categories: tuple[str, ...]
    ) -> tuple[list[str], np.ndarray]:

        docs = CorpusFile().ingest(filename)
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

    def extract_train_features(
        self, train_filename: Path, categories: tuple[str, ...]
    ) -> None:

        features, target = self.__extract_text_features(
            train_filename, categories
        )
        self.clf.set_train_features(features, target)
        print("distribution of train targets:", Metrics.distribution(target))

    def extract_test_features(
        self, test_filename: Path, categories: tuple[str, ...]
    ) -> None:

        features, target = self.__extract_text_features(
            test_filename, categories
        )
        self.clf.set_test_features(features, target)
        print("distribution of test targets:", Metrics.distribution(target))

    def train(self) -> None:

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

        print(
            "distribution of predicted targets:",
            Metrics.distribution(self.predicted),
        )
        print(
            Metrics.classification_report(self.clf.test_target, self.predicted)
        )

    def dump_cv_results(self) -> None:

        cv_results = self.clf.get_cv_results()
        content_str = "weight,tokenization,score\n"
        for param, score in zip(
            cv_results["params"], cv_results["mean_test_score"]
        ):
            content_str += f"{param['clf__class_weight'][1]},{param['cv__tokenizer']},{score}\n"

        IO.dump("outputs/cross_validations.csv", content_str)

    def dump_predict_vals(self, test_filename: Path) -> None:

        doc_ids, _ = self.__extract_text_features(test_filename, ("docid",))
        output_pairs = "\n".join(
            f"{doc_id}\t{p}" for doc_id, p in zip(doc_ids, self.predicted)
        )
        IO.dump(f"outputs/{JHED}.txt", output_pairs)
