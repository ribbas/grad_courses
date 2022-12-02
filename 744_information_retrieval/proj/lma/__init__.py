import pathlib

from .dataframe import DataFrame
from .emotions import Emotions
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
        self.normalizer = Normalizer()
        self.data = []

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.add_playlist(Playlist(filename.stem, file_data))

    def add_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.add_lyrics(playlist)

    def __transpose(self, tracks: list[Track]):

        df = []
        for track in tracks:
            if track.lyrics:
                line = {}
                lyrics = self.normalizer(track.lyrics)
                line["title"] = track.title
                line["artist"] = "::".join(track.artist)
                scores = self.emotions.score(lyrics)
                line["valence"] = scores["vad"]["valence"]
                line["arousal"] = scores["vad"]["arousal"]
                line["dominance"] = scores["vad"]["dominance"]

                line["anger"] = scores["wheel"]["anger"]
                line["anticipation"] = scores["wheel"]["anticipation"]
                line["disgust"] = scores["wheel"]["disgust"]
                line["fear"] = scores["wheel"]["fear"]
                line["joy"] = scores["wheel"]["joy"]
                line["sadness"] = scores["wheel"]["sadness"]
                line["surprise"] = scores["wheel"]["surprise"]
                line["trust"] = scores["wheel"]["trust"]

                line["anger_u"] = scores["wheel_unique"]["anger"]
                line["anticipation_u"] = scores["wheel_unique"]["anticipation"]
                line["disgust_u"] = scores["wheel_unique"]["disgust"]
                line["fear_u"] = scores["wheel_unique"]["fear"]
                line["joy_u"] = scores["wheel_unique"]["joy"]
                line["sadness_u"] = scores["wheel_unique"]["sadness"]
                line["surprise_u"] = scores["wheel_unique"]["surprise"]
                line["trust_u"] = scores["wheel_unique"]["trust"]

                line["n_words"] = scores["n_words"]
                line["n_words_u"] = scores["n_words_unique"]

                df.append(line)

        return df

    def load_datasets(self):

        self.emotions.load_all_datasets()

    def generate_data(self, playlist_name: str):

        if playlist_name == "all":
            for playlist in self.playlists:
                self.playlists.get_lyrics(playlist)
                self.data.extend(self.__transpose(playlist.tracks))

        else:
            playlist = self.playlists[playlist_name]
            self.playlists.get_lyrics(playlist)
            self.data.extend(self.__transpose(playlist.tracks))

    def dump(self, gen_data: pathlib.Path):

        df = DataFrame()
        df.generate(self.data)
        df.dump(gen_data)
