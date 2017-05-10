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


InvalidObject = _mgl.InvalidObject


class Attribute:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Attribute.__new__(Attribute)
		r._o = o
		return r


class Buffer:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Buffer.__new__(Buffer)
		r._o = o
		return r


class BufferAccess:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = BufferAccess.__new__(BufferAccess)
		r._o = o
		return r


class ComputeShader:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = ComputeShader.__new__(ComputeShader)
		r._o = o
		return r


class EnableFlag:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = EnableFlag.__new__(EnableFlag)
		r._o = o
		return r


class Framebuffer:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Framebuffer.__new__(Framebuffer)
		r._o = o
		return r


class MultisampleRenderbuffer:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = MultisampleRenderbuffer.__new__(MultisampleRenderbuffer)
		r._o = o
		return r


class MultisampleTexture:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = MultisampleTexture.__new__(MultisampleTexture)
		r._o = o
		return r


class Primitive:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Primitive.__new__(Primitive)
		r._o = o
		return r


class Program:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Program.__new__(Program)
		r._o = o
		return r


class ProgramStage:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = ProgramStage.__new__(ProgramStage)
		r._o = o
		return r


class Renderbuffer:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Renderbuffer.__new__(Renderbuffer)
		r._o = o
		return r


class Shader:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Shader.__new__(Shader)
		r._o = o
		return r


class Subroutine:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Subroutine.__new__(Subroutine)
		r._o = o
		return r


class SubroutineUniform:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = SubroutineUniform.__new__(SubroutineUniform)
		r._o = o
		return r


class Texture:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Texture.__new__(Texture)
		r._o = o
		return r


class Uniform:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Uniform.__new__(Uniform)
		r._o = o
		return r


class UniformBlock:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = UniformBlock.__new__(UniformBlock)
		r._o = o
		return r


class Varying:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Varying.__new__(Varying)
		r._o = o
		return r


class Version:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Version.__new__(Version)
		r._o = o
		return r


class VertexArray:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = VertexArray.__new__(VertexArray)
		r._o = o
		return r


class VertexArrayAttribute:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = VertexArrayAttribute.__new__(VertexArrayAttribute)
		r._o = o
		return r


class VertexArrayListAttribute:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = VertexArrayListAttribute.__new__(VertexArrayListAttribute)
		r._o = o
		return r


class VertexArrayMatrixAttribute:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = VertexArrayMatrixAttribute.__new__(VertexArrayMatrixAttribute)
		r._o = o
		return r


class Context:
	'''
	'''

	def __init__(self):
		pass


	@staticmethod
	def _new(o):
		r = Context.__new__(Context)
		r._o = o
		return r


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


	def release(self):
		'''
		'''

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

		self._o.copy_buffer(dst, src, size, read_offset, write_offset)


	def read_pixels(self, x, y, width, height, components = 3, floats = False):
		'''
		'''

		return self._o.read_pixels(x, y, width, height, components, floats)


	def Buffer(self, data, reserve = 0, dynamic = False):
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

		return VertexArray._new(self._o.VertexArray(program, content, index_buffer, skip_errors))


	def SimpleVertexArray(self, program, buffer, format, attributes, index_buffer = None, skip_errors = False):
		'''
		'''

		return VertexArray._new(self.VertexArray(program, [(buffer, format, attributes)], index_buffer, skip_errors))


	def Program(self, shaders, varyings = None):
		'''
		'''

		return Program._new(self._o.Program(shaders, varyings))


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
		An OpenGL context must exists.

		Keyword Arguments:
			require (:py:class:`ModernGL.Version`): OpenGL version.

		Returns:
			:py:class:`ModernGL.Context`
	'''

	return _mgl.create_context(require)


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

	return _mgl.create_standalone_context(size, require)


def detect_format(program, attributes):
	'''
		detect_format(program, attributes)
	'''

	return ''.join('%d%s' % (program.attributes[a].array_length * program.attributes[a].dimension, program.attributes[a].shape) for a in attributes)
