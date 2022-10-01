import heapq
from pathlib import Path

from .files import DataFile, Formatter, IO
from .invertedfile import InvertedFile
from .lexer import Lexer
from .normalize import Normalizer
from .packer import Packer
from .retriever import Retriever
from .types import Any, generator, counter

from itertools import groupby


class InformationRetrieval:
    def __init__(self) -> None:

        self.data: DataFile
        self.df: counter
        self.tf: counter
        self.num_docs: int = 0
        self.loaded = False
        self.term_doc_tf_str: str = ""
        self.term_docs: str = ""
        self.invf: InvertedFile

    def set_filename(self, filename: Path) -> None:

        self.data = DataFile(filename)

    def load_freqs(self) -> None:

        self.df = IO.read_json(self.data.df_file_name)
        self.tf = IO.read_json(self.data.tf_file_name)

        self.term_doc_tf_str = IO.read(self.data.tdt_file_name)
        self.loaded = True

    def generate_freqs(self) -> None:

        prep = Normalizer()
        lex = Lexer()

        term_doc_tf: list[tuple[str, str, int]] = []
        self.data.ingest(prep, lex, term_doc_tf)
        self.term_docs = "\n".join(
            " ".join(i[0] for i in g)
            for _, g in groupby(term_doc_tf, lambda x: x[1])
        )

        self.df = lex.get_df()
        self.tf = lex.get_tf()
        self.term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
        self.loaded = True

    def generate_stats(self) -> None:

        if self.loaded:
            lex = Lexer()
            lex.set_df(self.df)
            lex.set_tf(self.tf)
            contents: str = Formatter.format_stats(lex, self.data.num_docs)
            IO.dump(self.data.stats_file_name, contents)
        else:
            raise AttributeError("Data not generated yet")

    def dump_freqs(self) -> None:

        if self.loaded:
            IO.dump(self.data.tdt_file_name, self.term_doc_tf_str)
            IO.dump(self.data.doc_terms, self.term_docs)
            IO.dump_json(self.data.df_file_name, self.df)
            IO.dump_json(self.data.tf_file_name, self.tf)
            IO.dump_json(
                self.data.meta_file_name, {"num_docs": self.data.num_docs}
            )
        else:
            raise AttributeError("Data not generated yet")

    def build_sorted_tdt(self) -> None:

        if self.loaded:
            invf = InvertedFile()
            invf.build_dict(self.df, self.tf)
            mapped_tdt_chunks = invf.sort_mapped_tdt(self.term_doc_tf_str)
            chunk_filenames: list[str] = []
            for idx, mapped_tdt_chunk in enumerate(mapped_tdt_chunks):

                chunk_filenames.append(f"{self.data.sort_tdt_chunk}{idx}")
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
                self.data.sort_tdt,
                heapq.merge(*chunks, key=lambda k: int(k.split()[0])),
            )

            for chunk_files in chunks:
                chunk_files.close()

    def encode_inverted_file(self) -> None:

        if self.loaded:
            invf = InvertedFile()
            invf.build_dict(self.df, self.tf)

            mapped_tdt_str = IO.read(self.data.sort_tdt)[:-1]
            mapped_tdt = (v.split(" ") for v in mapped_tdt_str.split("\n"))
            mapped_tdt = (
                (int(i[0]), int(i[1]), int(i[2]), str(i[3])) for i in mapped_tdt
            )
            invf.convert(mapped_tdt)

            inv_file = invf.get_inverted_file_raw()
            if_data = Packer.encode(inv_file)
            IO.dump_bin(self.data.inv_file_name, if_data)
            IO.dump_json(self.data.dict_name, invf.get_dictionary())

        else:
            raise AttributeError("Data not generated yet")

    def load_inverted_file(self) -> None:

        self.invf = InvertedFile()
        inv_file = IO.read_bin(self.data.inv_file_name)
        dictionary = IO.read_json(self.data.dict_name)
        self.num_docs = IO.read_json(self.data.meta_file_name)["num_docs"]
        self.invf.set_inverted_file_bytes(inv_file)
        self.invf.set_dictionary(dictionary)

    def read_inverted_file(
        self, tokens: generator[str]
    ) -> list[dict[str, float]]:

        doc_vocabs: str = IO.read(self.data.doc_terms)

        retr = Retriever(self.invf, self.num_docs, doc_vocabs)

        retr.query(list(tokens))
        return retr.get_rankings()

    def normalize_test_terms(self, terms: tuple[str, ...]) -> generator[str]:

        prep = Normalizer()
        prep.set_document(" ".join(terms) + " ")
        prep.process()

        return prep.get_tokens()
