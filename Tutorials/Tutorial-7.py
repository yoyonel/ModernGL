import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

GL.InitializeModernGL()

# gl_InstanceID is added to the rotation.
# Now different instances won't overlap all the time.

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;
	in vec3 vert_color;

	out vec3 frag_color;

	uniform float rotate;
	uniform vec2 scale;

	void main() {
		float r = rotate * (0.5 + gl_InstanceID * 0.05);
		mat2 rot = mat2(cos(r), sin(r), -sin(r), cos(r));
		gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
		frag_color = vert_color;
	}
''')

frag = GL.NewFragmentShader('''
	#version 330

	in vec3 frag_color;
	out vec4 color;

	void main() {
		color = vec4(frag_color, 0.5);
	}
''')

prog, iface = GL.NewProgram([vert, frag])

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

width, height = WND.GetSize()

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.SetUniform(iface['rotate'], WND.GetTime())
	GL.SetUniform(iface['scale'], height / width * 0.75, 0.75)

	GL.RenderTriangles(vao, 3, instances = 10)
