import pathlib
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


class PlaylistService:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
    ) -> None:

        self.playlists: list[Playlist] = []
        self.ls = LyricsRetriever()
        self.playlist_dir = playlist_dir
        self.lyrics_dir = lyrics_dir
        self.log_dir = log_dir

    def add_playlist(self, playlist: Playlist):

        playlist.ingest()
        self.playlists.append(playlist)

    def add_lyrics(self, playlist_name: str):

        for playlist in self.playlists:
            if playlist.name == playlist_name:
                print(f"Searching lyrics for {len(playlist.tracks)} tracks")
                failed = self.ls.get_lyrics(
                    playlist.tracks,
                    str(self.lyrics_dir.absolute() / playlist_name),
                )

                IO.dump(
                    self.log_dir / playlist_name,
                    "\n".join(
                        sorted(
                            (
                                f"{track.title} :: {track.artist}"
                                for track in failed
                            )
                        )
                    ),
                )

    # def find_failed(self, playlist_name: str):

    #     found = []
    #     not_found = []
    #     for playlist in self.playlists:
    #         if playlist.name == playlist_name:
    #             not_found = [i for i in playlist.tracks]
    #             lyrics_files = list(i.stem for i in self.lyrics_dir.iterdir())
    #             for track in sorted(not_found, key=lambda x: x.title):
    #                 # print("checking", track.title)
    #                 for lyrics_file in lyrics_files:
    #                     if track.title.lower() in lyrics_file.lower():
    #                         print("removing", track.title)
    #                         found.append(track)
    #                         # not_found.remove(track)
    #                         # break

    #     not_found = set(not_found) - set(found)
    #     IO.dump(
    #         self.log_dir / playlist_name,
    #         "\n".join(
    #             sorted(
    #                 (f"{track.title} - {track.artist}" for track in not_found)
    #             )
    #         ),
    #     )
