# python -m pip install Pillow

from PIL import Image
import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
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

frag = GL.NewFragmentShader('''
	#version 330

	uniform sampler2D texture;
	
	in vec2 tex_coord;
	out vec4 color;

	void main() {
		color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
	}
''')

width, height = WND.GetSize()

prog, iface = GL.NewProgram([vert, frag])

vbo = GL.NewVertexBuffer(struct.pack('6f', 1.0, 0.0, -0.5, 0.86, -0.5, -0.86))
vao = GL.NewVertexArray('2f', vbo, [iface['vert']])

GL.Uniform2f(iface['scale'], height / width * 0.75, 0.75)

tex = GL.NewTexture(256, 256, Image.open('../Data/Noise.jpg').tobytes())
GL.UseTexture(tex)

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.Uniform1f(iface['rotation'], WND.GetTime())
	GL.RenderTriangles(vao, 3)
