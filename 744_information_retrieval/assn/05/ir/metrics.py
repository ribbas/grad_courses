class Metrics:
    def __init__(self) -> None:
        self.diff_set = set[frozenset[int]]

    @staticmethod
    def difference_union(
        set1: frozenset[int], set2: frozenset[int]
    ) -> frozenset[int]:

        return set1.difference(set2).union(set2.difference(set1))

    def convert_ds(self, gold: set[frozenset[int]], out: set[frozenset[int]]):

        self.gold_diff_out = gold.difference(out)
        self.out_diff_gold = out.difference(gold)

        for idx, gold_cluster in enumerate(self.gold_diff_out):
            for elem in gold_cluster:
                for idx2, out_cluster in enumerate(self.out_diff_gold):
                    if elem in out_cluster:
                        print(
                            gold_cluster,
                            out_cluster,
                            self.difference_union(
                                gold_cluster,
                                out_cluster,
                            ),
                        )

        # self.gold_dict = dict(enumerate(gold))
        # self.out_dict = dict(enumerate(out))
        # print(self.out_dict[1299])
        # self.gold_dict = {f"i{idx}": val for idx, val in enumerate(gold)}
        # self.out_dict = {f"i{idx}": val for idx, val in enumerate(out)}

    # def get_score(self):

    #     precision = bcubed.precision(self.out_dict, self.gold_dict)
    #     recall = bcubed.recall(self.out_dict, self.gold_dict)
    #     fscore = bcubed.fscore(precision, recall)

    #     print(fscore)
