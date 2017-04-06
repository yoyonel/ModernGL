import unittest

import ModernGL, struct

class TestCase(unittest.TestCase):

	@classmethod
	def setUpClass(cls):
		cls.ctx = ModernGL.create_standalone_context()

		cls.vert = cls.ctx.VertexShader('''
			#version 330

			in mat2 in_m;
			in vec2 in_v;

			out vec2 out_v;

			uniform Block {
				float x;
			};

			void main() {
				out_v = in_m * in_v * x;
			}
		''')

		cls.prog = cls.ctx.Program(cls.vert, ['out_v'])

	@classmethod
	def tearDownClass(cls):
		cls.vert.release()
		cls.prog.release()
		cls.ctx.release()

	def test_1(self):
		buf_m = self.ctx.Buffer(struct.pack('4f', 1, 1, 1, 2))
		buf_v = self.ctx.Buffer(struct.pack('2f', 4, 7))
		res = self.ctx.Buffer(reserve = buf_v.size)

		vao = self.ctx.VertexArray(self.prog, [
			(buf_m, '4f', ['in_m']),
			(buf_v, '2f', ['in_v']),
		])

		print(self.prog.uniforms)
		print(self.prog.uniform_blocks)

		vao.release()


if __name__ == '__main__':
	unittest.main()
