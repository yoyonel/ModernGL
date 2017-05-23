import os
import struct

import GLWindow
import ModernGL

from PIL import Image

# Window & Context

wnd = GLWindow.create_window()
ctx = ModernGL.create_context()

# Shaders & Program

prog = ctx.program([
    ctx.vertex_shader('''
        #version 330

        in vec2 vert;
        out vec2 tex_coord;

        uniform vec2 scale;
        uniform float rotation;

        void main() {
            float r = rotation * (0.5 + gl_InstanceID * 0.05);
            mat2 rot = mat2(cos(r), sin(r), -sin(r), cos(r));
            gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
            tex_coord = vert;
        }
    '''),
    ctx.fragment_shader('''
        #version 330

        uniform sampler2D texture;

        in vec2 tex_coord;
        out vec4 color;

        void main() {
            color = vec4(texture2D(texture, tex_coord).rgb, 1.0);
        }
    '''),
])

# Uniforms

scale = prog.uniforms['scale']
rotation = prog.uniforms['rotation']

width, height = wnd.size
scale.value = (height / width * 0.75, 0.75)

# Buffer

vbo = ctx.buffer(struct.pack(
    '6f',
    1.0, 0.0,
    -0.5, 0.86,
    -0.5, -0.86,
))

# Put everything together

vao = ctx.simple_vertex_array(prog, vbo, ['vert'])

# Texture

img = Image.open(os.path.join(os.path.dirname(__file__), '..', 'data', 'noise.jpg'))
texture = ctx.texture(img.size, 3, img.tobytes())
texture.use()

# Main loop

while wnd.update():
    ctx.viewport = wnd.viewport
    ctx.clear(0.9, 0.9, 0.9)
    rotation.value = wnd.time
    vao.render()
