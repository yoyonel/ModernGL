import os

import moderngl
import numpy as np
from PIL import Image
from pyrr import Matrix44

from example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


def terrain(size):
    vertices = np.dstack(np.mgrid[0:size, 0:size][::-1]) / size
    temp = np.dstack([np.arange(0, size * size - size), np.arange(size, size * size)])
    index = np.pad(temp.reshape(size - 1, 2 * size), [[0, 0], [0, 1]], 'constant', constant_values=-1)
    return vertices, index


class WireframeTerrain(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;
                uniform sampler2D Heightmap;

                in vec2 in_vert;
                in vec3 in_color;

                out vec3 v_color;

                void main() {
                    v_color = in_color;
                    float height = texture(Heightmap, in_vert.xy).r * 0.5;
                    gl_Position = Mvp * vec4(in_vert.xy - 0.5, height, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                in vec3 v_color;
                out vec4 f_color;

                void main() {
                    f_color = vec4(v_color, 1.0);
                }
            ''',
        )

        self.mvp = self.prog['Mvp']

        vertices, index = terrain(32)

        self.vbo = self.ctx.buffer(vertices.astype('f4').tobytes())
        self.ibo = self.ctx.buffer(index.astype('i4').tobytes())

        vao_content = [
            (self.vbo, '2f', 'in_vert'),
        ]

        self.vao = self.ctx.vertex_array(self.prog, vao_content, self.ibo)

        self.img = Image.open(local('data', 'noise.jpg')).convert('L')
        texture = self.ctx.texture(self.img.size, 1, self.img.tobytes())
        texture.use()

    def render(self):
        width, height = self.wnd.size
        angle = self.wnd.time * 0.2

        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)
        self.ctx.wireframe = True

        proj = Matrix44.perspective_projection(45.0, width / height, 0.1, 1000.0)
        lookat = Matrix44.look_at(
            (np.cos(angle), np.sin(angle), 0.8),
            (0.0, 0.0, 0.1),
            (0.0, 0.0, 1.0),
        )

        self.mvp.write((proj * lookat).astype('f4').tobytes())
        self.vao.render(moderngl.TRIANGLE_STRIP)


run_example(WireframeTerrain)
