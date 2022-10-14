from collections import Counter
from statistics import mean, median
from pprint import pprint
from typing import Any


class Stats:
    def __init__(self, filename: str) -> None:

        self.filename: str = filename
        self.elapsed_time: float = 0
        self.rankings: list[dict[str, int]] = []
        self.queries: list[list[str]] = []

    def read_ranking_file(self) -> None:

        line_num: int = 1
        line: str = ""
        with open(self.filename) as fp:
            line_data = []
            for line in fp:
                if line_num % 2:
                    line_data = line[:-1].split(" ")
                else:
                    self.queries.append(line_data)
                    self.rankings.append(
                        {
                            "ndocs": int(line),
                            "nqueries": len(line_data),
                        }
                    )
                line_num += 1

        self.elapsed_time = float(line[:-2])

    def count_q(self) -> list[tuple[str, int]]:

        return Counter(
            item for sublist in self.queries for item in sublist
        ).most_common(10)

    def summary_stats(self, field: str) -> dict[str, float]:

        agg = [i[field] for i in self.rankings]
        return {
            "mean": mean(agg),
            "median": median(agg),
            "min": min(agg),
            "max": max(agg),
        }

    def generate(self) -> dict[str, Any]:

        self.read_ranking_file()
        summary: dict[str, Any] = {}
        summary["time"] = self.elapsed_time
        summary["queries"] = self.count_q()
        summary["ndocs"] = self.summary_stats("ndocs")
        summary["nqueries"] = self.summary_stats("nqueries")

        return summary


pprint(Stats("sahmed80-a-dump.txt").generate())
pprint(Stats("sahmed80-b-dump.txt").generate())
