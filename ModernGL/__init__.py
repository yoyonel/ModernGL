'''
    ModernGL: PyOpenGL alternative
'''

from typing import Dict

from ModernGL import ModernGL as _mgl

from .objects import Object, InvalidObject
from .errors import Error

from .constants import (
    Version, EnableFlag, Primitive,
    CORE_330, CORE_400, CORE_410, CORE_420, CORE_430, CORE_440, CORE_450,
    BLEND, DEPTH_TEST, CULL_FACE, MULTISAMPLE,
    TRIANGLES, TRIANGLE_STRIP, TRIANGLE_FAN, LINES, LINE_STRIP, LINE_LOOP, POINTS,
    LINE_STRIP_ADJACENCY, LINES_ADJACENCY, TRIANGLE_STRIP_ADJACENCY, TRIANGLES_ADJACENCY,
)

from .program_members import (
    Uniform, UniformMap, UniformBlock, Varying, Attribute, AttributeMap,
    Subroutine, SubroutineUniform,
)

from .vertex_array_member import (
    VertexArrayAttribute, VertexArrayListAttribute, VertexArrayMatrixAttribute,
)

__all__ = [
    'Version', 'EnableFlag', 'Primitive',
    'CORE_330', 'CORE_400', 'CORE_410', 'CORE_420', 'CORE_430', 'CORE_440', 'CORE_450',
    'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'MULTISAMPLE',
    'TRIANGLES', 'TRIANGLE_STRIP', 'TRIANGLE_FAN', 'LINES', 'LINE_STRIP', 'LINE_LOOP', 'POINTS',
    'LINE_STRIP_ADJACENCY', 'LINES_ADJACENCY', 'TRIANGLE_STRIP_ADJACENCY', 'TRIANGLES_ADJACENCY',
    'Uniform', 'UniformMap', 'UniformBlock',
    'Varying', 'Attribute', 'AttributeMap',
    'Subroutine', 'SubroutineUniform',
    'VertexArrayAttribute', 'VertexArrayListAttribute', 'VertexArrayMatrixAttribute',
    'Object', 'InvalidObject', 'Error',
    'VERSION',
    'create_context',
    'create_standalone_context',
    'BufferAccess',
    'Buffer',
    'ComputeShader',
    'Framebuffer',
    'MultisampleRenderbuffer',
    'MultisampleTexture',
    'Shader',
    'Program',
    'Renderbuffer',
    'Texture',
    'VertexArray',
    'Context',
]

VERSION = '3.1.5'
'''
    ModernGL version
'''


class BufferAccess:
    '''
        BufferAccess
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('BufferAccess')

    def __enter__(self):
        self.mglo.open()
        return self

    def __exit__(self, *args):
        self.mglo.close()

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = BufferAccess.__new__(BufferAccess)
        res.mglo = obj
        return res

    def open(self):
        '''
            Map the buffer.
        '''

        self.mglo.open()

    def close(self):
        '''
            Unmap the buffer.
        '''

        self.mglo.close()

    def read(self, size=-1, offset=0) -> bytes:
        '''
            Read the content.

            Args:
                size: The size. Value `-1` means all.

            Keyword Args:
                offset: The offset.

            Returns:
                bytes: binary data
        '''

        return self.mglo.read(size, offset)

    def write(self, data, offset=0):
        '''
            Write the content.

            Args:
                size: The data.

            Keyword Args:
                offset: The offset.
        '''

        self.mglo.write(data, offset)

    # @property
    # def buffer(self) -> Buffer:
    # 	'''
    # 		The buffer.
    # 	'''

    # 	return self.mglo.buffer

    @property
    def offset(self) -> int:
        '''
            The offset.
        '''

        return self.mglo.offset

    @property
    def size(self) -> int:
        '''
            The size.
        '''

        return self.mglo.size

    @property
    def readonly(self) -> bool:
        '''
            Is readonly.
        '''

        return self.mglo.readonly


