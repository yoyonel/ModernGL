from typing import Any


class Query:
    __slots__ = ['__mglo', 'elapsed', 'primitives', 'samples', 'extra']

    def __init__(self):
        self.__mglo = None  # type: Any
        self.elapsed = None  # type: int
        self.primitives = None  # type: int
        self.samples = None  # type: int
        self.extra = None  # type: Any

    def __enter__(self):
        self.__mglo.begin()
        return self

    def __exit__(self, *args):
        self.__mglo.end()
