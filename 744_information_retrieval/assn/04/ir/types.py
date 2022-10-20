from typing import Any, Counter, Generator, Iterable, TextIO, TypeAlias, TypeVar


iterable: TypeAlias = Iterable[Any]

counter: TypeAlias = Counter[str]

text_io: TypeAlias = TextIO

T = TypeVar("T")
generator: TypeAlias = Generator[T, None, None]
