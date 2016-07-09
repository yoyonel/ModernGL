# python -m pip install Pillow

from PIL import Image
from PyQt5 import QtOpenGL, QtWidgets
import ModernGL as GL
import struct, time

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
				#version 330

				in vec2 vert;
				out vec2 tex_coord;

				uniform vec2 scale;
				uniform float rotation;

				void main() {
					mat2 rot = mat2(cos(rotation), sin(rotation), -sin(rotation), cos(rotation));
					gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
					tex_coord = vert;
				}
			''')

			frag = GL.NewFragmentShader('''
				#version 330

				uniform sampler2D texture;
				
				in vec2 tex_coord;
				out vec4 color;

				void main() {
					color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
				}
			''')

			prog, iface = GL.NewProgram([vert, frag])
			context['rotation'] = iface['rotation']

			vbo = GL.NewVertexBuffer(struct.pack('6f', 1.0, 0.0, -0.5, 0.86, -0.5, -0.86))
			context['vao'] = GL.NewVertexArray(prog, vbo, '2f', ['vert'])

			GL.Uniform2f(iface['scale'], context['height'] / context['width'] * 0.75, 0.75)

			tex = GL.NewTexture(256, 256, Image.open('../Data/Noise.jpg').tobytes())
			GL.UseTexture(tex)
			
		except GL.Error as error:
			print(error)
			exit(1)

	def paintGL(self):
		print('asd')
		GL.Clear(240, 240, 240)
		GL.Uniform1f(context['rotation'], time.time())
		GL.RenderTriangles(context['vao'], 3)

class QTWithGLTest(QtWidgets.QMainWindow):
	def __init__(self, parent = None):
		super(QTWithGLTest, self).__init__(parent)

		fmt = QtOpenGL.QGLFormat()
		fmt.setVersion(3, 3)
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
