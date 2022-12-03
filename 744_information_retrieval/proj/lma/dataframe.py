import pathlib
from typing import Any

import pandas as pd

from .emotions import EMOTION_KEYS

TRANSFORM_KEY_FMT = ("{0}", "u_{0}", "s_{0}")


class DataFrame:
    def __init__(self) -> None:

        self.df: pd.DataFrame

    def read_csv(self, filename: pathlib.Path):

        self.df = pd.read_csv(filename)

    def generate(self, df_dict: list[dict[str, Any]]):

        self.df = pd.DataFrame.from_dict(df_dict)

        self.df.drop(
            self.df[(sum(self.df[k] for k in EMOTION_KEYS)) == 0].index,
            inplace=True,
        )
        self.df.sort_values(by=["title"], inplace=True, ignore_index=True)

    def create_wheel_ratio_columns(self, col: str, transform_key: str):

        self.df[f"{transform_key.format(col)}_ratio"] = self.df.apply(
            lambda row: row[transform_key.format(col)]
            / sum(row[transform_key.format(k)] for k in EMOTION_KEYS),
            axis=1,
        )

    def head(self):

        print(self.df)
        print(self.df.columns)
        gk = self.df.groupby("playlist")
        print(gk.mean())

    def dump(self, filename: pathlib.Path):

        self.df.to_csv(filename, index=False)
