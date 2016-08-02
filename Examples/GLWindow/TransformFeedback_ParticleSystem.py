import ModernGL as GL
import GLWindow as WND
from random import *
from math import *
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

width, height = WND.GetSize()

transform = GL.NewVertexShader('''
	#version 330

	in float inValue;
	out float outValue;

	void main() {
		outValue = sqrt(inValue);
	}
''')

transform = GL.NewTransformProgram([transform], ['outValue'])

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

vao = GL.NewVertexArray(transform, vbo1, '1f', ['inValue'])

GL.TransformPoints(vao, vbo2, 0, 4)

vao1 = GL.NewVertexArray(prog, vbo1, '2f', ['vert'])
vao2 = GL.NewVertexArray(prog, vbo2, '2f', ['vert'])


while WND.Update():
	GL.Clear(240, 240, 240)
	GL.RenderLines(vao1, 2)
	GL.RenderLines(vao2, 2)

