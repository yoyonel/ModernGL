from PyQt5 import QtOpenGL, QtWidgets
import ModernGL as GL
import struct, time

context = {
	'width' : 800,
	'height' : 600,
	'start' : time.time(),
}

class QGLControllerWidget(QtOpenGL.QGLWidget):
	def __init__(self, format = None):
		super(QGLControllerWidget, self).__init__(format, None)

	def initializeGL(self):
		try:
			GL.Init()
			GL.Viewport(0, 0, context['width'], context['height'])

			vert = GL.NewVertexShader('''
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

			frag = GL.NewFragmentShader('''
				#version 330
				
				in vec4 frag_color;
				out vec4 color;

				void main() {
					color = frag_color;
				}
			''')

			prog, iface = GL.NewProgram([vert, frag])
			context['rotation'] = iface['rotation']

			verts = [
				1.0, 0.0,
				1.0, 0.0, 0.0, 0.5,

				-0.5, 0.86,
				0.0, 1.0, 0.0, 0.5,

				-0.5, -0.86,
				0.0, 0.0, 1.0, 0.5,
			]

			vbo = GL.NewVertexBuffer(struct.pack('18f', *verts))
			context['vao'] = GL.NewVertexArray(prog, vbo, '2f4f', ['vert', 'vert_color'])

			GL.SetUniform(iface['scale'], context['height'] / context['width'] * 0.75, 0.75)

		except GL.Error as error:
			print(error)
			exit(1)

	def paintGL(self):
		GL.Clear(240, 240, 240)
		GL.EnableOnly(GL.ENABLE_BLEND + GL.ENABLE_MULTISAMPLE)
		GL.SetUniform(context['rotation'], time.time() - context['start'])
		GL.RenderTriangles(context['vao'], 3, instances = 10)
		self.update()

class GLCanvas(QtWidgets.QMainWindow):
	def __init__(self, parent = None):
		super(GLCanvas, self).__init__(parent)

		fmt = QtOpenGL.QGLFormat()
		fmt.setVersion(3, 3)
		fmt.setProfile(QtOpenGL.QGLFormat.CoreProfile)
		fmt.setSampleBuffers(True)

		self.setFixedSize(context['width'], context['height'])
		self.widget = QGLControllerWidget(fmt)
		self.setCentralWidget(self.widget)
		self.show()

app = QtWidgets.QApplication([])
window = GLCanvas()
window.show()
app.exec_()
