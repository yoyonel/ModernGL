from PyQt5 import QtOpenGL, QtWidgets
import ModernGL as GL
import struct

context = {
	'width' : 800,
	'height' : 600,

	'dmx' : 0.0,
	'dmy' : 0.0,
	'ds' : 0.0,

	'mx': 0.78,
	'my' : -0.15,
	's' : 1.84,
}

class QGLControllerWidget(QtOpenGL.QGLWidget):
	def __init__(self, format = None):
		super(QGLControllerWidget, self).__init__(format, None)

	def initializeGL(self):
		try:
			GL.InitializeModernGL()
			GL.Viewport(0, 0, context['width'], context['height'])

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
			context['center'] = iface['center']
			context['scale'] = iface['scale']

			vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
			context['vao'] = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

			GL.SetUniform(iface['iter'], 100)
			GL.SetUniform(iface['scale'], 1.0)
			GL.SetUniform(iface['center'], 0.3, 0.2)
			
		except GL.Error as error:
			print(error)
			exit(1)

	def paintGL(self):
		context['mx'] += context['dmx']
		context['my'] += context['dmy']
		context['s'] += context['ds']
		GL.Clear(240, 240, 240)
		GL.SetUniform(context['center'], context['mx'], context['my'])
		GL.SetUniform(context['scale'], 0.5 ** context['s'])
		GL.RenderTriangleStrip(context['vao'], 4)
		self.update()

	def keyPressEvent(self, event):
		if event.key() == ord('D'):
			context['dmx'] += 0.01
		if event.key() == ord('A'):
			context['dmx'] -= 0.01
		if event.key() == ord('W'):
			context['dmy'] += 0.01
		if event.key() == ord('S'):
			context['dmy'] -= 0.01
		if event.key() == ord('Q'):
			context['ds'] += 0.01
		if event.key() == ord('E'):
			context['ds'] -= 0.01

	def keyReleaseEvent(self, event):
		if event.key() == ord('D'):
			context['dmx'] -= 0.01
		if event.key() == ord('A'):
			context['dmx'] += 0.01
		if event.key() == ord('W'):
			context['dmy'] -= 0.01
		if event.key() == ord('S'):
			context['dmy'] += 0.01
		if event.key() == ord('Q'):
			context['ds'] -= 0.01
		if event.key() == ord('E'):
			context['ds'] += 0.01

class GLCanvas(QtWidgets.QMainWindow):

	def keyPressEvent(self, event):
		self.widget.keyPressEvent(event)

	def keyReleaseEvent(self, event):
		self.widget.keyReleaseEvent(event)

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
