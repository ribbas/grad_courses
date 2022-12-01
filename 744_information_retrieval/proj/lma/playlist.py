from typing import Any


from .emotions import Emotions
from .files import IO


class Track:
    def __init__(
        self, title: str, artist: list[str], emotion: str, lyrics: str = ""
    ) -> None:
        self.title = title
        self.artist = artist
        self.emotion = emotion
        self.lyrics = lyrics


class Playlist:
    def __init__(self, name: str, file_data: Any, emotion: str) -> None:

        self.name = name
        self.file_data = file_data
        self.tracks: list[Track] = []
        self.emotion = emotion
        self.quadrant = Emotions.get_quadrant(emotion)

    def ingest(self) -> None:

        for line in self.file_data["items"]:
            title = line["track"]["name"]
            artist = [i["name"] for i in line["track"]["artists"]]
            track = Track(title, artist, self.emotion)
            self.tracks.append(track)
