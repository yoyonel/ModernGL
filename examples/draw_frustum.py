import os

import moderngl
import numpy as np
from objloader import Obj
from PIL import Image
from pyrr import Matrix44

from example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class DrawFrustumExample(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;

                in vec3 in_vert;
                
                void main() {
                    gl_Position = Mvp * vec4(in_vert, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                out vec4 f_color;

                void main() {
                    f_color = vec4(vec3(1), 1.0);
                }
            ''',
        )

        self.mvp = self.prog['Mvp']

        obj = Obj.open(local('data', 'crate.obj'))

        self.vbo = self.ctx.buffer(obj.pack('vx vy vz'))
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')

    def render(self):
        angle = self.wnd.time
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(0.0, 0.0, 0.0)
        self.ctx.enable(moderngl.DEPTH_TEST)
        self.ctx.wireframe = True

        ###############################################################################################################
        # View Camera Matrices
        ###############################################################################################################
        camera_pos = (np.cos(angle) * 5.0, np.sin(angle) * 5.0, 2.0)
        proj = Matrix44.perspective_projection(45.0, self.wnd.ratio, 0.1, 1000.0)
        lookat = Matrix44.look_at(
            camera_pos,
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0),
        )
        ###############################################################################################################

        ###############################################################################################################
        # Frustum Matrices (Camera Light (for example))
        ###############################################################################################################
        # Map vertices to centered unit cube [-0.5, -0.5, 0.0]x[+0.5, +0.5, 1.0] -> [-1, -1, -1]x[+1, +1, +1]
        mv_frustum = Matrix44.from_translation((0, 0, -1)) * Matrix44.from_scale((2, 2, 2))
        pos_frustum = (0, -1, 0)
        target_frustum = (0.0, 1.0, 0.0)
        lookat_frustum = Matrix44.look_at(pos_frustum, target_frustum, (0.0, 0.0, 1.0))
        proj_frustum = Matrix44.perspective_projection(60.0, self.wnd.ratio, 1.0, 10.0)
        mvp_frustum = proj_frustum * lookat_frustum * mv_frustum
        inv_mvp_frustrum = mvp_frustum.inverse

        self.mvp.write((proj * lookat * inv_mvp_frustrum).astype('f4').tobytes())
        self.vao.render()


run_example(DrawFrustumExample)