class Buffer:
    '''
        Create a :py:class:`Buffer` using :py:meth:`Context.Buffer`.
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Buffer')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Buffer.__new__(Buffer)
        res.mglo = obj
        return res

    @property
    def size(self) -> int:
        '''
            The size of the buffer.
        '''

        return self.mglo.size

    @property
    def dynamic(self) -> bool:
        '''
            Is the buffer created with the dynamic flag?
        '''

        return self.mglo.dynamic

    def release(self):
        '''
            Release the buffer.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    def access(self, size=-1, offset=0, readonly=False) -> BufferAccess:
        '''
            Create a buffer access object.

            Keyword Args:
                size: The size.
                offset: The offset.
                readonly: The readonly.
        '''

        return BufferAccess.new(self.mglo.access(size, offset, readonly))

    def read(self, size=-1, offset=0) -> bytes:
        '''
            Read the content.

            Args:
                size: The size. Value `-1` means all.

            Keyword Args:
                offset: The offset.

            Returns:
                bytes: binary data.
        '''

        return self.mglo.read(size, offset)

    def write(self, data, offset=0):
        '''
            Write the content.

            Args:
                data: The data.

            Keyword Args:
                offset: The offset.
        '''

        self.mglo.write(data, offset)

    def orphan(self):
        '''
            Orphan the buffer.
        '''

        self.mglo.orphan()

    def bind_to_uniform_block(self, location=0):
        '''
            Bind the buffer to a uniform block.

            Args:
                location: The uniform block location.
        '''

        self.mglo.bind_to_uniform_block(location)

    def bind_to_storage_buffer(self, location=0):
        '''
            Bind the buffer to a shader storage buffer.

            Args:
                location: The shader storage location.
        '''

        self.mglo.bind_to_storage_buffer(location)


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
            internal use only
        '''

        res = ComputeShader.__new__(ComputeShader)
        res.mglo = obj
        return res

    def release(self):
        '''
            release
        '''

        self.mglo.release()
        self.__class__ = InvalidObject


class Framebuffer:
    '''
        Framebuffer
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Framebuffer')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Framebuffer.__new__(Framebuffer)
        res.mglo = obj
        return res

    def release(self):
        '''
            Release the framebuffer.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    def read(self, viewport=None, components=3, floats=False) -> bytes:
        '''
            read
        '''

        return self.mglo.read(viewport, components, floats)

    def use(self):
        '''
            Bind the framebuffer. Set the target for the
            `VertexArray.render` or `VertexArray.transform` methods.
        '''

        self.mglo.use()


class MultisampleRenderbuffer:
    '''
        MultisampleRenderbuffer
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('MultisampleRenderbuffer')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = MultisampleRenderbuffer.__new__(MultisampleRenderbuffer)
        res.mglo = obj
        return res

    def release(self):
        '''
            release
        '''

        self.mglo.release()
        self.__class__ = InvalidObject


class MultisampleTexture:
    '''
        MultisampleTexture
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('MultisampleTexture')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = MultisampleTexture.__new__(MultisampleTexture)
        res.mglo = obj
        return res

    def release(self):
        '''
            release
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    def use(self, location=0):
        '''
            Args:
                location (int): The texture location.
                        Same as the integer value that is used for sampler2D
                        uniforms in the shaders. The value ``0`` will bind the
                        texture to the ``GL_TEXTURE0`` binding point.
        '''

        self.mglo.use(location)


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

    def release(self):
        '''
            Release the shader object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject


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

    def release(self):
        '''
            Release the program object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

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
            internal use only
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo = obj
        return res

    def release(self):
        '''
            release
        '''

        self.mglo.release()
        self.__class__ = InvalidObject


