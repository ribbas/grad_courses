import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns


class Scatter:
    def __init__(self) -> None:

        self.ax = plt.figure(figsize=(16, 16)).add_subplot()

    def set_axes(self, valence, arousal, playlist, df, set_limits=True):

        graph = sns.scatterplot(
            x=valence, y=arousal, hue=playlist, data=df, alpha=0.5
        )
        graph.axhline(0.50, linestyle="--", color="#A9A9A9")
        graph.axvline(0.50, linestyle="--", color="#A9A9A9")

        if set_limits:
            self.ax.set_xlim(0, 1)
            self.ax.set_ylim(0, 1)
            plt.legend(
                prop={"size": 16},
            )

        self.ax.set_xlabel("valence", fontsize=16)
        self.ax.set_ylabel("arousal", fontsize=16)

    def save_fig(self, filename):

        plt.tight_layout()
        plt.savefig(filename)
        plt.close()


class Scatter3D:
    def __init__(self) -> None:

        self.ax = plt.figure(figsize=(16, 16)).add_subplot(projection="3d")

    def set_axes(self, valence, arousal, dominance, c):

        self.ax.scatter(valence, arousal, dominance, c=dominance)

        x = np.linspace(0.5, 0.5, 10)
        y = np.linspace(0, 1, 10)
        z = np.linspace(0.5, 0.5, 10)
        self.ax.plot3D(x, y, z)

        y = np.linspace(0.5, 0.5, 10)
        x = np.linspace(0, 1, 10)
        z = np.linspace(0.5, 0.5, 10)
        self.ax.plot3D(x, y, z)

        self.ax.set_xlim(0, 1)
        self.ax.set_ylim(0, 1)
        self.ax.set_zlim(0, 1)
        self.ax.set_xlabel("valence", fontsize=16)
        self.ax.set_ylabel("arousal", fontsize=16)
        self.ax.set_zlabel("dominance", fontsize=16)
        self.ax.view_init(elev=20)

    def save_fig(self, filename):

        plt.tight_layout()
        plt.savefig(filename)
        plt.close()


class BoxPlot:
    def __init__(self) -> None:
        plt.figure(figsize=(16, 9))

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

    def save_fig(self, filename):
        plt.tight_layout()
        plt.savefig(filename)
        plt.close()
