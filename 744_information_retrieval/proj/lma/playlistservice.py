import pathlib
from typing import Generator

from .files import IO
from .lyrics import LyricsRetriever
from .playlist import Playlist


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

    def __iter__(self) -> Generator[Playlist, None, None]:

        for playlist in self.playlists:
            yield playlist

    def __getitem__(self, playlist_name: str) -> Playlist:

        for playlist in self.playlists:
            if playlist.name == playlist_name:
                return playlist

        raise IndexError

    def add_playlist(self, playlist: Playlist):

        playlist.ingest()
        self.playlists.append(playlist)

    def add_lyrics(self, playlist: Playlist):

        print(f"Searching lyrics for {len(playlist.tracks)} tracks")
        failed = self.ls.get_lyrics(
            playlist.tracks,
            str(self.lyrics_dir.absolute() / playlist.name),
        )

        IO.dump(
            self.log_dir / playlist.name,
            "\n".join(
                sorted((f"{track.title} :: {track.artist}" for track in failed))
            )
            + "\n",
        )

    def get_lyrics(self, playlist: Playlist):

        lyrics_files = list((self.lyrics_dir / playlist.name).iterdir())
        for track in playlist.tracks:
            for lyrics_file in lyrics_files:
                if track.title in lyrics_file.stem:
                    track.lyrics = IO.read(lyrics_file)
