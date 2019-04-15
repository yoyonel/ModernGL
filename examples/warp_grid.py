"""

"""
try:
    import _pickle as pickle
except ImportError:
    import pickle
import logging
import moderngl
import numpy as np
import os
from PIL import Image
#
from window import Example, run_example

logger = logging.getLogger(__name__)


def local(*path):
    """

    :param path:
    :return:
    """
    return os.path.join(os.path.dirname(__file__), *path)


def terrain(size: tuple):
    xv, yv = np.mgrid[0:size[0], 0:size[1]][::-1]
    xv = xv / (size[1] - 1)
    yv = yv / (size[0] - 1)
    vertices = np.dstack((xv, yv))

    temp = np.dstack([np.arange(0, size[0] * size[1] - size[1]),
                      np.arange(size[1], size[0] * size[1])])
    index = np.pad(temp.reshape(size[0] - 1, 2 * size[1]), [[0, 0], [0, 1]],
                   'constant', constant_values=-1)
    return vertices, index


class WarpGridTex3D(Example):
    title = "Warp Grid with 3D Texture"
    gl_version = (3, 3)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.prog_render_tex3d = self.ctx.program(
            vertex_shader='''
                        #version 330

                        uniform float time;

                        in vec2 in_vert;
                        out vec3 v_text;

                        void main() {
                            v_text = vec3(in_vert, time);
                            gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                        }
                    ''',
            fragment_shader='''
                        #version 330

                        uniform sampler3D tex_grid;

                        in vec3 v_text;
                        out vec4 f_color;

                        void main() {
                            f_color = texture(tex_grid, v_text);
                        }
                    ''',
        )

        try:
            self.prog_render_tex3d['time'].value = self.wnd.time
        except:
            pass

        self.prog_hm = self.ctx.program(
            vertex_shader='''
                        #version 330

                        uniform float time;

                        uniform sampler3D Heightmap;

                        in vec2 in_vert;

                        out vec2 v_text;

                        void main() {
                            vec2 pos_in_grid = in_vert.yx - 0.5;
                            v_text = texture(Heightmap, vec3(in_vert.xy, time)).xy;
                            
                            // y scrolling
                            v_text -= vec2(0, time)*8;
                            
                            gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                        }
                    ''',
            fragment_shader='''
                        #version 330

                        uniform sampler2D tex_cooling_map;

                        in vec2 v_text;

                        out vec4 f_color;

                        void main() {
                            f_color = vec4(texture(tex_cooling_map, v_text).r*10.0, 1, 1, 1);
                            //f_color = vec4(v_text, 0.0, 1.0);
                        }
                    ''',
        )

        self.render_final = self.ctx.program(
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
                            //f_color = vec4(vec3(texture(Texture, v_text).r), 1.0);
                            f_color = vec4(vec3(texture(Texture, v_text).rgb), 1.0);
                        }
                    ''',
        )

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')

        #######################################
        # [CPU side]
        #######################################
        vertices, index = terrain((13, 11))
        img = Image.open(local('data', 'fire_cooling_map.png')).transpose(
            Image.FLIP_TOP_BOTTOM)

        #######################################
        # [GPU side]
        #######################################
        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao_final_render = self.ctx.simple_vertex_array(self.render_final,
                                                             self.vbo,
                                                             'in_vert')
        self.final_render_size = np.array(img.size) * 1
        logger.debug(f'self.final_render_size: {self.final_render_size}')
        self.tex_final_render = self.ctx.texture(self.final_render_size, 1,
                                                 dtype='f1')
        self.tex_final_render.use(2)
        self.render_final['Texture'].value = 2
        self.fbo_final_render = self.ctx.framebuffer(self.tex_final_render)

        # For HeightMap GPU object:
        # Vertex Buffer Object
        self.vbo_hm = self.ctx.buffer(vertices.astype('f4').tobytes())
        # Index Buffer Object
        self.ibo_hm = self.ctx.buffer(index.astype('i4').tobytes())
        # -> Building Vertex Array Object (from Vertex Buffer Object)
        vao_content = [
            (self.vbo_hm, '2f', 'in_vert'),
        ]
        self.vao_hm = self.ctx.vertex_array(
            self.prog_hm, vao_content, self.ibo_hm)

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
        logger.debug(f"Nb warp grid loaded: {grids_array.shape[0]}")

        # https://moderngl.readthedocs.io/en/stable/reference/texture3d.html?highlight=write
        self.texture_grids = self.ctx.texture3d(
            (grids_array.shape[1], grids_array.shape[2], grids_array.shape[0]),
            components=grids_array.shape[3],
            data=grids_array.tobytes(),
            dtype='f4'
        )
        self.texture_grids.repeat_x = False
        self.texture_grids.repeat_y = False
        self.texture_grids.repeat_z = True
        self.texture_grids.filter = (moderngl.LINEAR, moderngl.LINEAR)
        self.texture_grids.use(0)
        self.prog_render_tex3d['tex_grid'].value = 0
        self.prog_hm['Heightmap'].value = 0

        self.texture_cooling_map = self.ctx.texture(img.size, 1, img.tobytes())
        self.texture_cooling_map.repeat_x = False
        self.texture_cooling_map.repeat_y = True
        self.texture_grids.filter = (moderngl.LINEAR, moderngl.LINEAR)
        self.texture_cooling_map.use(1)
        self.prog_hm['tex_cooling_map'].value = 1

    def render_grid(self):
        self.texture_grids.use(0)
        self.texture_cooling_map.use(1)
        self.vao_hm.render(moderngl.TRIANGLE_STRIP)

    def update_grid(self, dt: float = None):
        self.fbo_final_render.use()
        if dt is None:
            try:
                self.prog_hm[
                    'time'].value = self.wnd.time * 0.025  # 4 hz record
            except:
                pass
        else:
            try:
                self.prog_hm['time'].value = dt
            except:
                pass
        self.render_grid()

    def render(self, _time, frame_time):
        self.update_grid()

        self.ctx.screen.use()
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.disable(moderngl.DEPTH_TEST)
        self.ctx.wireframe = False
        self.tex_final_render.use(2)
        self.vao_final_render.render(moderngl.TRIANGLE_STRIP)


if __name__ == '__main__':
    run_example(WarpGridTex3D)
