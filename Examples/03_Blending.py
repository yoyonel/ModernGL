# python -m pip install ModernGL
# python -m pip install GLWindow

import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 400

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
''')

if not vert:
	print('NewVertexShader failed')
	print(GL.CompilerLog())

frag = GL.NewFragmentShader('''
	#version 400
	
	in vec4 frag_color;
	out vec4 color;

	void main() {
		color = frag_color;
	}
''')

if not frag:
	print('NewFragmentShader failed')
	print(GL.CompilerLog())

width, height = WND.GetSize()

prog = GL.NewProgram([vert, frag])

verts = [
	1.0, 0.0,
	1.0, 0.0, 0.0, 0.5,

	-0.5, 0.86,
	0.0, 1.0, 0.0, 0.5,

	-0.5, -0.86,
	0.0, 0.0, 1.0, 0.5,
]

vbo = GL.NewVertexBuffer(struct.pack('18f', *verts))

attribs = [
	(vbo, GL.AttributeLocation(prog, 'vert')),
	(vbo, GL.AttributeLocation(prog, 'vert_color')),
]

vao = GL.NewVertexArray('2f4f', attribs, vbo)

rotation = GL.UniformLocation(prog, 'rotation')
scale = GL.UniformLocation(prog, 'scale')

GL.Uniform2f(scale, height / width * 0.75, 0.75)

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UseProgram(prog)
	GL.EnableOnly(GL.ENABLE_BLEND | GL.ENABLE_MULTISAMPLE)
	GL.Uniform1f(rotation, WND.GetTime())
	GL.RenderTriangles(vao, 3, 0, 10)
