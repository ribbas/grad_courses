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
    def emotion_sentiment_ratios(df):

        emotion_ratios = {}
        for emo in EMOTION_KEYS:
            emotion_ratios[emo] = Metrics.sentiment_ratio(
                df, "emotion_playlist", emo
            )

        return emotion_ratios

    @staticmethod
    def quad_sentiment_ratios(df):

        quad_ratios = {}
        for quad in {"q1", "q2", "q3", "q4"}:
            quad_ratios[quad] = Metrics.sentiment_ratio(
                df, "quadrant_playlist", quad
            )

        return quad_ratios

    @staticmethod
    def get_function():

        for func, args in FUNCTIONS.items():
            yield func, args
