'''
    ModernGL Vertex array members
'''

from typing import Dict

from .common import TRIANGLES, POINTS
from .programs import Program
from .buffers import Buffer

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


class VertexArray:
    '''
        VertexArray
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('VertexArray')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = VertexArray.__new__(VertexArray)
        res.mglo = obj
        return res

    @property
    def program(self) -> Program:
        '''
            The program assinged to the VertexArray.
            The program used when rendering or transforming primitives.
        '''

        return self.mglo.program

    @property
    def content(self) -> list:
        '''
            The content assinged to the VertexArray.
        '''

        return self.mglo.content

    @property
    def attributes(self) -> Dict[str, VertexArrayAttribute]:
        '''
            Individual vertex attributes.
            Use the bind() method to assign vertex attributes to buffers.
        '''

        return self.mglo.attributes

    @property
    def index_buffer(self) -> Buffer:
        '''
            The index buffer if the index_buffer is set otherwise ``None``.
        '''

        return self.mglo.index_buffer

    @property
    def vertices(self) -> int:
        '''
            The number of vertices detected.
            This is the minimum of the number of vertices possible per Buffer.
            The size of the index_buffer determines the number of vertices.
            Per instance vertex attributes does not affect this number.
        '''

        return self.mglo.vertices

    def render(self, mode=TRIANGLES, vertices=-1, first=0, instances=1):
        '''
            The render primitive (mode) must be the same as
            the input primitive of the GeometryShader.

            Args:
                mode: By default `TRIANGLES` will be used.
                vertices: The number of vertices to transform.

            Keyword Args:
                first: The index of the first vertex to start with.
                instances: The number of instances.
        '''

        self.mglo.render(mode, vertices, first, instances)

    def transform(self, buf, mode=POINTS, vertices=-1, *, first=0, instances=1):
        '''
            Transform vertices.
            Stores the output in a single buffer.
            The transform primitive (mode) must be the same as
            the input primitive of the GeometryShader.

            Args:
                output: The buffer to store the output.
                mode: By default `TRIANGLES` will be used.
                vertices: The number of vertices to transform.

            Keyword Args:
                first: The index of the first vertex to start with.
                instances: The number of instances.
        '''

        self.mglo.transform(buf.mglo, mode, vertices, first, instances)
