from pygame.locals import *
import ModernGL, struct, pygame

pygame.init()
pygame.display.set_mode((800, 600), DOUBLEBUF | OPENGL)

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

running = True
while running:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			running = False

	ctx.clear(240, 240, 240)
	vao.render()

	pygame.display.flip()
	pygame.time.wait(10)
