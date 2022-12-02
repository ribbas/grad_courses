from typing import Any

import pandas as pd


class DataFrame:
    def __init__(self, df_dict: list[dict[str, Any]]) -> None:

        self.df = pd.DataFrame.from_dict(df_dict)

    def head(self):

        print(self.df)

    def dump(self, filename: str):

        self.df.to_csv(filename)
