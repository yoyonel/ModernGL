from PIL import Image, ImageDraw, ImageFont
import ModernGL, GLWindow
import struct

GLWindow.Init()

# Context

ctx = ModernGL.create_context()

# Using Pillow to create a Texture

font = ImageFont.truetype('../data/OpenSans-Regular.ttf', 120)

msg = 'Hello World!'
msg_size = font.getsize(msg)

im = Image.new('RGBA', msg_size, (0, 0, 0, 0))

draw = ImageDraw.Draw(im)
draw.text((1, 0), msg, font = font, fill = (0, 0, 0, 255))
del draw

tex = ctx.Texture(im.size, 4, im.tobytes())
tex.use()

# Shaders & Program

prog = ctx.Program([
	ctx.VertexShader('''
		#version 330

		uniform vec2 Screen;

		in vec2 vert;
		in vec2 texcoord;

		out vec2 v_texcoord;

		void main() {
			gl_Position = vec4(vert / Screen * 2.0 - 1.0, 0.0, 1.0);
			v_texcoord = texcoord;
		}
	'''),
	ctx.FragmentShader('''
		#version 330

		uniform sampler2D Texture;

		in vec2 v_texcoord;
		out vec4 color;

		void main() {
			color = texture(Texture, v_texcoord);
		}
	'''),
])

prog.uniforms['Screen'].value = GLWindow.GetSize()

# Buffer

vbo = ctx.Buffer(struct.pack('16f',
	0, 0,
	0, 0,

	0, msg_size[1],
	0, -1,

	msg_size[0], 0,
	1, 0,

	msg_size[0], msg_size[1],
	1, -1,
))

# Put everything together

vao = ctx.SimpleVertexArray(prog, vbo, '2f2f', ['vert', 'texcoord'])

# Main loop

while GLWindow.Update():
	ctx.clear(240, 240, 240)
	ctx.enable(ModernGL.BLEND)
	vao.render(ModernGL.TRIANGLE_STRIP)

# Cleanup

vao.release()
vbo.release()
prog.release()
