import struct
import random

import GLWindow
import ModernGL

wnd = GLWindow.create_window(1024, 1024)
ctx = ModernGL.create_context()

prog = ctx.program([
    ctx.vertex_shader('''
        #version 330

        in vec2 vert;
        out vec2 text;

        void main() {
            text = vert;
            gl_Position = vec4((vert * 2.0 - 1.0) * 1, 0.0, 1.0);
        }
    '''),
    ctx.fragment_shader('''
        #version 330

        uniform sampler2D Texture;

        in vec2 text;
        out vec4 color;

        void main() {
            color = texture(Texture, text);
        }
    '''),
])

trans = ctx.program(
    ctx.vertex_shader('''
        #version 330

        uniform sampler2D Texture;

        in vec2 text;
        out float vert;

        #define LIVING 0.0
        #define DEAD 1.0

        #define DX 1.0 / 1024.0
        #define DY 1.0 / 1024.0

        void main() {
            bool living = texture(Texture, text).r < 0.5;

            int neighbours = 0;
            if (texture(Texture, text + vec2(-DX, -DY)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(-DX, 0.0)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(-DX, DY)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(DX, -DY)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(DX, 0.0)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(DX, DY)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(0.0, DY)).r < 0.5) neighbours++;
            if (texture(Texture, text + vec2(0.0, -DY)).r < 0.5) neighbours++;

            if (living) {
                vert = (neighbours == 2 || neighbours == 3) ? LIVING : DEAD;
//                vert = (neighbours >= 2 && neighbours <= 4) ? LIVING : DEAD;
            } else {
                vert = (neighbours == 3) ? LIVING : DEAD;
            }
        }
    '''),
    varyings=['vert']
)

data = bytearray()
for i in range(1024):
    for j in range(1024):
        data += struct.pack('f', random.randint(0, 1))

texture = ctx.texture((1024, 1024), 1, data, floats=True)
texture.filter = ModernGL.NEAREST
texture.swizzle = 'RRR1'
texture.use()

vbo = ctx.buffer(struct.pack('8f', 0, 0, 0, 1, 1, 0, 1, 1))
vao = ctx.simple_vertex_array(prog, vbo, ['vert'])

data = bytearray()
for i in range(1024):
    for j in range(1024):
        data += struct.pack('2f', (j + 0.5) / 1024, (i + 0.5) / 1024)

text = ctx.buffer(bytes(data))
tao = ctx.simple_vertex_array(trans, text, ['text'])
pbo = ctx.buffer(reserve=1024 * 1024 * 4)

while wnd.update():
    ctx.viewport = wnd.viewport

    tao.transform(pbo)
    texture.write(pbo)

    vao.render(ModernGL.TRIANGLE_STRIP)
