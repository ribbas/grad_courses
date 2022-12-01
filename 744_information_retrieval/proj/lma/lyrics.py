import random

import azapi

from .playlist import Track


class LyricsRetriever:
    def __init__(self) -> None:

        self.az = azapi.AZlyrics()

    def get_lyrics(self, tracks: list[Track], path: str) -> list[Track]:

        failed: list[Track] = []
        for track in tracks:
            self.az.title = track.title
            for artist in track.artist:
                self.az.artist = artist
                print(f"Searching for '{self.az.title} :: {self.az.artist}'")
                self.az.getLyrics(
                    save=True, path=path, sleep=random.uniform(3, 5)
                )

                if len(self.az.lyrics):
                    track.lyrics = self.az.lyrics
                    self.az.lyrics = ""
                    break
                else:
                    track.lyrics = ""

            if not track.lyrics:
                print(f"Failed '{track.title}'")
                failed.append(track)

        return failed
