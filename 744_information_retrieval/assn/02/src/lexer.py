from collections import Counter
from typing import Generator


class Lexer:
    def __init__(self) -> None:

        self.tf: Counter[str] = Counter()
        self.df: Counter[str] = Counter()
        self.tf_in_doc: Counter[str] = Counter()

    def add(self, tokens: list[str]) -> None:

        self.tf_in_doc.clear()
        self.tf_in_doc.update(tokens)
        self.tf.update(self.tf_in_doc)
        self.df.update(self.tf_in_doc.keys())

    def vocabulary(self) -> list[str]:

        return sorted(self.tf.keys())

    def term_doc_tf(
        self, doc_id: str
    ) -> Generator[tuple[str, str, int], None, None]:

        for term in self.tf_in_doc:
            yield term, doc_id, self.tf_in_doc[term]

    def get_tf(self) -> Counter[str]:

        return self.tf

    def get_df(self) -> Counter[str]:

        return self.df

    def get_collection_size(self) -> int:

        return self.tf.total()

    def get_vocab_size(self) -> int:

        return len(self.tf)

    def get_top_n_tf_df(
        self, n: int
    ) -> Generator[tuple[str, int, int], None, None]:

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
