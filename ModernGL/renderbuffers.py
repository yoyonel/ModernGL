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
