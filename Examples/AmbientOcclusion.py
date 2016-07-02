import ModernGL as GL
import GLWindow as WND
import struct, random, math

kernel = [
	(-0.3688, 0.9738), (0.2746, 0.64), (-0.939, -0.2796), (-0.2382, -0.5376),
	(-0.8624, -0.4059), (0.1506, -0.5648), (0.1378, -0.9476), (-0.4886, -0.6751),
	(-0.1642, -0.2665), (-0.7122, 0.6795), (-0.3952, 0.3800), (0.8540, 0.6715),
	(-0.8699, -0.9000), (0.3355, -0.5726), (-0.1401, -0.2665), (-0.8217, -0.9512),
	(-0.6397, 0.7962), (-0.2865, 0.7450), (-0.6415, 0.1081), (-0.5407, 0.912),
	(-0.6563, -0.3000), (0.8985, -0.4526), (-0.4899, 0.4935), (0.461, 0.1373),
	(0.2371, 0.5156), (0.2058, -0.7032), (-0.7509, 0.3060), (0.8289, -0.1775),
	(-0.2009, 0.2743), (0.9844, -0.2703), (0.8164, 0.3067), (-0.2206, -0.4205),
	(-0.8077, 0.5851), (0.3844, -0.8923), (0.735, -0.954), (0.1315, -0.384),
	(-0.4332, -0.2655), (0.2403, 0.166), (-0.5501, -0.87), (-0.3067, 0.7591),
	(-0.7793, -0.2932), (-0.5887, -0.982), (-0.3087, -0.6407), (-0.487, -0.3723),
	(0.4397, 0.5765), (-0.8822, 0.6933), (-0.364, 0.9799), (-0.8306, 0.9190),
]

camera = [
	-1.0820, -0.6046, -0.6985, -0.6985,
	1.3525, -0.4837, -0.5588, -0.5588,
	0.0000, 1.5493, -0.4470, -0.4470,
	0.0000, -12.3948, 74.9584, 75.1584,
]

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

grass_vert = GL.NewVertexShader('''
	#version 400

	uniform mat4 mat;

	in vec3 vert;
	in vec3 direction;
	in vec3 color;
	in float thickness;
	in float power;

	out vec3 frag_color;

	void main() {
		vec4 vertex = vec4(vert - (direction * power) / 4.0, 1.0);
		frag_color = color * smoothstep(0.0, 1.0, vertex.z / 22.0);
		frag_color *= 0.75 + 0.25 * smoothstep(0.0, 1.0, thickness);
		frag_color *= 1.0 - smoothstep(0.0, 1.0, thickness);
		gl_Position = mat * vertex + vec4(thickness, 0.0, 0.0, 0.0);
	}
''')

grass_frag = GL.NewFragmentShader('''
	#version 400

	in vec3 frag_color;
	out vec4 color;

	void main() {
		color = vec4(frag_color, 1.0);
	}
''')

grass_prog = GL.NewProgram([grass_vert, grass_frag])

ssao_vert = GL.NewVertexShader('''
	#version 400

	in vec2 vert;
	out vec2 position;

	void main() {
		gl_Position = vec4(vert * 2.0 - 1.0, 0.0, 1.0);
		position = vert;
	}
''')

ssao_frag = GL.NewFragmentShader('''
	#version 400

	uniform sampler2D depth;
	uniform sampler2D texture;

	in vec2 position;
	out vec4 color;

	uniform Kernel {
		vec2 kernel[48];
	};

	float random(vec2 seed) {
		float x = seed.x * 3.123987;
		float y = seed.y * 17.000559;
		return(fract(x + y));
	}

	void main() {
		float diffuse = 0.0;
		for (int i = 0; i < 48; ++i) {
			float depth1 = texture2D(depth, position).x;
			float depth2 = texture2D(depth, position + kernel[i] * 0.017).x;
			float delta = depth2 - depth1;
			if (delta > 0.0) {
				diffuse += 1.0 / 48.0;
			}
		}
		color = vec4(texture2D(texture, position).rgb * diffuse, 1.0);
	}
''')

