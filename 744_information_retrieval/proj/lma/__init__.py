import pathlib

from .dataframe import DataFrame, TRANSFORM_KEY_FMT
from .emotions import Emotions, EMOTION_KEYS, VAD_KEYS, SENTIMENT_KEYS
from .files import IO
from .playlist import Playlist
from .playlistservice import PlaylistService
from .plot import Scatter, Scatter3D, BoxPlot
from .text import Normalizer

import numpy as np


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
        emolex_dir: pathlib.Path,
        norm_emolex_dir: pathlib.Path,
    ) -> None:

        self.playlists = PlaylistService(playlist_dir, lyrics_dir, log_dir)
        self.emotions = Emotions(emolex_dir, norm_emolex_dir)
        self.norm = Normalizer()
        self.data = []

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.add_playlist(Playlist(filename.stem, file_data))

    def add_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.add_lyrics(playlist)

    def load_datasets(self):

        self.emotions.load_all_datasets()

    def clean_datasets(self):

        self.emotions.normalize_datasets()

    def generate_data(self, playlist_name: str):

        if playlist_name == "all":
            for playlist in self.playlists:
                self.playlists.get_lyrics(playlist)
                df = DataFrame.transpose(playlist, self.norm, self.emotions)
                self.data.extend(df)

        else:
            playlist = self.playlists[playlist_name]
            self.playlists.get_lyrics(playlist)
            df = DataFrame.transpose(playlist, self.norm, self.emotions)
            self.data.extend(df)

        self.data = DataFrame.create_wheel_playlist(self.data)

    def read_csv(self, gen_data: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)

    def generate_plots(self, gen_data: pathlib.Path, plot_dir: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        data.drop_duplicate_artists()

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes("playlist", f"{key}", data.df)
            bp.save_fig(plot_dir / f"{key}.png")

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes("playlist", f"s_{key}", data.df)
            bp.save_fig(plot_dir / f"s_{key}.png")

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes("playlist", f"{key}_ratio", data.df, showfliers=False)
            bp.save_fig(plot_dir / f"{key}_ratio.png")

        bp = BoxPlot()
        bp.set_axes("playlist", "sentiment", data.df)
        bp.save_fig(plot_dir / "sentiment.png")

        data.drop_duplicate_titles()

        bp = BoxPlot()
        bp.set_axes("wheel_playlist", "sentiment", data.df, showfliers=False)
        bp.save_fig(plot_dir / "wheel_playlist.png")

        sc = Scatter()
        sc.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["playlist"],
            data.df,
        )
        sc.save_fig(plot_dir / "va.png")

        sc.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["playlist"],
            data.df,
            set_limits=False,
        )
        sc.save_fig(plot_dir / "va_zoom.png")

        sc.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["wheel_playlist"],
            data.df,
            set_limits=False,
        )
        sc.save_fig(plot_dir / "va_zoom_wheel.png")

        sc3d = Scatter3D()
        sc3d.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["dominance"],
            data.df["playlist"],
        )
        sc3d.save_fig(plot_dir / "vad.png")

    def dump(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.generate(self.data)
        df.head()
        df.dump(gen_data)
