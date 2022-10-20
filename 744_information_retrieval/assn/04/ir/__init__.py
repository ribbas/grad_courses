from pathlib import Path

from .files import CorpusFile, Formatter, IO, QueryFile

# from .invertedfile import InvertedFile
# from .lexer import Lexer, LexerStatistics
# from .packer import Packer
# from .retriever import Retriever
# from .types import counter, generator


class InformationRetrieval:
    def __init__(self, filename: Path) -> None:

        self.corpus: CorpusFile = CorpusFile(filename)

        # self.invf: InvertedFile
        # self.retr: Retriever

        # self.df: counter
        # self.cf: counter

        self.num_docs: int = 0
        self.freq_loaded = False
        self.term_doc_tf_str: str = ""

    def generate_freqs(self) -> None:

        # lex = Lexer()

        term_doc_tf: list[tuple[str, int, int]] = []
        self.corpus.ingest()

        # self.df = lex.get_df()
        # self.cf = lex.get_cf()
        # self.term_doc_tf_str: str = Formatter.format_term_doc_tf(term_doc_tf)
        # self.freq_loaded = True
