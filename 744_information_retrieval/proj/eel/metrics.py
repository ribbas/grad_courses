import numpy as np

from .emotions import EMOTION_KEYS

POSITIVE_VALENCE = {"anticipation", "joy", "surprise", "trust", "q1", "q4"}
NEGATIVE_VALENCE = {"anger", "disgust", "fear", "sadness", "q2", "q3"}

FUNCTIONS = {
    "mean": (np.nanmean,),
    "25": (np.nanquantile, 0.25),
    "50": (np.nanquantile, 0.50),
    "75": (np.nanquantile, 0.75),
}


class Metrics:
    @staticmethod
    def sentiment_ratio(df, group, col_name):

        sentiment = df[df[group] == col_name]["sentiment"]
        if col_name in POSITIVE_VALENCE:
            return sentiment.gt(0).sum() / sentiment.count()
        else:
            return sentiment.lt(0).sum() / sentiment.count()

    @staticmethod
    def n_unique_titles(df, col_name):

        return df[df[col_name].notna()]["title"].nunique()

    @staticmethod
    def accuracy(ratios: dict[str, float]):

        return np.mean(list(ratios.values()))

    @staticmethod
    def score_metrics(df):

        # wheel_ratios = {}
        # for emo in EMOTION_KEYS:
        #     wheel_ratios[emo] = Metrics.sentiment_ratio(
        #         df, "wheel_playlist", emo
        #     )

        quad_ratios = {}
        for quad in {"q1", "q2", "q3", "q4"}:
            quad_ratios[quad] = Metrics.sentiment_ratio(
                df, "quadrant_playlist", quad
            )

        # print(wheel_ratios)
        print(quad_ratios)
        # print(
        #     Metrics.n_unique_titles(df, "wheel_playlist"),
        #     Metrics.accuracy(wheel_ratios),
        # )
        print(
            Metrics.n_unique_titles(df, "quadrant_playlist"),
            Metrics.accuracy(quad_ratios),
        )

    @staticmethod
    def get_function():

        for func, args in FUNCTIONS.items():
            yield func, args
