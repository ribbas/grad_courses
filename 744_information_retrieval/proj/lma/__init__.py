import pathlib

from .dataframe import DataFrame, TRANSFORM_KEY_FMT
from .emotions import Emotions, EMOTION_KEYS, VAD_KEYS, SENTIMENT_KEYS
from .files import IO
from .playlist import Playlist
from .playlistservice import PlaylistService
from .plot import Scatter, Scatter3D, BoxPlot
from .text import Normalizer


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
        emolex_dir: pathlib.Path,
        norm_emolex_dir: pathlib.Path,
    ) -> None:

        self.scatter3d: Scatter3D
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

    def __transpose(self, playlist: Playlist):

        df = []
        for track in playlist.tracks:

            if track.lyrics:

                line = {}

                line["title"] = track.title
                line["playlist"] = playlist.name

                lyrics = self.norm(track.lyrics)

                for t_key, t_lyrics in zip(
                    TRANSFORM_KEY_FMT,
                    (
                        lyrics,
                        set(lyrics),
                        self.norm.remove_stopwords(set(lyrics)),
                    ),
                ):

                    line[t_key.format("n_words")] = len(t_lyrics)
                    vad = self.emotions.get_vad(t_lyrics)
                    for key in VAD_KEYS:
                        line[t_key.format(key)] = vad[key]

                    sentiment = self.emotions.get_sentiment(t_lyrics)
                    for key in SENTIMENT_KEYS:
                        line[t_key.format(key)] = sentiment[key]

                    wheel = self.emotions.get_wheel_category(t_lyrics)
                    for key in EMOTION_KEYS:
                        line[t_key.format(key)] = wheel[key]

                for artist in track.artist:
                    _line = line.copy()
                    _line["artist"] = artist
                    df.append(_line)

        return df

    def load_datasets(self):

        self.emotions.load_all_datasets()

    def clean_datasets(self):

        self.emotions.normalize_datasets()

    def generate_data(self, playlist_name: str):

        if playlist_name == "all":
            for playlist in self.playlists:
                self.playlists.get_lyrics(playlist)
                self.data.extend(self.__transpose(playlist))

        else:
            playlist = self.playlists[playlist_name]
            self.playlists.get_lyrics(playlist)
            self.data.extend(self.__transpose(playlist))

    def read_csv(self, gen_data: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        # data.create_sentiment_ratio_columns()
        data.drop_duplicate_artists()
        print(data.df["playlist"].unique())

        for key in EMOTION_KEYS:
            data.create_wheel_ratio_columns(key, "{0}")
            print(f"{key}_ratio")
            print(
                data.df[["title", "playlist", f"{key}_ratio"]].loc[
                    data.df[f"{key}_ratio"].idxmax()
                ]
            )
            print(
                data.df[["title", "playlist", f"{key}_ratio"]].loc[
                    data.df[f"{key}_ratio"].idxmin()
                ]
            )
            print()

    def generate_plots(self, gen_data: pathlib.Path, plot_dir: pathlib.Path):

        data = DataFrame()
        data.read_csv(gen_data)
        data.drop_duplicate_artists()

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes(f"{key}", data.df)
            bp.save_fig(plot_dir / f"{key}.png")

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes(f"s_{key}", data.df)
            bp.save_fig(plot_dir / f"s_{key}.png")

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            data.create_wheel_ratio_columns(key, "{0}")
            bp.set_axes(f"{key}_ratio", data.df)
            bp.save_fig(plot_dir / f"{key}_ratio.png")

        bp = BoxPlot()
        data.create_sentiment_ratio_columns()
        bp.set_axes("sentiment", data.df)
        bp.save_fig(plot_dir / "sentiment.png")
        print(data.df[data.df["sentiment"] < 0]["artist"].describe())
        print(data.df[data.df["sentiment"] > 0]["artist"].describe())

        data.drop_duplicate_titles()

        sc = Scatter()
        sc.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["playlist"],
            data.df,
        )
        sc.save_fig(plot_dir / "s_va.png")

        sc3d = Scatter3D()
        sc3d.set_axes(
            data.df["valence"],
            data.df["arousal"],
            data.df["dominance"],
            data.df["playlist"],
        )
        sc3d.save_fig(plot_dir / "s_vad.png")

    def dump(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.generate(self.data)
        df.head()
        df.dump(gen_data)
