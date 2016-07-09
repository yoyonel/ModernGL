import struct, math

from PyQt5 import QtOpenGL, QtWidgets
import ModernGL as GL

context = {
	'width' : 800,
	'height' : 600,
}

class QGLControllerWidget(QtOpenGL.QGLWidget):
	def __init__(self, format = None):
		super(QGLControllerWidget, self).__init__(format, None)

	def initializeGL(self):
		try:
			GL.InitializeModernGL()
			GL.Viewport(0, 0, context['width'], context['height'])

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

			prog, iface = GL.NewProgram([vert, frag])

			vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
			context['vao'] = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

			ssbo = GL.NewStorageBuffer(open('../Data/Raytrace-scene.dat', 'rb').read())
			GL.UseStorageBuffer(ssbo, 1)

			GL.Uniform1f(iface['ratio'], context['width'] / context['height'])
			GL.Uniform3f(iface['position'], 0.7, 0.7, 0.0)
			GL.Uniform3f(iface['target'], 0, 0, 0)

		except GL.Error as error:
			print(error)
			exit(1)

	def paintGL(self):
		GL.Clear(240, 240, 240)
		GL.RenderTriangleStrip(context['vao'], 4)

class QTWithGLTest(QtWidgets.QMainWindow):
	def __init__(self, parent = None):
		super(QTWithGLTest, self).__init__(parent)

		fmt = QtOpenGL.QGLFormat()
		fmt.setVersion(4, 3)
		fmt.setProfile(QtOpenGL.QGLFormat.CoreProfile)
		fmt.setSampleBuffers(True)

		self.setFixedSize(context['width'], context['height'])
		self.widget = QGLControllerWidget(fmt)
		self.setCentralWidget(self.widget)
		self.show()

app = QtWidgets.QApplication([])
window = QTWithGLTest()
window.show()
app.exec_()
