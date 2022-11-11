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
        help="normalize documents",
    )
    parser.add_argument(
        "-n",
        "--norm",
        action=argparse.BooleanOptionalAction,
        help="normalize documents",
    )
    parser.add_argument(
        "-g",
        "--gen",
        action=argparse.BooleanOptionalAction,
        help="perform min-hashing",
    )
    parser.add_argument(
        "-d",
        "--dump",
        action=argparse.BooleanOptionalAction,
        help="dump classifier to disk",
    )
    parser.add_argument("-s", "--score", type=str, help="path of query file")

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval(Path(args["path"]))

    if args["all"]:
        ir_obj.normalize()
        ir_obj.generate_signatures()
        ir_obj.dump_clusters()

    else:

        if args["norm"]:
            ir_obj.normalize()

        if args["gen"]:
            ir_obj.generate_signatures()

        if args["dump"]:
            ir_obj.dump_clusters()

        if args["score"]:
            ir_obj.score(Path(args["score"]))
