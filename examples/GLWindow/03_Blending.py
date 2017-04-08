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

		in vec4 vert_color;
		out vec4 frag_color;

		uniform vec2 scale;
		uniform float rotation;

		void main() {
			frag_color = vert_color;
			float r = rotation * (0.5 + gl_InstanceID * 0.05);
			mat2 rot = mat2(cos(r), sin(r), -sin(r), cos(r));
			gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
		}
	'''),
	ctx.FragmentShader('''
		#version 330

		in vec4 frag_color;
		out vec4 color;

		void main() {
			color = vec4(frag_color);
		}
	'''),
])

# Uniforms

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

width, height = GLWindow.GetSize()
scale.value = (height / width * 0.75, 0.75)

# Buffer

vbo = ctx.Buffer(struct.pack('18f',
	1.0, 0.0,
	1.0, 0.0, 0.0, 0.5,

	-0.5, 0.86,
	0.0, 1.0, 0.0, 0.5,

	-0.5, -0.86,
	0.0, 0.0, 1.0, 0.5,
))

# Put everything together

vao = ctx.SimpleVertexArray(prog, vbo, '2f4f', ['vert', 'vert_color'])

# Main loop

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	ctx.enable(ModernGL.BLEND)
	rotation.value = GLWindow.GetTime()
	vao.render(instances = 10)

# Cleanup

vao.release()
vbo.release()
prog.release()
