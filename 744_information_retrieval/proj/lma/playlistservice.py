import pathlib

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
