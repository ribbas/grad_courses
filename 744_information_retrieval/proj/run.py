import argparse
from pathlib import Path

from eel import EmotionExtractionFromLyrics

if __name__ == "__main__":

    emolex_dir = Path("data/emolex")
    norm_emolex_dir = Path("data/norm_emolex")
    log_dir = Path("data/logs")
    bin_dir = Path("data/bin")
    lyrics_dir = Path("data/lyrics")
    playlist_dir = Path("data/spotify")
    gen_path = Path("data/gen/final.csv")
    plot_dir = Path("docs/statics/plots")

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p", "--play", type=str, default="all", help="name of playlist"
    )
    parser.add_argument(
        "-s",
        "--scrape",
        action=argparse.BooleanOptionalAction,
        help="grab lyrics of playlist",
    )
    parser.add_argument(
        "-c",
        "--clean",
        action=argparse.BooleanOptionalAction,
        help="clean source lexicons",
    )
    parser.add_argument(
        "-b",
        "--build",
        action=argparse.BooleanOptionalAction,
        help="build dataframe",
    )
    parser.add_argument(
        "-l",
        "--load",
        action=argparse.BooleanOptionalAction,
        help="load checkpoint",
    )
    parser.add_argument(
        "-m",
        "--metrics",
        action=argparse.BooleanOptionalAction,
        help="generate metrics",
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

    if args["scrape"]:
        eel_obj.get_playlists()
        eel_obj.add_lyrics(args["play"])

    if args["clean"]:
        eel_obj.get_playlists()
        eel_obj.clean_datasets(
            emolex_dir=emolex_dir, norm_emolex_dir=emolex_dir
        )

    if args["build"]:
        eel_obj.get_playlists()
        eel_obj.load_datasets()
        eel_obj.create_df(playlist_name=args["play"])
        eel_obj.save_checkpoint(bin_dir)
        eel_obj.dump(gen_path)

    if args["load"]:
        eel_obj.get_playlists()
        eel_obj.load_datasets()
        eel_obj.load_checkpoint(bin_dir)

    if args["metrics"]:
        eel_obj.compute_metrics()

    if args["graph"]:
        eel_obj.generate_exploratory_plots(plot_dir)
        eel_obj.generate_emotion_playlist_plots(plot_dir)
        eel_obj.generate_quadrant_playlist_plots(plot_dir)

    if args["read"]:
        eel_obj.read_csv(gen_path)
