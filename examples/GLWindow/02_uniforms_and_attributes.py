import struct

import GLWindow
import ModernGL

GLWindow.Init()

# Context

ctx = ModernGL.create_context()

# Shaders & Program

prog = ctx.Program([
	ctx.VertexShader('''
		#version 330

		in vec2 vert;

		in vec3 vert_color;
		out vec3 frag_color;

		uniform vec2 scale;
		uniform float rotation;

		void main() {
			frag_color = vert_color;
			mat2 rot = mat2(
				cos(rotation), sin(rotation),
				-sin(rotation), cos(rotation)
			);
			gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
		}
	'''),
	ctx.FragmentShader('''
		#version 330

		in vec3 frag_color;
		out vec4 color;

		void main() {
			color = vec4(frag_color, 1.0);
		}
	'''),
])

# Uniforms

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

width, height = GLWindow.GetSize()
scale.value = (height / width * 0.75, 0.75)

# Buffer

vbo = ctx.Buffer(struct.pack('15f',
	1.0, 0.0,
	1.0, 0.0, 0.0,

	-0.5, 0.86,
	0.0, 1.0, 0.0,

	-0.5, -0.86,
	0.0, 0.0, 1.0,
))

# Put everything together

vao = ctx.SimpleVertexArray(prog, vbo, '2f3f', ['vert', 'vert_color'])

# Main loop

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	rotation.value = GLWindow.GetTime()
	vao.render()

# Cleanup

vao.release()
vbo.release()
prog.release()
