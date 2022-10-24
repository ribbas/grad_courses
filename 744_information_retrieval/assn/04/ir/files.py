from pathlib import Path
import joblib

from .const import TARGET_FIELD, FEATURE_FIELDS, FIELD_DELIM, LIST_DELIM, JHED
from .lexer import LexerStatistics
from .normalize import Normalizer
from .types import Any, iterable, text_io, generator


class CorpusFile:
    def __init__(self, filename: Path) -> None:

        self.prep = Normalizer()
        self.filename: Path = filename
        self.num_docs: int = 0

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
                    self.num_docs += 1

        return docs


class IO:
    @staticmethod
    def open_file(filename: str) -> text_io:

        return open(f"{filename}.txt")

    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(f"{filename}.txt", "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}.txt'")

    @staticmethod
    def read_joblib(filename: str) -> Any:

        return joblib.load(f"{filename}.joblib")

    @staticmethod
    def dump_joblib(filename: str, clf: Any) -> None:

        joblib.dump(clf, f"{filename}.joblib")
        print(f"Dumped model to '{filename}.joblib'")


class Formatter:

    hr: str = "------------------------------\n"
    table_header: str = f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n{hr}"

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}\n"

    @staticmethod
    def format_stats(lex_stats: LexerStatistics, num_docs: int = 0) -> str:

        contents: str = ""

        return contents

    @staticmethod
    def format_term_doc_tf(term_doc_tf: list[tuple[str, int, int]]) -> str:

        contents: str = ""
        for line in term_doc_tf:
            contents += " ".join(str(i) for i in line) + "\n"

        return contents

    @staticmethod
    def format_rankings(
        all_rankings: dict[int, list[tuple[int, float]]]
    ) -> str:

        contents: str = ""
        for query_id, rankings in all_rankings.items():
            contents += (
                "\n".join(
                    f"{query_id} Q0 {doc_id} {rank + 1} {score:.6f} {JHED}"
                    for rank, (doc_id, score) in enumerate(rankings)
                )
                + "\n"
            )

        return contents
