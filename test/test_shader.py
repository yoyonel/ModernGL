import os; os.chdir(os.path.dirname(__file__))
import unittest

import ModernGL as GL

class TestShader(unittest.TestCase):

	def test_buffer(self):
		ctx = GL.create_standalone_context()
		a = ctx.VertexShader('''
			#version 330

			void main() {
				gl_Position = vec4(0, 0, 0, 0);
			}
		''')
		b = ctx.FragmentShader('''
			#version 330

			out vec4 color;

			void main() {
				color = vec4(0, 0, 0, 0);
			}
		''')
		# print(a.source)
		# print(a, b)

if __name__ == '__main__':
	unittest.main()
