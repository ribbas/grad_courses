import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import pandas as pd


class Scatter:
    def __init__(self) -> None:

        plt.figure(figsize=(16, 9))
        self.ax = plt.figure().add_subplot()

    def set_axes(self, x, y, z, df):

        graph = sns.scatterplot(x=x, y=y, hue=z, data=df)
        graph.axhline(0.50, linestyle="--", color="#A9A9A9")
        graph.axvline(0.50, linestyle="--", color="#A9A9A9")

    def save_fig(self, filename):
        # Make legend, set axes limits and labels
        # self.ax.legend()
        self.ax.set_xlim(0, 1)
        self.ax.set_ylim(0, 1)
        self.ax.set_xlabel("valence")
        self.ax.set_ylabel("arousal")

        plt.tight_layout()
        plt.savefig(filename)
        plt.close()


class Scatter3D:
    def __init__(self) -> None:

        self.ax = plt.figure().add_subplot(projection="3d")

    def set_axes(self, x, y, z):

        self.ax.scatter(x, y, z, c=z)

        x = np.linspace(0.5, 0.5, 10)
        y = np.linspace(0, 1, 10)
        z = np.linspace(0.5, 0.5, 10)
        self.ax.plot3D(x, y, z)

        y = np.linspace(0.5, 0.5, 10)
        x = np.linspace(0, 1, 10)
        z = np.linspace(0.5, 0.5, 10)
        self.ax.plot3D(x, y, z)

    def save_fig(self, filename):

        # self.ax.legend()
        self.ax.set_xlim(0, 1)
        self.ax.set_ylim(0, 1)
        self.ax.set_zlim(0, 1)
        self.ax.set_xlabel("X")
        self.ax.set_ylabel("Y")
        self.ax.set_zlabel("Z")

        self.ax.view_init(elev=20.0, azim=-35, roll=0)
        plt.tight_layout()
        plt.savefig(filename)
        plt.close()


class BoxPlot:
    def __init__(self) -> None:
        plt.figure(figsize=(16, 9))

    def set_axes(self, y: str, df: pd.DataFrame):

        sns.boxplot(x="playlist", y=y, data=df, orient="v")

    def save_fig(self, filename):
        plt.tight_layout()
        plt.savefig(filename)
        plt.close()
