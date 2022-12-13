from .emotions import EMOTION_KEYS, QUADRANT_KEYS


class AutoPlaylist:
    @staticmethod
    def threshold(df_data, func, args, key_fmt, keys):

        if args:
            return {
                col: func([i[key_fmt.format(col)] for i in df_data], args)
                for col in keys
            }
        else:
            return {
                col: func([i[key_fmt.format(col)] for i in df_data])
                for col in keys
            }

    @staticmethod
    def create_emotion_playlist(df_data, func, args=None):

        thresh = AutoPlaylist.threshold(
            df_data, func, args, "{0}_ratio", EMOTION_KEYS
        )

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

        for line in df_data:
            line["q1"] = line["joy_ratio"] + line["surprise_ratio"]
            line["q2"] = line["anger_ratio"] + line["disgust_ratio"]
            line["q3"] = line["sadness_ratio"] + line["fear_ratio"]
            line["q4"] = line["trust_ratio"] + line["anticipation_ratio"]

        thresh = AutoPlaylist.threshold(
            df_data, func, args, "{0}", QUADRANT_KEYS
        )

        new_data = []

        for line in df_data:
            for key in QUADRANT_KEYS:
                if line[key] >= thresh[key]:
                    _line = line.copy()
                    _line["quadrant_playlist"] = key
                    new_data.append(_line)

        print("Generated quadrant playlists")
        return new_data
