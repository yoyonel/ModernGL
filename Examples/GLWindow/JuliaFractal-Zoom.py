import ModernGL as GL
import GLWindow as WND
import struct, time

WND.Init()
GL.Init()

vert = GL.NewVertexShader('''
	#version 330

	uniform vec2 pos;
	uniform float zoom;

	in vec2 vert;
	out vec2 textcoord;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
		textcoord = ((vert + pos) * zoom) / 2.0 + vec2(0.5, 0.5);
	}
''')

frag = GL.NewFragmentShader('''
	#version 330
	
	in vec2 textcoord;
	out vec4 color;

	uniform int iter;

	void main() {
		vec2 z = vec2(3.0 * (textcoord.x - 0.5), 2.0 * (textcoord.y - 0.5));
		vec2 c = vec2(0.0, 1.0);

		int i;
		for(i = 0; i < iter; i++) {
			float x = (z.x * z.x - z.y * z.y) + c.x;
			float y = (z.y * z.x + z.x * z.y) + c.y;
			if ((x * x + y * y) > 4.0) break;
			z.x = x;
			z.y = y;
		}

		float cm = fract((i == iter ? 0.0 : float(i)) * 10 / iter);
		color = vec4(fract(cm + 0.0 / 3.0), fract(cm + 1.0 / 3.0), fract(cm + 2.0 / 3.0), 1.0);
	}
''')

prog = GL.NewProgram([vert, frag])

vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
vao = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

GL.SetUniform(prog['iter'], 100)

tx, ty = 0, 0
z = 1

while WND.Update():
	GL.Clear(240, 240, 240)
	dx, dy, mw = WND.GetMouse()

	z *= 1.1 ** (mw / 150)
	tx -= dx / 100 * z
	ty += dy / 100 * z

	GL.SetUniform(prog['pos'], tx / z, ty / z)
	GL.SetUniform(prog['zoom'], z)
	GL.RenderTriangleStrip(vao, 4)
