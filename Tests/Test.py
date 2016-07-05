import os, sys, unittest, importlib
import ModernGL as GL
import GLContext

class Case1_Failsafe(unittest.TestCase):
	def setUp(self):
		GLContext.Context(False)


	def test_init(self):
		with self.assertRaises(GL.Error):
			GL.InitializeModernGL()

		self.assertEqual(GL.ExtensionActive(), False)

		with self.assertRaises(GL.Error):
			GL.Viewport(0, 0, 10, 10)


class Case2_Methods(unittest.TestCase):
	def setUp(self):
		GLContext.Context(True)
		GL.InitializeModernGL()
	

	def test_init(self):
		GL.Viewport(0, 0, 10, 10)
	

	def test_vert_frag_vao(self):
		vert_sdr = GL.NewVertexShader('''
			#version 330
			in vec2 vert;
			void main() {
				gl_Position = vec4(vert, 0.0, 1.0);
			}
		''')

		self.assertIs(type(vert_sdr), GL.Shader)

		frag_sdr = GL.NewFragmentShader('''
			#version 330
			out vec4 color;
			void main() {
				color = vec4(0.30, 0.50, 1.00, 1.0);
			}
		''')

		self.assertIs(type(frag_sdr), GL.Shader)

		with self.assertRaises(GL.Error):
			prog = GL.NewProgram([vert_sdr, vert_sdr])
		
		prog = GL.NewProgram([vert_sdr, frag_sdr])

		self.assertIs(type(prog), GL.Program)

		with self.assertRaises(GL.Error):
			vert = GL.AttributeLocation(prog, 'vert')

		vert = GL.GetAttributeLocation(prog, 'vert')
		self.assertIs(type(vert), GL.AttributeLocation)

		vbo = GL.NewVertexBuffer(b'\x00' * 1024)
		self.assertIs(type(vbo), GL.VertexBuffer)

		ibo = GL.NewIndexBuffer(b'\x00' * 1024)
		self.assertIs(type(ibo), GL.IndexBuffer)

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('', [], ibo)

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('2f2i', [], ibo)

		with self.assertRaises(TypeError):
			vao = GL.NewVertexArray('2f2i', [(vbo, 0), (vbo, 0)], ibo)

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('2f', [vbo, vert])

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('5f', [(vbo, vert)])

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('f', [(vbo, vert)])

		with self.assertRaises(GL.Error):
			vao = GL.NewVertexArray('f', [(vbo, vert), (vbo, vert)])

		vao = GL.NewVertexArray('2f', [(vbo, vert)], ibo)

		self.assertIs(type(vao), GL.VertexArray)


	def test_buffers(self):
		vbo = GL.NewVertexBuffer(b'\x00' * 1024)
		self.assertIs(type(vbo), GL.VertexBuffer)

		ibo = GL.NewIndexBuffer(b'\x00' * 1024)
		self.assertIs(type(ibo), GL.IndexBuffer)

		ubo = GL.NewUniformBuffer(b'\x00' * 1024)
		self.assertIs(type(ubo), GL.UniformBuffer)

		sbo = GL.NewStorageBuffer(b'\x00' * 1024)
		self.assertIs(type(sbo), GL.StorageBuffer)


	def test_fbo(self):
		fbo, color, depth = GL.NewFramebuffer()
		self.assertIs(type(fbo), GL.Framebuffer)
		self.assertIs(type(color), GL.Texture)
		self.assertIs(type(depth), GL.Texture)


	def test_texture(self):
		tex = GL.NewTexture(4, 4, b'\x00' * 1024)
		self.assertIs(type(tex), GL.Texture)

		GL.SetTexturePixelated(tex)
		GL.SetTextureFiltered(tex)
		GL.SetTextureMipmapped(tex)
		GL.BuildMipmap(tex)


class Case3_Complete(unittest.TestCase):
	def test_full(self):
		vert_sdr = GL.NewVertexShader('''
			#version 330
			in vec2 vert;
			void main() {
				gl_Position = vec4(vert, 0.0, 1.0);
			}
		''')

		self.assertIs(type(vert_sdr), GL.Shader)

		frag_sdr = GL.NewFragmentShader('''
			#version 330
			out vec4 color;
			void main() {
				color = vec4(0.30, 0.50, 1.00, 1.0);
			}
		''')

		self.assertIs(type(frag_sdr), GL.Shader)

		prog = GL.NewProgram([vert_sdr, frag_sdr])
		
		self.assertIs(type(prog), GL.Program)

		print(prog)

if __name__ == '__main__':
	major = sys.hexversion >> 24
	if major >= 3:
		unittest.main(verbosity = 2, warnings = False)
	else:
		unittest.main(verbosity = 2)
