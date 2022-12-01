import argparse
from pathlib import Path

from lma import LyricsMoodAnalysis

if __name__ == "__main__":

    playlist_dir = Path("data/spotify")
    lyrics_dir = Path("data/lyrics")
    log_dir = Path("data/logs")

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-a",
        "--all",
        action=argparse.BooleanOptionalAction,
        help="perform all operations",
    )
    parser.add_argument("-p", "--play", type=str, help="name of playlist")

    args = vars(parser.parse_args())

    lma_obj = LyricsMoodAnalysis(playlist_dir, lyrics_dir, log_dir)

    if args["all"]:
        lma_obj.get_playlists()
        lma_obj.add_lyrics(args["play"])
