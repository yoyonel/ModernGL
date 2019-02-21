from typing import Any, Tuple

from .texture import Texture


class Sampler:
    __slots__ = ['__mglo', '__filter', '__repeat_x', '__repeat_y', '__repeat_z', '__anisotropy', '__min_lod', '__max_lod', 'texture', 'extra']

    def __init__(self):
        self.__mglo = None  # type: Any
        self.__filter = None  # type: Tuple[int, int]
        self.__repeat_x = None  # type: bool
        self.__repeat_y = None  # type: bool
        self.__repeat_z = None  # type: bool
        self.__anisotropy = None  # type: float
        self.__min_lod = None  # type: int
        self.__max_lod = None  # type: int
        self.texture = None  # type: Texture
        self.extra = None  # type: Any

    @property
    def filter(self):
        return self.__filter

    @filter.setter
    def filter(self, value):
        self.__mglo.filter = value

    @property
    def repeat_x(self):
        return self.__repeat_x

    @repeat_x.setter
    def repeat_x(self, value):
        self.__mglo.repeat_x = value

    @property
    def repeat_y(self):
        return self.__repeat_y

    @repeat_y.setter
    def repeat_y(self, value):
        self.__mglo.repeat_y = value

    @property
    def repeat_z(self):
        return self.__repeat_z

    @repeat_z.setter
    def repeat_z(self, value):
        self.__mglo.repeat_z = value

    @property
    def anisotropy(self):
        return self.__anisotropy

    @anisotropy.setter
    def anisotropy(self, value):
        self.__mglo.anisotropy = value

    @property
    def min_lod(self):
        return self.__min_lod

    @min_lod.setter
    def min_lod(self, value):
        self.__mglo.min_lod = value

    @property
    def max_lod(self):
        return self.__max_lod

    @max_lod.setter
    def max_lod(self, value):
        self.__mglo.max_lod = value

    def use(self, location=0) -> None:
        self.__mglo.use(location)
