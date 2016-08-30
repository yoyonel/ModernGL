import numpy as np
import ModernGL as GL
import GLWindow as WND

WND.Init()
GL.Init()

prog = GL.NewProgram([
	GL.NewVertexShader('''
		#version 330 core
		in vec2 vert;
		void main() {
			gl_Position = vec4(vert, 0.0, 1.0);
		}
	'''),
	GL.NewFragmentShader('''
		#version 330 core
		out vec4 color;
		void main() {
			color = vec4(0.2, 0.6, 0.9, 1.0);
		}
	'''),
])

vbo = GL.NewVertexBuffer(np.array([[0.0, 0.0], [0.0, 1.0], [1.0, 0.0]]))
vao = GL.NewVertexArray(prog, vbo, '2d', ['vert'])

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.RenderTriangles(vao, 3)
