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


BLEND = _mgl.BLEND
'''
	GL_BLEND
'''

DEPTH_TEST = _mgl.DEPTH_TEST
'''
	GL_DEPTH_TEST
'''

CULL_FACE = _mgl.CULL_FACE
'''
	GL_CULL_FACE
'''

MULTISAMPLE = _mgl.MULTISAMPLE
'''
	GL_MULTISAMPLE
'''

TRIANGLES = _mgl.TRIANGLES
'''
	GL_TRIANGLES
'''

TRIANGLE_STRIP = _mgl.TRIANGLE_STRIP
'''
	GL_TRIANGLE_STRIP
'''

TRIANGLE_FAN = _mgl.TRIANGLE_FAN
'''
	GL_TRIANGLE_FAN
'''

LINES = _mgl.LINES
'''
	GL_LINES
'''

LINE_STRIP = _mgl.LINE_STRIP
'''
	GL_LINE_STRIP
'''

LINE_LOOP = _mgl.LINE_LOOP
'''
	GL_LINE_LOOP
'''

POINTS = _mgl.POINTS
'''
	GL_POINTS
'''

LINE_STRIP_ADJACENCY = _mgl.LINE_STRIP_ADJACENCY
'''
	GL_LINE_STRIP_ADJACENCY
'''

LINES_ADJACENCY = _mgl.LINES_ADJACENCY
'''
	GL_LINES_ADJACENCY
'''

TRIANGLE_STRIP_ADJACENCY = _mgl.TRIANGLE_STRIP_ADJACENCY
'''
	GL_TRIANGLE_STRIP_ADJACENCY
'''

TRIANGLES_ADJACENCY = _mgl.TRIANGLES_ADJACENCY
'''
	GL_TRIANGLES_ADJACENCY
'''


class Version:
	'''
	'''

	def __init__(self, major, minor):
		self.major = major
		self.minor = minor


CORE_330 = Version(3, 3)
'''
	OpenGL 3.3
'''

CORE_400 = Version(4, 0)
'''
	OpenGL 4.0
'''

CORE_410 = Version(4, 1)
'''
	OpenGL 4.1
'''

CORE_420 = Version(4, 2)
'''
	OpenGL 4.2
'''

CORE_430 = Version(4, 3)
'''
	OpenGL 4.3
'''

CORE_440 = Version(4, 4)
'''
	OpenGL 4.4
'''

CORE_450 = Version(4, 5)
'''
	OpenGL 4.5
'''


class UniformMap:
	'''
	'''

	def __init__(self):
		self._o = {}
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = UniformMap.__new__(UniformMap)
		r._o = o
		return r


	def __getitem__(self, key):
		'''
		'''

		return Uniform._new(self._o[key])


	def __contains__(self, key):
		return key in self._o


	def __len__(self):
		return len(self._o)


class AttributeMap:
	'''
	'''

	def __init__(self):
		self._o = {}
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = UniformMap.__new__(UniformMap)
		r._o = o
		return r


	def __getitem__(self, key):
		'''
		'''

		return Attribute._new(self._o[key])


	def __contains__(self, key):
		return key in self._o


	def __len__(self):
		return len(self._o)


class InvalidObject:
	'''
		A ModernGL object turns into an InvalidObject once the release method is successfully called.
	'''

	pass # TODO:


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


