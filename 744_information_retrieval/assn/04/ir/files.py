import heapq
from pathlib import Path
import pickle

from pprint import pprint

from .const import FIELDS, FIELD_DELIM, LIST_DELIM, JHED
from .lexer import Lexer, LexerStatistics
from .normalize import Normalizer
from .types import Any, iterable, text_io, generator


class DataFile:
    def __init__(self, filename: Path) -> None:

        self.prep = Normalizer()
        self.filename: Path = filename
        self.num_docs: int = 0
        self.doc_begin_tag: str = ""
        self.doc_end_tag: str = ""

    def _ingest(self, doc_id: int, prep: Normalizer, *args: Any) -> None:
        raise NotImplementedError

    @staticmethod
    def __map_list(field: str) -> list[str]:

        return field.split(LIST_DELIM)

    def __map_to_fields(self, line: str) -> dict[str, Any]:

        mapped_field: dict[str, Any] = dict(
            zip(FIELDS, line.split(FIELD_DELIM))
        )

        # assessment
        mapped_field["Assessment"] = int(mapped_field["Assessment"])

        # title
        mapped_field["Title"] = " ".join(
            self.prep.process(mapped_field["Title"])
        )

        # authors
        mapped_field["Authors"] = self.__map_list(mapped_field["Authors"])

        # journal
        mapped_field["Journal"] = self.__map_list(mapped_field["Journal"])

        # ISSN
        mapped_field["ISSN"] = self.__map_list(mapped_field["ISSN"])

        # year
        if mapped_field["Year"]:
            if not (" " in mapped_field["Year"] or "-" in mapped_field["Year"]):
                mapped_field["Year"] = int(mapped_field["Year"])

        mapped_field["Abstract"] = " ".join(
            self.prep.process(mapped_field["Abstract"])
        )

        # keywords
        mapped_field["Keywords"] = self.__map_list(mapped_field["Keywords"])
        mapped_field["Keywords"] = [
            " ".join(self.prep.process(doc)) for doc in mapped_field["Keywords"]
        ]
        return mapped_field

    def ingest(self, *args: Any) -> None:

        docs: list[dict[str, Any]] = []

        with open(self.filename) as fp:
            for line in fp:

                if line:
                    docs.append(self.__map_to_fields(line[:-1]))
                    self.num_docs += 1

        pprint(docs[:10])


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
    def dump_sorted_chunks(filename: str, chunk_filenames: list[str]) -> None:

        chunks: list[text_io] = []
        for chunk_filename in chunk_filenames:
            chunks.append(IO.open_file(chunk_filename))

        with open(f"{filename}.txt", "w") as fp:
            fp.writelines(heapq.merge(*chunks, key=lambda k: int(k.split()[0])))

        for chunk_files in chunks:
            chunk_files.close()

    @staticmethod
    def dump(filename: str, data: str) -> None:

        with open(f"{filename}.txt", "w") as fp:
            fp.write(data)
        print(f"Dumped to '{filename}.txt'")

    @staticmethod
    def read_pickle(filename: str) -> Any:

        with open(f"{filename}.pickle", "rb") as fp:
            return pickle.load(fp)

    @staticmethod
    def dump_pickle(filename: str, data: Any) -> None:

        with open(f"{filename}.pickle", "wb") as fp:
            pickle.dump(data, fp, protocol=pickle.HIGHEST_PROTOCOL)
        print(f"Dumped Pickle to '{filename}.pickle'")

    @staticmethod
    def read_bin(filename: str) -> bytes:

        with open(f"{filename}.bin", "rb") as fp:
            return fp.read()

    @staticmethod
    def dump_bin(filename: str, data: bytes) -> None:

        with open(f"{filename}.bin", "wb") as fp:
            fp.write(data)
        print(f"Dumped binary to '{filename}.bin'")


class Formatter:

    hr: str = "------------------------------\n"
    table_header: str = f"{'Word':<12} | {'TF':<6} | {'DF':<6}\n{hr}"

    @staticmethod
    def __format_tf_df(term: str, tf: int, df: int) -> str:

        return f"{term:<12} | {tf:<6} | {df:<6}\n"

    @staticmethod
    def format_stats(lex_stats: LexerStatistics, num_docs: int = 0) -> str:

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
    def format_term_doc_tf(term_doc_tf: list[tuple[str, int, int]]) -> str:

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


class QueryFile(DataFile):
    def __init__(self, filename: Path) -> None:

        super().__init__(filename)

        self.doc_begin_tag: str = "<Q ID="
        self.doc_end_tag: str = "</Q>"

    def _ingest(
        self, doc_id: int, prep: Normalizer, tokens: dict[int, generator[str]]
    ) -> None:

        tokens[doc_id] = prep.get_tokens()


class CorpusFile(DataFile):
    def __init__(self, filename: Path) -> None:

        super().__init__(filename)

        self.doc_begin_tag: str = "<P ID="
        self.doc_end_tag: str = "</P>"

        self.df_file: str = f"outputs/stats/{filename.stem}_df"
        self.cf_file: str = f"outputs/stats/{filename.stem}_cf"
        self.len_file: str = f"outputs/stats/{filename.stem}_len"
        self.stats_file: str = f"outputs/stats/{filename.stem}_summary"
        self.ranking_file: str = f"outputs/stats/{filename.stem}_rank"
        self.dict_file: str = f"outputs/stats/{filename.stem}_dict"

        self.meta_file: str = f"outputs/tmp/{filename.stem}_ndocs"
        self.tdt_file: str = f"outputs/tmp/{filename.stem}_tdt"
        self.sorted_tdt_chunk_file: str = f"outputs/tmp/{filename.stem}_chunk_"
        self.sorted_tdt_file: str = f"outputs/tmp/{filename.stem}_sort"

        self.inv_file: str = f"outputs/bin/{filename.stem}_if"

    def _ingest(
        self,
        doc_id: int,
        prep: Normalizer,
        lex: Lexer,
        term_doc_tf: list[tuple[str, int, int]],
    ) -> None:

        # add processed tokens to the lexer
        lex.add(prep.get_tokens())

        # save records of term-DocID-tf
        term_doc_tf.extend(lex.get_term_docid_tf(doc_id))
