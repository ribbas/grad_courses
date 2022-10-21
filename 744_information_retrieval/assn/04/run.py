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
        "--train",
        action=argparse.BooleanOptionalAction,
        help="generate frequencies",
    )
    parser.add_argument("-t", "--test", type=str, help="path of test file")

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval(Path(args["path"]), Path(args["test"]))
    if args["all"]:
        ir_obj.extract_train_features(("title",))
        ir_obj.extract_test_features(args["test"])

    else:

        if args["train"]:
            ir_obj.extract_train_features(("title",))

        if args["test"]:
            ir_obj.extract_test_features(("title",))
