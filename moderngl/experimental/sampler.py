from typing import Any, Tuple

from .texture import Texture


class Sampler:
    __slots__ = ['__mglo', '__swizzle', '__filter', 'texture', 'extra']

    def __init__(self):
        self.__mglo = None  # type: Any
        self.__swizzle = None  # type: str
        self.__filter = None  # type: Tuple[int, int]
        self.texture = None  # type: Texture
        self.extra = None  # type: Any

    @property
    def swizzle(self):
        return self.__swizzle

    @swizzle.setter
    def swizzle(self, value):
        self.__mglo.swizzle = value

    @property
    def filter(self):
        return self.__filter

    @filter.setter
    def filter(self, value):
        self.__mglo.filter = value

    def use(self, location=0) -> None:
        self.__mglo.use(location)
