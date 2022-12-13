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

pd.set_option("display.float_format", lambda x: "%.3f" % x)


class DataFrame:
    def __init__(self) -> None:

        self.__df: pd.DataFrame

    def read_csv(self, filename: pathlib.Path):

        self.__df = pd.read_csv(filename)

    def get_df(self):

        return self.__df

    def get_dist(self, cols):

        return self.__df[cols].describe().loc[["mean"]].transpose().to_latex()

    def get_top_emotions(self, title: str):

        return self.__df[self.__df["title"] == title][
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

                    wheel = emotions.get_emotion_intensities(t_lyrics)
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

    def generate(self, df_dict: list[dict[str, Any]]):

        self.__df = pd.DataFrame.from_dict(df_dict)

        self.__df.drop(
            self.__df[(sum(self.__df[k] for k in EMOTION_KEYS)) == 0].index,
            inplace=True,
        )
        self.__df.sort_values(by=["title"], inplace=True, ignore_index=True)

    def drop_duplicate_artists(self):

        self.__df.drop_duplicates(
            subset=["title", "playlist"], keep="first", inplace=True
        )

    def drop_duplicate_titles(self):

        self.__df.drop_duplicates(
            subset=["title", "artist"], keep="first", inplace=True
        )

    def drop_custom_titles(self):

        self.__df.drop(
            self.__df[self.__df["title"] == "Pumped Up Kicks"].index,
            inplace=True,
        )

    def dump(self, filename: pathlib.Path):

        self.__df.to_csv(filename, index=False)
        print(f"Saved data to {filename}")
