from typing import Any, Counter, Generator, Iterable, TypeAlias, TypeVar


iterable: TypeAlias = Iterable[Any]

counter: TypeAlias = Counter[str]

T = TypeVar("T")
generator: TypeAlias = Generator[T, None, None]
