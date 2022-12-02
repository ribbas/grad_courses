import pathlib

from .const import LABELED_PLAYLISTS
from .emotions import Emotions
from .files import IO
from .playlist import Playlist
from .playlistservice import PlaylistService
from .model import Model
from .text import Normalizer


class LyricsMoodAnalysis:
    def __init__(
        self,
        playlist_dir: pathlib.Path,
        lyrics_dir: pathlib.Path,
        log_dir: pathlib.Path,
        emolex_dir: pathlib.Path,
    ) -> None:

        self.clf: Model = Model()
        self.playlists = PlaylistService(playlist_dir, lyrics_dir, log_dir)
        self.emotions = Emotions(emolex_dir)
        self.normalizer = Normalizer()

    def get_playlists(self):

        for filename in self.playlists.playlist_dir.iterdir():
            file_data = IO.read_json(filename)
            self.playlists.add_playlist(
                Playlist(
                    filename.stem, file_data, LABELED_PLAYLISTS[filename.stem]
                )
            )

    def add_lyrics(self, playlist_name: str):

        playlist = self.playlists[playlist_name]
        self.playlists.add_lyrics(playlist)

    # def __extract_text_features(
    #     self, filename: Path, categories: tuple[str, ...]
    # ) -> tuple[list[str], np.ndarray]:

    #     docs = CorpusFile().ingest(filename)
    #     target = np.array([i[TARGET_FIELD] for i in docs])
    #     features: list[str] = []

    #     for row in docs:

    #         feature_list = []

    #         for feature in categories:

    #             if feature in LIST_FEATURE_FIELDS:
    #                 feature_list.extend(row[feature])

    #             else:
    #                 feature_list.append(row[feature])

    #         features.append(" ".join(feature_list))

    #     return features, target

    # def extract_train_features(self) -> None:

    #     self.emotions.load_all_datasets()
    #     target = [
    #         self.emotions.get_quadrant(e) for e in self.emotions.emotion_lex
    #     ]
    #     features = [
    #         " ".join(self.emotions.emotion_lex[e])
    #         for e in self.emotions.emotion_lex
    #     ]
    #     self.clf.set_train_features(features, target)

    # def extract_test_features(self, playlist_name: str) -> None:

    #     playlist = self.playlists[playlist_name]
    #     self.playlists.get_lyrics(playlist)

    #     target = []

    #     features = []
    #     for track in playlist.tracks:
    #         if track.lyrics:
    #             target.append(1)
    #             features.append(track.lyrics)

    #     self.clf.set_test_features(features, target)

    # def train(self) -> None:

    #     self.clf.grid_search()
    #     self.model_loaded = True
    # https://aclanthology.org/2021.cmcl-1.18.pdf

    def tokenize_lyrics(self, playlist_name: str):

        self.emotions.load_all_datasets()

        playlist = self.playlists[playlist_name]
        self.playlists.get_lyrics(playlist)

        targets = []
        for track in playlist.tracks[:10]:
            if track.lyrics:
                # print(track.title, track.artist)
                lyrics = self.normalizer(track.lyrics)
                print(self.emotions.score(lyrics))
        #         targets.append(
        #             self.emotions.get_quadrant(self.emotions.score(lyrics))
        #         )

        # print(sorted(targets))
