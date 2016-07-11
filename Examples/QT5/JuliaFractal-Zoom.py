from PyQt5 import QtOpenGL, QtWidgets
import ModernGL as GL
import struct, time

context = {
	'width' : 800,
	'height' : 600,

	'dmx' : 0.0,
	'dmy' : 0.0,
	'ds' : 0.0,

	'mx': 0,
	'my' : 0,
	's' : -1,
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

				uniform vec2 pos;
				uniform float zoom;

				in vec2 vert;
				out vec2 textcoord;

				void main() {
					gl_Position = vec4(vert, 0.0, 1.0);
					textcoord = ((vert + pos) * zoom) / 2.0 + vec2(0.5, 0.5);
				}
			''')

			frag = GL.NewFragmentShader('''
				#version 330
				
				in vec2 textcoord;
				out vec4 color;

				uniform int iter;

				void main() {
					vec2 z = vec2(3.0 * (textcoord.x - 0.5), 2.0 * (textcoord.y - 0.5));
					vec2 c = vec2(0.0, 1.0);

					int i;
					for(i = 0; i < iter; i++) {
						float x = (z.x * z.x - z.y * z.y) + c.x;
						float y = (z.y * z.x + z.x * z.y) + c.y;
						if ((x * x + y * y) > 4.0) break;
						z.x = x;
						z.y = y;
					}

					float cm = fract((i == iter ? 0.0 : float(i)) * 10 / iter);
					color = vec4(fract(cm + 0.0 / 3.0), fract(cm + 1.0 / 3.0), fract(cm + 2.0 / 3.0), 1.0);
				}
			''')

			prog, iface = GL.NewProgram([vert, frag])
			context['pos'] = iface['pos']
			context['zoom'] = iface['zoom']

			vbo = GL.NewVertexBuffer(struct.pack('8f', -1.0, -1.0, -1.0, 1.0, 1.0, -1.0, 1.0, 1.0))
			context['vao'] = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

			GL.Uniform1i(iface['iter'], 100)
			
		except GL.Error as error:
			print(error)
			exit(1)

	def paintGL(self):
		z = 0.5 ** context['s']
		context['mx'] += context['dmx'] * z
		context['my'] += context['dmy'] * z
		context['s'] += context['ds']
		GL.Clear(240, 240, 240)

		GL.Uniform2f(context['pos'], context['mx'] / z, context['my'] / z)
		GL.Uniform1f(context['zoom'], z)
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
