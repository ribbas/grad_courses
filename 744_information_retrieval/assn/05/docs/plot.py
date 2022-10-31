from matplotlib import pyplot as plt
import pandas as pd

# Set the figure size
plt.figure(figsize=(16, 9))

# Make a list of columns
columns = ["weight", "tokenization", "score"]

# Read a CSV file
df = pd.read_csv("outputs/cross_validations.csv", usecols=columns)

# Plot the lines
df.set_index("weight", inplace=True)
df1 = df.groupby("tokenization")["score"]
df1.plot(
    x="weight",
    style="o",
    markersize=10,
    legend=True,
)
plt.xlabel("Ratio of Positive to Negative Class Weight", size=16)
plt.ylabel("Mean F1-score", size=16)

plt.legend(
    [
        "No stemming, no stop words",
        "Snowball, no stop words",
        "Porter, no stop words",
        "Snowball, custom stop words",
        "Porter, custom stop words",
        "Snowball, sklearn stop words",
        "Porter, sklearn stop words",
    ],
    bbox_to_anchor=(1.01, 1),
    prop={"size": 16},
)
plt.tight_layout()
plt.savefig("report/statics/cv.png")
