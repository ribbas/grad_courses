# aardvark    & 5 & 10 & 2 & 6 & 10 & 50
# bird        & 1 & 10 & 1 & 6 & 20 & 50
# dog         & 0 & 10 & 1 & 6 & 8  & 50

cs = 50
table = {
    "aardvark": {"tf_d1": 5, "L_d1": 10, "tf_d2": 2, "L_d2": 6, "cf_t": 10},
    "bird": {"tf_d1": 1, "L_d1": 10, "tf_d2": 1, "L_d2": 6, "cf_t": 20},
    "dog": {"tf_d1": 0, "L_d1": 10, "tf_d2": 1, "L_d2": 6, "cf_t": 8},
}

lamb = 0.4

query = ["aardvark", "bird", "dog", "dog"]


def prob(doc: int):

    score = 1
    if doc == 1:
        tf_d = "tf_d1"
        L_d = "L_d1"
    else:
        tf_d = "tf_d2"
        L_d = "L_d2"

    for t in query:
        print(f"({t},d{doc}):")
        print(
            f"""(1 - lambda)={(1 - lamb)}, cf_{t}={table[t]['cf_t']}, cs={cs}, lambda={lamb}, tf_({t},d{doc})={table[t][tf_d]}, L_d{doc}={table[t][L_d]}"""
        )
        tempscore = (1 - lamb) * table[t]["cf_t"] / cs + lamb * table[t][
            tf_d
        ] / table[t][L_d]
        print(
            f"""{(1 - lamb)} * {table[t]["cf_t"]} / {cs} + {lamb} * {table[t][tf_d]} / {table[t][L_d]} = {tempscore}"""
        )
        score *= tempscore

    return score


if __name__ == "__main__":
    print(f"{prob(1):e}")
    print("\n\n")
    print(f"{prob(2):e}")
