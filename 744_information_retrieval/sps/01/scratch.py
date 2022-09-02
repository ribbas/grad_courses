class Dictionary:
    def __init__(self) -> None:

        self.doc_id_cur: int = 0
        self.dictionary: dict[str, list[int]] = {}

    def add(self, doc) -> None:

        doc = doc.lower().split()

        self.doc_id_cur += 1
        for i in doc:
            if i in self.dictionary:
                if self.doc_id_cur not in self.dictionary[i]:
                    self.dictionary[i].append(self.doc_id_cur)
            else:
                self.dictionary[i] = [self.doc_id_cur]

    def get(self):

        return self.dictionary

    @staticmethod
    def docID(postings):

        return postings[0]

    def postings(self, term):

        p = self.dictionary[term].copy()
        return p

    @staticmethod
    def next(postings):

        postings.pop(0)
        return postings


def intersect(p1, p2):

    answer = set()
    while p1 and p2:
        if dic.docID(p1) == dic.docID(p2):
            answer.add(dic.docID(p1))
            p1 = dic.next(p1)
            p2 = dic.next(p2)

        else:
            if dic.docID(p1) < dic.docID(p2):
                p1 = dic.next(p1)
            else:
                p2 = dic.next(p2)

    return answer


doc1 = "breakthrough drug for schizophrenia"
doc2 = "new schizophrenia drug"
doc3 = "new approach for treatment of schizophrenia"
doc4 = "new hopes for schizophrenia patients"

dic = Dictionary()
dic.add(doc1)
dic.add(doc2)
dic.add(doc3)
dic.add(doc4)

t1 = "schizophrenia"
t2 = "drug"

p1 = dic.postings(t1)
p2 = dic.postings(t2)
print(p1, p2)

# schizophrenia AND drug
# expecting {1, 2}
print(t1, "AND", t2)
print(intersect(p1, p2))


def difference(p1, p2):

    answer = set()
    while p1:
        if dic.docID(p1) == dic.docID(p2):
            p1 = dic.next(p1)
            p2 = dic.next(p2)

        else:
            if dic.docID(p1) < dic.docID(p2):
                answer.add(dic.docID(p1))
                p1 = dic.next(p1)
            else:
                p2 = dic.next(p2)

        if not p2:
            while p1:
                answer.add(dic.docID(p1))
                p1 = dic.next(p1)

    return answer


p1 = dic.postings(t1)
p2 = dic.postings(t2)


# schizophrenia AND NOT drug
# expecting {3, 4}
print(t1, "AND NOT", t2)
print(difference(p1, p2))
