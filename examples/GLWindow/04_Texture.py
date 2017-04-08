import struct

import GLWindow
import ModernGL
from PIL import Image

GLWindow.Init()

# Context

ctx = ModernGL.create_context()

# Shaders & Program

prog = ctx.Program([
	ctx.VertexShader('''
		#version 330

		in vec2 vert;
		out vec2 tex_coord;

		uniform vec2 scale;
		uniform float rotation;

		void main() {
			mat2 rot = mat2(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));
			gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
			tex_coord = vert;
		}
	'''),
	ctx.FragmentShader('''
		#version 330

		uniform sampler2D texture;

		in vec2 tex_coord;
		out vec4 color;

		void main() {
			color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
		}
	'''),
])

# Uniforms

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

width, height = GLWindow.GetSize()
scale.value = (height / width * 0.75, 0.75)

# Buffer

vbo = ctx.Buffer(struct.pack('6f',
	1.0, 0.0,
	-0.5, 0.86,
	-0.5, -0.86,
))

# Put everything together

vao = ctx.SimpleVertexArray(prog, vbo, '2f', ['vert'])

# Texture

img = Image.open('../data/noise.jpg')
texture = ctx.Texture(img.size, 3, img.tobytes())
texture.use()

# Main loop

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	rotation.value = GLWindow.GetTime()
	vao.render()

# Cleanup

vao.release()
vbo.release()
prog.release()
