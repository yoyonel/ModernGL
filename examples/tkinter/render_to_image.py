import tkinter as tk
from PIL import Image, ImageTk

import ModernGL, struct

ctx = ModernGL.create_standalone_context()

size = (500, 500)
color_rbo = ctx.Renderbuffer(size)
depth_rbo = ctx.DepthRenderbuffer(size)
fbo = ctx.Framebuffer([color_rbo, depth_rbo])
fbo.use()

prog = ctx.program([
	ctx.vertex_shader('''
		#version 330

		in vec2 vert;

		void main() {
			gl_Position = vec4(vert, 0.0, 1.0);
		}
	'''),
	ctx.fragment_shader('''
		#version 330

		uniform float R;
		uniform float G;
		uniform float B;

		out vec4 color;

		void main() {
			color = vec4(R, G, B, 1.0);
		}
	'''),
])

vbo = ctx.buffer(struct.pack('6f',
	0.0, 0.8,
	-0.6, -0.8,
	0.6, -0.8,
))

vao = ctx.simple_vertex_array(prog, vbo, ['vert'])

ctx.viewport = (0, 0, size[0], size[1])
ctx.clear(240, 240, 240)
vao.render()

root = tk.Tk()

img = ImageTk.PhotoImage(Image.frombytes('RGB', size, fbo.read(size, components = 3)).transpose(Image.FLIP_TOP_BOTTOM))
panel = tk.Label(root, image = img)
panel.pack()

def redraw(col, val):
	prog.uniforms[col].value = val
	ctx.viewport = (0, 0, size[0], size[1])
	ctx.clear(240, 240, 240)
	vao.render()

	img2 = ImageTk.PhotoImage(Image.frombytes('RGB', size, fbo.read(size, components = 3)).transpose(Image.FLIP_TOP_BOTTOM))
	panel.configure(image = img2)
	panel.image = img2


R = tk.Scale(root, from_ = 0, to = 255, orient = tk.HORIZONTAL, command = lambda x: redraw('R', int(x) / 255))
G = tk.Scale(root, from_ = 0, to = 255, orient = tk.HORIZONTAL, command = lambda x: redraw('G', int(x) / 255))
B = tk.Scale(root, from_ = 0, to = 255, orient = tk.HORIZONTAL, command = lambda x: redraw('B', int(x) / 255))

R.pack()
G.pack()
B.pack()

root.mainloop()
