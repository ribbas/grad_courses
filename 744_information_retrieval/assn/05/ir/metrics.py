class Metrics:
    def __init__(self) -> None:
        self.diff_set = set[frozenset[int]]

    def score(self, gold: set[frozenset[int]], out: set[frozenset[int]]) -> int:

        self.gold_diff_out = gold.difference(out)
        self.out_diff_gold = out.difference(gold)

        for gold_cluster in self.gold_diff_out:
            for elem in gold_cluster:
                for out_cluster in self.out_diff_gold:
                    if elem in out_cluster:
                        print(gold_cluster, out_cluster)

        return min(len(self.gold_diff_out), len(self.out_diff_gold))
