from pathlib import Path

from .files import CorpusFile, Formatter, IO, QueryFile
from .invertedfile import InvertedFile
from .lexer import Lexer
from .normalize import Normalizer
from .packer import Packer
from .retriever import Retriever
from .types import counter, generator


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.corpus = CorpusFile(filename)

        self.invf: InvertedFile
        self.retr: Retriever

        self.df: counter
        self.cf: counter

        self.num_docs: int = 0
        self.freq_loaded = False
        self.term_doc_tf_str: str = ""

    def load_freqs(self) -> None:

        self.df = IO.read_json(self.corpus.df_file)
        self.cf = IO.read_json(self.corpus.tf_file)

        self.term_doc_tf_str = IO.read(self.corpus.tdt_file)
        self.freq_loaded = True

    def generate_freqs(self) -> None:

        prep = Normalizer()
        lex = Lexer()

        term_doc_tf: list[tuple[str, str, int]] = []
        self.corpus.ingest(prep, lex, term_doc_tf)

        self.df = lex.get_df()
        self.cf = lex.get_cf()
        self.term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
        self.freq_loaded = True

    def generate_stats(self) -> None:

        if self.freq_loaded:
            lex = Lexer()
            lex.set_df(self.df)
            lex.set_cf(self.cf)
            contents: str = Formatter.format_stats(lex, self.corpus.num_docs)
            IO.dump(self.corpus.stats_file, contents)

        else:
            raise AttributeError("Corpus frequencies not generated yet")

    def dump_freqs(self) -> None:

        if self.freq_loaded:
            IO.dump(self.corpus.tdt_file, self.term_doc_tf_str)
            IO.dump_json(self.corpus.df_file, self.df)
            IO.dump_json(self.corpus.tf_file, self.cf)
            IO.dump(self.corpus.meta_file, str(self.corpus.num_docs))

        else:
            raise AttributeError("Corpus frequencies not generated yet")

    def build_sorted_tdt(self) -> None:

        if self.freq_loaded:

            invf = InvertedFile()
            invf.build_dict(self.df)

            mapped_tdt_chunks = invf.sort_mapped_tdt(self.term_doc_tf_str)
            chunk_filenames: list[str] = []
            for idx, mapped_tdt_chunk in enumerate(mapped_tdt_chunks):

                chunk_filenames.append(
                    f"{self.corpus.sorted_tdt_chunk_file}{idx}"
                )
                IO.dumplines(chunk_filenames[-1], mapped_tdt_chunk)

            IO.dump_sorted_chunks(self.corpus.sorted_tdt_file, chunk_filenames)

    def encode_inverted_file(self) -> None:

        if self.freq_loaded:

            invf = InvertedFile()
            invf.build_dict(self.df)

            mapped_tdt = invf.parse_sorted_tdt(
                IO.open_file(self.corpus.sorted_tdt_file)
            )
            invf.convert(mapped_tdt)

            inv_file = invf.get_inverted_file_raw()
            if_data = Packer.encode(inv_file)
            IO.dump_bin(self.corpus.inv_file, if_data)
            IO.dump_json(self.corpus.dict_file, invf.get_dictionary())

        else:
            raise AttributeError("Corpus frequencies not generated yet")

    def load_inverted_file(self) -> None:

        self.invf = InvertedFile()
        inv_file = IO.read_bin(self.corpus.inv_file)
        dictionary = IO.read_json(self.corpus.dict_file)
        self.num_docs = int(IO.read(self.corpus.meta_file))
        self.invf.set_inverted_file_bytes(inv_file)
        self.invf.set_dictionary(dictionary)

    def precompute_lengths(self) -> None:

        self.load_inverted_file()

        self.retr = Retriever(self.invf, self.num_docs)
        self.retr.decode_inverted_file()
        self.retr.compute_sum_of_squares()
        self.retr.compute_lengths()

        IO.dump_json(self.corpus.len_file, self.retr.get_lengths())

    def normalize_query(self, query: str) -> generator[str]:

        prep = Normalizer()
        prep.set_document(query)
        prep.process()

        return prep.get_tokens()

    def generate_rankings(self, filename: Path):

        self.load_inverted_file()

        self.retr = Retriever(self.invf, self.num_docs)
        lengths = IO.read_json(self.corpus.len_file)
        self.retr.set_lengths(lengths)
        self.retr.decode_inverted_file()

        prep = Normalizer()
        query_file = QueryFile(filename)
        queries = query_file.ingest(prep)

        rankings = {}
        for doc_id, tokens in queries.items():
            self.retr.query(list(tokens))
            rankings[doc_id] = self.retr.get_rankings()
            self.retr.reset()

        IO.dump(self.corpus.ranking_file, Formatter.format_rankings(rankings))
