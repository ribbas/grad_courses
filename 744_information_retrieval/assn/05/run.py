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
        help="perform all operations",
    )
    parser.add_argument(
        "-r",
        "--read",
        type=int,
        nargs="?",
        default=None,
        const=2,
        help="read and ingest file",
    )
    parser.add_argument(
        "-n",
        "--norm",
        default=False,
        action="store_true",
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
        help="dump clusters to disk",
    )
    parser.add_argument(
        "-s", "--score", type=str, help="score clusters against golden file"
    )
    parser.add_argument(
        "-t",
        "--test",
        action=argparse.BooleanOptionalAction,
        help="perform all operations",
    )

    args = vars(parser.parse_args())

    ir_obj = InformationRetrieval(Path(args["path"]))

    if args["all"]:
        ir_obj.ingest(ngrams=2, normalize=True)
        ir_obj.generate_signatures()
        ir_obj.dump_clusters()

    elif args["test"]:

        scores: list[tuple[int, bool, tuple[int, int]]] = []
        for ngram in range(1, 7):
            for normalize in (True, False):
                ir_obj.ingest(ngrams=ngram, normalize=normalize)
                ir_obj.generate_signatures()
                ir_obj.dump_clusters()
                scores.append(
                    (ngram, normalize, ir_obj.score(Path(args["score"])))
                )

        print(scores)

    else:

        if args["read"]:
            ir_obj.ingest(ngrams=args["read"], normalize=args["norm"])

        if args["gen"]:
            ir_obj.generate_signatures()

        if args["dump"]:
            ir_obj.dump_clusters()

        if args["score"]:
            print(ir_obj.score(Path(args["score"])))
