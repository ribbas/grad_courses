import pathlib
from typing import Any

import numpy as np
import pandas as pd

from .emotions import Emotions, EMOTION_KEYS, VAD_KEYS, SENTIMENT_KEYS
from .playlist import Playlist
from .text import Normalizer

TRANSFORM_KEY_FMT = {
    "{0}",
    "u_{0}",
    "s_{0}",
}
QUAD = ("q1", "q2", "q3", "q4")


class DataFrame:
    def __init__(self) -> None:

        self.df: pd.DataFrame

    def read_csv(self, filename: pathlib.Path):

        self.df = pd.read_csv(filename)

    def get_dist(self, cols):

        # return (
        #     self.df[cols].describe().loc[["mean", "50%"]].transpose().to_latex()
        # )
        return self.df[cols].nunique()

    def get_top_emotions(self, title: str):

        return self.df[self.df["title"] == title][
            ["wheel_playlist"] + [f"{i}_ratio" for i in EMOTION_KEYS]
        ]

    @staticmethod
    def transpose(playlist: Playlist, norm: Normalizer, emotions: Emotions):

        df = []
        for track in playlist.tracks:

            if track.lyrics:

                line = {}

                line["title"] = track.title
                line["playlist"] = playlist.name

                lyrics = norm(track.lyrics)

                for t_key, t_lyrics in zip(
                    TRANSFORM_KEY_FMT,
                    (lyrics, set(lyrics), norm.remove_stopwords(set(lyrics))),
                ):

                    line[t_key.format("n_words")] = len(t_lyrics)
                    vad = emotions.get_vad(t_lyrics)
                    for key in VAD_KEYS:
                        line[t_key.format(key)] = vad[key]

                    sentiment = emotions.get_sentiment(t_lyrics)
                    for key in SENTIMENT_KEYS:
                        line[t_key.format(key)] = sentiment[key]

                    wheel = emotions.get_wheel_category(t_lyrics)
                    for key in EMOTION_KEYS:
                        line[t_key.format(key)] = wheel[key]

                for key in EMOTION_KEYS:
                    den = sum(line[k] for k in EMOTION_KEYS)
                    if den:
                        line[f"{key}_ratio"] = line[key] / den
                    else:
                        line[f"{key}_ratio"] = np.nan

                line["sentiment"] = (
                    (line["positive"] - line["negative"]) / line["n_words"] * 4
                )

                for artist in track.artist:
                    _line = line.copy()
                    _line["artist"] = artist
                    df.append(_line)

        return df

    def score_metrics(self):

        wdiffs = {}
        for n in ("anger", "disgust", "fear", "sadness"):
            wdiffs[n] = (
                self.df[self.df["wheel_playlist"] == n]["sentiment"].lt(0).sum()
                / self.df[self.df["wheel_playlist"] == n]["sentiment"].count()
            )

        for p in ("anticipation", "joy", "surprise", "trust"):
            wdiffs[p] = (
                self.df[self.df["wheel_playlist"] == p]["sentiment"].gt(0).sum()
                / self.df[self.df["wheel_playlist"] == p]["sentiment"].count()
            )

        qdiffs = {}
        for n in ("q2", "q3"):
            qdiffs[n] = (
                self.df[self.df["quadrant_playlist"] == n]["sentiment"]
                .lt(0)
                .sum()
                / self.df[self.df["quadrant_playlist"] == n][
                    "sentiment"
                ].count()
            )

        for p in ("q1", "q4"):
            qdiffs[p] = (
                self.df[self.df["quadrant_playlist"] == p]["sentiment"]
                .gt(0)
                .sum()
                / self.df[self.df["quadrant_playlist"] == p][
                    "sentiment"
                ].count()
            )

        print(wdiffs)
        print(qdiffs)
        print(
            self.df[self.df["quadrant_playlist"].notna()]["title"].nunique(),
            sum(v for v in qdiffs.values()) / 4,
        )
        print(
            self.df[self.df["wheel_playlist"].notna()]["title"].nunique(),
            sum(v for v in wdiffs.values()) / 8,
        )

    @staticmethod
    def create_wheel_playlist(df_data):

        for i in df_data:
            i["q1"] = i["joy_ratio"] + i["surprise_ratio"]
            i["q2"] = i["anger_ratio"] + i["disgust_ratio"]
            i["q3"] = i["sadness_ratio"] + i["fear_ratio"]
            i["q4"] = i["trust_ratio"] + i["anticipation_ratio"]

        qthresh = {
            col: np.nanpercentile([i[col] for i in df_data], 75) for col in QUAD
        }
        thresh = {
            col: np.nanpercentile([i[f"{col}_ratio"] for i in df_data], 75)
            for col in EMOTION_KEYS
        }
        print(thresh)

        new_data = []
        for line in df_data:
            for key in EMOTION_KEYS:
                if line[f"{key}_ratio"] >= thresh[key]:
                    _line = line.copy()
                    _line["wheel_playlist"] = key
                    new_data.append(_line)

            for key in QUAD:
                if line[key] >= qthresh[key]:
                    _line = line.copy()
                    _line["quadrant_playlist"] = key
                    new_data.append(_line)

        return new_data

    def generate(self, df_dict: list[dict[str, Any]]):

        self.df = pd.DataFrame.from_dict(df_dict)

        self.df.drop(
            self.df[(sum(self.df[k] for k in EMOTION_KEYS)) == 0].index,
            inplace=True,
        )
        self.df.sort_values(by=["title"], inplace=True, ignore_index=True)

    def drop_duplicate_artists(self):

        self.df.drop_duplicates(
            subset=["title", "playlist"], keep="first", inplace=True
        )

    def drop_duplicate_titles(self):

        self.df.drop_duplicates(
            subset=["title", "artist"], keep="first", inplace=True
        )

    def dump(self, filename: pathlib.Path):

        self.df.to_csv(filename, index=False)
