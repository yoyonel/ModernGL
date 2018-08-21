from itertools import chain
import os
import struct
from colorsys import hls_to_rgb as hls
from random import uniform

import moderngl
import numpy as np
from objloader import Obj
from pyrr import Matrix44

from example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


def random_color():
    return hls(uniform(0.0, 1.0), 0.5, 0.5)


cars = []
cars += [{'color': random_color(), 'pos': (1.5, i * 2.0 - 9.0, 0.0), 'angle': uniform(-0.5, 0.5)} for i in range(10)]
cars += [{'color': random_color(), 'pos': (-1.5, i * 2.0 - 9.0, 0.0), 'angle': uniform(-0.5, 0.5)} for i in range(10)]


class ToyCars(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;

                in vec3 in_vert;
                in vec3 in_norm;

                in vec3 in_color;
                in vec3 in_origin;
                in mat4 in_basis;

                out vec3 v_vert;
                out vec3 v_norm;
                out vec3 v_color;

                void main() {
                    v_vert = in_origin + vec3(in_basis * vec4(in_vert, 1));
                    v_norm = vec3(in_basis * vec4(in_norm, 1));
                    v_color = in_color;
                    gl_Position = Mvp * vec4(v_vert, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                uniform vec3 Light;
                uniform sampler2D Texture;

                in vec3 v_vert;
                in vec3 v_norm;
                in vec3 v_color;

                out vec4 f_color;

                void main() {
                    float lum = clamp(dot(normalize(Light - v_vert), normalize(v_norm)), 0.0, 1.0) * 0.8 + 0.2;
                    f_color = vec4(v_color * lum, 1.0);
                }
            ''',
        )

        self.mvp = self.prog['Mvp']
        self.light = self.prog['Light']

        obj = Obj.open(local('data', 'lowpoly_toy_car.obj'))

        self.vbo1 = self.ctx.buffer(obj.pack('vx vy vz nx ny nz'))
        self.vbo2 = self.ctx.buffer(struct.pack(
            '22f',
            1.0, 1.0, 1.0,
            0.0, 0.0, 0.0,
            # ModelView Matrix of car (identity => no transformation in local space object)
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        ) * len(cars))
        self.vao = self.ctx.vertex_array(self.prog, [
            (self.vbo1, '3f 3f', 'in_vert', 'in_norm'),
            (self.vbo2, '3f 3f 16f/i', 'in_color', 'in_origin', 'in_basis'),
        ])

    def render(self):
        angle = self.wnd.time
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        camera_pos = (np.cos(angle) * 20.0, np.sin(angle) * 20.0, 5.0)

        proj = Matrix44.perspective_projection(45.0, self.wnd.ratio, 0.1, 1000.0)
        lookat = Matrix44.look_at(
            camera_pos,
            (0.0, 0.0, 0.5),
            (0.0, 0.0, 1.0),
        )

        self.mvp.write((proj * lookat).astype('f4').tobytes())
        self.light.value = camera_pos

        # self.vbo2.write(Matrix33.from_z_rotation(self.wnd.time).astype('f4').tobytes(), offset=24)
        # Cars
        self.vbo2.write(b''.join(struct.pack(
            '22f',
            *car['color'],
            *car['pos'],
            # ModelView Matrix of car (identity => no transformation in local space object)
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0,
        ) for car in cars))
        self.vao.render(instances=len(cars))
        # Shadow
        # near_plane = 1.0
        # far_plane = 10.0
        # light_projection = Matrix44.orthogonal_projection(-10.0, 10.0, -10.0, 10.0, near_plane, far_plane)
        # light_view = Matrix44.look_at((0, -10, -1), (0, 0, 0), (0, 1, 0))
        # light_space_matrix = light_projection * light_view
        light_z_plane = 0
        self.vbo2.write(b''.join(struct.pack(
            '22f',
            0.0, 0.0, 0.0,
            *car['pos'],
            # Projection matrix (on plane - floor)
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.3, 0.6, 0.0, 0.0,
            0.0, 0.0, light_z_plane, 1.0,
            # *chain(*light_space_matrix.astype('f4').tolist()),
        ) for car in cars))
        self.vao.render(instances=len(cars))


run_example(ToyCars)
