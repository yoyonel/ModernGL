import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 330

	in vec2 vert;
	out vec2 tex;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
		tex = vert / 2.0 + vec2(0.5, 0.5);
	}
''')

frag = GL.NewFragmentShader('''
	#version 330
	
	in vec2 tex;
	out vec4 color;

	uniform float scale;
	uniform vec2 center;
	uniform int iter;

	void main() {
		vec2 z = vec2(5.0 * (tex.x - 0.5), 3.0 * (tex.y - 0.5));
		vec2 c = vec2(1.33 * (tex.x - 0.5) * scale - center.x, (tex.y - 0.5) * scale - center.y);

		int i;
		for(i = 0; i < iter; i++) {
			vec2 v = vec2((z.x * z.x - z.y * z.y) + c.x, (z.y * z.x + z.x * z.y) + c.y);
			if (dot(v, v) > 4.0) break;
			z = v;
		}

		float cm = fract((i == iter ? 0.0 : float(i)) * 10 / iter);
		color = vec4(fract(cm + 0.0 / 3.0), fract(cm + 1.0 / 3.0), fract(cm + 2.0 / 3.0), 1.0);
	}
''')

prog, iface = GL.NewProgram([vert, frag])

vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
vao = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

GL.Uniform1i(iface['iter'], 100)
GL.Uniform1f(iface['scale'], 1.0)
GL.Uniform2f(iface['center'], 0.3, 0.2)

while WND.Update():
	GL.Clear(240, 240, 240)
	mx, my, mw = WND.GetMouse()
	scale = 1.1 ** (mw / 150)
	mx = mx / 100
	my = my / 100

	GL.Uniform2f(iface['center'], mx, my)
	GL.Uniform1f(iface['scale'], scale)
	GL.RenderTriangleStrip(vao, 4)

