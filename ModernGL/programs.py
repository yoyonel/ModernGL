'''
    Placeholder
'''

# pylint: disable=too-few-public-methods

from typing import Dict

from .common import Primitive
from .program_members import Uniform, UniformBlock, UniformMap, Varying, Attribute


class ComputeShader:
    '''
        ComputeShader
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('ComputeShader')

    @staticmethod
    def new(obj):
        '''
            For internal use only.
        '''

        res = ComputeShader.__new__(ComputeShader)
        res.mglo = obj
        return res


class Shader:
    '''
        Create a :py:class:`~ModernGL.Shader` using:

            - :py:meth:`~ModernGL.Context.VertexShader`
            - :py:meth:`~ModernGL.Context.FragmentShader`
            - :py:meth:`~ModernGL.Context.GeometryShader`
            - :py:meth:`~ModernGL.Context.TessEvaluationShader`
            - :py:meth:`~ModernGL.Context.TessControlShader`
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('GeometryShader')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Shader.__new__(Shader)
        res.mglo = obj
        return res

    @property
    def source(self) -> str:
        '''
            The source code of the shader.
        '''

        return self.mglo.source

    @property
    def typename(self) -> str:
        '''
            The type of the shader.
            The return value is a string.

            - ``'VertexShader'``
            - ``'FragmentShader'``
            - ``'GeometryShader'``
            - ``'TessEvaluationShader'``
            - ``'TessControlShader'``
        '''

        return self.mglo.typename


class Program:
    '''
        Program
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Program')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Program.__new__(Program)
        res.mglo = obj
        return res

    @property
    def uniforms(self) -> Dict[str, Uniform]:
        '''
            The program's uniforms.
            The return value is a dictinary.
            It can be used to access uniforms by name.
        '''

        return UniformMap.new(self.mglo.uniforms)

    @property
    def uniform_blocks(self) -> Dict[str, UniformBlock]:
        '''
            The program's uniform blocks.
            The return value is a dictinary.
            It can be used to access uniform blocks by name.
        '''

        return self.mglo.uniform_blocks

    @property
    def attributes(self) -> Dict[str, Attribute]:
        '''
            The program's attributes.
            The return value is a dictinary.
            It can be used to access attributes by name.
        '''

        return self.mglo.attributes

    @property
    def varyings(self) -> Dict[str, Varying]:
        '''
            The program's varyings.
            The return value is a dictinary.
            It can be used to access varyings by name.
        '''

        return self.mglo.varyings

    @property
    def geometry_input(self) -> Primitive:
        '''
            The geometry input primitive.
            The GeometryShader's input primitive if the GeometryShader exists.
            The geometry input primitive will be used for validation.
        '''

        return self.mglo.geometry_input

    @property
    def geometry_output(self) -> Primitive:
        '''
            The geometry output primitive.
            The GeometryShader's output primitive if the GeometryShader exists.
        '''

        return self.mglo.geometry_output

    @property
    def geometry_vertices(self) -> int:
        '''
            The maximum number of vertices that the geometry shader in program
            will output.
        '''

        return self.mglo.geometry_vertices

    @property
    def vertex_shader(self) -> Shader:
        '''
            vertex_shader
        '''

        return self.mglo.vertex_shader

    @property
    def fragment_shader(self) -> Shader:
        '''
            fragment_shader
        '''

        return self.mglo.fragment_shader

    @property
    def geometry_shader(self) -> Shader:
        '''
            geometry_shader
        '''

        return self.mglo.geometry_shader

    @property
    def tess_evaluation_shader(self) -> Shader:
        '''
            tess_evaluation_shader
        '''

        return self.mglo.tess_evaluation_shader

    @property
    def tess_control_shader(self) -> Shader:
        '''
            tess_control_shader
        '''

        return self.mglo.tess_control_shader
