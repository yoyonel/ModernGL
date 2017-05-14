'''
    ModernGL Vertex array members
'''

# pylint: disable=too-few-public-methods


class VertexArrayAttribute:
    '''
        VertexArrayAttribute
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('VertexArrayAttribute')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = VertexArrayAttribute.__new__(VertexArrayAttribute)
        res.mglo = obj
        return res

    @property
    def location(self):
        '''
            location
        '''

        return self.mglo.location

    @property
    def divisor(self):
        '''
            divisor
        '''

        return self.mglo.divisor

    @property
    def stride(self):
        '''
            stride
        '''

        return self.mglo.stride

    @property
    def enabled(self):
        '''
            enabled
        '''

        return self.mglo.enabled

    @property
    def default(self):
        '''
            default
        '''

        return self.mglo.default


class VertexArrayListAttribute:
    '''
        VertexArrayAttribute
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('VertexArrayListAttribute')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = VertexArrayListAttribute.__new__(VertexArrayListAttribute)
        res.mglo = obj
        return res


class VertexArrayMatrixAttribute:
    '''
        VertexArrayMatrixAttribute
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('VertexArrayMatrixAttribute')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = VertexArrayMatrixAttribute.__new__(VertexArrayMatrixAttribute)
        res.mglo = obj
        return res
