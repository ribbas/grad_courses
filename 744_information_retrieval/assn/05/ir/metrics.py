import bcubed


class Metrics:
    def __init__(self) -> None:
        self.out_dict = {}
        self.gold_dict = {}

    def convert_ds(self, gold, out):

        print(len(out), len(gold))
        if len(gold) < len(out):
            for _ in range(len(out) - len(gold)):
                out.pop()

        self.gold_dict = dict(enumerate(gold))
        self.out_dict = dict(enumerate(out))
        # print(self.out_dict[1299])
        # self.gold_dict = {f"i{idx}": val for idx, val in enumerate(gold)}
        # self.out_dict = {f"i{idx}": val for idx, val in enumerate(out)}

    def get_score(self):

        precision = bcubed.precision(self.out_dict, self.gold_dict)
        recall = bcubed.recall(self.out_dict, self.gold_dict)
        fscore = bcubed.fscore(precision, recall)

        print(fscore)
