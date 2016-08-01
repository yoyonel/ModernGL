import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

GL.InitializeModernGL()

# Lets add a color attribute per vertex
# We need the color in the fragment shader but we can specify attributes
# for the vertex shader so the value will be forwarded for the fragment shader

# VertexShader:

# the vert_color is an input
# the frag_color is an output

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;
	in vec3 vert_color;

	out vec3 frag_color;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
		frag_color = vert_color;
	}
''')

# FragmentShader:

# the frag_color is an input
# the color is the output

frag = GL.NewFragmentShader('''
	#version 330

	in vec3 frag_color;
	out vec4 color;

	void main() {
		color = vec4(frag_color, 1.0);
	}
''')

prog, iface = GL.NewProgram([vert, frag])

# Last time we had x, y for each vertex
# Now we have x, y, r, g, b (5 floats) per vertex

triangle = [
# A
	0.0, 0.8,
	1.0, 0.0, 0.0,
# B
	-0.6, -0.8,
	0.0, 1.0, 0.0,
# C
	0.6, -0.8,
	0.0, 0.0, 1.0,
]

packed_triangle = struct.pack('15f', *triangle)

vbo = GL.NewVertexBuffer(packed_triangle)

# The new format is:
# 2 floats for the "vert"
# 3 floats for the "vert_color"

vao = GL.NewVertexArray(prog, vbo, '2f3f', ['vert', 'vert_color'])

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.RenderTriangles(vao, 3)
