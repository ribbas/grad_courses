from .emotions import EMOTION_KEYS, QUADRANT_KEYS


class AutoPlaylist:
    @staticmethod
    def create_emotion_playlist(df_data, func, args=None):

        thresh = {}

        if args:
            thresh = {
                col: func([i[f"{col}_ratio"] for i in df_data], args)
                for col in EMOTION_KEYS
            }
        else:
            thresh = {
                col: func([i[f"{col}_ratio"] for i in df_data])
                for col in EMOTION_KEYS
            }

        new_data = []
        for line in df_data:
            for key in EMOTION_KEYS:
                if line[f"{key}_ratio"] >= thresh[key]:
                    _line = line.copy()
                    _line["emotion_playlist"] = key
                    new_data.append(_line)

        print("Generated emotion playlists")
        return new_data

    @staticmethod
    def create_quadrant_playlist(df_data, func, args=None):

        for i in df_data:
            i["q1"] = i["joy_ratio"] + i["surprise_ratio"]
            i["q2"] = i["anger_ratio"] + i["disgust_ratio"]
            i["q3"] = i["sadness_ratio"] + i["fear_ratio"]
            i["q4"] = i["trust_ratio"] + i["anticipation_ratio"]

        thresh = {}

        if args:
            thresh = {
                col: func([i[col] for i in df_data], args)
                for col in QUADRANT_KEYS
            }
        else:
            thresh = {
                col: func([i[col] for i in df_data]) for col in QUADRANT_KEYS
            }

        new_data = []

        for line in df_data:
            for key in QUADRANT_KEYS:
                if line[key] >= thresh[key]:
                    _line = line.copy()
                    _line["quadrant_playlist"] = key
                    new_data.append(_line)

        print("Generated quadrant playlists")
        return new_data
