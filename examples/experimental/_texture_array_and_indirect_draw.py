"""

"""
import moderngl
import numpy as np
from PIL import Image
#
from examples.example_window import Example, run_example


class TextureArrayAndIndirectDraw(Example):
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

        x1 = np.cos(np.linspace(0.0, 2.0 * np.pi, 3, False)) * 0.3 * 9 / 16 - 0.4
        y1 = np.sin(np.linspace(0.0, 2.0 * np.pi, 3, False)) * 0.3
        z1 = np.full(3, 0.0)

        x2 = np.cos(np.linspace(0.0, 2.0 * np.pi, 4, False)) * 0.3 * 9 / 16
        y2 = np.sin(np.linspace(0.0, 2.0 * np.pi, 4, False)) * 0.3
        z2 = np.full(4, 1.0)

        x3 = np.cos(np.linspace(0.0, 2.0 * np.pi, 5, False)) * 0.3 * 9 / 16 + 0.4
        y3 = np.sin(np.linspace(0.0, 2.0 * np.pi, 5, False)) * 0.3
        z3 = np.full(5, 2.0)

        shapes = [
            np.dstack([x1, y1, x1, y1, z1]).astype('f4'),
            np.dstack([x2, y2, x2, y2, z2]).astype('f4'),
            np.dstack([x3, y3, x3, y3, z3]).astype('f4'),
        ]

        vbo = self.ctx.buffer(b''.join(shape.tobytes() for shape in shapes))
        # https://www.khronos.org/opengl/wiki/Vertex_Rendering#Indirect_rendering
        self.dbo = self.ctx.buffer(
            np.array([
                3, 1, 0, 0, 0,
                4, 1, 3, 0, 0,
                5, 1, 7, 0, 0,
            ], dtype='i4')
        )

        images = [
            Image.new('RGB', (256, 256), 'red'),
            Image.new('RGB', (256, 256), 'green'),
            Image.new('RGB', (256, 256), 'blue'),
        ]

        merged = b''.join(img.tobytes() for img in images)

        tex = self.ctx.texture_array((256, 256, 3), 3, merged)
        tex.use()

        self.vao = self.ctx.simple_vertex_array(prog, vbo, 'in_vert', 'in_text')

    def render(self):
        self.ctx.clear(1.0, 1.0, 1.0, 1.0)
        # self.vao.mglo.render(moderngl.TRIANGLE_FAN, 3, 0, 1)
        # self.vao.mglo.render(moderngl.TRIANGLE_FAN, 4, 3, 1)
        # self.vao.mglo.render(moderngl.TRIANGLE_FAN, 5, 7, 1)
        self.vao.render_indirect(self.dbo, moderngl.TRIANGLE_FAN)


if __name__ == '__main__':
    run_example(TextureArrayAndIndirectDraw)
