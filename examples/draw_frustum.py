"""

"""
import moderngl
import numpy as np
from objloader import Obj
import os
from pyrr import Matrix44

from examples.example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class DrawFrustumExample(Example):
    def __init__(self, ctx=None):
        if ctx is None:
            self.ctx = moderngl.create_context()
        else:
            self.ctx = ctx

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

                uniform vec4 Color;
                
                out vec4 f_color;

                void main() {
                    f_color = Color;
                }
            ''',
        )

        self.mvp = self.prog['Mvp']
        self.color = self.prog['Color']

        obj = Obj.open(local('data', 'crate.obj'))

        self.vbo = self.ctx.buffer(obj.pack('vx vy vz'))
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')

        # Map vertices to centered unit cube [-0.5, -0.5, 0.0]x[+0.5, +0.5, 1.0] -> [-1, -1, -1]x[+1, +1, +1]
        self.mv_frustum = Matrix44.from_translation((0, 0, -1)) * Matrix44.from_scale((2, 2, 2))

    def _render_frustum(self, mvp_cam, inv_mvp_frustrum, color=(0.0, 1.0, 0.0, 1.0)):
        """

        :param mvp_cam:
        :param inv_mvp_frustrum:
        :param color:
        :return:
        """
        self.color.value = color
        self.mvp.write((mvp_cam * inv_mvp_frustrum).astype('f4').tobytes())
        self.vao.render()

    def render_frustum(
            self,
            mvp_cam,
            inv_mvp_frustrum,
            draw_edges=True,
            draw_faces=True,
            color_edges=(1.0, 0.0, 0.0, 1.0),
            color_faces=(0.10, 0.0, 0.75, 0.1),
    ):
        """

        :param mvp_cam:
        :param inv_mvp_frustrum:
        :param draw_edges:
        :param draw_faces:
        :param color_edges:
        :param color_faces:
        :return:
        """
        mv_frustum = inv_mvp_frustrum * self.mv_frustum

        if draw_edges:
            self.ctx.wireframe = True
            self._render_frustum(mvp_cam, mv_frustum, color_edges)
            self.ctx.wireframe = False

        if draw_faces:
            self.ctx.wireframe = False
            self.ctx.enable(moderngl.BLEND)
            # set depthMask to False
            self._render_frustum(mvp_cam, mv_frustum, color_faces)
            self.ctx.disable(moderngl.BLEND)
            # restore depthMask to True

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
        proj_cam = Matrix44.perspective_projection(45.0, self.wnd.ratio, 0.1, 1000.0)
        lookat_cam = Matrix44.look_at(
            camera_pos,
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0),
        )
        mvp_cam = proj_cam * lookat_cam
        ###############################################################################################################

        ###############################################################################################################
        # Frustum Matrices (Camera Light (for example))
        ###############################################################################################################
        pos_frustum = (0, -1, 0)
        target_frustum = (0.0, 1.0, 0.0)
        lookat_frustum = Matrix44.look_at(pos_frustum, target_frustum, (0.0, 0.0, 1.0))
        proj_frustum = Matrix44.perspective_projection(60.0, self.wnd.ratio, 1.0, 10.0)
        mvp_frustum = proj_frustum * lookat_frustum * self.mv_frustum
        inv_mvp_frustrum = mvp_frustum.inverse

        self.render_frustum(mvp_cam, inv_mvp_frustrum)


if __name__ == '__main__':
    run_example(DrawFrustumExample)
