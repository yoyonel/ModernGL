import os
import struct

import moderngl
import numpy as np
import pymunk
from PIL import Image
from pymunk import Vec2d

from example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class PymunkExample(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform vec4 Camera;

                // Per vertex
                in vec2 in_vert;
                in vec2 in_texture;

                // Per instance
                in vec3 in_pos;
                in vec2 in_size;
                in vec4 in_tint;

                out vec2 v_vert;
                out vec2 v_texture;
                out vec4 v_tint;

                void main() {
                    mat2 rotate = mat2(
                        cos(in_pos.z), sin(in_pos.z),
                        -sin(in_pos.z), cos(in_pos.z)
                    );
                    v_vert = rotate * (in_vert * in_size) + in_pos.xy;
                    gl_Position = vec4((v_vert - Camera.xy) / Camera.zw, 0.0, 1.0);
                    v_texture = in_texture;
                    v_tint = in_tint;
                }
            ''',
            fragment_shader='''
                #version 330

                uniform sampler2D Texture;

                in vec2 v_vert;
                in vec2 v_texture;
                in vec4 v_tint;

                out vec4 f_color;

                void main() {
                    vec4 tex = texture(Texture, v_texture);
                    vec3 color = tex.rgb * (1.0 - v_tint.a) + v_tint.rgb * v_tint.a;
                    f_color = vec4(color, tex.a);
            }
            ''',
        )

        img = Image.open(local('data', 'crate.png')).convert('RGBA')
        self.tex1 = self.ctx.texture(img.size, 4, img.tobytes())
        self.tex1.use(0)

        img = Image.open(local('data', 'ball.png')).convert('RGBA')
        self.tex2 = self.ctx.texture(img.size, 4, img.tobytes())
        self.tex2.use(1)

        vertices = np.array([
            -1.0, -1.0, 0.0, 0.0,
            -1.0, 1.0, 0.0, 1.0,
            1.0, -1.0, 1.0, 0.0,
            1.0, 1.0, 1.0, 1.0,
        ])

        vbo1 = self.ctx.buffer(vertices.astype('f4').tobytes())

        self.vbo2 = self.ctx.buffer(reserve=1024 * 1024)

        vao_content = [
            (vbo1, '2f 2f', 'in_vert', 'in_texture'),
            (self.vbo2, '3f 2f 4f/i', 'in_pos', 'in_size', 'in_tint'),
        ]

        self.vao = self.ctx.vertex_array(self.prog, vao_content)

        self.space = pymunk.Space()
        self.space.gravity = (0.0, -900.0)

        shape = pymunk.Segment(self.space.static_body, (5, 100), (595, 100), 1.0)
        shape.friction = 1.0
        self.space.add(shape)

        self.bodies = []
        self.balls = []

        for x in range(5):
            for y in range(10):
                size = 20
                mass = 10.0
                moment = pymunk.moment_for_box(mass, (size, size))
                body = pymunk.Body(mass, moment)
                body.position = Vec2d(300 + x * 50, 105 + y * (size + 0.1))
                shape = pymunk.Poly.create_box(body, (size, size))
                shape.friction = 0.3
                self.space.add(body, shape)
                self.bodies.append(body)

    def shoot(self):
        mass = 100
        r = 15
        moment = pymunk.moment_for_circle(mass, 0, r, (0, 0))
        body = pymunk.Body(mass, moment)
        body.position = (0, 165)
        shape = pymunk.Circle(body, r, (0, 0))
        shape.friction = 0.3
        self.space.add(body, shape)
        f = 50000
        body.apply_impulse_at_local_point((f, 0), (0, 0))
        self.balls.append(body)

    def render(self):
        width, height = self.wnd.size
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.BLEND)

        if self.wnd.key_pressed(32):
            self.shoot()

        nb_sub_steps = 10
        for i in range(nb_sub_steps):
            self.space.step(1 / 60 / nb_sub_steps)

        self.prog['Camera'].value = (200, 300, width / 2, height / 2)

        bodies = np.array(
            [
                (b.position.x, b.position.y, b.angle, 10, 10, 1, 1, 1, 0)
                for b in self.bodies
            ], dtype='f4'
        )
        self.vbo2.write(bodies.tobytes())
        self.prog['Texture'].value = 0
        self.vao.render(moderngl.TRIANGLE_STRIP, instances=len(self.bodies))

        self.vbo2.orphan()

        balls = np.array(
            [
                (b.position.x, b.position.y, b.angle, 15, 15, 1, 1, 1, 0)
                for b in self.balls
            ],
            dtype='f4'
        )
        self.vbo2.write(balls.tobytes())
        self.prog['Texture'].value = 1
        self.vao.render(moderngl.TRIANGLE_STRIP, instances=len(self.balls))


run_example(PymunkExample)
