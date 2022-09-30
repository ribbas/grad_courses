from collections import Counter

from .types import generator, counter


class Lexer:
    def __init__(self) -> None:

        self.tf: counter = Counter()
        self.df: counter = Counter()
        self.tf_in_doc: counter = Counter()

    def add(self, tokens: generator[str]) -> None:

        # create a Counter for the document
        self.tf_in_doc.clear()
        self.tf_in_doc.update(tokens)

        # update the total term-frequency values with the Counter
        self.tf.update(self.tf_in_doc)

        # increment the document-frequency values
        self.df.update(self.tf_in_doc.keys())

    def term_doc_tf(self, doc_id: str) -> generator[tuple[str, str, int]]:

        for term in self.tf_in_doc:
            yield term, doc_id, self.tf_in_doc[term]

    def set_tf(self, tf: counter) -> None:

        self.tf = tf

    def set_df(self, df: counter) -> None:

        self.df = df

    def get_tf(self) -> counter:

        return self.tf

    def get_df(self) -> counter:

        return self.df

    def get_collection_size(self) -> int:

        return self.tf.total()

    def get_vocab_size(self) -> int:

        return len(self.tf)

    def get_top_n_tf_df(self, n: int) -> generator[tuple[str, int, int]]:

        top_n_tf = self.tf.most_common(n)
        for tf in top_n_tf:
            term, freq = tf
            yield term, freq, self.df[term]

    def get_nth_freq_term(self, n: int) -> tuple[str, int, int]:

        term, freq = self.tf.most_common(n)[-1]
        return term, freq, self.df[term]

    def get_single_occs(self) -> int:

        single_occs: int = 0
        for df in self.df.values():
            if df == 1:
                single_occs += 1

        return single_occs
