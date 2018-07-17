from typing import Tuple

__all__ = ['Sampler']


class Sampler:
    '''
        A Sampler Object is an OpenGL Object that stores the sampling parameters for a
        Texture access inside of a shader. When a sampler object is bound to a texture image unit,
        the internal sampling parameters for a texture bound to the same image unit are all ignored.
        Instead, the sampling parameters are taken from this sampler object.
    '''

    __slots__ = ['mglo', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._glo = None
        self.ctx = None
        self.extra = None
        raise TypeError()

    def use(self, location=0) -> None:
        '''
            Bind the sampler to a texture unit

            Args:
                location (int): The texture unit
        '''
        self.mglo.use(location)

    def release(self) -> None:
        self.mglo.release()

    @property
    def repeat_x(self) -> bool:
        return self.mglo.repeat_x

    @repeat_x.setter
    def repeat_x(self, value: bool):
        self.mglo.repeat_x = value

    @property
    def repeat_y(self) -> bool:
        return self.mglo.repeat_x

    @repeat_y.setter
    def repeat_y(self, value: bool):
        self.mglo.repeat_y = value

    @property
    def filter(self) -> Tuple[int, int]:
        '''
            tuple: The filter of the sampler
        '''
        return self.mglo.filter

    @filter.setter
    def filter(self, value: Tuple[int, int]):
        self.mglo.filter = value

    @property
    def compare_func(self) -> str:
        return self.mglo.compare_func

    @compare_func.setter
    def compare_func(self, value: str):
        self.mglo.compare_func = value

    @property
    def anisotropy(self) -> float:
        return self.mglo.anisotropy

    @anisotropy.setter
    def anisotropy(self, value: float):
        self.mglo.anisotropy = value
