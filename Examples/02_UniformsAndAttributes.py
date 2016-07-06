import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 400

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
	#version 400
	
	in vec3 frag_color;
	out vec4 color;

	void main() {
		color = vec4(frag_color, 1.0);
	}
''')

width, height = WND.GetSize()

prog = GL.NewProgram([vert, frag])

vert_idx = GL.GetAttributeLocation(prog, 'vert')
color_idx = GL.GetAttributeLocation(prog, 'vert_color')
rotation = GL.GetUniformLocation(prog, 'rotation')
scale = GL.GetUniformLocation(prog, 'scale')

vbo = GL.NewVertexBuffer(struct.pack('15f', 1.0, 0.0, 1.0, 0.0, 0.0, -0.5, 0.86, 0.0, 1.0, 0.0, -0.5, -0.86, 0.0, 0.0, 1.0))
vao = GL.NewVertexArray('2f3f', vbo, [vert_idx, color_idx])

GL.Uniform2f(scale, height / width * 0.75, 0.75)

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UseProgram(prog)
	GL.Uniform1f(rotation, WND.GetTime())
	GL.RenderTriangles(vao, 3)
