import argparse
from pathlib import Path

from ir import InformationRetrieval

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str, help="path of corpus file")
    parser.add_argument(
        "-1",
        "--baseline",
        action=argparse.BooleanOptionalAction,
        help="extract training features",
    )
    parser.add_argument(
        "-f",
        "--train",
        action=argparse.BooleanOptionalAction,
        help="extract training features",
    )
    parser.add_argument(
        "-l",
        "--load",
        action=argparse.BooleanOptionalAction,
        help="load classifier from disk",
    )
    parser.add_argument(
        "-d",
        "--dump",
        action=argparse.BooleanOptionalAction,
        help="dump classifier to disk",
    )
    parser.add_argument(
        "-cv",
        "--cross_validate",
        action=argparse.BooleanOptionalAction,
        help="perform grid search",
    )
    parser.add_argument(
        "-s",
        "--score",
        action=argparse.BooleanOptionalAction,
        help="perform grid search",
    )
    parser.add_argument("-t", "--test", type=str, help="path of test file")

    args = vars(parser.parse_args())

    categories: tuple = ()
    phase_name: str = ""
    if args["baseline"]:
        categories = ("title",)
        print("training on categories:", categories)
        phase_name = "1"
    else:
        categories = ("title", "abstract", "keywords")
        print("training on categories:", categories)
        phase_name = "2"

    ir_obj = InformationRetrieval(Path(args["path"]))

    if args["train"]:
        ir_obj.extract_train_features(categories)

    if args["load"]:
        ir_obj.load_classifier(phase_name)

    if args["cross_validate"]:
        ir_obj.grid_search()
        ir_obj.dump_classifier(phase_name)

    if args["test"]:
        ir_obj.extract_test_features(Path(args["test"]), categories)

    if args["score"]:
        ir_obj.score()
