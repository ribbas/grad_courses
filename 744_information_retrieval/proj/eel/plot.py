import pathlib

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns


class Plot:
    def __init__(self, scatter=True) -> None:

        if scatter:
            self.ax = plt.figure(figsize=(16, 16))
        else:
            self.ax = plt.figure(figsize=(16, 9))

    def save_fig(self, filename):

        plt.tight_layout()
        plt.savefig(filename)
        plt.close()


class Scatter(Plot):
    def set_axes(
        self, x: str, y: str, c: str, df: pd.DataFrame, set_limits=True
    ):

        fig = self.ax.add_subplot()
        graph = sns.scatterplot(
            x=df[x], y=df[y], hue=df[c], data=df, alpha=0.5, s=100
        )
        graph.axhline(0.50, linestyle="--", color="#A9A9A9")
        graph.axvline(0.50, linestyle="--", color="#A9A9A9")

        if set_limits:
            fig.set_xlim(0, 1)
            fig.set_ylim(0, 1)
        plt.legend(
            prop={"size": 20},
        )

        fig.set_xlabel(x, fontsize=20)
        fig.set_ylabel(y, fontsize=20)
        fig.tick_params(axis="both", which="major", labelsize=15)


class Scatter3D(Plot):
    def set_axes(self, x: str, y: str, c: str, df: pd.DataFrame):

        fig = self.ax.add_subplot(projection="3d")
        fig.scatter(df[x], df[y], df[c], c=df[c], s=100)

        fig.plot3D(
            np.linspace(0.5, 0.5, 10),
            np.linspace(0, 1, 10),
            np.linspace(0.5, 0.5, 10),
        )
        fig.plot3D(
            np.linspace(0, 1, 10),
            np.linspace(0.5, 0.5, 10),
            np.linspace(0.5, 0.5, 10),
        )

        fig.set_xlim(0, 1)
        fig.set_ylim(0, 1)
        fig.set_zlim(0, 1)
        fig.set_xlabel(x, fontsize=20)
        fig.set_ylabel(y, fontsize=20)
        fig.set_zlabel(c, fontsize=20)
        fig.tick_params(axis="both", which="major", labelsize=15)
        fig.view_init(elev=20)


class BoxPlot(Plot):
    def __init__(self) -> None:
        super().__init__(scatter=False)

    def set_axes(self, x: str, y: str, df: pd.DataFrame, showfliers=True):

        graph = sns.boxplot(
            x=x,
            y=y,
            data=df,
            order=sorted(df[x].unique()),
            orient="v",
            showfliers=showfliers,
        )
        graph.axhline(0, linestyle="--", color="#A9A9A9")

        plt.xlabel(x, fontsize=16)
        plt.ylabel(y, fontsize=16)


class PlotFactory:
    def __init__(
        self, df: pd.DataFrame, emotion_keys: set[str], plot_dir: pathlib.Path
    ) -> None:
        self.df = df
        self.emotion_keys = emotion_keys
        self.plot_dir = plot_dir

    def make_wheel_playlist_boxplots(self, key_fmt: str, showfliers=True):

        for key in self.emotion_keys:
            bp = BoxPlot()
            bp.set_axes(
                "playlist",
                key_fmt.format(key),
                self.df,
                showfliers=showfliers,
            )
            bp.save_fig(self.plot_dir / (key_fmt.format(key) + ".png"))

    def make_sentiment_playlist_boxplot(self):

        bp = BoxPlot()
        bp.set_axes("playlist", "sentiment", self.df)
        bp.save_fig(self.plot_dir / "sentiment.png")

    def make_sentiment_emotion_playlist_boxplot(self):

        bp = BoxPlot()
        bp.set_axes("emotion_playlist", "sentiment", self.df, showfliers=False)
        bp.save_fig(self.plot_dir / "emotion_playlist.png")

    def make_sentiment_quadrant_playlist_boxplot(self):

        bp = BoxPlot()
        bp.set_axes("quadrant_playlist", "sentiment", self.df, showfliers=False)
        bp.save_fig(self.plot_dir / "quadrant_playlist.png")

    def make_va_scatter(self, c: str, set_limits=True):

        sc = Scatter()
        sc.set_axes("valence", "arousal", c, self.df, set_limits=set_limits)
        sc.save_fig(self.plot_dir / f"va_{c}_{set_limits}.png")

    def make_vad_scatter(self):

        sc3d = Scatter3D()
        sc3d.set_axes("valence", "arousal", "dominance", self.df)
        sc3d.save_fig(self.plot_dir / "vad.png")
