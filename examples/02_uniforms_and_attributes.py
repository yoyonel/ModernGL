'''
    Renders a rotating and scaling traignle
'''

import moderngl
import numpy as np

from example_window import Example, run_example


class UniformsAndAttributes(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330
                in vec2 vert;

                uniform vec2 scale;
                uniform float rotation;

                void main() {

                    mat2 rot = mat2(
                        cos(rotation), sin(rotation),
                        -sin(rotation), cos(rotation)
                    );
                    gl_Position = vec4((rot * vert) * scale, 0.0, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                out vec4 color;
                void main() {
                    color = vec4(0.3, 0.5, 1.0, 1.0);
                }
            ''',
        )

        self.scale = self.prog['scale']
        self.rotation = self.prog['rotation']

        width, height = self.wnd.size
        self.scale.value = (height / width * 0.75, 0.25)

        vertices = np.array([
            1.0, 0.0,
            -0.5, 0.86,
            -0.5, -0.86,
        ])

        self.vbo = self.ctx.buffer(vertices.astype('f4').tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'vert')

    def render(self):
        sin_scale = np.sin(np.deg2rad(self.wnd.time * 60))

        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.vao.render()
        self.rotation.value = self.wnd.time

        # Change the scale of the triangle sin-ly
        self.scale.value = (sin_scale * 0.75, 0.75)


run_example(UniformsAndAttributes)
