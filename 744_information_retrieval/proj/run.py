import argparse
from pathlib import Path

from lma import LyricsMoodAnalysis

if __name__ == "__main__":

    # https://aclanthology.org/2021.cmcl-1.18.pdf
    emolex_dir = Path("data/emotion_dynamics")
    log_dir = Path("data/logs")
    lyrics_dir = Path("data/lyrics")
    playlist_dir = Path("data/spotify")
    gen_data = Path("data/final.csv")

    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--play", type=str, help="name of playlist")
    parser.add_argument(
        "-l",
        "--lyrics",
        action=argparse.BooleanOptionalAction,
        help="perform lyrics operations",
    )
    parser.add_argument(
        "-g",
        "--gen",
        action=argparse.BooleanOptionalAction,
        help="perform lyrics operations",
    )

    args = vars(parser.parse_args())

    lma_obj = LyricsMoodAnalysis(playlist_dir, lyrics_dir, log_dir, emolex_dir)

    if args["lyrics"]:
        lma_obj.get_playlists()
        lma_obj.add_lyrics(args["play"])

    if args["gen"]:
        lma_obj.get_playlists()
        lma_obj.load_datasets()
        lma_obj.generate_data(args["play"])
        lma_obj.dump(gen_data)
