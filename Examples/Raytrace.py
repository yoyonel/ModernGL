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
	out vec2 frag_vert;

	uniform float ratio;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
		frag_vert = -vec2(vert.x * ratio, vert.y);
	}
''')

print('Vert:', GL.CompilerLog(), sep = '\n')

frag = GL.NewFragmentShader('''
	#version 430

	struct Face {
		vec4 color;
		vec3 T1;
		vec3 T2_T1;
		vec3 T3_T1;
		vec3 T2_T1_C_T3_T1;
		vec3 N;
	};
	
	in vec2 frag_vert;
	out vec4 frag;

	layout (binding = 1) buffer Input {
		int faces;
		Face face[];
	};

	void main() {
		float factor = 1.0;
		vec3 R1 = vec3(0.0, 0.0, 0.0);
		vec3 R1_R2 = normalize(vec3(frag_vert, 1.0));

		vec3 color = vec3(0.0, 0.0, 0.0);
		for (int h = 0; h < 5; ++h) {
			int hit = 0;
			float dist = -1;

			for (int i = 0; i < faces; ++i) {
				vec3 T1 = face[i].T1;

				float f = dot(R1_R2, face[i].N);
				if (f <= 0.0) continue;

				float D = dot(R1_R2, face[i].T2_T1_C_T3_T1);
				if (D == 0.0) continue;

				vec3 R1_T1 = R1 - T1;

				float u = dot(R1_T1, face[i].T2_T1_C_T3_T1) / D;
				if (u < 0.0) continue;

				if (dist > 0.0 && dist < u) continue;

				vec3 R1_R2_C_R1_T1 = cross(R1_R2, R1_T1);

				float v = dot(face[i].T3_T1, R1_R2_C_R1_T1) / D;
				if (v < 0.0) continue;

				float w = -dot(face[i].T2_T1, R1_R2_C_R1_T1) / D;
				if (w < 0.0) continue;

				if (v + w > 1.0) continue;

				dist = u;
				hit = i;
			}

			if (dist > 0) {
				float g = dot(R1_R2, face[hit].N);
				color += face[hit].color.rgb * factor * g;

				R1 = R1 - R1_R2 * dist;
				R1_R2 = reflect(R1_R2, face[hit].N);
				factor *= 1.0 - face[hit].color.a;

				if (factor < 0.01) break;
			} else {
				break;
			}
		}

		frag = vec4(color, 1.0);
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


faces = []
data = open('raytrace.dat', 'rb').read()
for k, i in enumerate(range(0, len(data), 48)):
	verts = struct.unpack('12f', data[i : i + 48])
	faces.append(list(color[k // 12] + verts))

for i in range(len(faces)):
	faces[i][0] *= faces[i][3]
	faces[i][1] *= faces[i][3]
	faces[i][2] *= faces[i][3]
	faces[i][7] = faces[i][7] - faces[i][4]
	faces[i][8] = faces[i][8] - faces[i][5]
	faces[i][9] = faces[i][9] - faces[i][6]
	faces[i][10] = faces[i][10] - faces[i][4]
	faces[i][11] = faces[i][11] - faces[i][5]
	faces[i][12] = faces[i][12] - faces[i][6]
#	faces[i][7]  faces[i][8]  faces[i][9]
#	faces[i][10] faces[i][11] faces[i][12]
	cross = [
		faces[i][8] * faces[i][12] - faces[i][9] * faces[i][11],
		faces[i][10] * faces[i][9] - faces[i][12] * faces[i][7],
		faces[i][7] * faces[i][11] - faces[i][8] * faces[i][10],
	]

	faces[i] = faces[i][:13] + cross + faces[i][13:]

data = struct.pack('I12x', len(faces))
data += b''.join(struct.pack('4f3f4x3f4x3f4x3f4x3f4x', *node) for node in faces)

ssbo = GL.NewStorageBuffer(data)
GL.UseStorageBuffer(ssbo, 1)
GL.DisableMultisample()

while WND.Update():
	GL.Clear(240, 240, 240)

	GL.UseProgram(prog)
	GL.RenderTriangleStrip(vao, 4)
