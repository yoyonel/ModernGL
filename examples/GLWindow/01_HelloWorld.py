import ModernGL, GLWindow
import struct

GLWindow.Init()

GL = ModernGL.create_context()

vert = GL.VertexShader('''
	#version 330

	in vec2 vert;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
	}
''')

frag = GL.FragmentShader('''
	#version 330

	out vec4 color;

	void main() {
		color = vec4(0.3, 0.5, 1.0, 1.0);
	}
''')

prog = GL.Program([vert, frag])

vbo = GL.Buffer(struct.pack('6f',
	0.0, 0.8,
	-0.6, -0.8,
	0.6, -0.8
))

vao = GL.VertexArray(prog, [(vbo, '2f', ['vert'])])

while GLWindow.Update():
	GL.clear(240, 240, 240)
	vao.render(ModernGL.TRIANGLES)
