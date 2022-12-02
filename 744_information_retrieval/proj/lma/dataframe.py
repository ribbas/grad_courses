import pathlib
from typing import Any

import pandas as pd


class DataFrame:
    def __init__(self) -> None:

        self.df: pd.DataFrame

    def read_csv(self, filename: pathlib.Path):

        self.df = pd.read_csv(filename)

    def generate(self, df_dict: list[dict[str, Any]]):

        self.df = pd.DataFrame.from_dict(df_dict)
        self.df.sort_values(by=["title"], inplace=True, ignore_index=True)

    def head(self):

        print(self.df)
        print(self.df.columns)
        print(self.df[["n_words", "u_n_words", "s_n_words"]].describe())

    def dump(self, filename: pathlib.Path):

        self.df.to_csv(filename, index=False)
