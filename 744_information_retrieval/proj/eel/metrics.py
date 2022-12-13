from pprint import pprint

import numpy as np
import pandas as pd

from .emotions import EMOTION_KEYS

POSITIVE_VALENCE = {"anticipation", "joy", "surprise", "trust", "q1", "q4"}
NEGATIVE_VALENCE = {"anger", "disgust", "fear", "sadness", "q2", "q3"}

FUNCTIONS = {
    "25% percentile": (np.nanpercentile, 25),
    "50% percentile": (np.nanpercentile, 50),
    "75% percentile": (np.nanpercentile, 75),
    "mean": (np.nanmean,),
}


class Metrics:
    def __init__(self, nunique_all: int) -> None:

        self.nunique_all = nunique_all
        self.best_func_name = ""
        self.best_func_acc = 0.0

    def set_df(self, df: pd.DataFrame):
        self.df = df

    def sentiment_ratio(self, group, col_name):

        sentiment = self.df[self.df[group] == col_name]["sentiment"]
        if col_name in POSITIVE_VALENCE:
            return sentiment.gt(0).sum() / sentiment.count()
        else:
            return sentiment.lt(0).sum() / sentiment.count()

    def n_unique_titles(self, col_name):

        return self.df[self.df[col_name].notna()]["title"].nunique()

    @staticmethod
    def accuracy(ratios: dict[str, float]):

        return np.mean(list(ratios.values()))

    def emotion_sentiment_ratios(self):

        emotion_ratios = {}
        for emo in EMOTION_KEYS:
            emotion_ratios[emo] = self.sentiment_ratio("emotion_playlist", emo)

        return emotion_ratios

    def quadrant_sentiment_ratios(self):

        quad_ratios = {}
        for quad in {"q1", "q2", "q3", "q4"}:
            quad_ratios[quad] = self.sentiment_ratio("quadrant_playlist", quad)

        return quad_ratios

    @staticmethod
    def get_function():

        for func, args in FUNCTIONS.items():
            yield func, args

    def emotion_playlist_summary(self, func_name):

        ratios = self.emotion_sentiment_ratios()
        accuracy = self.accuracy(ratios)
        nunique = self.n_unique_titles("emotion_playlist")

        print("--------------------------------")
        print(f"Function: {func_name}")
        pprint(ratios)
        print(f"nunique_titles after:", nunique)
        print(f"Loss:", (self.nunique_all - nunique) / self.nunique_all)
        print(f"Accuracy:", accuracy)
        print("--------------------------------")

        if accuracy > self.best_func_acc:
            self.best_func_name = func_name
            self.best_func_acc = accuracy

    def quadrant_playlist_summary(self, func_name):

        ratios = self.quadrant_sentiment_ratios()
        accuracy = self.accuracy(ratios)
        nunique = self.n_unique_titles("quadrant_playlist")

        print("--------------------------------")
        print(f"Function: {func_name}")
        pprint(ratios)
        print(f"nunique_titles after:", nunique)
        print(f"Loss:", (self.nunique_all - nunique) / self.nunique_all)
        print(f"Accuracy:", accuracy)
        print("--------------------------------")

        if accuracy > self.best_func_acc:
            self.best_func_name = func_name
            self.best_func_acc = accuracy

    def best_metric(self):

        return (
            self.best_func_name,
            self.best_func_acc,
            FUNCTIONS[self.best_func_name],
        )
