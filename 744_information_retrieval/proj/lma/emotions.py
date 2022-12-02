import pathlib

from .files import IO
from .text import Normalizer

EMOTIONS = {
    "anger",
    "anticipation",
    "disgust",
    "fear",
    "joy",
    "sadness",
    "surprise",
    "trust",
}


class Emotions:
    def __init__(self, emolex_dir: pathlib.Path) -> None:

        self.emolex_dir = emolex_dir
        self.normalizer = Normalizer()

        self.emotion_lex: dict[str, list[str]] = {
            "anger": [],
            "anticipation": [],
            "disgust": [],
            "fear": [],
            "joy": [],
            "sadness": [],
            "surprise": [],
            "trust": [],
        }

        self.vad_lex: dict[str, dict[str, float]] = {}

    # @staticmethod
    # def get_quadrant(emotion: str) -> int:

    #     emotion_q = {
    #         "anger": 1,
    #         "anticipation": 2,
    #         "disgust": 1,
    #         "fear": 4,
    #         "joy": 2,
    #         "sadness": 4,
    #         "surprise": 3,
    #         "trust": 3,
    #     }

    #     return emotion_q[emotion]

    def load_dataset(self, dataset: str):

        return IO.read(self.emolex_dir / dataset).split("\n")

    def load_all_datasets(self):

        for emotion in EMOTIONS:
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

        counts = {e: 0 for e in EMOTIONS}

        for word in lyrics:
            for emotion_key, lex in self.emotion_lex.items():
                if word in lex:
                    counts[emotion_key] += 1

        return counts
        # return max(counts, key=counts.get)

    def get_vad(self, lyrics: list[str]):

        counts = {"valence": {}, "arousal": {}, "dominance": {}}

        for word in lyrics:
            if word in self.vad_lex:
                for key in counts.keys():
                    counts[key][word] = self.vad_lex[word][key]

        try:
            return {k: sum(v.values()) / len(v) for k, v in counts.items()}
        except ZeroDivisionError:
            print(lyrics, counts)
            exit()

    def score(self, lyrics: list[str]):

        return {
            "vad": self.get_vad(lyrics),
            "wheel": self.get_wheel_category(lyrics),
            "wheel_unique": self.get_wheel_category(set(lyrics)),
            "n_words": len(lyrics),
            "n_words_unique": len(set(lyrics)),
        }
