import argparse
from pathlib import Path

from eel import EmotionExtractionFromLyrics

if __name__ == "__main__":

    emolex_dir = Path("data/emolex")
    norm_emolex_dir = Path("data/norm_emolex")
    log_dir = Path("data/logs")
    lyrics_dir = Path("data/lyrics")
    playlist_dir = Path("data/spotify")
    gen_data = Path("data/final.csv")
    plot_dir = Path("docs/statics/plots")

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p", "--play", type=str, default="all", help="name of playlist"
    )
    parser.add_argument(
        "-l",
        "--lyrics",
        action=argparse.BooleanOptionalAction,
        help="grab lyrics of playlist",
    )
    parser.add_argument(
        "-c",
        "--clean",
        action=argparse.BooleanOptionalAction,
        help="generate dataframe",
    )
    parser.add_argument(
        "-d",
        "--data",
        action=argparse.BooleanOptionalAction,
        help="generate dataframe",
    )
    parser.add_argument(
        "-b",
        "--load",
        action=argparse.BooleanOptionalAction,
        help="generate dataframe",
    )
    parser.add_argument(
        "-g",
        "--graph",
        action=argparse.BooleanOptionalAction,
        help="read generated dataframe",
    )
    parser.add_argument(
        "-r",
        "--read",
        action=argparse.BooleanOptionalAction,
        help="read generated dataframe",
    )

    args = vars(parser.parse_args())

    eel_obj = EmotionExtractionFromLyrics(
        playlist_dir=playlist_dir,
        lyrics_dir=lyrics_dir,
        log_dir=log_dir,
        norm_emolex_dir=emolex_dir,
    )

    if args["lyrics"]:
        eel_obj.get_playlists()
        eel_obj.add_lyrics(args["play"])

    if args["clean"]:
        eel_obj.get_playlists()
        eel_obj.clean_datasets(
            emolex_dir=emolex_dir, norm_emolex_dir=emolex_dir
        )

    if args["data"]:
        eel_obj.get_playlists()
        eel_obj.load_datasets()
        eel_obj.generate_data(playlist_name=args["play"])
        eel_obj.dump(gen_data)

    if args["load"]:
        eel_obj.get_playlists()
        eel_obj.load_datasets()
        eel_obj.load_checkpoint()
        eel_obj.generate_data(playlist_name=args["play"])
        eel_obj.compute_metrics()
        eel_obj.dump(gen_data)

    if args["graph"]:
        eel_obj.generate_plots(gen_data, plot_dir)

    if args["read"]:
        eel_obj.read_csv(gen_data)
