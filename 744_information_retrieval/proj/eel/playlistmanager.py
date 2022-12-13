import pathlib
from typing import Generator

from .files import IO
from .lyrics import LyricsRetriever
from .playlist import Playlist
from .text import Normalizer


class PlaylistManager:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        raw_lyrics_dir: pathlib.Path,
        norm_lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
    ) -> None:

        self.playlist_dir = playlist_dir
        self.raw_lyrics_dir = raw_lyrics_dir
        self.norm_lyrics_dir = norm_lyrics_dir
        self.log_dir = log_dir

        self.playlists: list[Playlist] = []
        self.lr = LyricsRetriever()

    def __iter__(self) -> Generator[Playlist, None, None]:

        for playlist in self.playlists:
            yield playlist

    def __getitem__(self, playlist_name: str) -> Playlist:

        for playlist in self.playlists:
            if playlist.name == playlist_name:
                return playlist

        raise IndexError

    def append(self, playlist: Playlist):

        playlist.ingest()
        self.playlists.append(playlist)

    def add_lyrics(self, playlist: Playlist):

        print(f"Searching lyrics for {len(playlist.tracks)} tracks")
        failed = self.lr.get_lyrics(
            playlist.tracks,
            str(self.raw_lyrics_dir.absolute() / playlist.name),
        )

        IO.dump(
            self.log_dir / playlist.name,
            "\n".join(
                sorted((f"{track.title} :: {track.artist}" for track in failed))
            )
            + "\n",
        )

    @staticmethod
    def __get_lyrics(lyrics_dir: pathlib.Path, playlist: Playlist):

        lyrics_dir_path = lyrics_dir / playlist.name
        print(
            f"Loading lyrics from '{lyrics_dir_path.absolute()}'...",
            end="",
        )
        lyrics_files = list(lyrics_dir_path.iterdir())
        for track in playlist.tracks:
            for lyrics_file in lyrics_files:
                if track.title in lyrics_file.stem:
                    track.lyrics = IO.read(lyrics_file)
        print(" done!")

    def get_lyrics(self, playlist: Playlist):

        self.__get_lyrics(self.raw_lyrics_dir, playlist)

    def get_normalized_lyrics(self, playlist: Playlist):

        self.__get_lyrics(self.norm_lyrics_dir, playlist)

    def dump_lyrics(self, playlist: Playlist, norm: Normalizer):

        lyrics_files = list((self.raw_lyrics_dir / playlist.name).iterdir())
        for track in playlist.tracks:
            for lyrics_file in lyrics_files:
                if track.title in lyrics_file.stem:
                    playlist_dir = self.norm_lyrics_dir / playlist.name
                    playlist_dir.mkdir(exist_ok=True)
                    IO.dump(
                        playlist_dir / f"{track.title}.txt",
                        " ".join(norm(track.lyrics)),
                    )
