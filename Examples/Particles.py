import ModernGL as GL
import GLWindow as WND
import struct, random

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 430

	in vec2 vert;

	uniform vec2 scale;

	struct Particle {
		vec2 pos;
		vec2 vel;
		vec2 acc;
	};

	layout (binding = 1) buffer Input {
		Particle particle[];
	};
	
	void main() {
		gl_Position = vec4((particle[gl_InstanceID].pos + vert) * 2.0 / scale, 0.0, 1.0);
	}
''')

frag = GL.NewFragmentShader('''
	#version 430
	
	out vec4 color;

	void main() {
		color = vec4(0.30, 0.50, 1.00, 1.0);
	}
''')

physics = GL.NewComputeShader('''
	#version 430

	struct Particle {
		vec2 pos;
		vec2 vel;
		vec2 acc;
	};

	layout (binding = 1) buffer Input {
		Particle particle[];
	};

	layout (local_size_x = 512, local_size_y = 1, local_size_z = 1) in;

	void main() {
		particle[gl_GlobalInvocationID.x].pos += particle[gl_GlobalInvocationID.x].vel;
		particle[gl_GlobalInvocationID.x].vel += particle[gl_GlobalInvocationID.x].acc;
	}
''')

sbo = GL.NewStorageBuffer(b''.join(struct.pack('ffffff', 0, 0, random.uniform(-1, 1), random.uniform(-1, 1), 0, -0.1) for i in range(10240)))

prog = GL.NewProgram([vert, frag])

GL.Uniform2f(GL.GetUniformLocation(prog, 'scale'), 1920, 1080)

vbo = GL.NewVertexBuffer(struct.pack('6f', 0, 8, -6, -8, 6, -8))
vao = GL.NewVertexArray('2f', [(vbo, GL.GetAttributeLocation(prog, 'vert'))])

GL.UseStorageBuffer(sbo, 1)

GL.UseProgram(prog)

k = 0
while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UpdateStorageBuffer(sbo, k * 24, b''.join(struct.pack('ffffff', 0, 0, random.uniform(-1, 1), random.uniform(-1, 1), 0, -0.1) for i in range(16)))
	k = (k + 16) % 10240

	GL.RunComputeShader(physics, 20)
	GL.RenderTriangles(vao, 3, instances = 10240)
