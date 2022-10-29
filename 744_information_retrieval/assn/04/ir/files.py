import joblib
from pathlib import Path
from typing import Any

TARGET_FIELD = "assessment"

FEATURE_FIELDS = (
    "docid",
    "title",
    "authors",
    "journal",
    "issn",
    "year",
    "language",
    "abstract",
    "keywords",
)

LIST_FEATURE_FIELDS = (
    "authors",
    "journal",
    "issn",
    "keywords",
)


class CorpusFile:

    field_delim = "\t"
    list_delim = ";"

    @staticmethod
    def __map_list(field: str) -> list[str]:

        return field.split(CorpusFile.list_delim)

    @staticmethod
    def __map_to_fields(line: str) -> dict[str, Any]:

        mapped_field: dict[str, Any] = dict(
            zip(
                (TARGET_FIELD, *FEATURE_FIELDS),
                line.split(CorpusFile.field_delim),
            )
        )

        for field, value in mapped_field.items():
            if field == TARGET_FIELD:
                mapped_field[field] = int(value)
            elif field in LIST_FEATURE_FIELDS:
                mapped_field[field] = CorpusFile.__map_list(value)

        return mapped_field

    @staticmethod
    def ingest(filename: Path) -> list[dict[str, Any]]:

        docs: list[dict[str, Any]] = []

        with open(filename) as fp:
            for line in fp:
                if line:
                    docs.append(CorpusFile.__map_to_fields(line[:-1]))

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
