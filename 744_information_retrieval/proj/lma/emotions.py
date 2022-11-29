class Emotions:

    EMOTIONS = {
        "anger": 1,
        "anticipation": 2,
        "disgust": 1,
        "fear": 4,
        "joy": 2,
        "sadness": 4,
        "surprise": 3,
        "trust": 3,
    }

    @staticmethod
    def get_quadrant(emotion: str) -> int:

        return Emotions.EMOTIONS[emotion]
