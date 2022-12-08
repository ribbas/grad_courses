import joblib
import json
import pathlib
from typing import Any


class IO:
    @staticmethod
    def dump(filename: pathlib.Path, data: str) -> None:

        with open(filename, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}'")

    @staticmethod
    def read(filename: pathlib.Path) -> str:

        with open(filename) as fp:
            return fp.read()

    @staticmethod
    def read_json(filename: pathlib.Path) -> Any:

        with open(f"{filename}") as fp:
            return json.loads(fp.read())

    @staticmethod
    def dump_json(filename: pathlib.Path, data: Any) -> None:

        with open(f"{filename}", "w") as fp:
            json.dump(data, fp)
        print(f"Dumped json to '{filename}'")

    @staticmethod
    def read_joblib(filename: str) -> Any:

        return joblib.load(f"{filename}.joblib")

    @staticmethod
    def dump_joblib(filename: str, clf: Any) -> None:

        joblib.dump(clf, f"{filename}.joblib")
        print(f"Dumped model to '{filename}.joblib'")
