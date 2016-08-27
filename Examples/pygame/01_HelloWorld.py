from pygame.locals import *
import ModernGL as GL
import pygame, struct

pygame.init()
pygame.display.set_mode((800, 600), DOUBLEBUF | OPENGL)

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

running = True
while running:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False

	GL.Clear(240, 240, 240)
	GL.RenderTriangles(vao, 3)

	pygame.display.flip()
	pygame.time.wait(10)
