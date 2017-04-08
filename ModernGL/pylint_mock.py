# pylint: disable=import-error
# pylint: disable=line-too-long
# pylint: disable=wildcard-import
# pylint: disable=mixed-indentation
# pylint: disable=bad-whitespace

class Primitive:
	'''
		https://cprogrammer1994.github.io/ModernGL/Primitive.html
	'''

	def __init__(self):
		'''
		'''

TRIANGLES = Primitive()
TRIANGLE_STRIP = Primitive()
TRIANGLE_FAN = Primitive()
LINES = Primitive()
LINE_STRIP = Primitive()
LINE_LOOP = Primitive()
POINTS = Primitive()
LINE_STRIP_ADJACENCY = Primitive()
LINES_ADJACENCY = Primitive()
TRIANGLE_STRIP_ADJACENCY = Primitive()
TRIANGLES_ADJACENCY = Primitive()

class Buffer:
	'''
		https://cprogrammer1994.github.io/ModernGL/Buffer.html
	'''

	def __init__(self, data, reserve = 0, dynamic = False):
		'''
		'''

		self.size = 0
	
	def read(self, size, offset = 0):
		'''
		'''

	def write(self, data, offset = 0):
		'''
		'''

	def access(self, size, offset = 0, readonly = False):
		'''
		'''

	def release(self):
		'''
		'''

class Program:
	'''
		https://cprogrammer1994.github.io/ModernGL/Program.html
	'''

	def __init__(self, shaders, varyings = None):
		'''
		'''

		self.uniforms = {}
		self.uniform_blocks = {}
		self.attributes = {}
		self.varyings = {}

	def release(self):
		'''
		'''

class Shader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

class VertexShader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

	def __init__(self, source):
		'''
		'''

		self.source = ''

	def release(self):
		'''
		'''

class FragmentShader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

	def __init__(self, source):
		'''
		'''

		self.source = ''

	def release(self):
		'''
		'''

class GeometryShader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

	def __init__(self, source):
		'''
		'''

		self.source = ''

	def release(self):
		'''
		'''

class TessEvaluationShader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

	def __init__(self, source):
		'''
		'''

		self.source = ''

	def release(self):
		'''
		'''

class TessControlShader:
	'''
		https://cprogrammer1994.github.io/ModernGL/Shader.html
	'''

	def __init__(self, source):
		'''
		'''

		self.source = ''

	def release(self):
		'''
		'''

class VertexArray:
	'''
		https://cprogrammer1994.github.io/ModernGL/VertexArray.html
	'''

	def __init__(self, program, content, index_buffer = None, skip_errors = False):
		'''
		'''

	def render(self, mode = TRIANGLES, vertices = 1, first = 0, instances = 1):
		'''
		'''

	def transform(self, output, mode = POINTS, vertices = 1, first = 0, instances = 1):
		'''
		'''

	def release(self):
		'''
		'''

class SimpleVertexArray:
	'''
		https://cprogrammer1994.github.io/ModernGL/VertexArray.html
	'''

	def __init__(self, program, buffer, format, attributes, index_buffer = None, skip_errors = False):
		'''
		'''

	def render(self, mode = TRIANGLES, vertices = 1, first = 0, instances = 1):
		'''
		'''

	def transform(self, output, mode = POINTS, vertices = 1, first = 0, instances = 1):
		'''
		'''

	def release(self):
		'''
		'''

class Framebuffer:
	'''
		https://cprogrammer1994.github.io/ModernGL/Framebuffer.html
	'''

	def __init__(self, attachments):
		'''
		'''

	def release(self):
		'''
		'''

class Renderbuffer:
	'''
		https://cprogrammer1994.github.io/ModernGL/Renderbuffer.html
	'''

	def __init__(self, size, components, floats = True):
		'''
		'''

	def release(self):
		'''
		'''

class DepthRenderbuffer:
	'''
		https://cprogrammer1994.github.io/ModernGL/DepthRenderbuffer.html
	'''

	def __init__(self, size):
		'''
		'''

	def release(self):
		'''
		'''

class Texture:
	'''
		https://cprogrammer1994.github.io/ModernGL/Texture.html
	'''

	def __init__(self, size, components, data = None, floats = False):
		'''
		'''

	def release(self):
		'''
		'''

class DepthTexture:
	'''
		https://cprogrammer1994.github.io/ModernGL/DepthTexture.html
	'''

	def __init__(self, size, data = None):
		'''
		'''

	def release(self):
		'''
		'''

class MultisampleRenderbuffer:
	'''
		https://cprogrammer1994.github.io/ModernGL/MultisampleRenderbuffer.html
	'''

class MultisampleTexture:
	'''
		https://cprogrammer1994.github.io/ModernGL/MultisampleTexture.html
	'''

class Context:
	'''
		https://cprogrammer1994.github.io/ModernGL/Context.html
	'''

	def __init__(self):
		'''
		'''

		self.Buffer = Buffer
		self.Program = Program
		self.Shader = Shader
		self.VertexShader = VertexShader
		self.FragmentShader = FragmentShader
		self.GeometryShader = GeometryShader
		self.TessEvaluationShader = TessEvaluationShader
		self.TessControlShader = TessControlShader
		self.VertexArray = VertexArray
		self.SimpleVertexArray = SimpleVertexArray
		self.Framebuffer = Framebuffer
		self.Renderbuffer = Renderbuffer
		self.Texture = Texture
		self.DepthRenderbuffer = DepthRenderbuffer
		self.DepthTexture = DepthTexture
		self.MultisampleRenderbuffer = MultisampleRenderbuffer
		self.MultisampleTexture = MultisampleTexture

	def clear(self, r = 0, g = 0, b = 0, a = 0):
		'''
		'''

	def release(self):
		'''
		'''

def create_context():
	'''
		https://cprogrammer1994.github.io/ModernGL/ModernGL.html#ModernGL.create_context
	'''

	return Context()

def create_standalone_context():
	'''
		https://cprogrammer1994.github.io/ModernGL/ModernGL.html#ModernGL.create_standalone_context
	'''

	return Context()
