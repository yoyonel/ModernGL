import os; os.chdir(os.path.dirname(__file__))
import unittest

import ModernGL as GL
import struct

ctx = GL.create_standalone_context()

vtypes = [
	{
		'type': 'int',
		'input': [-1],
		'output': [-2],
	},
	{
		'type': 'ivec2',
		'input': [-1, -1],
		'output': [-2, -2],
	},
	{
		'type': 'ivec3',
		'input': [-1, -1, -1],
		'output': [-2, -2, -2],
	},
	{
		'type': 'ivec4',
		'input': [-1, -1, -1, -1],
		'output': [-2, -2, -2, -2],
	},
	{
		'type': 'uint',
		'input': [1],
		'output': [2],
	},
	{
		'type': 'uvec2',
		'input': [1, 1],
		'output': [2, 2],
	},
	{
		'type': 'uvec3',
		'input': [1, 1, 1],
		'output': [2, 2, 2],
	},
	{
		'type': 'uvec4',
		'input': [1, 1, 1, 1],
		'output': [2, 2, 2, 2],
	},
	{
		'type': 'float',
		'input': [1.0],
		'output': [2.0],
	},
	{
		'type': 'vec2',
		'input': [1.0, 1.0],
		'output': [2.0, 2.0],
	},
	{
		'type': 'vec3',
		'input': [1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0],
	},
	{
		'type': 'vec4',
		'input': [1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'double',
		'input': [1.0],
		'output': [2.0],
	},
	{
		'type': 'dvec2',
		'input': [1.0, 1.0],
		'output': [2.0, 2.0],
	},
	{
		'type': 'dvec3',
		'input': [1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0],
	},
	{
		'type': 'dvec4',
		'input': [1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat2',
		'input': [1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat2x3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat2x4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat3x2',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat3x4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat4x2',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat4x3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'mat4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat2',
		'input': [1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat2x3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat2x4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat3x2',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat3x4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat4x2',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat4x3',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
	{
		'type': 'dmat4',
		'input': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
		'output': [2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0],
	},
]

class TestCase(unittest.TestCase):

	def test_1(self):
		vert_src = '''
			#version 410

			in %(type)s v_in;
			out %(type)s v_out;

			void main() {
				v_out = v_in * 2;
			}
		'''

		for vtype in vtypes:
			print(vtype['type'])
			prog = ctx.Program(ctx.VertexShader(vert_src % vtype), ['v_out'])
			fmt = GL.detect_format(prog, ['v_in'])
			vbo1 = ctx.Buffer(struct.pack(fmt, *vtype['input']))
			vbo2 = ctx.Buffer(b'\xAA' * struct.calcsize(fmt))
			vao = ctx.SimpleVertexArray(prog, vbo1, fmt, ['v_in'])
			vao.transform(vbo2, GL.POINTS, 1)

			# print(vbo1.read().hex())
			# print(vbo2.read().hex())

			for a, b in zip(struct.unpack(fmt, vbo2.read()), vtype['output']):
				self.assertAlmostEqual(a, b)

	def q_test_2(self):
		vert_src = '''
			#version 410

			in %(type)s v_in[];
			out %(type)s v_out[];

			void main() {
				v_out[0] = v_in[0] * 2;
				v_out[1] = v_in[1] * 2;
			}
		'''

		for vtype in vtypes:
			print(vtype['type'])
			prog = ctx.Program(ctx.VertexShader(vert_src % vtype), ['v_out'])
			fmt = GL.detect_format(prog, ['v_in'])
			vbo1 = ctx.Buffer(struct.pack(fmt, *(vtype['input'] * 2)))
			vbo2 = ctx.Buffer(b'\xAA' * struct.calcsize(fmt))
			vao = ctx.SimpleVertexArray(prog, vbo1, fmt, ['v_in'])
			vao.transform(vbo2, GL.POINTS, 1)

			# print(vbo1.read().hex())
			# print(vbo2.read().hex())

			for a, b in zip(struct.unpack(fmt, vbo2.read()), vtype['output'] * 2):
				self.assertAlmostEqual(a, b)


if __name__ == '__main__':
	unittest.main()
