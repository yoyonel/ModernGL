# python -m pip install Pillow

from PIL import Image
import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 400

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

if not vert:
	print('NewVertexShader failed')
	print(GL.CompilerLog())

frag = GL.NewFragmentShader('''
	#version 400

	uniform sampler2D texture;
	
	in vec2 tex_coord;
	out vec4 color;

	void main() {
		color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
	}
''')

if not frag:
	print('NewFragmentShader failed')
	print(GL.CompilerLog())

width, height = WND.GetSize()

prog = GL.NewProgram([vert, frag])

vert_idx = GL.GetAttributeLocation(prog, 'vert')
color_idx = GL.GetAttributeLocation(prog, 'vert_color')
rotation = GL.GetUniformLocation(prog, 'rotation')
scale = GL.GetUniformLocation(prog, 'scale')

vbo = GL.NewVertexBuffer(struct.pack('15f', 1.0, 0.0, 1.0, 0.0, 0.0, -0.5, 0.86, 0.0, 1.0, 0.0, -0.5, -0.86, 0.0, 0.0, 1.0))
vao = GL.NewVertexArray('2f3f', vbo, [vert_idx, color_idx])

GL.Uniform2f(scale, height / width * 0.75, 0.75)

tex = GL.NewTexture(256, 256, Image.open('Data/Noise.jpg').tobytes())
GL.UseTexture(tex)

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UseProgram(prog)
	GL.Uniform1f(rotation, WND.GetTime())
	GL.RenderTriangles(vao, 3)