class Buffer:
	'''
		Create a :py:class:`~ModernGL.Buffer` using :py:meth:`~ModernGL.Context.Buffer`.
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
			The size of the buffer.
		'''

		return self._o.size


	@property
	def dynamic(self):
		'''
			Is the buffer created with the dynamic flag?
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
			Create a buffer access object.

			Keyword Args:
				size: The size.
				offset: The offset.
				readonly: The readonly.
		'''

		return BufferAccess._new(self._o.access(size, offset, readonly))


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
			Bind the buffer to a uniform block.

			Args:
				location: The uniform block location.
		'''

		self._o.bind_to_uniform_block(location)


	def bind_to_storage_buffer(self, location = 0):
		'''
			Bind the buffer to a shader storage buffer.

			Args:
				location: The shader storage location.
		'''

		self._o.bind_to_storage_buffer(location)


class BufferAccess:
	'''
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	def __enter__(self):
		self._o.open()
		return self


	def __exit__(self, *args):
		self._o.close()


	@staticmethod
	def _new(o):
		r = BufferAccess.__new__(BufferAccess)
		r._o = o
		return r


	def open(self):
		'''
			Map the buffer.
		'''

		self._o.open()


	def close(self):
		'''
			Unmap the buffer.
		'''

		self._o.close()


	def read(self, size = -1, offset = 0):
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
			Release the framebuffer.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	def read(self, size = None, origin = (0, 0), components = 3, floats = False):
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


	# def use # TODO:
	'''
		Args:
		optional index: The texture location.
			Same as the integer value that is used for sampler2D uniforms in the shaders.
			The value ``0`` will bind the texture to the ``GL_TEXTURE0`` binding point.
	'''


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
			Release the program object.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def uniforms(self):
		'''
			The program's uniforms.
			The return value is a dictinary.
			It can be used to access uniforms by name.
		'''

		return UniformMap._new(self._o.uniforms)


	@property
	def uniform_blocks(self):
		'''
			The program's uniform blocks.
			The return value is a dictinary.
			It can be used to access uniform blocks by name.
		'''

		return self._o.uniform_blocks


	@property
	def attributes(self):
		'''
			The program's attributes.
			The return value is a dictinary.
			It can be used to access attributes by name.
		'''

		return self._o.attributes


	@property
	def varyings(self):
		'''
			The program's varyings.
			The return value is a dictinary.
			It can be used to access varyings by name.
		'''

		return self._o.varyings


	@property
	def geometry_input(self):
		'''
			The geometry input primitive.
			The GeometryShader's input primitive if the GeometryShader is present otherwise ``None``.
			The geometry input primitive will be used for validation when rendering.
		'''

		return self._o.geometry_input


	@property
	def geometry_output(self):
		'''
			The geometry output primitive.
			The GeometryShader's output primitive if the GeometryShader is present otherwise ``None``.
		'''

		return self._o.geometry_output


	@property
	def geometry_vertices(self):
		'''
			The maximum number of vertices that the geometry shader in program will output.
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
		Create a :py:class:`~ModernGL.Shader` using:

			- :py:meth:`~ModernGL.Context.VertexShader`
			- :py:meth:`~ModernGL.Context.FragmentShader`
			- :py:meth:`~ModernGL.Context.GeometryShader`
			- :py:meth:`~ModernGL.Context.TessEvaluationShader`
			- :py:meth:`~ModernGL.Context.TessControlShader`
	'''

	def __init__(self):
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Shader.__new__(Shader)
		r._o = o
		return r


	@property
	def source(self):
		'''
			The source code of the shader.
		'''

		return self._o.source


	@property
	def typename(self):
		'''
			The type of the shader.
			The return value is a string.

			- ``'VertexShader'``
			- ``'FragmentShader'``
			- ``'GeometryShader'``
			- ``'TessEvaluationShader'``
			- ``'TessControlShader'``
		'''

		return self._o.typename


	def release(self):
		'''
			Release the shader object.
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


	@property
	def width(self):
		'''
		'''

		return self._o.width


	@property
	def height(self):
		'''
		'''

		return self._o.height


	@property
	def size(self):
		'''
		'''

		return (self._o.width, self._o.height)


	def release(self):
		'''
			Release the texture object.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	def update(self, data, size = None, offset = (0, 0)):
		'''

		'''

		self._o.update()


	def use(self, index = 0):
		'''
			Bind the texture.

			Args:
				index (int): The texture location.
					Same as the integer value that is used for sampler2D uniforms in the shaders.
					The value ``0`` will bind the texture to the ``GL_TEXTURE0`` binding point.
		'''

		self._o.use(index)


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


	@property
	def name(self):
		'''
		'''

		return self._o.name


	@property
	def location(self):
		'''
		'''

		return self._o.location


	@property
	def dimension(self):
		'''
		'''

		return self._o.dimension


	@property
	def array_length(self):
		'''
		'''

		return self._o.array_length


	@property
	def value(self):
		'''
		'''

		return self._o.value


	@value.setter
	def value(self, value):
		self._o.value = value


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
			Release the vertex array object.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def program(self):
		'''
			The program assinged to the VertexArray.
			The program will be used automatically when rendering and transforming.
		'''

		return self._o.program


	@property
	def content(self):
		'''
			The content assinged to the VertexArray.
		'''

		return self._o.content


	@property
	def attributes(self):
		'''
			Individual vertex attributes.
			Use the bind() method to assign vertex attributes to buffers.
		'''

		return self._o.attributes


	@property
	def index_buffer(self):
		'''
			The index buffer if the index_buffer is set otherwise ``None``.
		'''

		return self._o.index_buffer


	@property
	def vertices(self):
		'''
			The number of vertices detected.
			This is the minimum of the number of vertices possible per Buffer.
			The size of the index_buffer will be used when the VertexArray has a valid index_buffer set.
			Per instance vertex attributes does not affect this number.
		'''

		return self._o.vertices


	def render(self, mode = TRIANGLES, vertices = -1, first = 0, instances = 1):
		'''
			The render primitive (mode) must be the same as the input primitive of the GeometryShader.

			Args:
				optional mode: By default :py:const:`~ModernGL.TRIANGLES` will be used.
				optional vertices: The number of vertices to transform.

			Keyword Args:
				first: The index of the first vertex to start with.
				instances: The number of instances.
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
		self._o = None
		raise NotImplementedError()


	@staticmethod
	def _new(o):
		r = Context.__new__(Context)
		r._o = o
		return r


	def release(self):
		'''
			Release the OpenGL context.
		'''

		self._o.release()
		self.__class__ = InvalidObject


	@property
	def line_width(self):
		'''
			Set the default line width.
		'''

		return self._o.line_width


	@line_width.setter
	def line_width(self, value):
		self._o.line_width = value


	@property
	def point_size(self):
		'''
			Set the default point size.
		'''

		return self._o.point_size


	@point_size.setter
	def point_size(self, value):
		self._o.point_size = value


	@property
	def viewport(self):
		'''
			The viewport.
		'''

		return self._o.viewport


	@viewport.setter
	def viewport(self, value):
		self._o.viewport = tuple(value)


	@property
	def default_texture_unit(self):
		'''
			The default texture unit.
		'''

		return self._o.default_texture_unit


	@default_texture_unit.setter
	def default_texture_unit(self, value):
		self._o.default_texture_unit = value


	@property
	def max_texture_units(self):
		'''
			The max texture units.
		'''

		return self._o.max_texture_units


	@property
	def default_framebuffer(self):
		'''
			The default framebuffer.
		'''

		return self._o.default_framebuffer


		self._o.release()


	def clear(self, r = 0, g = 0, b = 0, a = 0):
		'''
			Clear the framebuffer.

			Args:
				r, g, b: color components.
				a: alpha component.
		'''

		self._o.clear(r, g, b, a)


	def enable(self, flag):
		'''
			Enable flags.

			Args:
				flags: flags to enable.
		'''

		self._o.enable(flag)


	def disable(self, flag):
		'''
			Disable flags.

			Args:
				flags: flags to disable.
		'''

		self._o.disable(flag)


	def finish(self):
		'''
			Wait for all drawing commands to finish.
		'''

		self._o.finish()


	def copy_buffer(self, dst, src, size = -1, read_offset = 0, write_offset = 0):
		'''
			Copy buffer content.

			Args:
				dst: Destination buffer.
				src: Source buffer.
				optional size: Size to copy.

			Keyword Args:
				read_offset: Read offset.
				write_offset: Write offset.
		'''

		self._o.copy_buffer(dst._o, src._o, size, read_offset, write_offset)


	# TODO:
	# def read_pixels(self, size = None, origin = (0, 0), components = 3, floats = False):
	# 	'''
	# 	'''

	# 	return self._o.read_pixels(x, y, width, height, components, floats)


	def Buffer(self, data = None, reserve = 0, dynamic = False):
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

		return Buffer._new(self._o.Buffer(data, reserve, dynamic))


	def Texture(self, size, components, data = None, floats = False):
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

		return Texture._new(self._o.Texture(size, components, data, floats))


	def DepthTexture(self, size, data = None):
		'''
			Create a DepthTexture.

			Args:
				size: The width and height.
				optional data: The pixels.

			Returns:
				:py:class:`Texture`
		'''

		return Texture._new(self._o.DepthTexture(size, data))


	def VertexArray(self, program, content, index_buffer = None, skip_errors = False):
		'''
			Create a VertexArray.

			Args:
				program: The program used by :py:meth:`~VertexArray.render` and :py:meth:`~VertexArray.transform`.
				content: A list of (buffer, format, attributes).
				optional index_buffer: An index buffer.

			Keyword Args:
				skip_errors: Ignore missing attributes.

			Returns:
				:py:class:`VertexArray`
		'''

		if index_buffer is not None:
			index_buffer = index_buffer._o

		content = list((a._o, b, c) for a, b, c in content) # tuple

		return VertexArray._new(self._o.VertexArray(program._o, list(content), index_buffer, skip_errors)) # tuple


	def SimpleVertexArray(self, program, buffer, format, attributes, index_buffer = None, skip_errors = False):
		'''
			Create a SimpleVertexArray.

			Args:
				program: The program used by :py:meth:`~VertexArray.render` and :py:meth:`~VertexArray.transform`.
				buffer: The buffer.
				format: The buffer format string.
				attributes: A list of attribute names.
				optional index_buffer: An index buffer.

			Keyword Args:
				skip_errors: Ignore missing attributes.

			Returns:
				:py:class:`VertexArray`
		'''

		return self.VertexArray(program, [(buffer, format, attributes)], index_buffer, skip_errors)


	def Program(self, shaders, varyings = []):
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

		return Program._new(self._o.Program([x._o for x in shaders], varyings)) # TODO: tuple


	def VertexShader(self, source):
		'''
			Create a VertexShader.

			Args:
				source: The source code in GLSL.

			Returns:
				:py:class:`Shader`
		'''

		return Shader._new(self._o.VertexShader(source))


	def FragmentShader(self, source):
		'''
			Create a FragmentShader.

			Args:
				source: The source code in GLSL.

			Returns:
				:py:class:`Shader`
		'''

		return Shader._new(self._o.FragmentShader(source))


	def GeometryShader(self, source):
		'''
			Create a GeometryShader.

			Args:
				source: The source code in GLSL.

			Returns:
				:py:class:`Shader`
		'''

		return Shader._new(self._o.GeometryShader(source))


	def TessEvaluationShader(self, source):
		'''
			Create a TessEvaluationShader.

			Args:
				source: The source code in GLSL.

			Returns:
				:py:class:`Shader`
		'''

		return Shader._new(self._o.TessEvaluationShader(source))


	def TessControlShader(self, source):
		'''
			Create a TessControlShader.

			Args:
				source: The source code in GLSL.

			Returns:
				:py:class:`Shader`
		'''

		return Shader._new(self._o.TessControlShader(source))


	def Framebuffer(self, attachments):
		'''
			Create a Framebuffer.

			Args:
				attachments: A list of :py:class:`Texture` or :py:class:`Renderbuffer` objects.

			Returns:
				:py:class:`Framebuffer`
		'''

		return Framebuffer._new(self._o.Framebuffer(attachments))


	def Renderbuffer(self, size, components, floats = True):
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

		return Renderbuffer._new(self._o.Renderbuffer(size, components, floats))


	def DepthRenderbuffer(self, size, floats = True):
		'''
			Create a Renderbuffer.

			Args:
				size: Width, height.

			Keyword Args:
				floats: Use floating point precision.

			Returns:
				:py:class:`Renderbuffer`
		'''

		return Renderbuffer._new(self._o.DepthRenderbuffer(size, floats))


	def ComputeShader(self, source):
		'''
			Create a ComputeShader.

			Args:
				source: The source of the compute shader.

			Returns:
				:py:class:`ComputeShader`
		'''

		return ComputeShader._new(self._o.ComputeShader(source))


def create_context(require = None) -> Context:
	'''
		Create a context and load OpenGL functions.
		An OpenGL context must exists.

		Keyword Arguments:
			require (Version): OpenGL version.
	'''

		# Returns:
		# 	Context

	return Context._new(_mgl.create_context())


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

	width, height = size

	return Context._new(_mgl.create_standalone_context(width, height))


def detect_format(program, attributes):
	'''
		detect_format(program, attributes)
	'''

	return ''.join('%d%s' % (program.attributes[a].array_length * program.attributes[a].dimension, program.attributes[a].shape) for a in attributes)
