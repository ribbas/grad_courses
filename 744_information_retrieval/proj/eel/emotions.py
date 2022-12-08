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
SENTIMENT_KEYS = {"negative", "positive"}


class EmotionLexicon:
    def __init__(self, emolex_dir: pathlib.Path) -> None:

        self.emolex_dir = emolex_dir

        self.normalizer = Normalizer()

        # lexicons
        self.emotion_lex: dict[str, dict[str, float]] = {
            e: {} for e in EMOTION_KEYS
        }
        self.vad_lex: dict[str, dict[str, float]] = {}
        self.sentiment: dict[str, list[str]] = {}

    def __load_dataset(self, dataset: str) -> list[str]:

        return IO.read(self.emolex_dir / dataset).split("\n")

    def __normalize_dataset(self, data: list[str]):

        normalized_data = ""
        for line in data:
            if line:
                word, value = line.split("\t", maxsplit=1)
                normalized_data += (
                    f"{self.normalizer._stem([word])[0]}\t{value}\n"
                )

        return normalized_data

    def normalize_datasets(self, norm_emolex_dir: pathlib.Path):

        for emotion in EMOTION_KEYS:

            data = self.__load_dataset(f"{emotion}.txt")
            normalized_data = self.__normalize_dataset(data)
            IO.dump(norm_emolex_dir / f"{emotion}.txt", normalized_data)

        data = self.__load_dataset("VAD-Lexicon.txt")
        normalized_data = self.__normalize_dataset(data)
        IO.dump(norm_emolex_dir / "VAD-Lexicon.txt", normalized_data)

        for sentiment in SENTIMENT_KEYS:
            normalized_data = (
                "\n".join(
                    self.normalizer(
                        " ".join(self.__load_dataset(f"{sentiment}.txt"))
                    )
                )
                + "\n"
            )
            IO.dump(norm_emolex_dir / f"{sentiment}.txt", normalized_data)

    def load_emotion_datasets(self):

        for emotion in EMOTION_KEYS:
            emotion_data = self.__load_dataset(f"{emotion}.txt")
            for line in emotion_data:
                if line:
                    word, value = line.split("\t")
                    self.emotion_lex[emotion][word] = float(value)

    def load_sentiment_datasets(self):

        for sentiment in SENTIMENT_KEYS:
            self.sentiment[sentiment] = self.__load_dataset(f"{sentiment}.txt")

    def load_vad_datasets(self):

        vad_data = self.__load_dataset("VAD-Lexicon.txt")
        for line in vad_data:
            if line:
                word, valence, arousal, dominance = line.split("\t")
                vad = {
                    "valence": float(valence),
                    "arousal": float(arousal),
                    "dominance": float(dominance),
                }
                self.vad_lex[word] = vad


class Emotions(EmotionLexicon):
    def __init__(self, emolex_dir: pathlib.Path) -> None:

        super().__init__(emolex_dir)

    def load_all_datasets(self):

        print(f"Loading datasets from {self.emolex_dir}")
        self.load_emotion_datasets()
        self.load_sentiment_datasets()
        self.load_vad_datasets()

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
