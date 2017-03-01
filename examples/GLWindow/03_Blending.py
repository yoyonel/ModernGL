import ModernGL, GLWindow
import struct

GLWindow.Init()

ctx = ModernGL.create_context()

vert = ctx.VertexShader('''
	#version 330

	in vec2 vert;

	in vec4 vert_color;
	out vec4 frag_color;

	uniform vec2 scale;
	uniform float rotation;

	void main() {
		frag_color = vert_color;
		float r = rotation * (0.5 + gl_InstanceID * 0.05);
		mat2 rot = mat2(cos(r), sin(r), -sin(r), cos(r));
		gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
	}
''')

frag = ctx.FragmentShader('''
	#version 330

	in vec4 frag_color;
	out vec4 color;

	void main() {
		color = frag_color;
	}
''')

width, height = GLWindow.GetSize()

prog = ctx.Program([vert, frag])

verts = [
	1.0, 0.0,
	1.0, 0.0, 0.0, 0.5,

	-0.5, 0.86,
	0.0, 1.0, 0.0, 0.5,

	-0.5, -0.86,
	0.0, 0.0, 1.0, 0.5,
]

vbo = ctx.Buffer(struct.pack('18f', *verts))
vao = ctx.VertexArray(prog, [
	(vbo, '2f4f', ['vert', 'vert_color']),
])

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

scale.value = (height / width * 0.75, 0.75)

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	ctx.enable(ModernGL.BLEND)
	rotation.value = GLWindow.GetTime()
	vao.render(ModernGL.TRIANGLES, instances = 10)
