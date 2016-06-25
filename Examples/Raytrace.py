# python -m pip install ModernGL
# python -m pip install GLWindow

import ModernGL as GL
import GLWindow as WND
import struct, random

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 430

	in vec2 vert;
	out vec3 light;

	uniform float ratio;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
		light = vec3(vert.x * ratio, vert.y, -1.0);
	}
''')

print('Vert:', GL.CompilerLog(), sep = '\n')

frag = GL.NewFragmentShader('''
	#version 430

	struct Triangle {
		vec4 color;
		vec3 T1;
		vec3 T2;
		vec3 T3;
		vec3 N;
	};
	
	in vec3 light;
	out vec4 frag;

	layout (binding = 1) buffer Input {
		int triangles;
		Triangle triangle[];
	};

	float rand(vec2 co) {
		return fract(sin(dot(co.xy ,vec2(12.9898, 78.233))) * 43758.5453);
	}

	vec3 raycast(vec3 R1, vec3 R2, float factor) {
		vec3 color = vec3(0, 0, 0);
		for (int h = 0; h < 5; ++h) {
			int hit = 0;
			float dist = -1;

			for (int i = 0; i < triangles; ++i) {
				vec3 T1 = triangle[i].T1;
				vec3 T2 = triangle[i].T2;
				vec3 T3 = triangle[i].T3;

				float f = dot(normalize(R1 - R2), triangle[i].N);
				if (f <= 0) continue;

				float D = determinant(mat3(R1 - R2, T2 - T1, T3 - T1));
				if (D == 0) continue;

				float u = determinant(mat3(R1 - T1, T2 - T1, T3 - T1)) / D;
				if (u < 0) continue;

				if (dist > 0 && dist < u) continue;

				float v = determinant(mat3(R1 - R2, R1 - T1, T3 - T1)) / D;
				if (v < 0) continue;

				float w = determinant(mat3(R1 - R2, T2 - T1, R1 - T1)) / D;
				if (w < 0) continue;

				if (v + w > 1) continue;

				dist = u;
				hit = i;
			}

			if (dist > 0) {
				int i = hit;
				float u = dist;

				vec3 K1 = R1 + (R2 - R1) * u;
				vec3 K2 = K1 + reflect(normalize(R2 - R1), normalize(triangle[i].N));

				float g = abs(dot(normalize(R2 - R1), normalize(triangle[i].N)));
				float a = triangle[i].color.a;
				color += triangle[i].color.rgb * a * factor * g;

				R1 = K1;
				R2 = K2;
				factor *= 1 - a;

				if (factor < 0.01) break;
			} else {
				break;
			}
		}
		return color;
	}

	void main() {
//		if (rand(light.xy) < 0.1) {
//			discard;
//		}

		frag = vec4(raycast(vec3(0, 0, 0), light, 1.0), 1.0);
	}
''')

print('Frag:', GL.CompilerLog(), sep = '\n')

prog = GL.NewProgram([vert, frag])

GL.Uniform1f(GL.UniformLocation(prog, 'ratio'), 16 / 9)

vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
vao = GL.NewVertexArray('2f', [(vbo, GL.AttributeLocation(prog, 'vert'))], vbo)

color = [
	(0.85, 0.85, 0.85, 0.95),
	(0.05, 0.25, 0.85, 0.25),
	(0.05, 0.85, 0.25, 0.25),
]

triangles = []
data = open('raytrace.dat', 'rb').read()
for k, i in enumerate(range(0, len(data), 48)):
	verts = struct.unpack('12f', data[i : i + 48])
	triangles.append(color[k // 12] + verts)

data = struct.pack('I12x', len(triangles))
data += b''.join(struct.pack('4f3f4x3f4x3f4x3f4x', *node) for node in triangles)

ssbo = GL.NewStorageBuffer(data)
GL.UseStorageBuffer(ssbo, 1)
GL.DisableMultisample()

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UseProgram(prog)
	GL.RenderTriangleStrip(vao, 4)
