class Metrics:
    def score(
        self, gold: set[frozenset[int]], out: set[frozenset[int]]
    ) -> tuple[int, int]:

        self.gold_diff_out = gold.difference(out)
        self.out_diff_gold = out.difference(gold)

        return (len(self.gold_diff_out), len(self.out_diff_gold))
