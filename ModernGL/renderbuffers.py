'''
    Placeholder
'''

# pylint: disable=too-few-public-methods

from .common import Object


class Renderbuffer(Object):
    '''
        Renderbuffer
    '''

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
            width
        '''

        return self.mglo.width

    @property
    def height(self) -> int:
        '''
            height
        '''

        return self.mglo.height

    @property
    def size(self) -> tuple:
        '''
            size
        '''

        return (self.mglo.width, self.mglo.height)

    @property
    def samples(self) -> int:
        '''
            samples
        '''

        return self.mglo.samples
