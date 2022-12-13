import pathlib
from pprint import pprint

from .autoplaylist import AutoPlaylist
from .dataframe import DataFrame
from .emotions import Emotions, EmotionLexicon, EMOTION_KEYS
from .files import IO
from .metrics import Metrics, FUNCTIONS
from .playlist import Playlist
from .playlistmanager import PlaylistManager
from .plot import PlotFactory
from .text import Normalizer


class EmotionExtractionFromLyrics:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
        norm_emolex_dir: pathlib.Path,
    ) -> None:

        self.log_dir = log_dir
        self.loaded_checkpoint = False
        self.playlists = PlaylistManager(
            playlist_dir=playlist_dir, lyrics_dir=lyrics_dir, log_dir=log_dir
        )
        self.emotions = Emotions(emolex_dir=norm_emolex_dir)
        self.data = []

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.append(Playlist(filename.stem, file_data))

    def add_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.add_lyrics(playlist)

    def load_datasets(self):

        self.emotions.load_all_datasets()

    def clean_datasets(
        self, emolex_dir: pathlib.Path, norm_emolex_dir: pathlib.Path
    ):

        dc = EmotionLexicon(emolex_dir)
        dc.normalize_datasets(norm_emolex_dir)

    def save_checkpoint(self, bin_dir: pathlib.Path):

        IO.dump_pickle(bin_dir / "checkpoint", self.data)
        print("Dumped checkpoint")

    def load_checkpoint(self, bin_dir: pathlib.Path):

        self.loaded_checkpoint = True
        self.data = IO.read_pickle(bin_dir / "checkpoint")
        print("Loaded checkpoint.")

    def create_df(self, playlist_name: str):

        if not self.loaded_checkpoint:
            norm = Normalizer()
            if playlist_name == "all":
                for playlist in self.playlists:
                    print(f"Processing '{playlist.name}'")
                    self.playlists.get_lyrics(playlist)
                    df = DataFrame.transpose(playlist, norm, self.emotions)
                    self.data.extend(df)

            else:
                playlist = self.playlists[playlist_name]
                self.playlists.get_lyrics(playlist)
                df = DataFrame.transpose(playlist, norm, self.emotions)
                self.data.extend(df)

        else:
            print("Data already loaded from checkpoint")

    def create_emotion_playlist(self):
        return AutoPlaylist.create_emotion_playlist(
            self.data, *FUNCTIONS["75% percentile"]
        )

    def create_quadrant_playlist(self):
        return AutoPlaylist.create_quadrant_playlist(
            self.data, *FUNCTIONS["75% percentile"]
        )

    def compute_metrics(self):

        ds = DataFrame()
        nunique_all = len(set(i["title"] for i in self.data))
        print("nunique titles before:", nunique_all)

        mt = Metrics(nunique_all)

        for func_name, args in mt.get_function():

            data = AutoPlaylist.create_emotion_playlist(self.data, *args)
            ds.generate(data)
            mt.set_df(ds.get_df())
            mt.emotion_playlist_summary(func_name)

        print(mt.best_metric())

        for func_name, args in mt.get_function():

            data = AutoPlaylist.create_quadrant_playlist(self.data, *args)
            ds.generate(data)
            mt.set_df(ds.get_df())
            mt.quadrant_playlist_summary(func_name)

        print(mt.best_metric())

    def read_csv(self, gen_data: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        # print(data.get_top_emotions("Pumped Up Kicks"))
        # print(data.get_dist(i for i in EMOTION_KEYS))
        # print(data.get_dist(f"u_{i}" for i in EMOTION_KEYS))
        # print(data.get_dist(f"s_{i}" for i in EMOTION_KEYS))
        # print(data.get_dist(f"{i}_ratio" for i in EMOTION_KEYS))
        # print(data.get_dist(["title"]))
        # print(data.get_dist(["title"]))

    def generate_exploratory_plots(self, plot_dir: pathlib.Path):

        ds = DataFrame()
        ds.generate(self.data)
        ds.drop_duplicate_artists()
        ds.drop_custom_titles()

        plt = PlotFactory(ds.get_df(), EMOTION_KEYS, plot_dir)
        plt.make_wheel_playlist_boxplots("{0}")
        plt.make_wheel_playlist_boxplots("s_{0}")
        plt.make_wheel_playlist_boxplots("{0}_ratio", showfliers=False)

        plt.make_sentiment_playlist_boxplot()

        ds.drop_duplicate_titles()

        plt.make_va_scatter(c="playlist")
        plt.make_va_scatter(c="playlist", set_limits=False)

        plt.make_vad_scatter()

    def generate_emotion_playlist_plots(self, plot_dir: pathlib.Path):

        data = self.create_emotion_playlist()
        ds = DataFrame()
        ds.generate(data)
        ds.drop_duplicate_artists()
        ds.drop_custom_titles()
        ds.drop_duplicate_titles()

        plt = PlotFactory(ds.get_df(), EMOTION_KEYS, plot_dir)
        plt.make_va_scatter(c="emotion_playlist", set_limits=False)
        plt.make_sentiment_emotion_playlist_boxplot()

    def generate_quadrant_playlist_plots(self, plot_dir: pathlib.Path):

        data = self.create_quadrant_playlist()
        ds = DataFrame()
        ds.generate(data)
        ds.drop_duplicate_artists()
        ds.drop_custom_titles()
        ds.drop_duplicate_titles()

        plt = PlotFactory(ds.get_df(), EMOTION_KEYS, plot_dir)
        plt.make_sentiment_quadrant_playlist_boxplot()

    def dump(self, gen_data: pathlib.Path):

        ds = DataFrame()
        ds.generate(self.data)
        ds.dump(gen_data)
