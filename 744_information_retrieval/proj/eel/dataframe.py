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
# TRANSFORM_KEY_FMT = {
#     "def": "{0}",
#     "set": "u_{0}",
#     "sw": "s_{0}",
# }


class DataFrame:
    def __init__(self) -> None:

        self.df: pd.DataFrame

    def read_csv(self, filename: pathlib.Path):

        self.df = pd.read_csv(filename)

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

    @staticmethod
    def create_wheel_playlist(df_data):

        medians = {
            col: np.nanmedian([i[f"{col}_ratio"] for i in df_data])
            for col in EMOTION_KEYS
        }

        new_data = []
        for line in df_data:
            for key in EMOTION_KEYS:
                if line[f"{key}_ratio"] >= medians[key]:
                    _line = line.copy()
                    _line["wheel_playlist"] = key
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
