import ModernGL as GL
import GLWindow as WND
import struct, random

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

tvert = GL.NewVertexShader('''
	#version 330

	uniform vec2 acc;

	in vec2 in_pos;
	in vec2 in_prev;

	out vec2 out_pos;
	out vec2 out_prev;

	void main() {
		out_pos = in_pos * 2.0 - in_prev + acc;
		out_prev = in_pos;
	}
''')

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
	}
''')

frag = GL.NewFragmentShader('''
	#version 330
	
	out vec4 color;

	void main() {
		color = vec4(0.30, 0.50, 1.00, 1.0);
	}
''')

prog, iface = GL.NewProgram([vert, frag])

transform, tiface = GL.NewTransformProgram([tvert], ['out_pos', 'out_prev'])

vbo1 = GL.NewVertexBuffer(b''.join(struct.pack('2f2f', 0.0, 0.0, random.uniform(-0.001, 0.001), random.uniform(-0.001, 0.0)) for i in range(1024)))
vbo2 = GL.NewVertexBuffer(b''.join(struct.pack('2f2f', 0.0, 0.0, random.uniform(-0.001, 0.001), random.uniform(-0.001, 0.0)) for i in range(1024)))

vao1 = GL.NewVertexArray(transform, vbo1, '2f2f', ['in_pos', 'in_prev'])
vao2 = GL.NewVertexArray(transform, vbo2, '2f2f', ['in_pos', 'in_prev'])

render_vao = GL.NewVertexArray(prog, vbo1, '2f8x', ['vert'])

GL.SetUniform(tiface['acc'], 0, -0.00001)

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.RenderPoints(render_vao, 1024)
	GL.TransformPoints(vao1, vbo2, 1024)
	GL.TransformPoints(vao2, vbo1, 1024)
