import argparse
from pathlib import Path

from ir import InformationRetrieval

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str, help="path of corpus file")
    parser.add_argument(
        "-a",
        "--all",
        action=argparse.BooleanOptionalAction,
        help="run through the entire list of default pipeline tasks",
    )
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
        "-l",
        "--load",
        action=argparse.BooleanOptionalAction,
        help="load pre-generated frequencies data",
    )
    parser.add_argument(
        "-t",
        "--sort",
        action=argparse.BooleanOptionalAction,
        help="sort term-docID-tf",
    )
    parser.add_argument(
        "-e",
        "--encode",
        action=argparse.BooleanOptionalAction,
        help="generate inverted file",
    )
    parser.add_argument(
        "-p",
        "--precompute",
        action=argparse.BooleanOptionalAction,
        help="precompute document lengths",
    )
    parser.add_argument("-q", "--query", type=str, help="path of query file")

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval(Path(args["path"]))
    if args["all"]:
        ir_obj.generate_freqs()
    #     ir_obj.generate_stats()
    #     ir_obj.dump_freqs()
    #     ir_obj.build_sorted_tdt()
    #     ir_obj.encode_inverted_file()
    #     ir_obj.precompute_lengths()

    # elif args["query"]:
    #     ir_obj.generate_rankings(args["query"])

    else:

        if args["freq"]:
            ir_obj.generate_freqs()

    #     if args["stat"]:
    #         ir_obj.generate_stats()

    #     if args["dump"]:
    #         ir_obj.dump_freqs()

    #     if args["load"]:
    #         ir_obj.load_freqs()

    #     if args["sort"]:
    #         ir_obj.build_sorted_tdt()

    #     if args["encode"]:
    #         ir_obj.encode_inverted_file()

    #     if args["precompute"]:
    #         ir_obj.precompute_lengths()
