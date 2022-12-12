import pathlib

from .dataframe import Dataset
from .emotions import Emotions, EmotionLexicon, EMOTION_KEYS
from .files import IO
from .metrics import Metrics, FUNCTIONS
from .playlist import Playlist
from .playlistservice import PlaylistService
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
        self.playlists = PlaylistService(
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

    def save_checkpoint(self):

        IO.dump_pickle(self.log_dir / "checkpoint", self.data)

    def load_checkpoint(self):

        self.loaded_checkpoint = True

        self.data = IO.read_pickle(self.log_dir / "checkpoint")

    def generate_data(self, playlist_name: str):

        if not self.loaded_checkpoint:
            norm = Normalizer()
            if playlist_name == "all":
                for playlist in self.playlists:
                    print(f"Processing '{playlist.name}'")
                    self.playlists.get_lyrics(playlist)
                    df = Dataset.transpose(playlist, norm, self.emotions)
                    self.data.extend(df)

            else:
                playlist = self.playlists[playlist_name]
                self.playlists.get_lyrics(playlist)
                df = Dataset.transpose(playlist, norm, self.emotions)
                self.data.extend(df)

            self.save_checkpoint()

        else:
            print("Checkpoint already generated")
        self.data = Dataset.create_wheel_playlist(self.data, *FUNCTIONS["75"])

    def compute_metrics(self):

        ds = Dataset()

        for func_name, args in Metrics().get_function():

            data_with_playcols = ds.create_wheel_playlist(self.data, *args)

            ds.generate(data_with_playcols)

            print(func_name, len(set(i["title"] for i in self.data)))
            Metrics().score_metrics(ds.df)

    def read_csv(self, gen_data: pathlib.Path):

        data = Dataset()
        data.read_csv(gen_data)
        # print(data.get_top_emotions("Pumped Up Kicks"))
        print(data.get_dist(i for i in EMOTION_KEYS))
        print(data.get_dist(f"u_{i}" for i in EMOTION_KEYS))
        print(data.get_dist(f"s_{i}" for i in EMOTION_KEYS))
        # print(data.get_dist(f"{i}_ratio" for i in EMOTION_KEYS))
        # print(data.get_dist(["title"]))
        # print(data.get_dist(["title"]))

    def generate_plots(self, gen_data: pathlib.Path, plot_dir: pathlib.Path):

        ds = Dataset()
        ds.read_csv(gen_data)
        ds.drop_duplicate_artists()
        ds.drop_custom_titles()

        plt = PlotFactory(ds.df, EMOTION_KEYS, plot_dir)
        plt.make_wheel_playlist_boxplots("{0}")
        plt.make_wheel_playlist_boxplots("s_{0}")
        plt.make_wheel_playlist_boxplots("{0}_ratio", showfliers=False)

        plt.make_sentiment_playlist_boxplot()

        ds.drop_duplicate_titles()

        plt.make_sentiment_wheel_playlist_boxplot()

        plt.make_vad_scatter()
        plt.make_va_scatter(c="playlist")
        plt.make_va_scatter(c="playlist", set_limits=False)

        plt.make_va_scatter(c="wheel_playlist", set_limits=False)

    def dump(self, gen_data: pathlib.Path):

        ds = Dataset()

        ds.generate(self.data)

        # Metrics().score_metrics(ds.df)

        ds.dump(gen_data)
