from OpenGL.error import NullFunctionError
from OpenGL.GLUT import *
import ModernGL as GL
import struct

try:
	glutInit(sys.argv)

except NullFunctionError as ex:
	print('(Windows) Maybe missing glut32.dll.')
	print('(Linux) Maybe apt-get install python-opengl will help.')
	print(ex)
	exit()

glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowSize(800, 600)
glutCreateWindow('')

GL.Init()

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

vbo = GL.NewVertexBuffer(struct.pack('6f', 0.0, 0.8, -0.6, -0.8, 0.6, -0.8))
vao = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

def display():
	GL.Clear(240, 240, 240)
	GL.RenderTriangles(vao, 3)
	glutSwapBuffers()

glutDisplayFunc(display)
glutMainLoop()
