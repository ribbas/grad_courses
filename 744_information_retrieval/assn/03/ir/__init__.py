import heapq
from pathlib import Path
from itertools import groupby

from .files import DataFile, Formatter, IO
from .invertedfile import InvertedFile
from .lexer import Lexer
from .normalize import Normalizer
from .packer import Packer
from .retriever import Retriever
from .types import Any, generator, counter


class InformationRetrieval:
    def __init__(self) -> None:

        self.data: DataFile
        self.invf: InvertedFile

        self.df: counter
        self.cf: counter
        self.tid: dict[int | str, int | str] = {}
        self.doc_terms: dict[int, list[int]] = {}

        self.num_docs: int = 0
        self.loaded = False
        self.term_doc_tf_str: str = ""

    def set_filename(self, filename: Path) -> None:

        self.data = DataFile(filename)

    def load_freqs(self) -> None:

        self.df = IO.read_json(self.data.df_file)
        self.cf = IO.read_json(self.data.tf_file)
        self.tid = IO.read_json(self.data.tid_file)

        self.term_doc_tf_str = IO.read(self.data.tdt_file)
        self.loaded = True

    def generate_freqs(self) -> None:

        prep = Normalizer()
        lex = Lexer()

        term_doc_tf: list[tuple[str, str, int]] = []
        self.data.ingest(prep, lex, term_doc_tf)
        lex.build_term_idx()
        self.tid = lex.get_term_idx()
        self.doc_terms = {
            k: [self.tid[i[0]] for i in g]
            for k, g in groupby(term_doc_tf, lambda x: x[1])
        }

        self.df = lex.get_df()
        self.cf = lex.get_cf()
        self.term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
        self.loaded = True

    def generate_stats(self) -> None:

        if self.loaded:
            lex = Lexer()
            lex.set_df(self.df)
            lex.set_cf(self.cf)
            contents: str = Formatter.format_stats(lex, self.data.num_docs)
            IO.dump(self.data.stats_file, contents)
        else:
            raise AttributeError("Data not generated yet")

    def dump_freqs(self) -> None:

        if self.loaded:
            IO.dump(self.data.tdt_file, self.term_doc_tf_str)
            IO.dump_json(self.data.df_file, self.df)
            IO.dump_json(self.data.tf_file, self.cf)
            IO.dump_json(self.data.tid_file, self.tid)
            IO.dump_json(self.data.doc_terms_file, self.doc_terms)
            IO.dump_json(self.data.meta_file, {"num_docs": self.data.num_docs})
        else:
            raise AttributeError("Data not generated yet")

    def build_sorted_tdt(self) -> None:

        if self.loaded:
            invf = InvertedFile()
            invf.build_dict(self.df, self.cf)
            mapped_tdt_chunks = invf.sort_mapped_tdt(self.term_doc_tf_str)
            chunk_filenames: list[str] = []
            for idx, mapped_tdt_chunk in enumerate(mapped_tdt_chunks):

                chunk_filenames.append(
                    f"{self.data.sorted_tdt_chunk_file}{idx}"
                )
                IO.dumplines(
                    chunk_filenames[-1],
                    (
                        " ".join(str(s) for s in l) + "\n"
                        for l in mapped_tdt_chunk
                    ),
                )

            chunks: Any = []
            for filename in chunk_filenames:
                chunks.append(open(f"{filename}.txt", "r"))

            IO.dumplines(
                self.data.sorted_tdt_file,
                heapq.merge(*chunks, key=lambda k: int(k.split()[0])),
            )

            for chunk_files in chunks:
                chunk_files.close()

    def encode_inverted_file(self) -> None:

        if self.loaded:
            invf = InvertedFile()
            invf.build_dict(self.df, self.cf)

            mapped_tdt_str = IO.read(self.data.sorted_tdt_file)[:-1]
            mapped_tdt = (v.split(" ") for v in mapped_tdt_str.split("\n"))
            mapped_tdt = (
                (int(i[0]), int(i[1]), int(i[2]), str(i[3])) for i in mapped_tdt
            )
            invf.convert(mapped_tdt)

            inv_file = invf.get_inverted_file_raw()
            if_data = Packer.encode(inv_file)
            IO.dump_bin(self.data.inv_file, if_data)
            IO.dump_json(self.data.dict_file, invf.get_dictionary())

        else:
            raise AttributeError("Data not generated yet")

    def load_inverted_file(self) -> None:

        self.invf = InvertedFile()
        inv_file = IO.read_bin(self.data.inv_file)
        dictionary = IO.read_json(self.data.dict_file)
        self.num_docs = IO.read_json(self.data.meta_file)["num_docs"]
        self.invf.set_inverted_file_bytes(inv_file)
        self.invf.set_dictionary(dictionary)

    def read_inverted_file(
        self, tokens: generator[str]
    ) -> list[dict[str, float]]:

        self.doc_terms = IO.read_json(self.data.doc_terms_file)
        self.tid = IO.read_json(self.data.tid_file)

        retr = Retriever(self.invf, self.num_docs, self.doc_terms, self.tid)

        retr.query(list(tokens))
        return retr.get_rankings()

    def normalize_test_terms(self, terms: tuple[str, ...]) -> generator[str]:

        prep = Normalizer()
        prep.set_document(" ".join(terms) + " ")
        prep.process()

        return prep.get_tokens()
