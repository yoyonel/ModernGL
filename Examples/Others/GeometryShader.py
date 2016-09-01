import GLWindow as WND
import ModernGL as GL
import numpy, random
import math

WND.Init()
GL.Init()

points = GL.NewProgram([
	GL.NewVertexShader('''
		#version 330 core

		in vec2 vert;
		uniform vec2 scale;

		void main() {
			gl_Position = vec4(vert / scale, 0.0, 1.0);
		}
	'''),
	GL.NewGeometryShader('''
		#version 330 core

		layout(points) in;
		layout(line_strip, max_vertices = 17) out;

		uniform vec2 scale;

		void main() {
			for (int i = 0; i <= 16; ++i) {
				float a = 3.14159265 * 2.0 * ((i * 6) / 16.0);
				vec2 move = vec2(cos(a) * 0.1, sin(a) * 0.1) / scale;
				gl_Position = gl_in[0].gl_Position + vec4(move, 0.0, 1.0);
				EmitVertex();
			}
			EndPrimitive();
		}
	'''),
	GL.NewFragmentShader('''
		#version 330 core

		out vec4 color;

		void main() {
			color = vec4(0.05, 0.05, 0.05, 1.0);
		}
	'''),
])

width, height = WND.GetSize()

GL.SetUniform(points['scale'], 10, 10 * height / width)

def vec(a, r = 1):
	return [math.cos(a) * r, math.sin(a) * r]

def rvec(a, b):
	return vec(random.uniform(0.0, math.pi * 2.0), random.uniform(a, b))

P = numpy.array([[0.0, 0.0] for i in range(100)])
V = numpy.array([rvec(0.01, 0.05) for i in range(100)])

vbo = GL.NewVertexBuffer(P, dynamic = True)
vao = GL.NewVertexArray(points, vbo, '2d', ['vert'])

while WND.Update():
	P += V
	GL.Clear(240, 240, 240)
	GL.RenderPoints(vao, 100)
	GL.UpdateVertexBuffer(vbo, 0, P)

	if WND.KeyPressed(' '):
		P = numpy.array([[0.0, 0.0] for i in range(100)])
		V = numpy.array([rvec(0.01, 0.05) for i in range(100)])
