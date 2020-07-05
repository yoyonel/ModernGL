"""
Demonstrates redering a terrain/height map on the fly without any
pre-generated geometry.
"""

import numpy as np
from pyrr import Matrix44

import moderngl
from ported._example import Example


class HeightmapOnTheFly(Example):
    title = "Multitexture Terrain"
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.dim = 5
        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 projection;
                uniform mat4 modelview;
                uniform float map_size;

                void main() {
                    gl_Position = 
                }
            ''',
            fragment_shader='''
                #version 330

                out vec4 f_color;

                void main() {
                    f_color = vec4(1.0);
                }
            ''',
        )

        self.vao = self.ctx.vertex_array(self.prog, [])

        projection = Matrix44.perspective_projection(45.0, self.aspect_ratio, 0.1, 1000.0, dtype='f4')
        self.prog['projection'].write(projection)

    def render(self, time, frame_time):
        angle = time * 0.2
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        lookat = Matrix44.look_at(
            (np.cos(angle), np.sin(angle), 0.8),
            (0.0, 0.0, 0.1),
            (0.0, 0.0, 1.0),
            dtype='f4',
        )
        
        self.prog['modelview'].write(lookat)
        self.vao.render(moderngl.POINTS, vertices=(self.dim - 1) ** 2)


if __name__ == '__main__':
    HeightmapOnTheFly.run()
