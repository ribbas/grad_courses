from pprint import pprint

training = {
    "Travel": [
        "denver hospital administrator takes vacation in florida",
        "nurses plan a trip to florida",
        "employers offering more jobs with vacation benefits",
    ],
    "Business": [
        "employers see growth in information science",
        "hospital nurses in denver say high paying jobs are vanishing",
        "employers say florida is nice vacation spot and there are good jobs",
    ],
    "Health": [
        "study: more hospital nurses need to take a vacation",
        "local doctors attend florida conference on diabetes",
        "hospital trains maternity ward nurses",
        "denver hospital says local employers have jobs for nurses",
    ],
}


class_probs = [len(v) / 10 for v in training.values()]
class_names = ["Travel", "Business", "Health"]
terms = [
    "denver",
    "employers",
    "florida",
    "hospital",
    "jobs",
    "nurses",
    "vacation",
]
table = {}
for t in terms:
    table[t] = []
    for k, v in training.items():
        table[t].append(sum(i.count(t) for i in v) / len(v))


pprint(class_probs)
pprint(table)

best_class = {}
test1 = {"florida", "nurses", "vacation", "denver"}
test2 = {"jobs", "nurses", "florida", "hospital"}


def lol(test):

    for c in range(3):
        print(class_names[c], class_probs[c])
        print("--------------------------------------------")
        p = class_probs[c]
        for k, v in table.items():
            if k in test:
                print("yes", k, end="")
                print(f": {p} * {v[c]} = ", end="")
                p *= v[c]
                print(p)
            else:
                print("not", k, end="")
                print(f": {p} * (1 - {v[c]}) = ", end="")
                p = p * (1 - v[c])
                print(p)
        best_class[class_names[c]] = f"{p:e}"
        print("--------------------------------------------")


lol(test1)
pprint(best_class)

best_class = {}
lol(test2)
pprint(best_class)
