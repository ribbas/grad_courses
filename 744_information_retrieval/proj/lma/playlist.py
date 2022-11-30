import random
from typing import Any

import azapi

from .emotions import Emotions
from .files import IO


class Track:
    def __init__(
        self,
        title: str,
        artist: list[str],
        emotion: str,
        lyrics: str = "",
    ) -> None:
        self.title = title
        self.artist = artist
        self.emotion = emotion
        self.lyrics = lyrics

    def set_lyrics(self, lyrics: str):

        self.lyrics = lyrics


class Playlist:
    def __init__(self, file_data: Any, emotion: str) -> None:

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


class LyricsRetriever:
    def __init__(self) -> None:

        self.az = azapi.AZlyrics()
        self.failed: set[str] = set()

    def get_lyrics(self, tracks: list[Track], path: str):

        for track in tracks:
            print(track.title, track.artist)
            self.az.title = track.title
            for artist in track.artist:
                self.az.artist = artist
                self.az.getLyrics(
                    save=True, path=path, sleep=random.uniform(3, 5)
                )

                # add condition to check if success
                if self.az.lyrics:
                    track.set_lyrics(self.az.lyrics)
                    print(f"Retrieved '{track.title}'")
                    break
            if not track.lyrics:
                print(f"Failed '{track.title}'")
                self.failed.add(track.title)

        print(self.failed)
        return self.failed
