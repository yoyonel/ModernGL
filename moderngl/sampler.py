

class Sampler:
    '''
        Docstring
    '''

    __slots__ = ['mglo', '_glo', 'ctx', 'extra']

    def __init__(self):
        self.mglo = None
        self._glo = None
        self.ctx = None
        self.extra = None
        raise TypeError()

    @property
    def bar(self) -> None:
        return self.mglo.bar

    @bar.setter
    def bar(self, value):
        self.mglo.bar = value

    def foo(self) -> None:
        self.mglo.foo()

    def release(self) -> None:
        self.mglo.release()
