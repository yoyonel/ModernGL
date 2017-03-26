import ModernGL, struct, pyglet

window = pyglet.window.Window()

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

@window.event
def on_draw():
	ctx.clear(240, 240, 240)
	vao.render()

pyglet.app.run()
