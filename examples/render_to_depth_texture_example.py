import os

import moderngl
import numpy as np
from objloader import Obj
from PIL import Image
from pyrr import Matrix44

from examples.example_window import Example, run_example


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class RenderToTexture(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform mat4 Mvp;

                in vec3 in_vert;
                in vec3 in_norm;
                in vec2 in_text;

                out vec3 v_vert;
                out vec3 v_norm;
                out vec2 v_text;

                void main() {
                    gl_Position = Mvp * vec4(in_vert, 1.0);
                    v_vert = in_vert;
                    v_norm = in_norm;
                    v_text = in_text;
                }
            ''',
            fragment_shader='''
                #version 330

                uniform vec3 Light;
                uniform vec3 Color;
                uniform bool UseTexture;

                uniform sampler2D Texture;

                in vec3 v_vert;
                in vec3 v_norm;
                in vec2 v_text;

                out vec4 f_color;

                void main() {
                    float lum = clamp(dot(normalize(Light - v_vert), normalize(v_norm)), 0.0, 1.0) * 0.8 + 0.2;
                    if (UseTexture) {
                        vec4 tex_color = texture(Texture, v_text);
                        f_color = vec4(tex_color);
                    } else {
                        f_color = vec4(Color * lum, 1.0);
                    }
                }
            ''',
        )

        self.prog_for_depth = self.ctx.program(
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
                        uniform float z_near;
                        uniform float z_far;

                        in vec2 v_text;

                        out vec4 f_color;

                        void main() {
                            float depth = texture(Texture, v_text).r;
                            //float depth_linear = (2.0 * z_near) / (z_far + z_near - depth * (z_far - z_near));
                            float depth_linear = depth; 
                            f_color = vec4(vec3(depth_linear), 1.0);
                        }
                    ''',
        )

        self.mvp = self.prog['Mvp']
        self.light = self.prog['Light']
        self.color = self.prog['Color']
        self.use_texture = self.prog['UseTexture']

        # self.z_near = self.prog_for_depth['z_near']
        # self.z_far = self.prog_for_depth['z_far']

        self.objects = {}

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao_final_render = self.ctx.simple_vertex_array(self.prog_for_depth, self.vbo, 'in_vert')

        for name in ['ground', 'grass', 'billboard', 'billboard-holder', 'billboard-image']:
            obj = Obj.open(local('data', 'scene-1-%s.obj' % name))
            vbo = self.ctx.buffer(obj.pack('vx vy vz nx ny nz tx ty'))
            vao = self.ctx.simple_vertex_array(self.prog, vbo, "in_vert", "in_norm", "in_text")
            self.objects[name] = vao

        img = Image.open(local('data', 'infographic-1.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture1 = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture1.build_mipmaps()

        self.size_tex = (128, 128)
        # size = self.wnd.size
        self.texture2 = self.ctx.texture(self.size_tex, 3)
        self.texture_depth = self.ctx.depth_texture(self.size_tex)
        self.fbo = self.ctx.framebuffer(color_attachments=[self.texture2], depth_attachment=self.texture_depth)

        self.texture_depth.use(0)

        self.prog_for_depth['Texture'].value = 0

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        near_plane = 40.0
        far_plane = 60.0
        # self.prog_for_depth['z_near'].value = near_plane
        # self.prog_for_depth['z_far'].value = far_plane
        proj = Matrix44.perspective_projection(45.0, self.wnd.ratio, near_plane, far_plane)
        lookat = Matrix44.look_at(
            (47.697, -8.147, 24.498),
            (0.0, 0.0, 8.0),
            (0.0, 0.0, 1.0),
        )

        rotate = Matrix44.from_z_rotation(np.sin(self.wnd.time) * 0.5 + 0.2)

        for mode in ['render_to_texture', 'render_to_window']:
            if mode == 'render_to_texture':
                self.fbo.clear(1.0, 1.0, 1.0)
                self.fbo.use()
            else:
                self.ctx.screen.use()
                self.ctx.viewport = self.wnd.viewport

            self.use_texture.value = False

            self.light.value = (67.69, -8.14, 52.49)
            self.mvp.write((proj * lookat * rotate).astype('f4').tobytes())

            self.color.value = (0.67, 0.49, 0.29)
            self.objects['ground'].render()

            self.color.value = (0.46, 0.67, 0.29)
            self.objects['grass'].render()

            self.color.value = (1.0, 1.0, 1.0)
            self.objects['billboard'].render()

            self.color.value = (0.2, 0.2, 0.2)
            self.objects['billboard-holder'].render()

            self.use_texture.value = True

            if mode == 'render_to_texture':
                self.texture1.use()
            else:
                self.texture2.use(0)

            self.objects['billboard-image'].render()

        # show the result on 'screen' (main context)
        self.ctx.screen.use()
        self.ctx.viewport = (0, 0, self.wnd.viewport[2] // 4, self.wnd.viewport[3] // 4)
        # np_texture_depth = np.frombuffer(self.texture_depth.read(), dtype='f4').reshape(self.texture_depth.size)
        texture = self.ctx.texture(self.size_tex, 1, self.texture_depth.read(), dtype='f4')
        texture.use(0)
        # self.texture_depth.use(0)
        self.vao_final_render.render(moderngl.TRIANGLE_STRIP)


run_example(RenderToTexture)
