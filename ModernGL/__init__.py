# pylint: disable=import-error
# pylint: disable=line-too-long
# pylint: disable=wildcard-import
# pylint: disable=mixed-indentation
# pylint: disable=bad-whitespace

'''
	ModernGL: PyOpenGL alternative
'''


VERSION = '3.1.5'
'''
	ModernGL version
'''


from ModernGL import ModernGL as _mgl


Error = _mgl.Error


TRIANGLES = _mgl.TRIANGLES
TRIANGLE_STRIP = _mgl.TRIANGLE_STRIP
TRIANGLE_FAN = _mgl.TRIANGLE_FAN
LINES = _mgl.LINES
LINE_STRIP = _mgl.LINE_STRIP
LINE_LOOP = _mgl.LINE_LOOP
POINTS = _mgl.POINTS
LINE_STRIP_ADJACENCY = _mgl.LINE_STRIP_ADJACENCY
LINES_ADJACENCY = _mgl.LINES_ADJACENCY
TRIANGLE_STRIP_ADJACENCY = _mgl.TRIANGLE_STRIP_ADJACENCY
TRIANGLES_ADJACENCY = _mgl.TRIANGLES_ADJACENCY


class InvalidObject:
	pass


class Attribute:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Attribute.__new__(Attribute)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Buffer:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Buffer.__new__(Buffer)
		r._o = o
		return r


	@property
	def size(self):
		'''
		'''

		return self._o.size


	@property
	def dynamic(self):
		'''
		'''

		return self._o.dynamic


	def release(self):
		'''
			Release the buffer.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	def access(self, size = -1, offset = 0, readonly = False):
		'''
			Keyword Args:
				size: The size.
				offset: The offset.
				readonly: The readonly.
		'''

		return self._o.access(size, offset, readonly)


	def read(self, size = -1, offset = 0):
		'''
			Read the content.

			Args:
				size: The size. Value `-1` means all.

			Keyword Args:
				offset: The offset.

			Returns:
				bytes: binary data.
		'''

		return self._o.read(size, offset)


	def write(self, data, offset = 0):
		'''
			Write the content.

			Args:
				data: The data.

			Keyword Args:
				offset: The offset.
		'''

		self._o.write(data, offset)


	def orphan(self):
		'''
			Orphan the buffer.
		'''

		self._o.orphan()


	def bind_to_uniform_block(self, location = 0):
		'''
		'''

		self._o.bind_to_uniform_block(location)


	def bind_to_storage_buffer(self, location = 0):
		'''
		'''

		self._o.bind_to_storage_buffer(location)


class BufferAccess:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	def __enter__(self):
		return self._o.open()


	def __exit__(self, *args):
		self._o.close()


	@staticmethod
	def _new(o):
		r = BufferAccess.__new__(BufferAccess)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


	def open(self):
		'''
			Map the buffer.
		'''

		return self._o.open()


	def close(self):
		'''
			Unmap the buffer.
		'''

		self._o.close()


	def read(self, size, offset = 0):
		'''
			Read the content.

			Args:
				size: The size. Value `-1` means all.

			Keyword Args:
				offset: The offset.

			Returns:
				bytes: binary data
		'''

		return self._o.read(size, offset)


	def write(self, data, offset = 0):
		'''
			Write the content.

			Args:
				size: The data.

			Keyword Args:
				offset: The offset.
		'''

		return self._o.write(data, offset)


	@property
	def buffer(self):
		'''
			The buffer.
		'''

		return self._o.buffer


	@property
	def offset(self):
		'''
			The offset.
		'''

		return self._o.offset


	@property
	def size(self):
		'''
			The size.
		'''

		return self._o.size


	@property
	def readonly(self):
		'''
			Is readonly.
		'''

		return self._o.readonly


class ComputeShader:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = ComputeShader.__new__(ComputeShader)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class EnableFlag:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = EnableFlag.__new__(EnableFlag)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Framebuffer:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Framebuffer.__new__(Framebuffer)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


	def read(self):
		'''
		'''

		return self._o.read()


	def use(self):
		'''
			Bind the framebuffer. Set the target for the :py:func:`~VertexArray.render` or :py:func:`~VertexArray.transform` methods.
		'''

		self._o.use()


class MultisampleRenderbuffer:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = MultisampleRenderbuffer.__new__(MultisampleRenderbuffer)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class MultisampleTexture:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = MultisampleTexture.__new__(MultisampleTexture)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Primitive:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Primitive.__new__(Primitive)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Program:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Program.__new__(Program)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def uniforms(self):
		'''
		'''

		return self._o.uniforms


	@property
	def uniform_blocks(self):
		'''
		'''

		return self._o.uniform_blocks


	@property
	def attributes(self):
		'''
		'''

		return self._o.attributes


	@property
	def varyings(self):
		'''
		'''

		return self._o.varyings


	@property
	def geometry_input(self):
		'''
		'''

		return self._o.geometry_input


	@property
	def geometry_output(self):
		'''
		'''

		return self._o.geometry_output


	@property
	def geometry_vertices(self):
		'''
		'''

		return self._o.geometry_vertices


	@property
	def vertex_shader(self):
		'''
		'''

		return self._o.vertex_shader


	@property
	def fragment_shader(self):
		'''
		'''

		return self._o.fragment_shader


	@property
	def geometry_shader(self):
		'''
		'''

		return self._o.geometry_shader


	@property
	def tesselation_evaluation_shader(self):
		'''
		'''

		return self._o.tesselation_evaluation_shader


	@property
	def tesselation_control_shader(self):
		'''
		'''

		return self._o.tesselation_control_shader


class ProgramStage:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = ProgramStage.__new__(ProgramStage)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Renderbuffer:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Renderbuffer.__new__(Renderbuffer)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Shader:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Shader.__new__(Shader)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Subroutine:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Subroutine.__new__(Subroutine)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class SubroutineUniform:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = SubroutineUniform.__new__(SubroutineUniform)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Texture:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Texture.__new__(Texture)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Uniform:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Uniform.__new__(Uniform)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class UniformBlock:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = UniformBlock.__new__(UniformBlock)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Varying:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Varying.__new__(Varying)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Version:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Version.__new__(Version)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class VertexArray:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = VertexArray.__new__(VertexArray)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def program(self):
		'''
		'''

		return self._o.program


	@property
	def content(self):
		'''
		'''

		return self._o.content


	@property
	def attributes(self):
		'''
		'''

		return self._o.attributes


	@property
	def index_buffer(self):
		'''
		'''

		return self._o.index_buffer


	@property
	def vertices(self):
		'''
		'''

		return self._o.vertices


	def render(self, mode = TRIANGLES, vertices = -1, first = 0, instances = 1):
		'''
		'''

		self._o.render(mode, vertices, first, instances)


	def transform(self, output, mode = TRIANGLES, vertices = -1, first = 0, instances = 1):
		'''
			Transform vertices.
			Stores the output in a single buffer.
			The transform primitive (mode) must be the same as the input primitive of the GeometryShader.

			Args:
				output: The buffer to store the output.
				optional mode: By default :py:const:`~ModernGL.TRIANGLES` will be used.
				optional vertices: The number of vertices to transform.

			Keyword Args:
				first: The index of the first vertex to start with.
				instances: The number of instances.
		'''

		self._o.transform(output._o, mode, vertices, first, instances)


class VertexArrayAttribute:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = VertexArrayAttribute.__new__(VertexArrayAttribute)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class VertexArrayListAttribute:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = VertexArrayListAttribute.__new__(VertexArrayListAttribute)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class VertexArrayMatrixAttribute:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = VertexArrayMatrixAttribute.__new__(VertexArrayMatrixAttribute)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


class Context:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Context.__new__(Context)
		r._o = o
		return r


	def release(self):
		'''
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def line_width(self):
		'''
		'''

		return self._o.line_width


	@line_width.setter
	def line_width(self, value):
		self._o.line_width = value


	@property
	def point_size(self):
		'''
		'''

		return self._o.point_size


	@point_size.setter
	def point_size(self, value):
		self._o.point_size = value


	@property
	def viewport(self):
		'''
		'''

		return self._o.viewport


	@viewport.setter
	def viewport(self, value):
		self._o.viewport = tuple(value)


	@property
	def default_texture_unit(self):
		'''
		'''

		return self._o.default_texture_unit


	@default_texture_unit.setter
	def default_texture_unit(self, value):
		self._o.default_texture_unit = value


	@property
	def max_texture_units(self):
		'''
		'''

		return self._o.max_texture_units


	@property
	def default_framebuffer(self):
		'''
		'''

		return self._o.default_framebuffer


		self._o.release()


	def clear(self, r = 0, g = 0, b = 0, a = 0):
		'''
		'''

		self._o.clear(r, g, b, a)


	def enable(self, flag):
		'''
		'''

		self._o.enable(flag)


	def disable(self, flag):
		'''
		'''

		self._o.disable(flag)


	def finish(self):
		'''
		'''

		self._o.finish()


	def copy_buffer(self, dst, src, size = -1, read_offset = 0, write_offset = 0):
		'''
		'''

		self._o.copy_buffer(dst._o, src._o, size, read_offset, write_offset)


	def read_pixels(self, x, y, width, height, components = 3, floats = False):
		'''
		'''

		return self._o.read_pixels(x, y, width, height, components, floats)


	def Buffer(self, data = None, reserve = 0, dynamic = False):
		'''
		'''

		return Buffer._new(self._o.Buffer(data, reserve, dynamic))


	def Texture(self, size, components, data = None, floats = False):
		'''
		'''

		return Texture._new(self._o.Texture(size, components, data, floats))


	def DepthTexture(self, size, data = None):
		'''
		'''

		return Texture._new(self._o.DepthTexture(size, data))


	def VertexArray(self, program, content, index_buffer = None, skip_errors = False):
		'''
		'''

		if index_buffer is not None:
			index_buffer = index_buffer._o

		content = list((a._o, b, c) for a, b, c in content) # tuple

		return VertexArray._new(self._o.VertexArray(program._o, list(content), index_buffer, skip_errors)) # tuple


	def SimpleVertexArray(self, program, buffer, format, attributes, index_buffer = None, skip_errors = False):
		'''
		'''

		return self.VertexArray(program, [(buffer, format, attributes)], index_buffer, skip_errors)


	def Program(self, shaders, varyings = []):
		'''
		'''

		if isinstance(shaders, Shader):
			shaders = [shaders]

		return Program._new(self._o.Program([x._o for x in shaders], varyings)) # TODO: tuple


	def VertexShader(self, source):
		'''
		'''

		return Shader._new(self._o.VertexShader(source))


	def FragmentShader(self, source):
		'''
		'''

		return Shader._new(self._o.FragmentShader(source))


	def GeometryShader(self, source):
		'''
		'''

		return Shader._new(self._o.GeometryShader(source))


	def TessEvaluationShader(self, source):
		'''
		'''

		return Shader._new(self._o.TessEvaluationShader(source))


	def TessControlShader(self, source):
		'''
		'''

		return Shader._new(self._o.TessControlShader(source))


	def Framebuffer(self, attachments):
		'''
		'''

		return Framebuffer._new(self._o.Framebuffer(attachments))


	def Renderbuffer(self, size, components, floats = True):
		'''
		'''

		return Renderbuffer._new(self._o.Renderbuffer(size, components, floats))


	def DepthRenderbuffer(self, size, floats = True):
		'''
		'''

		return Renderbuffer._new(self._o.DepthRenderbuffer(size, floats))


	def ComputeShader(self, source):
		'''
		'''

		return ComputeShader._new(self._o.ComputeShader(source))


def create_context(require = None):
	'''
		Create a context and load OpenGL functions.
		An OpenGL context must eWxists.

		Keyword Arguments:
			require (:py:class:`ModernGL.Version`): OpenGL version.

		Returns:
			:py:class:`ModernGL.Context`
	'''

	return Context._new(_mgl.create_context(require))


def create_standalone_context(size = (256, 256), require = None):
	'''
		Create a context and load OpenGL functions.
		An OpenGL context must exists.

		Keyword Arguments:
			size (tuple): Initial framebuffer size.
			require (:py:class:`ModernGL.Version`): OpenGL version.

		Returns:
			:py:class:`ModernGL.Context`
	'''

	return Context._new(_mgl.create_standalone_context(size, require))


def detect_format(program, attributes):
	'''
		detect_format(program, attributes)
	'''

	return ''.join('%d%s' % (program.attributes[a].array_length * program.attributes[a].dimension, program.attributes[a].shape) for a in attributes)
