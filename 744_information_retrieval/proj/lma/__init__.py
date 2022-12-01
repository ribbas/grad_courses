import pathlib

from .const import LABELED_PLAYLISTS
from .emotions import Emotions
from .files import IO
from .playlist import Playlist
from .lyrics import LyricsRetriever
from .playlistservice import PlaylistService


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
    ) -> None:

        self.playlists = PlaylistService(playlist_dir, lyrics_dir, log_dir)

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.add_playlist(
                Playlist(
                    filename.stem, file_data, LABELED_PLAYLISTS[filename.stem]
                )
            )

    def add_lyrics(self, playlist_name: str):

        self.playlists.add_lyrics(playlist_name)
