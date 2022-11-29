import pathlib

from .const import LABELED_PLAYLISTS
from .emotions import Emotions
from .files import IO
from .playlist import Track, Playlist, LyricsScraper


class LyricsMoodAnalysis:
    def __init__(self) -> None:

        self.playlists: list[Playlist] = []
        self.ls = LyricsScraper()

    def get_playlists(self, dirname: pathlib.Path):

        for filename in dirname.iterdir():
            file_data = IO.read_json(filename)
            play = Playlist(file_data, LABELED_PLAYLISTS[filename.stem])
            play.ingest()
            self.playlists.append(play)

    def print_tracks(self):

        for playlist in self.playlists:
            self.ls.get_lyrics(playlist.tracks)
            break
            # for track in playlist.tracks:
            #     print(track.artist)
