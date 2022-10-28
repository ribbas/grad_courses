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
plt.xlabel("Ratio of Positive to Negative Class Weight", size=12)
plt.ylabel("Mean F1-score", size=12)
plt.title(
    "Mean F1-scores with Various Combinations of Class Weight Ratios, Tokenization Methods, and Stop Words Lists",
    size=16,
)

plt.legend(
    [
        "No stemmer, no stop words",
        "Snowball stemmer, no stop words",
        "Porter stemmer, no stop words",
        "Snowball stemmer, custom stop words",
        "Porter stemmer, custom stop words",
        "Snowball stemmer, sklearn stop words",
        "Porter stemmer, sklearn stop words",
    ],
    prop={"size": 12},
)
plt.tight_layout()
plt.savefig("report/statics/cv.png")
