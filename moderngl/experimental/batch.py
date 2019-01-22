from typing import Any


class Batch:
    __slots__ = ['__mglo', 'extra']

    def __init__(self):
        self.__mglo = None  # type: Any
        self.extra = None  # type: Any

    def run(self):
        self.__mglo.run()
