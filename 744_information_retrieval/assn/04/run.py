import argparse
from pathlib import Path

from ir import InformationRetrieval

if __name__ == "__main__":

    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str, help="path of corpus file")
    parser.add_argument(
        "-f",
        "--train",
        type=int,
        nargs="?",
        default=None,
        const=0,
        choices=(0, 1, 2, 3),
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
        "-g",
        "--gen",
        action=argparse.BooleanOptionalAction,
        help="perform grid search",
    )
    parser.add_argument(
        "-s",
        "--score",
        action=argparse.BooleanOptionalAction,
        help="compute scores of the model",
    )
    parser.add_argument(
        "-p",
        "--predict",
        action=argparse.BooleanOptionalAction,
        help="predict target values",
    )
    parser.add_argument("-t", "--test", type=str, help="path of test file")

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval(Path(args["path"]))

    categories: tuple = ()
    if args["train"]:

        if args["train"] == 0:
            categories = ("title",)
            print("training on categories:", categories)

        elif args["train"] == 1:
            categories = ("title", "abstract", "keywords")
            print("training on categories:", categories)

        elif args["train"] == 2:
            categories = (
                "title",
                "abstract",
                "keywords",
                "language",
            )
            print("training on categories:", categories)

        elif args["train"] == 3:
            categories = (
                "title",
                "abstract",
                "keywords",
                "language",
            )
            ir_obj.use_xgb()
            print("training on categories:", categories)

        ir_obj.extract_train_features(categories)

    if args["load"]:
        ir_obj.load_classifier(args["train"])

    if args["gen"]:
        ir_obj.grid_search()
        ir_obj.dump_classifier(args["train"])

    if args["test"]:
        ir_obj.extract_test_features(Path(args["test"]), categories)

    if args["score"]:
        ir_obj.predict()
        ir_obj.score()
        ir_obj.dump_cv_results()

    if args["predict"]:
        ir_obj.predict()
        ir_obj.dump_predict_vals(Path(args["test"]))
