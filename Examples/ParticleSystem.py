import ModernGL as GL
import GLWindow as WND
from random import *
from math import *
import struct

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

width, height = WND.GetSize()

circles_vert = GL.NewVertexShader('''
	#version 430

	in vec2 vert;
	uniform vec2 scale;

	struct Circle {
		vec2 pos;
		float radius;
	};

	uniform Circles {
		int circles;
		Circle circle[64];
	};
	
	void main() {
		gl_Position = vec4((circle[gl_InstanceID].pos + vert * circle[gl_InstanceID].radius) * scale, 0.0, 1.0);
	}
''')

circles_frag = GL.NewFragmentShader('''
	#version 430
	
	out vec4 color;

	void main() {
		color = vec4(0.30, 0.50, 1.00, 1.0);
	}
''')

particles_vert = GL.NewVertexShader('''
	#version 430

	in vec2 vert;
	uniform vec2 scale;

	struct Particle {
		vec2 prev;
		vec2 pos;
		vec2 acc;
	};

	layout (binding = 0) buffer Input {
		Particle particle[];
	};
	
	void main() {
		gl_Position = vec4((particle[gl_InstanceID].pos + vert * 5.0) * scale, 0.0, 1.0);
	}
''')

particles_frag = GL.NewFragmentShader('''
	#version 430
	
	out vec4 color;

	void main() {
		color = vec4(1.00, 0.50, 0.30, 1.0);
	}
''')

physics = GL.NewComputeShader('''
	#version 430

	struct Circle {
		vec2 pos;
		float radius;
	};

	struct Particle {
		vec2 prev;
		vec2 pos;
		vec2 acc;
	};

	uniform Circles {
		int circles;
		Circle circle[64];
	};

	layout (binding = 0) buffer Input {
		Particle particle[];
	};

	layout (local_size_x = 512, local_size_y = 1, local_size_z = 1) in;

	void update(inout Particle p) {
		vec2 pos = p.pos * 2 - p.prev + p.acc;
		p.prev = p.pos;
		p.pos = pos;

		for (int i = 0; i < circles; ++i) {
			vec2 sub = p.pos - circle[i].pos;
			float r = circle[i].radius + 2.5;
			if (dot(sub, sub) < r * r) {
				vec2 dir = p.pos - p.prev;
				p.pos = circle[i].pos + normalize(sub) * r;
				p.prev = p.pos - reflect(dir, normalize(sub)) * 0.7;
			}
		}
	}

	void main() {
		update(particle[gl_GlobalInvocationID.x]);
	}
''')

circles_prog = GL.NewProgram([circles_vert, circles_frag])
circles_iface = GL.GetProgramInterface(circles_prog)

GL.Uniform2f(circles_iface['scale'], 0.002 * height / width, 0.002)

circle_vbo = GL.NewVertexBuffer(b''.join(struct.pack('2f', cos(i * 2 * pi / 128), sin(i * 2 * pi / 128)) for i in range(128)))
circle_vao = GL.NewVertexArray('2f', circle_vbo, [circles_iface['vert']])

circles = [
	(-400, -200, 100),
	(-250, -350, 100),
	(0, -300, 100),
	(250, -350, 100),
	(400, -200, 100),
]

circles_ubo = GL.NewUniformBuffer(struct.pack('i4x', len(circles)) + b''.join(struct.pack('2f1f4x', *c) for c in circles))
GL.UseUniformBuffer(circles_ubo, circles_iface['Circles'])

particles_prog = GL.NewProgram([particles_vert, particles_frag])
particles_iface = GL.GetProgramInterface(particles_prog)

GL.Uniform2f(particles_iface['scale'], 0.002 * height / width, 0.002)

particle_vbo = GL.NewVertexBuffer(b''.join(struct.pack('2f', cos(i * 2 * pi / 16), sin(i * 2 * pi / 16)) for i in range(16)))
particle_vao = GL.NewVertexArray('2f', particle_vbo, [particles_iface['vert']])

sbo = GL.NewStorageBuffer(b''.join(struct.pack('ffffff', -10000, 0, -10000, 0, 0, 0) for i in range(10240)))
GL.UseUniformBuffer(circles_ubo, circles_iface['Circles'])
GL.UseStorageBuffer(sbo)

k = 0
while WND.Update():
	k = (k + 32) % 10240
	GL.UpdateStorageBuffer(sbo, k * 24, b''.join(struct.pack('ffffff', -400, 200, -400 + uniform(3, 5), 200 + uniform(2, 5), 0, -0.1) for i in range(32)))
	GL.Clear(240, 240, 240)
	GL.RunComputeShader(physics, 20)
	GL.UseProgram(circles_prog)
	GL.RenderTriangleFan(circle_vao, 128, instances = len(circles))
	GL.UseProgram(particles_prog)
	GL.RenderTriangleFan(particle_vao, 16, instances = 10240)

