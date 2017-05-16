'''
    ModernGL renderbuffers
'''

from .common import InvalidObject


class Renderbuffer:
    '''
        Renderbuffer
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError()

    def release(self):
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo = obj
        return res

    @property
    def width(self) -> int:
        '''
            Renderbuffer width
        '''

        return self.mglo.width

    @property
    def height(self) -> int:
        '''
            Renderbuffer height
        '''

        return self.mglo.height

    @property
    def size(self) -> tuple:
        '''
            Renderbuffer size
        '''

        return (self.mglo.width, self.mglo.height)

    @property
    def samples(self) -> int:
        '''
            Renderbuffer samples
        '''

        return self.mglo.samples

    @property
    def components(self) -> bool:
        '''
            Renderbuffer components
        '''

        return self.mglo.components

    @property
    def depth(self) -> bool:
        '''
            Renderbuffer depth
        '''

        return self.mglo.depth
