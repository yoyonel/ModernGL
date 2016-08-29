import ModernGL as GL
import GLWindow as WND
import struct

WND.Init()
GL.Init()

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;

	in vec3 vert_color;
	out vec3 frag_color;

	uniform vec2 scale;
	uniform float rotation;

	void main() {
		frag_color = vert_color;
		mat2 rot = mat2(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));
		gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
	}
''')

frag = GL.NewFragmentShader('''
	#version 330
	
	in vec3 frag_color;
	out vec4 color;

	void main() {
		color = vec4(frag_color, 1.0);
	}
''')

width, height = WND.GetSize()

prog = GL.NewProgram([vert, frag])

vbo = GL.NewVertexBuffer(struct.pack('15f', 1.0, 0.0, 1.0, 0.0, 0.0, -0.5, 0.86, 0.0, 1.0, 0.0, -0.5, -0.86, 0.0, 0.0, 1.0))
vao = GL.NewVertexArray(prog, vbo, '2f3f', ['vert', 'vert_color'])

GL.SetUniform(prog['scale'], height / width * 0.75, 0.75)

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.SetUniform(prog['rotation'], WND.GetTime())
	GL.RenderTriangles(vao, 3)
