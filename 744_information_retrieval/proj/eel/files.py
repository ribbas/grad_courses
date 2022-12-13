import json
import pathlib
import pickle
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
    def read_pickle(filename: pathlib.Path) -> Any:

        with open(f"{filename}.pickle", "rb") as fp:
            return pickle.load(fp)

    @staticmethod
    def dump_pickle(filename: pathlib.Path, data: Any) -> None:

        with open(f"{filename}.pickle", "wb") as fp:
            pickle.dump(data, fp, protocol=pickle.HIGHEST_PROTOCOL)
        print(f"Dumped checkpoint to '{filename}.pickle'")
