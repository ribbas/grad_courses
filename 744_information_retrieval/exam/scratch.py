from sklearn.metrics import precision_score


def precision():

    y_true = [0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2]
    y_pred = [0, 0, 2, 1, 1, 2, 0, 1, 2, 2, 2, 0]

    print(precision_score(y_true, y_pred, average="micro"))
    print(precision_score(y_true, y_pred, average="macro"))


precision()
