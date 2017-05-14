'''
    Placeholder
'''

# pylint: disable=too-few-public-methods


class Renderbuffer:
    '''
        Renderbuffer
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Renderbuffer')

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo = obj
        return res
