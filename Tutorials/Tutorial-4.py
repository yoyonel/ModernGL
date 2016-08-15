import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

GL.InitializeModernGL()

# Rendering with modern OpenGL:

# First we will need shaders, buffers and vertex arrays

# Shaders and Programs:
# a shader is a computer program that is used to do shading,
# transform vertices to the screen coordinates and assign colors to it.

# The first example will contain a simple Vertex and Fragment shader.
# The vertex shader will pass the vertices as is.

vert = GL.NewVertexShader('''
	#version 330
	in vec2 vert;
	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
	}
''')

# The fragment shader will assign a blue color for each fragment.

frag = GL.NewFragmentShader('''
	#version 330
	out vec4 color;
	void main() {
		color = vec4(0.30, 0.50, 1.00, 1.0);
	}
''')

# We will need a program object that will contain our shaders attached and linked together.
# The NewProgram() function also returns the program interface
# The program interface will be discussed later

prog, iface = GL.NewProgram([vert, frag])

# Now we want a triangle
# The screen coordinates are in the range of [-1, 1] and [-1, 1] for x and y respectively.

# We will have 3 points:
# A = 0.0, 0.8
# B = -0.6, -0.8 
# C = 0.6, -0.8

#       A
#      /\
#     /  \
#    /    \
#   /______\
#  B        C

triangle = [
	0.0, 0.8,     # A
	-0.6, -0.8,   # B
	0.6, -0.8     # C
]

# We have to pack the floats
packed_triangle = struct.pack('6f', *triangle)

# Now lets create a vertex buffer "containing" our triangle
vbo = GL.NewVertexBuffer(packed_triangle)

# Now we will create a VertexArray and specify what vertex attributes will be used during the rendering
# The first parameter is a program object used for rendering
# The second parameter is a VertexBuffer holding information about the triangle
# The third parameter is the format of a single vertex
#     Now we only define the position as 2 float x and y coordinate
#     Later we can define color normals or any other data used in the vertex shader.

# The fourth parameter must be a list containing a vertex attribute name in the vertex shader
vao = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

while WND.Update():
	GL.Clear(240, 240, 240)

	# Render a triangle using 3 vertices (remember we have 6 floats 3 * 2f)
	# RenderTriangles will use the program assigned to vao
	# By default the specified attribues are enabled (for now we have a single "vert" attribute)
	GL.RenderTriangles(vao, 3)
