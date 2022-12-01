import pathlib

from .files import IO

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

        self.emotion_lex["anger"] = self.load_dataset("anger.txt")
        self.emotion_lex["anticipation"] = self.load_dataset("anticipation.txt")
        self.emotion_lex["disgust"] = self.load_dataset("disgust.txt")
        self.emotion_lex["fear"] = self.load_dataset("fear.txt")
        self.emotion_lex["joy"] = self.load_dataset("joy.txt")
        self.emotion_lex["sadness"] = self.load_dataset("sadness.txt")
        self.emotion_lex["surprise"] = self.load_dataset("surprise.txt")
        self.emotion_lex["trust"] = self.load_dataset("trust.txt")

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

    def get_emotion(self, lyrics: list[str]):

        num_words = len(lyrics)
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

        return {k: sum(v.values()) / len(v) for k, v in counts.items()}

    def score(self, lyrics: list[str]):

        return self.get_emotion(lyrics), self.get_vad(lyrics), len(lyrics)
