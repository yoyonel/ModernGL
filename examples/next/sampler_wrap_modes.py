import moderngl.next as mgl
import numpy as np
from PIL import Image

import data
from window import Example, run_example


class SimpleColorTriangle(Example):
    gl_version = (3, 3)
    aspect_ratio = 1.0
    title = "Sampler Wrap Modes"

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                in vec2 in_vert;
                in vec2 in_text;

                out vec2 v_text;

                void main() {
                    gl_Position = vec4(in_vert, 0.0, 1.0);
                    v_text = in_text;
                }
            ''',
            fragment_shader='''
                #version 330

                uniform sampler2D Texture;

                in vec2 v_text;
                out vec4 f_color;

                void main() {
                    f_color = texture(Texture, v_text);
                }
            ''',
        )

        vertices = np.array([
            -0.9, -0.9, -2.0, -2.0,
            -0.9, 0.9, -2.0, 3.0,
            0.9, -0.9, 3.0, -2.0,
            0.9, 0.9, 3.0, 3.0,
        ], dtype='f4')

        self.vbo = self.ctx.buffer(vertices)
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert', 'in_text')
        self.vao.mode = mgl.TRIANGLE_STRIP

        img = Image.open(data.find('color_arrows.png')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture = self.ctx.texture(img)
        self.sampler = self.ctx.sampler(self.texture)
        self.sampler.wrap = mgl.REPEAT_X | mgl.MIRROR_CLAMP_TO_EDGE_Y

    def render(self, time: float, frame_time: float):
        self.ctx.clear(1.0, 1.0, 1.0)
        self.sampler.use()
        self.vao.render()


if __name__ == '__main__':
    run_example(SimpleColorTriangle)
