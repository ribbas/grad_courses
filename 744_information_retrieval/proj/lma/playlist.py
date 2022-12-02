from typing import Any


from .emotions import Emotions
from .files import IO


class Track:
    def __init__(self, title: str, artist: list[str], lyrics: str = "") -> None:
        self.title = title
        self.artist = artist
        self.lyrics = lyrics


class Playlist:
    def __init__(self, name: str, file_data: Any) -> None:

        self.name = name
        self.file_data = file_data
        self.tracks: list[Track] = []

    def ingest(self) -> None:

        for line in self.file_data["items"]:
            title = line["track"]["name"]
            artist = [i["name"] for i in line["track"]["artists"]]
            track = Track(title, artist)
            self.tracks.append(track)
