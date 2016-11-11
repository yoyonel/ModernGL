from kivy.app import App
from kivy.uix.widget import Widget
from kivy.graphics import Callback

import ModernGL as GL
import struct

class CustomWidget(Widget):
	def __init__(self, **kwargs):
		super(CustomWidget, self).__init__(**kwargs)

		with self.canvas:

			GL.Init()

			self.vert = GL.NewVertexShader('''
				#version 330

				in vec2 vert;

				void main() {
					gl_Position = vec4(vert, 0.0, 1.0);
				}
			''')

			self.frag = GL.NewFragmentShader('''
				#version 330
				
				out vec4 color;

				void main() {
					color = vec4(0.30, 0.50, 1.00, 1.0);
				}
			''')

			self.prog = GL.NewProgram([self.vert, self.frag])

			self.vbo = GL.NewVertexBuffer(struct.pack('6f', 0.0, 0.8, -0.6, -0.8, 0.6, -0.8))
			self.vao = GL.NewVertexArray(self.prog, self.vbo, '2f', ['vert'])

			self.draw()

			Callback(self.draw)

	def draw(self, *args):
		GL.Clear(240, 240, 240)
		GL.RenderTriangles(self.vao, 3)

	def ask_update(self, *largs):
		self.canvas.ask_update()

class MainApp(App):

	def build(self):
		self.root = root = CustomWidget()
		return root

if __name__ == '__main__':
	MainApp().run()
