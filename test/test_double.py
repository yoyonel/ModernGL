import os; os.chdir(os.path.dirname(__file__))
import unittest

import ModernGL as GL
import struct

ctx = GL.create_standalone_context()

class TestCase(unittest.TestCase):
	def test_1(self):
		vert_src = '''
			#version 410

			in double v_in;
			out double v_out;

			void main() {
				v_out = float(v_in);
			}
		'''

		prog = ctx.Program(ctx.VertexShader(vert_src), ['v_out'])

		vbo1 = ctx.Buffer(struct.pack('1d', 1.0) + b'\xAA' * 24)
		vbo2 = ctx.Buffer(b'\xAA' * 32)

		vao = ctx.SimpleVertexArray(prog, vbo1, '1d', ['v_in'])
		vao.transform(vbo2, GL.POINTS, 1)

		# print(vbo1.read().hex())
		# print(vbo2.read().hex())


if __name__ == '__main__':
	unittest.main()
