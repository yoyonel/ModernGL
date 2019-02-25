from typing import Any, Tuple

from .texture import Texture


class Sampler:
    __slots__ = ['__mglo', '__filter', '__wrap', '__anisotropy', '__compare_func', '__lod_range', '__lod_bias', '__border', 'texture', 'extra']

    def __init__(self):
        self.__mglo = None  # type: Any
        self.__filter = None  # type: Tuple[int, int]
        self.__wrap = None  # type: int
        self.__anisotropy = None  # type: float
        self.__compare_func = None  # type: str
        self.__lod_range = None  # type: Tuple[int, int]
        self.__lod_bias = None  # type: float
        self.__border = None  # type: Tuple[float, float, float, float]
        self.texture = None  # type: Texture
        self.extra = None  # type: Any

    @property
    def filter(self):
        return self.__filter

    @filter.setter
    def filter(self, value):
        self.__mglo.filter = value

    @property
    def wrap(self):
        return self.__wrap

    @wrap.setter
    def wrap(self, value):
        self.__mglo.wrap = value

    @property
    def anisotropy(self):
        return self.__anisotropy

    @anisotropy.setter
    def anisotropy(self, value):
        self.__mglo.anisotropy = value

    @property
    def compare_func(self):
        return self.__compare_func

    @compare_func.setter
    def compare_func(self, value):
        self.__mglo.compare_func = value

    @property
    def lod_range(self):
        return self.__lod_range

    @lod_range.setter
    def lod_range(self, value):
        self.__mglo.lod_range = value

    @property
    def lod_bias(self):
        return self.__lod_bias

    @lod_bias.setter
    def lod_bias(self, value):
        self.__mglo.lod_bias = value

    @property
    def border(self):
        return self.__border

    @border.setter
    def border(self, value):
        self.__mglo.border = value

    def use(self, location=0) -> None:
        self.__mglo.use(location)
