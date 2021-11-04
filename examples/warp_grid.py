"""
"""
import os
import pickle
from typing import Final

import numpy as np
from pyrr import Matrix44

import moderngl
#
from ported._example import Example

GRID_SIZE_CELL: Final[int] = 32
GRID_SIZE_X: Final[int] = 11
GRID_SIZE_Y: Final[int] = 13


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class WarpGrid(Example):
    title = "Warp Grid from Wireframe Terrain"
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.prog_animate_warp_grid = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;
                uniform sampler3D Heightmap;

                in vec2 in_vert;
                in vec3 in_color;                

                out vec3 v_color;
                out vec2 v_text;

                uniform float time;

                void main() {
                    v_color = in_color;

                    vec2 pos_from_tex = texture(Heightmap, vec3(in_vert.xy, time)).xy;
                    gl_Position = Mvp * vec4(pos_from_tex.xy, 0.0, 1.0);

                    v_text = in_vert;
                    v_text -= vec2(0, time) * 8;
                }
            ''',
            fragment_shader='''
                #version 330

                in vec3 v_color;
                in vec2 v_text;
                out vec4 f_color;

                uniform sampler2D Texture;

                void main() {
                    f_color = texture(Texture, v_text);
                }
            ''',
        )

        self.mvp = self.prog_animate_warp_grid['Mvp']

        proj = Matrix44.orthogonal_projection(
            0.0,
            1.0 - 1 / float(GRID_SIZE_X),
            1.0 - 1 / float(GRID_SIZE_Y),
            0.0,
            -1.0, +1.0
        )
        look_at = Matrix44.identity()
        self.mvp.write((proj * look_at).astype('f4').tobytes())

        vertices, index = WarpGrid.terrain((GRID_SIZE_X, GRID_SIZE_Y))

        vbo_warp_grid = self.ctx.buffer(vertices.astype('f4').tobytes())
        ibo_warp_grid = self.ctx.buffer(index.astype('i4').tobytes())
        vao_warp_grid = [
            (vbo_warp_grid, '2f', 'in_vert'),
        ]
        self.vao_warp_grid = self.ctx.vertex_array(self.prog_animate_warp_grid, vao_warp_grid, ibo_warp_grid)

        grids_array = WarpGrid.load_animated_grid()

        # https://moderngl.readthedocs.io/en/stable/reference/texture3d.html?highlight=write
        self.texture3d_grids = self.ctx.texture3d(
            (grids_array.shape[1], grids_array.shape[2], grids_array.shape[0]),
            components=grids_array.shape[3],
            data=grids_array.tobytes(),
            dtype='f4'
        )
        self.texture3d_grids.repeat_x = False
        self.texture3d_grids.repeat_y = False
        self.texture3d_grids.repeat_z = True
        self.texture3d_grids.filter = (moderngl.LINEAR, moderngl.LINEAR)

        self.texture_cooling_map = self.load_texture_2d('noise.jpg')
        self.texture_cooling_map.repeat_x = False
        self.texture_cooling_map.repeat_y = True
        self.texture_cooling_map.filter = (moderngl.LINEAR, moderngl.LINEAR)

        self.prog_animate_warp_grid['Heightmap'].value = 0
        self.prog_animate_warp_grid['Texture'].value = 1

        ########################################################################
        self.prog_render_rtt = self.ctx.program(
            vertex_shader='''
                #version 330

                in vec2 in_vert;
                out vec2 v_text;

                void main() {
                    v_text = in_vert;
                    gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                uniform sampler2D Texture;

                in vec2 v_text;

                out vec4 f_color;

                void main() {
                    f_color = vec4(vec3(texture(Texture, v_text).rgb), 1.0);
                }
            ''',
        )

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
        vbo_rtt = self.ctx.buffer(canvas.tobytes())
        self.vao_rtt = self.ctx.simple_vertex_array(self.prog_render_rtt, vbo_rtt, 'in_vert')
        self.tex_rtt = self.ctx.texture(self.texture_cooling_map.size, 1, dtype='f1')
        self.fbo_rtt = self.ctx.framebuffer([self.tex_rtt])

        self.ctx.wireframe = False

    @staticmethod
    def terrain(size: tuple):
        xv, yv = np.mgrid[0:size[0], 0:size[1]][::-1]
        xv = xv / (size[1] - 1)
        yv = yv / (size[0] - 1)
        vertices = np.dstack((xv, yv))

        temp = np.dstack([
            np.arange(0, size[0] * size[1] - size[1]),
            np.arange(size[1], size[0] * size[1])
        ])
        index = np.pad(temp.reshape(size[0] - 1, 2 * size[1]), [[0, 0], [0, 1]],
                       'constant', constant_values=-1)
        return vertices, index

    @staticmethod
    def load_animated_grid() -> np.array:
        # Load datas (precomputed) from Pymunk warp grid simulation
        # https://stackoverflow.com/questions/17623523/can-i-stream-a-python-pickle-list-tuple-or-other-iterable-data-type
        grids_array = []
        #
        # TODO: refactoring with self.load_binary()
        with open(local('data',
                        f'warp#4hz#{GRID_SIZE_X}#{GRID_SIZE_Y}#{GRID_SIZE_CELL}.pkl'),
                  'rb') as fp:
            try:
                while True:
                    grid_array = np.array(pickle.load(fp), dtype='f4')
                    # https://numpy.org/doc/stable/reference/arrays.ndarray.html#arithmetic-matrix-multiplication-and-comparison-operations
                    grid_array /= np.array([GRID_SIZE_X, GRID_SIZE_Y]) * GRID_SIZE_CELL
                    # https://docs.scipy.org/doc/numpy/reference/generated/numpy.reshape.html
                    grid_array = grid_array.reshape((GRID_SIZE_X, GRID_SIZE_Y, grid_array.shape[1]))
                    grids_array.append(grid_array)
            except EOFError:
                pass
        return np.array(grids_array)

    def update_grid(self, time):
        self.prog_animate_warp_grid['time'].value = time * (1. / 4.) * 0.1  # 4 hz records

        self.fbo_rtt.use()
        self.texture3d_grids.use(0)
        self.texture_cooling_map.use(1)
        # render textured warp grid
        self.vao_warp_grid.render(moderngl.TRIANGLE_STRIP)

    def render(self, time, frame_time):
        self.update_grid(time)

        # render rtt wrap grid
        self.ctx.screen.use()
        self.ctx.disable(moderngl.DEPTH_TEST)

        self.tex_rtt.use()
        self.vao_rtt.render(moderngl.TRIANGLE_STRIP)


if __name__ == '__main__':
    WarpGrid.run()
