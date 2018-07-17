import os
import warnings
from typing import Dict, Tuple

from . import mgl
from .buffer import Buffer
from .compute_shader import ComputeShader
from .conditional_render import ConditionalRender
from .framebuffer import Framebuffer
from .program import Program, detect_format
from .program_members import (Attribute, Subroutine, Uniform, UniformBlock,
                              Varying)
from .query import Query
from .renderbuffer import Renderbuffer
from .scope import Scope
from .texture import Texture
from .texture_3d import Texture3D
from .texture_array import TextureArray
from .texture_cube import TextureCube
from .vertex_array import VertexArray
from .sampler import Sampler

__all__ = ['Context', 'create_context', 'create_standalone_context',
           'NOTHING', 'BLEND', 'DEPTH_TEST', 'CULL_FACE', 'RASTERIZER_DISCARD',
           'ZERO', 'ONE', 'SRC_COLOR', 'ONE_MINUS_SRC_COLOR', 'SRC_ALPHA', 'ONE_MINUS_SRC_ALPHA', 'DST_ALPHA',
           'ONE_MINUS_DST_ALPHA', 'DST_COLOR', 'ONE_MINUS_DST_COLOR',
           'DEFAULT_BLENDING', 'PREMULTIPLIED_ALPHA',
           'Error']


Error = mgl.Error


NOTHING = 0
BLEND = 1
DEPTH_TEST = 2
CULL_FACE = 4
RASTERIZER_DISCARD = 8


ZERO = 0x0000
ONE = 0x0001
SRC_COLOR = 0x0300
ONE_MINUS_SRC_COLOR = 0x0301
SRC_ALPHA = 0x0302
ONE_MINUS_SRC_ALPHA = 0x0303
DST_ALPHA = 0x0304
ONE_MINUS_DST_ALPHA = 0x0305
DST_COLOR = 0x0306
ONE_MINUS_DST_COLOR = 0x0307


DEFAULT_BLENDING = (SRC_ALPHA, ONE_MINUS_SRC_ALPHA)
PREMULTIPLIED_ALPHA = (SRC_ALPHA, ONE)


