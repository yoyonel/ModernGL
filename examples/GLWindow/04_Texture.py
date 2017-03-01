import ModernGL, GLWindow
from PIL import Image
import struct

GLWindow.Init()

ctx = ModernGL.create_context()

print(ctx.max_texture_units)

vert = ctx.VertexShader('''
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
''')

frag = ctx.FragmentShader('''
	#version 330

	uniform sampler2D texture;

	in vec2 tex_coord;
	out vec4 color;

	void main() {
		color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
	}
''')

width, height = GLWindow.GetSize()

prog = ctx.Program([vert, frag])

vbo = ctx.Buffer(struct.pack('6f', 1.0, 0.0, -0.5, 0.86, -0.5, -0.86))
vao = ctx.VertexArray(prog, [(vbo, '2f', ['vert'])])

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

scale.value = (height / width * 0.75, 0.75)

img = Image.open('../DataFiles/Noise.jpg')
texture = ctx.Texture(img.size, 3, img.tobytes())
texture.use()

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	rotation.value = GLWindow.GetTime()
	vao.render(ModernGL.TRIANGLES)
