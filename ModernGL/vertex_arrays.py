'''
    ModernGL Vertex array members
'''

# pylint: disable=too-few-public-methods, function-redefined

from typing import Dict

from .common import Object, TRIANGLES, POINTS
from .programs import Program
from .buffers import Buffer


class VertexArrayAttribute(Object):
    '''
        VertexArrayAttribute
    '''

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = VertexArrayAttribute.__new__(VertexArrayAttribute)
        res.mglo = obj
        return res

    def __getitem__(self, key) -> VertexArrayAttribute:
        return VertexArrayAttribute.new(self.mglo[key])

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

    def bind(self, buffer, offset=0, stride=0, divisor=0):
        '''
            bind
        '''

        self.mglo.bind(buffer.mglo, offset, stride, divisor)

    def enable(self):
        '''
            enable
        '''

        self.mglo.enable()

    def disable(self):
        '''
            disable
        '''

        self.mglo.disable()


class VertexArrayAttributeMap:
    '''
        VertexArrayAttributeMap
    '''

    def __init__(self):
        self.mglo = {}
        raise NotImplementedError('VertexArrayAttributeMap')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = VertexArrayAttributeMap.__new__(VertexArrayAttributeMap)
        res.mglo = obj
        return res

    def __getitem__(self, key) -> VertexArrayAttribute:
        return VertexArrayAttribute.new(self.mglo[key])

    def __contains__(self, key):
        return key in self.mglo

    def __len__(self):
        return len(self.mglo)


class VertexArray(Object):
    '''
        VertexArray
    '''

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
    def attributes(self) -> VertexArrayAttributeMap:
        '''
            Individual vertex attributes.
            Use the bind() method to assign vertex attributes to buffers.
        '''

        return VertexArrayAttributeMap.new(self.mglo.attributes)

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
