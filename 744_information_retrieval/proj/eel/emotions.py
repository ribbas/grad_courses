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

SENTIMENT_KEYS = {"negative", "positive"}

VAD_KEYS = {"valence", "arousal", "dominance"}


class DataCleaner:
    def __init__(
        self, emolex_dir: pathlib.Path, norm_emolex_dir: pathlib.Path
    ) -> None:
        self.emolex_dir = emolex_dir
        self.norm_emolex_dir = norm_emolex_dir


class Emotions:
    def __init__(
        self, emolex_dir: pathlib.Path, norm_emolex_dir: pathlib.Path
    ) -> None:

        self.emolex_dir = emolex_dir
        self.norm_emolex_dir = norm_emolex_dir
        self.normalizer = Normalizer()

        self.emotion_lex: dict[str, dict[str, float]] = {
            e: {} for e in EMOTION_KEYS
        }

        self.vad_lex: dict[str, dict[str, float]] = {}

        self.sentiment = {}

    def load_dataset(self, dataset: str):

        return IO.read(self.emolex_dir / dataset).split("\n")

    def normalize_datasets(self):

        for emotion in EMOTION_KEYS:

            data = self.load_dataset(f"{emotion}_.txt")
            lex = ""
            for line in data:
                if line:
                    word, value = line.split("\t", maxsplit=1)
                    lex += f"{self.normalizer._stem([word])[0]}\t{value}\n"

            IO.dump(self.norm_emolex_dir / f"{emotion}_.txt", lex)

        for sentiment in SENTIMENT_KEYS:
            IO.dump(
                self.norm_emolex_dir / f"{sentiment}.txt",
                "\n".join(
                    self.normalizer(
                        " ".join(self.load_dataset(f"{sentiment}.txt"))
                    )
                )
                + "\n",
            )

        vad_data = self.load_dataset("VAD-Lexicon.txt")
        vad_lex = ""
        for line in vad_data:
            if line:
                word, value = line.split("\t", maxsplit=1)
                vad_lex += f"{self.normalizer._stem([word])[0]}\t{value}\n"

        IO.dump(self.norm_emolex_dir / "VAD-Lexicon.txt", vad_lex)

    def load_all_datasets(self):

        for emotion in EMOTION_KEYS:
            emotion_data = self.load_dataset(f"{emotion}_.txt")
            for line in emotion_data:
                if line:
                    word, value = line.split("\t")
                    self.emotion_lex[emotion][word] = float(value)

        for sentiment in SENTIMENT_KEYS:
            self.sentiment[sentiment] = self.load_dataset(f"{sentiment}.txt")

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

    def get_sentiment(self, lyrics: list[str] | set[str]):

        counts = {e: 0 for e in SENTIMENT_KEYS}

        for word in lyrics:
            for emotion_key, lex in self.sentiment.items():
                if word in lex:
                    counts[emotion_key] += 1

        return counts

    def get_wheel_category(self, lyrics: list[str] | set[str]):

        counts = {e: 0.0 for e in EMOTION_KEYS}

        for word in lyrics:
            for emotion_key, lex in self.emotion_lex.items():
                for emotion_word, val in lex.items():
                    if word == emotion_word:
                        counts[emotion_key] += val

        return counts

    def get_vad(self, lyrics: list[str] | set[str]):

        counts = {k: {} for k in VAD_KEYS}

        for word in lyrics:
            if word in self.vad_lex:
                for key in counts.keys():
                    counts[key][word] = self.vad_lex[word][key]

        return {k: sum(v.values()) / len(v.values()) for k, v in counts.items()}
