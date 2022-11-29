import json
import pathlib
from typing import Any


class IO:
    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(filename, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}'")

    @staticmethod
    def read_json(filename: pathlib.Path) -> Any:

        with open(f"{filename}") as fp:
            return json.loads(fp.read())

    @staticmethod
    def dump_json(filename: pathlib.Path, data: Any) -> None:

        with open(f"{filename}", "w") as fp:
            json.dump(data, fp)
        print(f"Dumped json to '{filename}'")
