import ModernGL as GL
import GLWindow as WND
from random import *
from math import *
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

width, height = WND.GetSize()

transform_src = '''
	#version 330

	in float inValue;
	out float outValue;

	void main() {
		outValue = sqrt(inValue);
	}
'''

transform = GL.NewTransformShader(transform_src, ['outValue'])

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

vbo1 = GL.NewVertexBuffer(struct.pack('4f', 0.1, 0.1, 0.2, 0.2))
vbo2 = GL.NewVertexBuffer(struct.pack('4f', 0.1, 0.2, 0.2, 0.1))

tao = GL.NewTransformArray(transform, vbo1, vbo2, '1f', ['inValue'])

GL.RunTransformShader(transform, tao, 4)

vao1 = GL.NewVertexArray(prog, vbo1, '2f', ['vert'])
vao2 = GL.NewVertexArray(prog, vbo2, '2f', ['vert'])

print(vbo1, vbo2, tao)

while WND.Update():
	GL.Clear(240, 240, 240)
	GL.RenderLines(vao1, 2)
	GL.RenderLines(vao2, 2)

