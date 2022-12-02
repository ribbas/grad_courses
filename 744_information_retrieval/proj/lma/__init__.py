import pathlib

from .dataframe import DataFrame
from .emotions import Emotions, EMOTION_KEYS, VAD_KEYS
from .files import IO
from .playlist import Playlist, Track
from .playlistservice import PlaylistService
from .model import Model
from .text import Normalizer


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
        emolex_dir: pathlib.Path,
    ) -> None:

        self.clf: Model = Model()
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
                    ("{0}", "u_{0}", "s_{0}"),
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

    def read(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.read_csv(gen_data)
        df.head()

    def dump(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.generate(self.data)
        df.head()
        df.dump(gen_data)
