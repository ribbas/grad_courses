import json
from pathlib import Path

from .const import DOC_PROC, JHED
from .lexer import Lexer, LexerStatistics
from .normalize import Normalizer
from .types import Any, iterable, text_io, generator


class IO:
    @staticmethod
    def open_file(filename: str) -> text_io:

        return open(f"{filename}.txt")

    @staticmethod
    def read(filename: str) -> str:

        with open(f"{filename}.txt") as fp:
            return fp.read()

    @staticmethod
    def dumplines(filename: str, data: iterable) -> None:

        with open(f"{filename}.txt", "w") as fp:
            fp.writelines(data)
        print(f"Dumped to '{filename}.txt'")

    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(f"{filename}.txt", "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}.txt'")

    @staticmethod
    def read_json(filename: str) -> Any:

        with open(f"{filename}.json") as fp:
            return json.loads(fp.read())

    @staticmethod
    def dump_json(filename: str, data: Any) -> None:

        with open(f"{filename}.json", "w") as fp:
            json.dump(data, fp)
        print(f"Dumped json to '{filename}.json'")

    @staticmethod
    def read_bin(filename: str) -> bytes:

        with open(f"{filename}.bin", "rb") as fp:
            return fp.read()

    @staticmethod
    def dump_bin(filename: str, data: bytes) -> None:

        with open(f"{filename}.bin", "wb") as fp:
            fp.write(data)
        print(f"Dumped binary to '{filename}.bin'")


class QueryFile:
    def __init__(self, filename: Path) -> None:

        self.filename: Path = filename
        self.num_docs: int = 0

    def ingest(self, prep: Normalizer) -> dict[int, generator[str]]:

        doc_id: int = -1
        doc: str = ""
        tokens: dict[int, generator[str]] = {}

        with open(self.filename) as fp:
            for line in fp:

                if line:
                    if "<Q ID=" in line:
                        doc_id = int(line[6:-2])
                        self.num_docs += 1

                    elif "</Q>" in line:

                        prep.set_document(doc)
                        prep.process()
                        tokens[doc_id] = prep.get_tokens()

                        doc = ""

                    else:
                        doc += line

        return tokens


class DataFile:
    def __init__(self, filename: Path) -> None:

        self.filename: Path = filename
        self.num_docs: int = 0

        self.df_file: str = f"stats/{filename.stem}_df"
        self.tf_file: str = f"stats/{filename.stem}_tf"
        self.len_file: str = f"stats/{filename.stem}_len"
        self.cf_file: str = f"stats/{filename.stem}_cf"
        self.stats_file: str = f"stats/{filename.stem}_stats"
        self.meta_file: str = f"stats/{filename.stem}_meta"
        self.ranking_file: str = f"stats/ED5859-{filename.stem}"

        self.tdt_file: str = f"tmp/{filename.stem}_tdt"
        self.sorted_tdt_chunk_file: str = f"tmp/{filename.stem}_chunk_"
        self.sorted_tdt_file: str = f"tmp/{filename.stem}_sort"

        self.inv_file: str = f"bin/{filename.stem}_if"
        self.dict_file: str = f"bin/{filename.stem}_dict"

    def ingest(
        self,
        prep: Normalizer,
        lex: Lexer,
        term_doc_tf: list[tuple[str, str, int]],
    ) -> None:

        doc_id: str = ""
        doc: str = ""

        with open(self.filename) as fp:
            for line in fp:

                if line:
                    if "<P ID=" in line:
                        doc_id = line[6:-2]
                        self.num_docs += 1

                    elif "</P>" in line:

                        prep.set_document(doc)
                        prep.process()

                        # add processed tokens to the lexer
                        lex.add(prep.get_tokens())

                        # save records of term-DocID-tf
                        term_doc_tf.extend(lex.get_term_docid_tf(doc_id))

                        doc = ""

                        if self.num_docs % DOC_PROC == 0:
                            print("Normalized", self.num_docs, "documents")

                    else:
                        doc += line

        print("Normalized", self.num_docs, "documents")


class Formatter:

    hr: str = "------------------------------\n"
    table_header: str = f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n{hr}"

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}\n"

    @staticmethod
    def format_stats(lex: Lexer, num_docs: int = 0) -> str:

        lex_stats = LexerStatistics(lex)

        contents: str = ""

        contents += f"{Formatter.hr}"
        contents += f"{num_docs} documents.\n"

        contents += f"{Formatter.hr}"
        contents += f"Collections size: {lex_stats.get_collection_size()}\n"
        contents += f"Vocabulary size: {lex_stats.get_vocab_size()}\n"
        contents += f"\n{Formatter.hr}"

        contents += "Top 100 most frequent words:\n"
        contents += Formatter.table_header
        for term in lex_stats.get_top_n_cf_df(100):
            contents += Formatter.__format_tf_df(*term)

        contents += f"\n{Formatter.hr}"
        contents += "500th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex_stats.get_nth_freq_term(500))

        contents += f"\n{Formatter.hr}"
        contents += "1000th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex_stats.get_nth_freq_term(1000))

        contents += f"\n{Formatter.hr}"
        contents += "5000th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex_stats.get_nth_freq_term(5000))

        contents += f"\n{Formatter.hr}"
        single_occs: int = lex_stats.get_single_occs()
        contents += "Number of words that occur in exactly one document:\n"
        contents += f"{single_occs} ({round(single_occs / lex_stats.get_vocab_size() * 100, 2)}%)\n"

        return contents

    @staticmethod
    def format_term_doc_tf(term_doc_tf: list[tuple[str, str, int]]) -> str:

        contents: str = ""
        for line in term_doc_tf:
            contents += " ".join(str(i) for i in line) + "\n"

        return contents

    @staticmethod
    def format_rankings(
        all_rankings: dict[int, list[tuple[int, float]]]
    ) -> str:

        contents: str = ""
        for query_id, rankings in all_rankings.items():
            contents += (
                "\n".join(
                    f"{query_id} Q0 {doc_id} {rank + 1} {score:.6f} {JHED}"
                    for rank, (doc_id, score) in enumerate(rankings)
                )
                + "\n"
            )

        return contents
