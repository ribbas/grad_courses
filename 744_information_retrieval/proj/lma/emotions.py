import pathlib

from .files import IO
from .text import Normalizer

EMOTION_KEYS = {
    "anger",
    "anticipation",
    "disgust",
    "fear",
    "joy",
    "sadness",
    "surprise",
    "trust",
}

VAD_KEYS = {"valence", "arousal", "dominance"}


class Emotions:
    def __init__(self, emolex_dir: pathlib.Path) -> None:

        self.emolex_dir = emolex_dir
        self.normalizer = Normalizer()

        self.emotion_lex: dict[str, list[str]] = {e: [] for e in EMOTION_KEYS}

        self.vad_lex: dict[str, dict[str, float]] = {}

    def load_dataset(self, dataset: str):

        return IO.read(self.emolex_dir / dataset).split("\n")

    def load_all_datasets(self):

        for emotion in EMOTION_KEYS:
            self.emotion_lex[emotion] = self.normalizer(
                " ".join(self.load_dataset(f"{emotion}.txt"))
            )

        vad_data = self.load_dataset("VAD-Lexicon.txt")
        for line in vad_data:
            if line:
                word, valence, arousal, dominance = line.split("\t")
                vad = {
                    "valence": float(valence),
                    "arousal": float(arousal),
                    "dominance": float(dominance),
                }
                self.vad_lex[word] = vad

    def get_wheel_category(self, lyrics: list[str] | set[str]):

        counts = {e: 0 for e in EMOTION_KEYS}

        for word in lyrics:
            for emotion_key, lex in self.emotion_lex.items():
                if word in lex:
                    counts[emotion_key] += 1

        return counts

    def get_vad(self, lyrics: list[str] | set[str]):

        counts = {k: {} for k in VAD_KEYS}

        for word in lyrics:
            if word in self.vad_lex:
                for key in counts.keys():
                    counts[key][word] = self.vad_lex[word][key]

        return {k: sum(v.values()) / len(v) for k, v in counts.items()}
