import argparse
from pathlib import Path

from ir import InformationRetrieval

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str, help="path of corpus file")
    parser.add_argument(
        "-f",
        "--freq",
        action=argparse.BooleanOptionalAction,
        help="generate frequencies",
    )
    parser.add_argument(
        "-s",
        "--stat",
        action=argparse.BooleanOptionalAction,
        help="generate frequency statistics",
    )
    parser.add_argument(
        "-d",
        "--dump",
        action=argparse.BooleanOptionalAction,
        help="save frequencies data to file",
    )
    parser.add_argument(
        "-lf",
        "--load_freqs",
        action=argparse.BooleanOptionalAction,
        help="load pregenerated frequencies data",
    )
    parser.add_argument(
        "-li",
        "--load_invf",
        action=argparse.BooleanOptionalAction,
        help="load pregenerated frequencies data",
    )
    parser.add_argument(
        "-i",
        "--invf",
        action=argparse.BooleanOptionalAction,
        help="generate inverted files",
    )

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval()
    ir_obj.set_filename(Path(args["path"]))

    if args["freq"]:
        ir_obj.generate_freqs()

    if args["stat"]:
        ir_obj.generate_stats()

    if args["dump"]:
        ir_obj.dump_freqs()

    if args["load_freqs"]:
        ir_obj.load_freqs()

    if args["load_invf"]:
        ir_obj.load_inverted_file()

    if args["invf"]:
        ir_obj.build_inverted_file()
