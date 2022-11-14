from matplotlib import pyplot as plt
import pandas as pd

# Set the figure size
plt.figure(figsize=(16, 9))

x = [30, 100, 300, 1_000, 3_000, 10_000, 30_000]
y = [0.38, 4.82, 11.14, 42.22, 170.38, 1198.42, 4132.88]

df = pd.DataFrame({"documents": x, "time": y})

# Plot the lines
df.plot(
    x="documents",
    style="o",
    legend=False,
    logx=True,
    logy=True,
)
plt.xlabel("Number of document comparisons (log)", size=16)
plt.ylabel("Execution times (log)", size=16)

plt.xticks(x, x)

plt.tight_layout()
plt.savefig("docs/statics/times.png")
