import ModernGL as GL, GLWindow as WND, struct, math

WND.InitializeWindow()
WND.BuildFullscreen()
GL.InitializeModernGL()

vert = GL.NewVertexShader('''
	#version 430

	in vec2 vert;
	out vec3 frag_vert;
	uniform float ratio;
	uniform vec3 position;
	uniform vec3 target;

	void main() {
		vec3 X = normalize(position - target);
		vec3 Y = normalize(cross(X, vec3(0.0, 0.0, 1.0)));
		vec3 Z = normalize(cross(X, Y));
		mat3 M = mat3(X, Y, Z);
		gl_Position = vec4(vert, 0.0, 1.0);
		frag_vert = M * vec3(1.0, vert.x * ratio, vert.y);
	}
''')

frag = GL.NewFragmentShader('''
	#version 430

	struct Face {
		vec4 color;
		vec3 T1, T2_T1, T3_T1, T2_T1_C_T3_T1, N;
	};
	
	in vec3 frag_vert;
	out vec4 frag;
	uniform vec3 position;

	layout (binding = 1) buffer Input {
		int faces;
		Face face[];
	};

	void main() {
		float factor = 1.0;
		vec3 R1 = position;
		vec3 R1_R2 = normalize(frag_vert);

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
				if (u < 0.0 || (dist > 0.0 && dist < u)) continue;
				vec3 R1_R2_C_R1_T1 = cross(R1_R2, R1_T1);
				float v = dot(face[i].T3_T1, R1_R2_C_R1_T1) / D;
				if (v < 0.0 || v > 1.0) continue;
				float w = -dot(face[i].T2_T1, R1_R2_C_R1_T1) / D;
				if (w < 0.0 || w > 1.0) continue;
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

prog = GL.NewProgram([vert, frag])
iface = GL.GetProgramInterface(prog)

vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
vao = GL.NewVertexArray('2f', vbo, [iface['vert']])

ssbo = GL.NewStorageBuffer(open('Data/Raytrace-scene.dat', 'rb').read())
GL.UseStorageBuffer(ssbo, 1)

GL.Uniform1f(iface['ratio'], 16 / 9)

x, y = 0.0, 0.0

while WND.Update():
	GL.Clear(240, 240, 240)

	if WND.GetKey(ord('A')) & 1:
		x -= 0.04
	if WND.GetKey(ord('D')) & 1:
		x += 0.04
	if WND.GetKey(ord('W')) & 1:
		y += 0.04
	if WND.GetKey(ord('S')) & 1:
		y -= 0.04

	GL.Uniform3f(iface['position'], math.cos(x) * math.cos(y), math.sin(x) * math.cos(y), math.sin(y))
	GL.Uniform3f(iface['target'], 0, 0, 0)
	GL.RenderTriangleStrip(vao, 4)
