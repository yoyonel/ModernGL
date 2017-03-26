from OpenGL.GLUT import *
import ModernGL, struct

glutInit(sys.argv)
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH)
glutInitWindowSize(800, 600)
glutCreateWindow(b'Hello World')

ctx = ModernGL.create_context()

vert = ctx.VertexShader('''
	#version 330
	in vec2 vert;
	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
	}
''')

frag = ctx.FragmentShader('''
	#version 330
	out vec4 color;
	void main() {
		color = vec4(0.30, 0.50, 1.00, 1.0);
	}
''')

prog = ctx.Program([vert, frag])

vbo = ctx.Buffer(struct.pack('6f', 0.0, 0.8, -0.6, -0.8, 0.6, -0.8))
vao = ctx.SimpleVertexArray(prog, vbo, '2f', ['vert'])

def display():
	ctx.clear(240, 240, 240)
	vao.render()
	glutSwapBuffers()

glutDisplayFunc(display)
glutMainLoop()
