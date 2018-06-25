"""

"""
import moderngl
import numpy as np
from PIL import Image
#
from examples.example_window import Example, run_example


class TextureArray(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

        prog = self.ctx.program(
            vertex_shader='''
                #version 330

                in vec2 in_vert;
                in vec3 in_text;

                out vec3 v_text;

                void main() {
                    v_text = in_text;
                    gl_Position = vec4(in_vert, 0.0, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                uniform sampler2DArray Texture;

                in vec3 v_text;

                out vec4 f_color;

                void main() {
                    f_color = texture(Texture, v_text);
                }
            ''',
        )

        vbo = self.ctx.buffer(np.array([
            (
                -0.3, -0.3 + i * 0.2 - 0.2, 0.0, 0.0, i,
                0.3, -0.3 + i * 0.2 - 0.2, 1.0, 0.0, i,
                0.0, 0.3 + i * 0.2 - 0.2, 0.5, 1.0, i,
            ) for i in range(3)
        ], dtype='f4'))

        images = [
            Image.new('RGB', (256, 256), 'red'),
            Image.new('RGB', (256, 256), 'green'),
            Image.new('RGB', (256, 256), 'blue'),
        ]

        merged = b''.join(img.tobytes() for img in images)

        self.tex = self.ctx.texture_array((256, 256, 3), 3, merged)
        self.tex.use()

        self.vao = self.ctx.simple_vertex_array(prog, vbo, 'in_vert', 'in_text')

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0, 1.0)
        self.vao.render()


if __name__ == '__main__':
    run_example(TextureArray)
