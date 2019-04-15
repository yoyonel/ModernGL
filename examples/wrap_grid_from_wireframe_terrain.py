import os
import pickle

import moderngl
import numpy as np
from PIL import Image
from pyrr import Matrix44

import data
from warp_grid import local
from window import Example, run_example


def terrain(size):
    vertices = np.dstack(np.mgrid[0:size, 0:size][::-1]) / size
    temp = np.dstack(
        [np.arange(0, size * size - size), np.arange(size, size * size)])
    index = np.pad(temp.reshape(size - 1, 2 * size), [[0, 0], [0, 1]],
                   'constant', constant_values=-1)
    return vertices, index


class WarpGrid_From_WireframeTerrain(Example):
    title = "Warp Grid from Wireframe Terrain"
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.prog = self.ctx.program(
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
                    v_text -= vec2(0, time)*8;
                }
            ''',
            fragment_shader='''
                #version 330

                in vec3 v_color;
                in vec2 v_text;
                out vec4 f_color;

                uniform sampler2D Texture;

                void main() {
                    f_color = texture(Texture, v_text) * 4;
                }
            ''',
        )

        self.mvp = self.prog['Mvp']

        vertices, index = terrain(16)

        self.vbo = self.ctx.buffer(vertices.astype('f4').tobytes())
        self.ibo = self.ctx.buffer(index.astype('i4').tobytes())

        vao_content = [
            (self.vbo, '2f', 'in_vert'),
        ]

        self.vao = self.ctx.vertex_array(self.prog, vao_content, self.ibo)

        def _init_texture():
            img = Image.open(data.find('noise.jpg')).convert('L')
            texture = self.ctx.texture(img.size, 1, img.tobytes())
            texture.use()

        def _init_texture_3d():
            # Load datas (precomputed) from Pymunk warp grid simulation
            # https://stackoverflow.com/questions/17623523/can-i-stream-a-python-pickle-list-tuple-or-other-iterable-data-type
            grids_array = []
            #
            grid_size_x = 11
            grid_size_y = 13
            grid_size_cell = 32
            #
            with open(local('data',
                            f'warp#4hz#{grid_size_x}#{grid_size_y}#{grid_size_cell}.pkl'),
                      'rb') as fp:
                try:
                    while True:
                        grid_array = np.array(pickle.load(fp), dtype='f4')
                        grid_array /= np.array(
                            [grid_size_x, grid_size_y]) * grid_size_cell
                        # https://docs.scipy.org/doc/numpy/reference/generated/numpy.reshape.html
                        grid_array = grid_array.reshape(
                            (grid_size_x, grid_size_y, grid_array.shape[1]))
                        grids_array.append(grid_array)
                except EOFError:
                    pass
            grids_array = np.array(grids_array)

            # https://moderngl.readthedocs.io/en/stable/reference/texture3d.html?highlight=write
            self.texture_grids = self.ctx.texture3d(
                (grids_array.shape[1], grids_array.shape[2],
                 grids_array.shape[0]),
                components=grids_array.shape[3],
                data=grids_array.tobytes(),
                dtype='f4'
            )
            self.texture_grids.repeat_x = False
            self.texture_grids.repeat_y = False
            self.texture_grids.repeat_z = True
            self.texture_grids.filter = (moderngl.LINEAR, moderngl.LINEAR)
            self.texture_grids.use(0)
            self.prog['Heightmap'].value = 0

            img = Image.open(local('data', 'fire_cooling_map.png')).transpose(
                Image.FLIP_TOP_BOTTOM)
            # img = Image.open(data.find('noise.jpg')).convert('L')
            self.texture_cooling_map = self.ctx.texture(img.size, 1,
                                                        img.tobytes())
            self.texture_cooling_map.repeat_x = False
            self.texture_cooling_map.repeat_y = True
            self.texture_cooling_map.filter = (moderngl.LINEAR, moderngl.LINEAR)
            self.texture_cooling_map.use(1)
            self.prog['Texture'].value = 1

        # _init_texture()
        _init_texture_3d()

    def render(self, time, frame_time):
        self.prog['time'].value = time * 0.025  # 4 hz record

        angle = time * 0.2 * 0

        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)
        self.ctx.wireframe = False

        proj = Matrix44.perspective_projection(45.0, self.aspect_ratio, 0.1,
                                               1000.0)
        lookat = Matrix44.look_at(
            (np.cos(angle), np.sin(angle), 1.0),
            (0.5, 0.5, 0.0),
            (0.0, 0.0, 1.0),
        )

        self.mvp.write((proj * lookat).astype('f4').tobytes())
        self.vao.render(moderngl.TRIANGLE_STRIP)


if __name__ == '__main__':
    run_example(WarpGrid_From_WireframeTerrain)
