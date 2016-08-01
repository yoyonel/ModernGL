import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

GL.InitializeModernGL()

# VertexShader:

# there are 2 uniforms:
# rotate (float)
# scale (x, y)

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;
	in vec3 vert_color;

	out vec3 frag_color;

	uniform float rotate;
	uniform vec2 scale;

	void main() {
		mat2 rot = mat2(cos(rotate), sin(rotate), -sin(rotate), cos(rotate));
		gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
		frag_color = vert_color;
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

prog, iface = GL.NewProgram([vert, frag])

# Coordinates are changed

triangle = [
# A
	1.0, 0.0,
	1.0, 0.0, 0.0,
# B
	-0.5, 0.86,
	0.0, 1.0, 0.0,
# C
	-0.5, -0.86,
	0.0, 0.0, 1.0,
]

packed_triangle = struct.pack('15f', *triangle)

vbo = GL.NewVertexBuffer(packed_triangle)
vao = GL.NewVertexArray(prog, vbo, '2f3f', ['vert', 'vert_color'])

# Some information we will need later

width, height = WND.GetSize()

while WND.Update():
	GL.Clear(240, 240, 240)

	# Set the value for the rotate and scale uniforms
	# The program interface contains the address of the rotate uniform

	GL.SetUniform(iface['rotate'], WND.GetTime())

	# We will scale the triangle using the dimension of the window

	GL.SetUniform(iface['scale'], height / width * 0.75, 0.75)

	GL.RenderTriangles(vao, 3)