class Texture:
    '''
        Texture
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('Texture')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Texture.__new__(Texture)
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

    def release(self):
        '''
            Release the texture object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    def update(self, data, size=None, offset=(0, 0)):
        '''
            update
        '''

        self.mglo.update(data, size, offset)

    def use(self, location=0):
        '''
            Bind the texture.

            Args:
                location (int): The texture location.
                    Same as the integer value that is used for sampler2D
                    uniforms in the shaders. The value ``0`` will bind the
                    texture to the ``GL_TEXTURE0`` binding point.
        '''

        self.mglo.use(location)


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

    def release(self):
        '''
            Release the vertex array object.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

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


class Context:
    '''
        Create a :py:class:`Context` using:

            - :py:func:`~ModernGL.create_context`
            - :py:func:`~ModernGL.create_standalone_context`

        Members:

            - :py:meth:`Context.Buffer`
            - :py:meth:`Context.DepthRenderbuffer`
            - :py:meth:`Context.DepthTexture`
            - :py:meth:`Context.Framebuffer`
            - :py:meth:`Context.Program`
            - :py:meth:`Context.Renderbuffer`
            - :py:meth:`Context.Shader`
            - :py:meth:`Context.SimpleVertexArray`
            - :py:meth:`Context.Texture`
            - :py:meth:`Context.VertexArray`
    '''

    def __init__(self):
        self.mglo = None
        raise NotImplementedError('SimpleVertexArray')

    @staticmethod
    def new(obj):
        '''
            internal use only
        '''

        res = Context.__new__(Context)
        res.mglo = obj
        return res

    def release(self):
        '''
            Release the OpenGL context.
        '''

        self.mglo.release()
        self.__class__ = InvalidObject

    @property
    def line_width(self) -> float:
        '''
            Set the default line width.
        '''

        return self.mglo.line_width

    @line_width.setter
    def line_width(self, value):
        self.mglo.line_width = value

    @property
    def point_size(self) -> float:
        '''
            Set the default point size.
        '''

        return self.mglo.point_size

    @point_size.setter
    def point_size(self, value):
        self.mglo.point_size = value

    @property
    def viewport(self) -> tuple:
        '''
            The viewport.
        '''

        return self.mglo.viewport

    @viewport.setter
    def viewport(self, value):
        self.mglo.viewport = tuple(value)

    @property
    def default_texture_unit(self) -> int:
        '''
            The default texture unit.
        '''

        return self.mglo.default_texture_unit

    @default_texture_unit.setter
    def default_texture_unit(self, value):
        self.mglo.default_texture_unit = value

    @property
    def max_texture_units(self) -> int:
        '''
            The max texture units.
        '''

        return self.mglo.max_texture_units

    @property
    def default_framebuffer(self) -> Framebuffer:
        '''
            The default framebuffer.
        '''

        return self.mglo.default_framebuffer

    @property
    def vendor(self) -> str:
        '''
            vendor
        '''

        return self.mglo.vendor

    @property
    def renderer(self) -> str:
        '''
            renderer
        '''

        return self.mglo.renderer

    @property
    def version(self) -> str:
        '''
            version
        '''

        return self.mglo.version

    def clear(self, red=0, green=0, blue=0, alpha=0):
        '''
            Clear the framebuffer.

            Args:
                red, green, blue: color components.
                alpha: alpha component.
        '''

        self.mglo.clear(red, green, blue, alpha)

    def enable(self, flag):
        '''
            Enable flags.

            Args:
                flags: flags to enable.
        '''

        self.mglo.enable(flag)

    def disable(self, flag):
        '''
            Disable flags.

            Args:
                flags: flags to disable.
        '''

        self.mglo.disable(flag)

    def finish(self):
        '''
            Wait for all drawing commands to finish.
        '''

        self.mglo.finish()

    def copy_buffer(self, dst, src, size=-1, *, src_offset=0, dst_offset=0):
        '''
            Copy buffer content.

            Args:
                dst: Destination buffer.
                src: Source buffer.
                optional size: Size to copy.

            Keyword Args:
                src_offset: Read offset.
                dst_offset: Write offset.
        '''

        self.mglo.copy_buffer(dst.mglo, src.mglo, size, src_offset, dst_offset)

    def buffer(self, data=None, reserve=0, dynamic=False) -> Buffer:
        '''
            Create a Buffer.

            Args:
                data: Content of the new buffer.

            Keyword Args:
                reserve: The number of bytes to reserve.
                dynamic: Treat buffer as dynamic.

            Returns:
                :py:class:`Buffer`
        '''

        return Buffer.new(self.mglo.Buffer(data, reserve, dynamic))

    def texture(self, size, components, data=None, floats=False) -> Texture:
        '''
            Create a Texture.

            Args:
                size: Width, height.
                components: The number of components 1, 2, 3 or 4.
                optional data: Content of the image.

            Keyword Args:
                floats: Use floating point precision.

            Returns:
                :py:class:`Texture`
        '''

        return Texture.new(self.mglo.Texture(size, components, data, floats))

    def depth_texture(self, size, data=None) -> Texture:
        '''
            Create a DepthTexture.

            Args:
                size: The width and height.
                optional data: The pixels.

            Returns:
                :py:class:`Texture`
        '''

        return Texture.new(self.mglo.DepthTexture(size, data))

    def vertex_array(self, program, content, index_buffer=None) -> VertexArray:
        '''
            Create a VertexArray.

            Args:
                program: The program used by `render` and `transform`.
                content: A list of (buffer, format, attributes).
                optional index_buffer: An index buffer.

            Returns:
                :py:class:`VertexArray`
        '''

        if index_buffer is not None:
            index_buffer = index_buffer.mglo

        content = list((a.mglo, b, c) for a, b, c in content)

        return VertexArray.new(self.mglo.VertexArray(program.mglo, list(content), index_buffer))

    def simple_vertex_array(self, program, buffer, attributes, index_buffer=None) -> VertexArray:
        '''
            Create a SimpleVertexArray.

            Args:
                program: The program used by `render` and `transform`.
                buffer: The buffer.
                attributes: A list of attribute names.
                optional index_buffer: An index buffer.

            Keyword Args:
                skip_errors: Ignore missing attributes.

            Returns:
                :py:class:`VertexArray`
        '''

        content = [(buffer, detect_format(program, attributes), attributes)]
        return self.vertex_array(program, content, index_buffer)

    def program(self, shaders, varyings=()) -> Program:
        '''
            Create a Program.

            Args:
                shaders: A list of :py:class:`Shader` objects.
                optional varyings: A list of varying names.

            Returns:
                :py:class:`Program`
        '''

        if isinstance(shaders, Shader):
            shaders = [shaders]

        return Program.new(self.mglo.Program([x.mglo for x in shaders], varyings))

    def vertex_shader(self, source) -> Shader:
        '''
            Create a VertexShader.

            Args:
                source: The source code in GLSL.

            Returns:
                :py:class:`Shader`
        '''

        return Shader.new(self.mglo.VertexShader(source))

    def fragment_shader(self, source) -> Shader:
        '''
            Create a FragmentShader.

            Args:
                source: The source code in GLSL.

            Returns:
                :py:class:`Shader`
        '''

        return Shader.new(self.mglo.FragmentShader(source))

    def geometry_shader(self, source) -> Shader:
        '''
            Create a GeometryShader.

            Args:
                source: The source code in GLSL.

            Returns:
                :py:class:`Shader`
        '''

        return Shader.new(self.mglo.GeometryShader(source))

    def tess_evaluation_shader(self, source) -> Shader:
        '''
            Create a TessEvaluationShader.

            Args:
                source: The source code in GLSL.

            Returns:
                :py:class:`Shader`
        '''

        return Shader.new(self.mglo.TessEvaluationShader(source))

    def tess_control_shader(self, source) -> Shader:
        '''
            Create a TessControlShader.

            Args:
                source: The source code in GLSL.

            Returns:
                :py:class:`Shader`
        '''

        return Shader.new(self.mglo.TessControlShader(source))

    def framebuffer(self, attachments) -> Framebuffer:
        '''
            Create a Framebuffer.

            Args:
                attachments: A list of `Texture` or `Renderbuffer` objects.

            Returns:
                :py:class:`Framebuffer`
        '''

        return Framebuffer.new(self.mglo.Framebuffer(attachments))

    def renderbuffer(self, size, components, floats=True) -> Renderbuffer:
        '''
            Create a Renderbuffer.

            Args:
                size: Width, height.
                components: The number of components 1, 2, 3 or 4.

            Keyword Args:
                floats: Use floating point precision.

            Returns:
                :py:class:`Renderbuffer`
        '''

        return Renderbuffer.new(self.mglo.Renderbuffer(size, components, floats))

    def depth_renderbuffer(self, size, floats=True) -> Renderbuffer:
        '''
            Create a Renderbuffer.

            Args:
                size: Width, height.

            Keyword Args:
                floats: Use floating point precision.

            Returns:
                :py:class:`Renderbuffer`
        '''

        return Renderbuffer.new(self.mglo.DepthRenderbuffer(size, floats))

    def compute_shader(self, source) -> ComputeShader:
        '''
            Create a ComputeShader.

            Args:
                source: The source of the compute shader.

            Returns:
                :py:class:`ComputeShader`
        '''

        return ComputeShader.new(self.mglo.ComputeShader(source))


if False:
    def _create_context() -> Context:
        return Context()

    def _create_standalone_context(*args) -> Context:
        return Context(*args)

    _mgl.create_context = _create_context
    _mgl.create_standalone_context = _create_standalone_context


def create_context(require=None) -> Context:
    '''
        Create a context and load OpenGL functions.
        An OpenGL context must exists.

        Keyword Arguments:
            require (Version): OpenGL version.

        Returns:
            :py:class:`ModernGL.Context`
    '''

    ctx = Context.new(_mgl.create_context())

    if require is not None and ctx.version < require:
        raise Exception('TODO')

    return ctx


def create_standalone_context(size=(256, 256), require=None) -> Context:
    '''
        Create a context and load OpenGL functions.
        An OpenGL context must exists.

        Keyword Arguments:
            size (tuple): Initial framebuffer size.
            require (:py:class:`ModernGL.Version`): OpenGL version.

        Returns:
            :py:class:`ModernGL.Context`
    '''

    ctx = Context.new(_mgl.create_standalone_context(*size))

    if require is not None and ctx.version < require:
        raise Exception('TODO')

    return ctx


def detect_format(program, attributes) -> str:
    '''
        detect_format
    '''

    def fmt(attr):
        '''
            size and shape
        '''

        return attr.array_length * attr.dimension, attr.shape

    return ''.join('%d%s' % fmt(program.attributes[a]) for a in attributes)
