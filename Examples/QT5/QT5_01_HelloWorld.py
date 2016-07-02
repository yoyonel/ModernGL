import sys, struct
from PyQt5.QtCore import pyqtSignal, QPoint, QSize, Qt
from PyQt5.QtWidgets import QApplication, QHBoxLayout, QOpenGLWidget, QSlider, QWidget

import ModernGL as GL

class Window(QWidget):
	def __init__(self):
		super(Window, self).__init__()

		self.setWindowTitle('QT5_01_HelloWorld')

		self.glWidget = GLWidget()
		mainLayout = QHBoxLayout()
		mainLayout.addWidget(self.glWidget)
		self.setLayout(mainLayout)

class GLWidget(QOpenGLWidget):
	def __init__(self, parent = None):
		super(GLWidget, self).__init__(parent)

	def sizeHint(self):
		return QSize(800, 600)

	def initializeGL(self):
		GL.InitializeModernGL()

		vert = GL.NewVertexShader('''
			#version 400

			in vec2 vert;

			void main() {
				gl_Position = vec4(vert, 0.0, 1.0);
			}
		''')

		frag = GL.NewFragmentShader('''
			#version 400
			
			out vec4 color;

			void main() {
				color = vec4(0.30, 0.50, 1.00, 1.0);
			}
		''')

		self.prog = GL.NewProgram([vert, frag])

		self.vbo = GL.NewVertexBuffer(struct.pack('6f', 0.0, 0.8, -0.6, -0.8, 0.6, -0.8))
		self.vao = GL.NewVertexArray('2f', [(self.vbo, GL.AttributeLocation(self.prog, 'vert'))])
		self.init = True

	def paintGL(self):
		GL.Clear(240, 240, 240)
		GL.UseProgram(self.prog)
		GL.RenderTriangles(self.vao, 3)

	def resizeGL(self, width, height):
		GL.Viewport(0, 0, width, height)

app = QApplication(sys.argv)
window = Window()
window.show()
sys.exit(app.exec_())