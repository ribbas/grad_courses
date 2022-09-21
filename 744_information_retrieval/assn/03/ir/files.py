import json
from pathlib import Path
from typing import Any

from .lexer import Lexer
from .normalize import Normalizer


class IO:
    @staticmethod
    def read(filename: str) -> str:

        with open(f"{filename}.txt") as fp:
            return fp.read()

    @staticmethod
    def dumplines(filename: str, data: str) -> None:

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


class DataFile:
    def __init__(self, filename: Path) -> None:

        self.filename: Path = filename
        self.num_docs: int = 0

        self.df_file_name: str = f"stats/{filename.stem}_df"
        self.tf_file_name: str = f"stats/{filename.stem}_tf"
        self.stats_file_name: str = f"stats/{filename.stem}_stats"

        self.tdt_file_name: str = f"tmp/{filename.stem}_tdt"
        self.sort_tdt_chunk: str = f"tmp/{filename.stem}_chunk_"
        self.sort_tdt: str = f"tmp/{filename.stem}_sort"

        self.inv_file_name: str = f"bin/{filename.stem}_if"
        self.dict_name: str = f"bin/{filename.stem}_dict"

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

                        if self.num_docs % 10000 == 0:
                            print("Processed", self.num_docs, "documents.")

                        prep.set_document(doc)
                        prep.process()

                        # add processed tokens to the lexer
                        lex.add(prep.get_tokens())

                        # save records of term-DocID-tf
                        term_doc_tf.extend(lex.term_doc_tf(doc_id))

                        doc = ""

                    else:
                        doc += line

        print("Processed", self.num_docs, "documents.")


class Formatter:

    hr: str = "------------------------------\n"
    table_header: str = f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n{hr}"

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}\n"

    @staticmethod
    def format_stats(lex: Lexer, num_docs: int = 0) -> str:

        contents: str = ""

        contents += f"{Formatter.hr}"
        contents += f"{num_docs} documents.\n"

        contents += f"{Formatter.hr}"
        contents += f"Collections size: {lex.get_collection_size()}\n"
        contents += f"Vocabulary size: {lex.get_vocab_size()}\n"
        contents += f"\n{Formatter.hr}"

        contents += "Top 100 most frequent words:\n"
        contents += Formatter.table_header
        for term in lex.get_top_n_tf_df(100):
            contents += Formatter.__format_tf_df(*term)

        contents += f"\n{Formatter.hr}"
        contents += "500th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex.get_nth_freq_term(500))

        contents += f"\n{Formatter.hr}"
        contents += "1000th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex.get_nth_freq_term(1000))

        contents += f"\n{Formatter.hr}"
        contents += "5000th word:\n"
        contents += Formatter.table_header
        contents += Formatter.__format_tf_df(*lex.get_nth_freq_term(5000))

        contents += f"\n{Formatter.hr}"
        single_occs: int = lex.get_single_occs()
        contents += "Number of words that occur in exactly one document:\n"
        contents += f"{single_occs} ({round(single_occs / lex.get_vocab_size() * 100, 2)}%)\n"

        return contents

    @staticmethod
    def format_term_doc_tf(term_doc_tf: list[tuple[str, str, int]]) -> str:

        contents: str = ""
        for line in term_doc_tf:
            contents += " ".join(str(i) for i in line) + "\n"

        return contents
