import pathlib

from .const import LABELED_PLAYLISTS
from .emotions import Emotions
from .files import IO
from .playlist import Playlist
from .text import Normalizer
from .playlistservice import PlaylistService


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
    ) -> None:

        self.playlists = PlaylistService(playlist_dir, lyrics_dir, log_dir)
        self.normalizer = Normalizer()

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.add_playlist(
                Playlist(
                    filename.stem, file_data, LABELED_PLAYLISTS[filename.stem]
                )
            )

    def add_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.add_lyrics(playlist)

    def tokenize_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.get_lyrics(playlist)

        for track in playlist.tracks:
            if track.lyrics:
                print(track.title, track.artist)
                print(self.normalizer(track.lyrics))
