import pathlib

from .dataframe import DataFrame, TRANSFORM_KEY_FMT
from .emotions import Emotions, EMOTION_KEYS, VAD_KEYS
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
    ) -> None:

        self.scatter3d: Scatter3D
        self.playlists = PlaylistService(playlist_dir, lyrics_dir, log_dir)
        self.emotions = Emotions(emolex_dir)
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
                line["artist"] = "::".join(track.artist)
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

                    wheel = self.emotions.get_wheel_category(t_lyrics)
                    for key in EMOTION_KEYS:
                        line[t_key.format(key)] = wheel[key]

                df.append(line)

        return df

    def load_datasets(self):

        self.emotions.load_all_datasets()

    def generate_data(self, playlist_name: str):

        if playlist_name == "all":
            for playlist in self.playlists:
                self.playlists.get_lyrics(playlist)
                self.data.extend(self.__transpose(playlist))

        else:
            playlist = self.playlists[playlist_name]
            self.playlists.get_lyrics(playlist)
            self.data.extend(self.__transpose(playlist))

    def generate_plots(self, gen_data: pathlib.Path, plot_dir: pathlib.Path):

        df = DataFrame()
        df.read_csv(gen_data)

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes(f"{key}", df.df)
            bp.save_fig(plot_dir / f"{key}.png")

        for key in EMOTION_KEYS:
            bp = BoxPlot()
            bp.set_axes(f"s_{key}", df.df)
            bp.save_fig(plot_dir / f"s_{key}.png")

        for key in EMOTION_KEYS:
            df.create_wheel_ratio_columns(key, "{0}")
            bp = BoxPlot()
            bp.set_axes(f"{key}_ratio", df.df)
            bp.save_fig(plot_dir / f"{key}_ratio.png")

        sc = Scatter()
        sc.set_axes(
            df.df["s_valence"], df.df["s_arousal"], df.df["s_dominance"], df.df
        )
        sc.save_fig(plot_dir / "s_va.png")

        sc3d = Scatter3D()
        sc3d.set_axes(
            df.df["s_valence"], df.df["s_arousal"], df.df["s_dominance"]
        )
        sc3d.save_fig(plot_dir / "s_vad.png")

    def dump(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.generate(self.data)
        df.head()
        df.dump(gen_data)
