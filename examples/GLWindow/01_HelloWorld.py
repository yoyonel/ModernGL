import ModernGL, GLWindow
import struct

GLWindow.Init()

# Context

ctx = ModernGL.create_context()

# Shaders & Program

prog = ctx.Program([
	ctx.VertexShader('''
		#version 330

		in vec2 vert;

		void main() {
			gl_Position = vec4(vert, 0.0, 1.0);
		}
	'''),
	ctx.FragmentShader('''
		#version 330

		out vec4 color;

		void main() {
			color = vec4(0.3, 0.5, 1.0, 1.0);
		}
	'''),
])

# Buffer

vbo = ctx.Buffer(struct.pack('6f',
	0.0, 0.8,
	-0.6, -0.8,
	0.6, -0.8,
))

# Put everything together

vao = ctx.SimpleVertexArray(prog, vbo, '2f', ['vert'])

# Main loop

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	vao.render()

# Cleanup

vao.release()
vbo.release()
prog.release()
