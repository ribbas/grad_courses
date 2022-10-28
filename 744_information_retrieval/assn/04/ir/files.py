import joblib
from pathlib import Path
from typing import Any

from .const import TARGET_FIELD, FEATURE_FIELDS, FIELD_DELIM, LIST_DELIM


class CorpusFile:
    def __init__(self, filename: Path) -> None:

        self.filename: Path = filename

    @staticmethod
    def __map_list(field: str) -> list[str]:

        return field.split(LIST_DELIM)

    def __map_to_fields(self, line: str) -> dict[str, Any]:

        mapped_field: dict[str, Any] = dict(
            zip((TARGET_FIELD, *FEATURE_FIELDS), line.split(FIELD_DELIM))
        )

        # assessment
        mapped_field["assessment"] = int(mapped_field["assessment"])

        # authors
        mapped_field["authors"] = self.__map_list(mapped_field["authors"])

        # journal
        mapped_field["journal"] = self.__map_list(mapped_field["journal"])

        # issn
        mapped_field["issn"] = self.__map_list(mapped_field["issn"])

        # year
        if mapped_field["year"]:
            if not (" " in mapped_field["year"] or "-" in mapped_field["year"]):
                mapped_field["year"] = int(mapped_field["year"])

        # keywords
        mapped_field["keywords"] = self.__map_list(mapped_field["keywords"])

        return mapped_field

    def ingest(self) -> list[dict[str, Any]]:

        docs: list[dict[str, Any]] = []

        with open(self.filename) as fp:
            for line in fp:
                if line:
                    docs.append(self.__map_to_fields(line[:-1]))

        return docs


class IO:
    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(filename, "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}'")

    @staticmethod
    def read_joblib(filename: str) -> Any:

        return joblib.load(f"{filename}.joblib")

    @staticmethod
    def dump_joblib(filename: str, clf: Any) -> None:

        joblib.dump(clf, f"{filename}.joblib")
        print(f"Dumped model to '{filename}.joblib'")