ssao_prog = GL.NewProgram([ssao_vert, ssao_frag])

step = 7

data = b''
for k in range(1000):
	a = random.uniform(0, 2.0 * math.pi)
	d = random.uniform(5.0, 7.5)

	height = random.uniform(18.0, 22.0)
	x = random.uniform(-20.0, 20.0)
	y = random.uniform(-20.0, 20.0)
	z = 0

	f = random.random()
	r = (0 + f * 89) / 255
	g = (94 + f * 39) / 255
	b = (32 + f * 7) / 255

	for i in range(step):
		p = i / step;
		s = (p ** 2.7) * d;
		t = math.tanh((p - 1.0) * 2.0 * math.pi) * 0.5;

		if i == 0 or i % 2 == 1:
			data += struct.pack('3f', x, y, z + height * p)
			data += struct.pack('3f', math.cos(a), math.sin(a), 0)
			data += struct.pack('3f', r, g, b)
			data += struct.pack('1f', -t)
			data += struct.pack('1f', s)

		if i == 0 or i % 2 == 0:
			data += struct.pack('3f', x, y, z + height * p)
			data += struct.pack('3f', math.cos(a), math.sin(a), 0)
			data += struct.pack('3f', r, g, b)
			data += struct.pack('1f', t)
			data += struct.pack('1f', s)

	data += struct.pack('3f', x, y, z + height)
	data += struct.pack('3f', math.cos(a), math.sin(a), 0)
	data += struct.pack('3f', r, g, b)
	data += struct.pack('1f', 0)
	data += struct.pack('1f', d)

idata = b''

for k in range(1000):
	idata += struct.pack('%di' % (step + 3), *([k * (step + 2) + i for i in range(step + 2)] + [-1]))

vbo = GL.NewVertexBuffer(data)
ibo = GL.NewIndexBuffer(idata)

attribs = [
	(vbo, GL.AttributeLocation(grass_prog, 'vert')),
	(vbo, GL.AttributeLocation(grass_prog, 'direction')),
	(vbo, GL.AttributeLocation(grass_prog, 'color')),
	(vbo, GL.AttributeLocation(grass_prog, 'thickness')),
	(vbo, GL.AttributeLocation(grass_prog, 'power')),
]

vao = GL.NewVertexArray('3f3f3f1f1f', attribs, ibo)

ssao_vbo = GL.NewVertexBuffer(struct.pack('8f', 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0))
ssao_vao = GL.NewVertexArray('2f', [(ssao_vbo, GL.AttributeLocation(ssao_prog, 'vert'))])

GL.UseProgram(grass_prog)
GL.UniformMatrix(GL.UniformLocation(grass_prog, 'mat'), camera)

ubo = GL.NewUniformBuffer(b''.join(struct.pack('2f', x, y) for x, y in kernel))

fbo, color, depth = GL.NewFramebuffer()

GL.UseProgram(ssao_prog)
GL.Uniform1i(GL.UniformLocation(ssao_prog, 'texture'), 0)
GL.Uniform1i(GL.UniformLocation(ssao_prog, 'depth'), 1)
GL.UseUniformBlock(GL.UniformBlockLocation(ssao_prog, 'Kernel'), ubo)

while WND.Update():
	GL.UseFramebuffer(fbo)
	GL.EnableDepthTest()
	GL.Clear(0, 0, 0)
	GL.UseProgram(grass_prog)
	GL.RenderIndexedTriangleStrip(vao, 1000 * 8)

	GL.UseDefaultFramebuffer()
	GL.DisableDepthTest()
	GL.UseProgram(ssao_prog)
	GL.UseTexture(color, 0)
	GL.UseTexture(depth, 1)
	GL.RenderTriangleStrip(ssao_vao, 4)