class Context:
    '''
        Class exposing OpenGL features.
        ModernGL objects can be created from this class.
    '''

    __slots__ = ['mglo', '_screen', '_info', 'version_code', 'fbo', 'extra']

    def __init__(self):
        self.mglo = None
        self._screen = None
        self._info = None
        self.version_code = None  #: int: The OpenGL version code.
        self.fbo = None  #: Framebuffer: The active framebuffer.
        self.extra = None
        raise TypeError()

    def __repr__(self):
        return '<Context>'

    def __eq__(self, other):
        return type(self) is type(other) and self.mglo is other.mglo

    @property
    def line_width(self) -> float:
        '''
            float: Set the default line width.
        '''

        return self.mglo.line_width

    @line_width.setter
    def line_width(self, value):
        self.mglo.line_width = value

    @property
    def point_size(self) -> float:
        '''
            float: Set the default point size.
        '''

        return self.mglo.point_size

    @point_size.setter
    def point_size(self, value):
        self.mglo.point_size = value

    @property
    def depth_func(self) -> int:
        '''
            int: Set the default depth func.
        '''

        raise NotImplementedError()

    @depth_func.setter
    def depth_func(self, value):
        self.mglo.depth_func = value

    @property
    def blend_func(self) -> Tuple[int, int]:
        '''
            tuple: Set the blend depth func.
        '''

        raise NotImplementedError()

    @blend_func.setter
    def blend_func(self, value):
        self.mglo.blend_func = tuple(value)

    @property
    def multisample(self) -> bool:
        '''
            bool: Multisample.
        '''

        raise NotImplementedError()

    @multisample.setter
    def multisample(self, value):
        self.mglo.multisample = value

    @property
    def viewport(self) -> Tuple[int, int, int, int]:
        '''
            tuple: The viewport.
        '''

        return self.mglo.fbo.viewport

    @viewport.setter
    def viewport(self, value):
        self.mglo.fbo.viewport = tuple(value)

    @property
    def max_samples(self) -> int:
        '''
            int: The max samples.
        '''

        return self.mglo.max_samples

    @property
    def max_integer_samples(self) -> int:
        '''
            int: The max integer samples.
        '''

        return self.mglo.max_integer_samples

    @property
    def max_texture_units(self) -> int:
        '''
            int: The max texture units.
        '''

        return self.mglo.max_texture_units

    @property
    def default_texture_unit(self) -> int:
        '''
            int: The default texture unit.
        '''

        return self.mglo.default_texture_unit

    @default_texture_unit.setter
    def default_texture_unit(self, value):
        self.mglo.default_texture_unit = value

    @property
    def max_anisotropy(self):
        '''
            float: Max anisotropy
        '''
        return self.mglo.max_anisotropy

    @property
    def screen(self) -> 'Framebuffer':
        '''
            Framebuffer: The default framebuffer.
        '''

        return self._screen

    @property
    def wireframe(self) -> bool:
        '''
            bool: Wireframe settings for debugging.
        '''

        return self.mglo.wireframe

    @wireframe.setter
    def wireframe(self, value):
        self.mglo.wireframe = value

    @property
    def front_face(self) -> str:
        '''
            str: The front_face.
        '''

        return self.mglo.front_face

    @front_face.setter
    def front_face(self, value):
        self.mglo.front_face = str(value)

    @property
    def patch_vertices(self) -> int:
        '''
            int: The number of vertices that will be used to make up a single patch
                 primitive.
        '''

        return self.mglo.patch_vertices

    @patch_vertices.setter
    def patch_vertices(self, value):
        self.mglo.patch_vertices = value

    @property
    def error(self) -> str:
        '''
            str: The result of glGetError() but human readable.
            This values is provided for debug purposes only.
        '''

        return self.mglo.error

    @property
    def info(self) -> Dict[str, object]:
        '''
            dict: The result of multiple glGet.
        '''

        if self._info is None:
            self._info = self.mglo.info

        return self._info

    def clear(self, red=0.0, green=0.0, blue=0.0, alpha=0.0, depth=1.0, *, viewport=None) -> None:
        '''
            Clear the bound framebuffer. By default clears the :py:data:`screen`.

            If the `viewport` is not ``None`` then scrissor test
            will be used to clear the given viewport.

            If the `viewport` is a 2-tuple it will clear the
            ``(0, 0, width, height)`` where ``(width, height)`` is the 2-tuple.

            If the `viewport` is a 4-tuple it will clear the given viewport.

            Args:
                red (float): color component.
                green (float): color component.
                blue (float): color component.
                alpha (float): alpha component.
                depth (float): depth value.

            Keyword Args:
                viewport (tuple): The viewport.
        '''

        self.mglo.fbo.clear(red, green, blue, alpha, depth, viewport)

    def enable_only(self, flags) -> None:
        '''
            Enable flags.

            - :py:data:`moderngl.NOTHING`
            - :py:data:`moderngl.BLEND`
            - :py:data:`moderngl.DEPTH_TEST`
            - :py:data:`moderngl.CULL_FACE`
            - :py:data:`moderngl.RASTERIZER_DISCARD`

            Args:
                flags (EnableFlag): The flags to enable. Unset flags will be disabled.
        '''

        self.mglo.enable_only(flags)

    def enable(self, flags) -> None:
        '''
            Enable flags.

            For valid flags, please see :py:meth:`enable_only`.

            Args:
                flag (int): The flags to enable.
        '''

        self.mglo.enable(flags)

    def disable(self, flags) -> None:
        '''
            Disable flags.

            For valid flags, please see :py:meth:`enable_only`.

            Args:
                flag (int): The flags to disable.
        '''

        self.mglo.disable(flags)

    def finish(self) -> None:
        '''
            Wait for all drawing commands to finish.
        '''

        self.mglo.finish()

    def copy_buffer(self, dst, src, size=-1, *, read_offset=0, write_offset=0) -> None:
        '''
            Copy buffer content.

            Args:
                dst (Buffer): The destination buffer.
                src (Buffer): The source buffer.
                size (int): The number of bytes to copy.

            Keyword Args:
                read_offset (int): The read offset.
                write_offset (int): The write offset.
        '''

        self.mglo.copy_buffer(dst.mglo, src.mglo, size, read_offset, write_offset)

    def copy_framebuffer(self, dst, src) -> None:
        '''
            Copy framebuffer content.

            Use this method to:

                - blit framebuffers.
                - copy framebuffer content into a texture.
                - downsample framebuffers. (it will allow to read the framebuffer's content)
                - downsample a framebuffer directly to a texture.

            Args:
                dst (Framebuffer or Texture): Destination framebuffer or texture.
                src (Framebuffer): Source framebuffer.
        '''

        self.mglo.copy_framebuffer(dst.mglo, src.mglo)

    def detect_framebuffer(self, glo=None) -> 'Framebuffer':
        '''
            Detect framebuffer.

            Args:
                glo (int): Framebuffer object.

            Returns:
                :py:class:`Framebuffer` object
        '''

        res = Framebuffer.__new__(Framebuffer)
        res.mglo, res._size, res._samples, res._glo = self.mglo.detect_framebuffer(glo)
        res._color_attachments = None
        res._depth_attachment = None
        res.ctx = self
        return res

    def buffer(self, data=None, *, reserve=0, dynamic=False) -> Buffer:
        '''
            Create a :py:class:`Buffer` object.

            Args:
                data (bytes): Content of the new buffer.

            Keyword Args:
                reserve (int): The number of bytes to reserve.
                dynamic (bool): Treat buffer as dynamic.

            Returns:
                :py:class:`Buffer` object
        '''

        if type(reserve) is str:
            reserve = mgl.strsize(reserve)

        res = Buffer.__new__(Buffer)
        res.mglo, res._size, res._glo = self.mglo.buffer(data, reserve, dynamic)
        res._dynamic = dynamic
        res.ctx = self
        return res

    def texture(self, size, components, data=None, *, samples=0, alignment=1, dtype='f1') -> 'Texture':
        '''
            Create a :py:class:`Texture` object.

            Args:
                size (tuple): The width and height of the texture.
                components (int): The number of components 1, 2, 3 or 4.
                data (bytes): Content of the texture.

            Keyword Args:
                samples (int): The number of samples. Value 0 means no multisample format.
                alignment (int): The byte alignment 1, 2, 4 or 8.
                dtype (str): Data type.

            Returns:
                :py:class:`Texture` object
        '''

        res = Texture.__new__(Texture)
        res.mglo, res._glo = self.mglo.texture(size, components, data, samples, alignment, dtype)
        res._size = size
        res._components = components
        res._samples = samples
        res._dtype = dtype
        res._depth = False
        res.ctx = self
        return res

    def texture_array(self, size, components, data=None, *, alignment=1, dtype='f1') -> 'TextureArray':
        '''
            Create a :py:class:`TextureArray` object.

            Args:
                size (tuple): The width, height and layers of the texture.
                components (int): The number of components 1, 2, 3 or 4.
                data (bytes): Content of the texture.

            Keyword Args:
                alignment (int): The byte alignment 1, 2, 4 or 8.
                dtype (str): Data type.

            Returns:
                :py:class:`Texture3D` object
        '''

        res = TextureArray.__new__(TextureArray)
        res.mglo, res._glo = self.mglo.texture_array(size, components, data, alignment, dtype)
        res.ctx = self
        return res

    def texture3d(self, size, components, data=None, *, alignment=1, dtype='f1') -> 'Texture3D':
        '''
            Create a :py:class:`Texture3D` object.

            Args:
                size (tuple): The width, height and depth of the texture.
                components (int): The number of components 1, 2, 3 or 4.
                data (bytes): Content of the texture.

            Keyword Args:
                alignment (int): The byte alignment 1, 2, 4 or 8.
                dtype (str): Data type.

            Returns:
                :py:class:`Texture3D` object
        '''

        res = Texture3D.__new__(Texture3D)
        res.mglo, res._glo = self.mglo.texture3d(size, components, data, alignment, dtype)
        res.ctx = self
        return res

    def texture_cube(self, size, components, data=None, *, alignment=1, dtype='f1') -> 'TextureCube':
        '''
            Create a :py:class:`TextureCube` object.

            Args:
                size (tuple): The width, height and depth of the texture.
                components (int): The number of components 1, 2, 3 or 4.
                data (bytes): Content of the texture.

            Keyword Args:
                alignment (int): The byte alignment 1, 2, 4 or 8.
                dtype (str): Data type.

            Returns:
                :py:class:`TextureCube` object
        '''

        res = TextureCube.__new__(TextureCube)
        res.mglo, res._glo = self.mglo.texture_cube(size, components, data, alignment, dtype)
        res._size = size
        res._components = components
        res._dtype = dtype
        res.ctx = self
        return res

    def depth_texture(self, size, data=None, *, samples=0, alignment=4) -> 'Texture':
        '''
            Create a :py:class:`Texture` object.

            Args:
                size (tuple): The width and height of the texture.
                data (bytes): Content of the texture.

            Keyword Args:
                samples (int): The number of samples. Value 0 means no multisample format.
                alignment (int): The byte alignment 1, 2, 4 or 8.

            Returns:
                :py:class:`Texture` object
        '''

        res = Texture.__new__(Texture)
        res.mglo, res._glo = self.mglo.depth_texture(size, data, samples, alignment)
        res._size = size
        res._components = 1
        res._samples = samples
        res._dtype = 'f4'
        res._depth = True
        res.ctx = self
        return res

    def vertex_array(self, program, content,
                     index_buffer=None, index_element_size=4, *, skip_errors=False) -> 'VertexArray':
        '''
            Create a :py:class:`VertexArray` object.

            Args:
                program (Program): The program used when rendering.
                content (list): A list of (buffer, format, attributes).
                index_buffer (Buffer): An index buffer.

            Keyword Args:
                index_element_size (int): byte size of each index element, 1, 2 or 4.
                skip_errors (bool): Ignore skip_errors varyings.

            Returns:
                :py:class:`VertexArray` object
        '''
        members = program._members
        index_buffer_mglo = None if index_buffer is None else index_buffer.mglo
        content = tuple((a.mglo, b) + tuple(getattr(members.get(x), 'mglo', None) for x in c) for a, b, *c in content)

        res = VertexArray.__new__(VertexArray)
        res.mglo, res._glo = self.mglo.vertex_array(program.mglo, content, index_buffer_mglo,
                                                    index_element_size, skip_errors)
        res._program = program
        res._index_buffer = index_buffer
        res._index_element_size = index_element_size
        res.ctx = self
        return res

    def simple_vertex_array(self, program, buffer, *attributes,
                            index_buffer=None, index_element_size=4) -> 'VertexArray':
        '''
            Create a :py:class:`VertexArray` object.

            Args:
                program (Program): The program used when rendering.
                buffer (Buffer): The buffer.
                attributes (list): A list of attribute names.

            Keyword Args:
                index_element_size (int): byte size of each index element, 1, 2 or 4.
                index_buffer (Buffer): An index buffer.

            Returns:
                :py:class:`VertexArray` object
        '''

        if type(buffer) is list:
            raise SyntaxError('Change simple_vertex_array to vertex_array')

        content = [(buffer, detect_format(program, attributes)) + attributes]
        return self.vertex_array(program, content, index_buffer, index_element_size)

    def program(self, *, vertex_shader, fragment_shader=None, geometry_shader=None,
                tess_control_shader=None, tess_evaluation_shader=None, varyings=()) -> 'Program':
        '''
            Create a :py:class:`Program` object.

            Only linked programs will be returned.

            A single shader in the `shaders` parameter is also accepted.
            The varyings are only used when a transform program is created.

            Args:
                shaders (list): A list of :py:class:`Shader` objects.
                varyings (list): A list of varying names.

            Returns:
                :py:class:`Program` object
        '''

        if type(varyings) is str:
            varyings = (varyings,)

        varyings = tuple(varyings)

        res = Program.__new__(Program)
        res.mglo, ls1, ls2, ls3, ls4, ls5, res._subroutines, res._geom, res._glo = self.mglo.program(
            vertex_shader, fragment_shader, geometry_shader, tess_control_shader, tess_evaluation_shader,
            varyings
        )

        members = {}

        for item in ls1:
            obj = Attribute.__new__(Attribute)
            obj.mglo, obj._location, obj._array_length, obj._dimension, obj._shape, obj._name = item
            members[obj.name] = obj

        for item in ls2:
            obj = Varying.__new__(Varying)
            obj._number, obj._array_length, obj._dimension, obj._name = item
            members[obj.name] = obj

        for item in ls3:
            obj = Uniform.__new__(Uniform)
            obj.mglo, obj._location, obj._array_length, obj._dimension, obj._name = item
            members[obj.name] = obj

        for item in ls4:
            obj = UniformBlock.__new__(UniformBlock)
            obj.mglo, obj._index, obj._size, obj._name = item
            members[obj.name] = obj

        for item in ls5:
            obj = Subroutine.__new__(Subroutine)
            obj._index, obj._name = item
            members[obj.name] = obj

        res._members = members
        res.ctx = self
        return res

    def query(self, *, samples=False, any_samples=False, time=False, primitives=False) -> 'Query':
        '''
            Create a :py:class:`Query` object.

            Keyword Args:
                samples (bool): Query ``GL_SAMPLES_PASSED`` or not.
                any_samples (bool): Query ``GL_ANY_SAMPLES_PASSED`` or not.
                time (bool): Query ``GL_TIME_ELAPSED`` or not.
                primitives (bool): Query ``GL_PRIMITIVES_GENERATED`` or not.
        '''

        res = Query.__new__(Query)
        res.mglo = self.mglo.query(samples, any_samples, time, primitives)
        res.crender = None

        if samples or any_samples:
            res.crender = ConditionalRender.__new__(ConditionalRender)
            res.crender.mglo = res.mglo

        res.ctx = self
        return res

    def scope(self, framebuffer, enable_only=None, *, textures=(), uniform_buffers=(), storage_buffers=()) -> 'Scope':
        '''
            Create a :py:class:`Scope` object.

            Args:
                framebuffer (Framebuffer): The framebuffer to use when entering.
                enable_only (int): The enable_only flags to set when entering.

            Keyword Args:
                textures (list): List of (texture, binding) tuples.
                uniform_buffers (list): List of (buffer, binding) tuples.
                storage_buffers (list): List of (buffer, binding) tuples.
        '''

        textures = tuple((tex.mglo, idx) for tex, idx in textures)
        uniform_buffers = tuple((buf.mglo, idx) for buf, idx in uniform_buffers)
        storage_buffers = tuple((buf.mglo, idx) for buf, idx in storage_buffers)

        res = Scope.__new__(Scope)
        res.mglo = self.mglo.scope(framebuffer.mglo, enable_only, textures, uniform_buffers, storage_buffers)
        res.ctx = self
        return res

    def simple_framebuffer(self, size, components=4, *, samples=0, dtype='f1') -> 'Framebuffer':
        '''
            A :py:class:`Framebuffer` is a collection of buffers that can be used as the destination for rendering.
            The buffers for Framebuffer objects reference images from either Textures or Renderbuffers.

            Args:
                size (tuple): The width and height of the renderbuffer.
                components (int): The number of components 1, 2, 3 or 4.

            Keyword Args:
                samples (int): The number of samples. Value 0 means no multisample format.
                dtype (str): Data type.

            Returns:
                :py:class:`Framebuffer` object
        '''

        return self.framebuffer(
            self.renderbuffer(size, components, samples=samples, dtype=dtype),
            self.depth_renderbuffer(size, samples=samples),
        )

    def framebuffer(self, color_attachments=(), depth_attachment=None) -> 'Framebuffer':
        '''
            A :py:class:`Framebuffer` is a collection of buffers that can be used as the destination for rendering.
            The buffers for Framebuffer objects reference images from either Textures or Renderbuffers.

            Args:
                color_attachments (list): A list of :py:class:`Texture` or :py:class:`Renderbuffer` objects.
                depth_attachment (Renderbuffer or Texture): The depth attachment.

            Returns:
                :py:class:`Framebuffer` object
        '''

        if type(color_attachments) is Texture or type(color_attachments) is Renderbuffer:
            color_attachments = (color_attachments,)

        ca_mglo = tuple(x.mglo for x in color_attachments)
        da_mglo = None if depth_attachment is None else depth_attachment.mglo

        res = Framebuffer.__new__(Framebuffer)
        res.mglo, res._size, res._samples, res._glo = self.mglo.framebuffer(ca_mglo, da_mglo)
        res._color_attachments = tuple(color_attachments)
        res._depth_attachment = depth_attachment
        res.ctx = self
        return res

    def renderbuffer(self, size, components=4, *, samples=0, dtype='f1') -> 'Renderbuffer':
        '''
            :py:class:`Renderbuffer` objects are OpenGL objects that contain images.
            They are created and used specifically with :py:class:`Framebuffer` objects.

            Args:
                size (tuple): The width and height of the renderbuffer.
                components (int): The number of components 1, 2, 3 or 4.

            Keyword Args:
                samples (int): The number of samples. Value 0 means no multisample format.
                dtype (str): Data type.

            Returns:
                :py:class:`Renderbuffer` object
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo, res._glo = self.mglo.renderbuffer(size, components, samples, dtype)
        res._size = size
        res._components = components
        res._samples = samples
        res._dtype = dtype
        res._depth = False
        res.ctx = self
        return res

    def depth_renderbuffer(self, size, *, samples=0) -> 'Renderbuffer':
        '''
            :py:class:`Renderbuffer` objects are OpenGL objects that contain images.
            They are created and used specifically with :py:class:`Framebuffer` objects.

            Args:
                size (tuple): The width and height of the renderbuffer.

            Keyword Args:
                samples (int): The number of samples. Value 0 means no multisample format.

            Returns:
                :py:class:`Renderbuffer` object
        '''

        res = Renderbuffer.__new__(Renderbuffer)
        res.mglo, res._glo = self.mglo.depth_renderbuffer(size, samples)
        res._size = size
        res._components = 1
        res._samples = samples
        res._dtype = 'f4'
        res._depth = True
        res.ctx = self
        return res

    def compute_shader(self, source) -> 'ComputeShader':
        '''
            A :py:class:`ComputeShader` is a Shader Stage that is used entirely for computing arbitrary information.
            While it can do rendering, it is generally used for tasks not directly related to drawing.

            Args:
                source (str): The source of the compute shader.

            Returns:
                :py:class:`ComputeShader` object
        '''

        res = ComputeShader.__new__(ComputeShader)
        res.mglo, res._glo = self.mglo.compute_shader(source)
        res.ctx = self
        return res

    def sampler(self, repeat_x: bool, repeat_y: bool, filter: Tuple[int, int], compare_func: str) -> Sampler:
        '''
            Docstring
        '''

        res = Sampler.__new__(Sampler)
        res.mglo, res._glo = self.mglo.sampler()
        res.ctx = self
        return res

    def core_profile_check(self) -> None:
        '''
            Core profile check.

            FOR DEBUG PURPOSES ONLY
        '''

        profile_mask = self.info['GL_CONTEXT_PROFILE_MASK']
        if profile_mask != 1:
            warnings.warn('The window should request a CORE OpenGL profile')

        version_code = self.version_code
        if not version_code:
            major, minor = map(int, self.info['GL_VERSION'].split('.', 2)[:2])
            version_code = major * 100 + minor * 10

        if version_code < 330:
            warnings.warn('The window should support OpenGL 3.3+ (version_code=%d)' % version_code)

    def release(self) -> None:
        '''
            Release the ModernGL object.
        '''

        self.mglo.release()


def create_context(require=None) -> Context:
    '''
        Create a ModernGL context by loading OpenGL functions from an existing OpenGL context.
        An OpenGL context must exists. If rendering is done without a window please use the
        :py:func:`create_standalone_context` instead.

        Keyword Arguments:
            require (int): OpenGL version code.

        Returns:
            :py:class:`Context` object
    '''

    ctx = Context.__new__(Context)
    ctx.mglo, ctx.version_code = mgl.create_context()
    ctx._screen = ctx.detect_framebuffer(0)
    ctx.fbo = ctx.detect_framebuffer()
    ctx.mglo.fbo = ctx.fbo.mglo
    ctx._info = None

    if require is not None and ctx.version_code < require:
        raise ValueError('The version required is not provided')

    return ctx


def create_standalone_context(require=None, **settings) -> 'Context':
    '''
        Create a standalone ModernGL context.

        Keyword Arguments:
            require (int): OpenGL version code.

        Returns:
            :py:class:`Context` object
    '''

    backend = os.environ.get('MODERNGL_BACKEND')
    if backend is not None:
        settings['backend'] = backend

    ctx = Context.__new__(Context)
    ctx.mglo, ctx.version_code = mgl.create_standalone_context(settings)
    ctx._screen = None
    ctx.fbo = None
    ctx._info = None

    if require is not None and ctx.version_code < require:
        raise ValueError('The version required is not provided')

    return ctx
