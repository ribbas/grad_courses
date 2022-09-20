from collections import Counter
from pathlib import Path
from typing import Generator

from .files import DataFile, Formatter, IO
from .invertedfile import InvertedFile
from .lexer import Lexer
from .normalize import Normalizer
from .packer import Packer


class InformationRetrieval:
    def __init__(self) -> None:

        self.data: DataFile
        self.df: Counter[str]
        self.tf: Counter[str]
        self.loaded = False
        self.term_doc_tf_str: str = ""
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
            IO.dump_json(self.data.df_file_name, self.df)
            IO.dump_json(self.data.tf_file_name, self.tf)
        else:
            raise AttributeError("Data not generated yet")

    def build_inverted_file(self) -> None:

        if self.loaded:
            invf = InvertedFile()
            invf.build_dict(self.df, self.tf)
            invf.ingest(self.term_doc_tf_str)

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
        self.invf.set_inverted_file(inv_file)
        self.invf.set_dictionary(dictionary)

    def read_inverted_file(
        self,
        tokens: Generator[str, None, None],
        keys: tuple[str, ...] = ("term",),
    ) -> Generator[dict[str, int | tuple[int, ...]], None, None]:

        for token in tokens:
            metadata = self.invf.lookup(token)
            yield {key: metadata.get(key, -1) for key in keys}

    def normalize_test_terms(
        self, terms: tuple[str, ...]
    ) -> Generator[str, None, None]:

        prep = Normalizer()
        prep.set_document(" ".join(terms))
        prep.process()

        return prep.get_tokens()
