import ModernGL as GL
import GLWindow as WND
import struct, json

WND.InitializeWindow()
WND.BuildFullscreen()
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

print(json.dumps(GL.DebugInfo(), indent = 4, sort_keys = True))

print('vert', GL.DebugVar(vert))
print('frag', GL.DebugVar(frag))
print('prog', GL.DebugVar(prog))
print('vbo', GL.DebugVar(vbo))
print('vao', GL.DebugVar(vao))
