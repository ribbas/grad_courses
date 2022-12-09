import pathlib

from .dataframe import DataFrame
from .emotions import Emotions, EmotionLexicon, EMOTION_KEYS
from .files import IO
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
        self.norm = Normalizer()
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

    # def score_metrics(self, data: DataFrame):

    #     print(len(set(i["title"] for i in self.data)))

    #     diffs = {}
    #     for p in ("anger", "disgust", "fear", "sadness"):
    #         diffs[p] = (
    #             data.df[data.df["wheel_playlist"] == p]["sentiment"].lt(0).sum()
    #             / data.df[data.df["wheel_playlist"] == p]["sentiment"].count()
    #         )

    #     for n in ("anticipation", "joy", "surprise", "trust"):
    #         diffs[n] = (
    #             data.df[data.df["wheel_playlist"] == n]["sentiment"].gt(0).sum()
    #             / data.df[data.df["wheel_playlist"] == n]["sentiment"].count()
    #         )

    #     print(diffs)
    #     print(sum(v * v for v in diffs.values()))

    def generate_data(self, playlist_name: str):

        if not self.loaded_checkpoint:
            if playlist_name == "all":
                for playlist in self.playlists:
                    print(f"Processing '{playlist.name}'")
                    self.playlists.get_lyrics(playlist)
                    df = DataFrame.transpose(playlist, self.norm, self.emotions)
                    self.data.extend(df)

            else:
                playlist = self.playlists[playlist_name]
                self.playlists.get_lyrics(playlist)
                df = DataFrame.transpose(playlist, self.norm, self.emotions)
                self.data.extend(df)

            self.save_checkpoint()

        print(
            f"Unique number of titles before reclassification: {len(set(i['title'] for i in self.data))}"
        )
        self.data = DataFrame.create_wheel_playlist(self.data)

    def read_csv(self, gen_data: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        print(data.get_top_emotions("Pumped Up Kicks"))
        print(data.get_dist(i for i in EMOTION_KEYS))
        # print(data.get_dist(f"u_{i}" for i in EMOTION_KEYS))
        # print(data.get_dist(f"s_{i}" for i in EMOTION_KEYS))
        # print(data.get_dist(f"{i}_ratio" for i in EMOTION_KEYS))
        # print(data.get_dist(["title"]))
        print(data.get_dist(["title"]))

    def generate_plots(self, gen_data: pathlib.Path, plot_dir: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        data.drop_duplicate_artists()
        data.df.drop(
            data.df[data.df["title"] == "Pumped Up Kicks"].index, inplace=True
        )

        plt = PlotFactory(data.df, EMOTION_KEYS, plot_dir)
        plt.make_wheel_playlist_boxplots("{0}")
        plt.make_wheel_playlist_boxplots("s_{0}")
        plt.make_wheel_playlist_boxplots("{0}_ratio", showfliers=False)

        plt.make_sentiment_playlist_boxplot()

        data.drop_duplicate_titles()

        plt.make_sentiment_wheel_playlist_boxplot()

        plt.make_va_scatter(c="playlist")
        plt.make_va_scatter(c="playlist", set_limits=False)

        plt.make_va_scatter(c="wheel_playlist", set_limits=False)

        plt.make_vad_scatter()

    def dump(self, gen_data: pathlib.Path):

        data = DataFrame()
        data.generate(self.data)
        data.score_metrics()
        data.dump(gen_data)
