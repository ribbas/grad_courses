import argparse
from pathlib import Path

from lma import LyricsMoodAnalysis

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--play", type=str, help="path of playlist data")
    parser.add_argument(
        "-l", "--lyric", type=str, help="path of lyrics dataset directory"
    )
    parser.add_argument(
        "-a",
        "--all",
        action=argparse.BooleanOptionalAction,
        help="perform all operations",
    )
    parser.add_argument(
        "-c",
        "--clean",
        type=int,
        nargs="?",
        default=None,
        const=2,
        help="clean and ingest file",
    )
    # parser.add_argument(
    #     "-n",
    #     "--norm",
    #     default=False,
    #     action="store_true",
    #     help="normalize documents",
    # )
    # parser.add_argument(
    #     "-g",
    #     "--gen",
    #     action=argparse.BooleanOptionalAction,
    #     help="perform min-hashing",
    # )
    # parser.add_argument(
    #     "-d",
    #     "--dump",
    #     action=argparse.BooleanOptionalAction,
    #     help="dump clusters to disk",
    # )
    # parser.add_argument(
    #     "-s", "--score", type=str, help="score clusters against golden file"
    # )
    # parser.add_argument(
    #     "-t",
    #     "--test",
    #     action=argparse.BooleanOptionalAction,
    #     help="perform all operations",
    # )

    args = vars(parser.parse_args())

    lma_obj = LyricsMoodAnalysis()

    if args["all"]:
        lma_obj.get_playlists(Path(args["play"]))

    else:

        if args["play"]:
            lma_obj.get_playlists(Path(args["play"]))
            lma_obj.print_tracks(Path(args["lyric"]))
