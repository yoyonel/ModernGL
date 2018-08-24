"""

"""
import logging
from math import sin
import moderngl
import numpy as np
import os
from PIL import Image
import time
#

from examples.example_window import Example, run_example

logger = logging.getLogger(__name__)


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class Blur(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')

        self.render_tex = self.ctx.program(
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
                            f_color = texture(Texture, v_text);
                        }
                    ''',
        )

        self.filter_blur13 = self.ctx.program(
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
                                uniform vec2 inv_Resolution;
                                uniform vec2 Direction;

                                in vec2 v_text;

                                out vec4 f_color;

                                vec4 blur13(sampler2D image, vec2 uv, vec2 inv_resolution, vec2 direction) {
                                    vec4 color = vec4(0.0);
                                    vec2 off1 = vec2(1.411764705882353) * direction;
                                    vec2 off2 = vec2(3.2941176470588234) * direction;
                                    vec2 off3 = vec2(5.176470588235294) * direction;
                                    color += texture2D(image, uv) * 0.1964825501511404;
                                    color += texture2D(image, uv + (off1 * inv_resolution)) * 0.2969069646728344;
                                    color += texture2D(image, uv - (off1 * inv_resolution)) * 0.2969069646728344;
                                    color += texture2D(image, uv + (off2 * inv_resolution)) * 0.09447039785044732;
                                    color += texture2D(image, uv - (off2 * inv_resolution)) * 0.09447039785044732;
                                    color += texture2D(image, uv + (off3 * inv_resolution)) * 0.010381362401148057;
                                    color += texture2D(image, uv - (off3 * inv_resolution)) * 0.010381362401148057;
                                    return color;
                                }

                                void main() {
                                    f_color = blur13(Texture, v_text, inv_Resolution, Direction);
                                }
                            '''
        )
        self.prog_filtering_blur = self.ctx.program(
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
                            uniform vec2 inv_Resolution;
                            uniform vec2 Direction;

                            uniform float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
                            uniform float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

                            in vec2 v_text;
                            out vec4 f_color;

                            vec4 filtering(sampler2D image, vec2 uv, vec2 inv_resolution, vec2 direction) {
                                vec2 off1 = vec2(offset[1]) * direction;
                                vec2 off2 = vec2(offset[2]) * direction;
                                vec4 color = texture2D(image, uv) * weight[0];
                                for(int i=1; i<3; i++) {
                                    color += texture2D(image, uv + (vec2(offset[i]) * direction * inv_resolution)) * weight[i];
                                    color += texture2D(image, uv - (vec2(offset[i]) * direction * inv_resolution)) * weight[i];
                                }
                                return color;
                            }

                            void main(void)
                            {

                                f_color = filtering(Texture, v_text, inv_Resolution, Direction);
                            }
                    '''
        )
        self.vbo = self.ctx.buffer(canvas.tobytes())
        #
        self.vao_render_texture = self.ctx.simple_vertex_array(self.render_tex, self.vbo, 'in_vert')
        # self.prog_cur_filter = self.filter_blur13
        self.prog_cur_filter = self.prog_filtering_blur
        self.vao_blur13 = self.ctx.simple_vertex_array(self.prog_cur_filter, self.vbo, 'in_vert')

        img = Image.open(local('data', 'panda.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture_panda = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture_panda.filter = (moderngl.LINEAR, moderngl.LINEAR)
        self.texture_panda.repeat_x = False
        self.texture_panda.repeat_y = False
        self.texture_panda.build_mipmaps()

        # Ping Pong Buffers
        self.tex_for_blurs = [
            self.ctx.texture(img.size, 3, dtype='f1')
            for _ in range(2)
        ]
        # Textures (attach to ping-pong frame buffer object) attributes
        for tex in self.tex_for_blurs:
            tex.filter = (moderngl.LINEAR, moderngl.LINEAR)
            tex.repeat_x = False
            tex.repeat_y = False

        try:
            self.prog_cur_filter['Texture'].value = 0
            self.prog_cur_filter['inv_Resolution'].value = (1./img.size[0], 1./img.size[1])
        except:
            logger.warning("", exc_info=True)

        # Init Frame Buffer Object from textures attachment
        self.fbos_blur = [
            self.ctx.framebuffer([tex])
            for tex in self.tex_for_blurs
        ]

        fbo_vertical = self.fbos_blur[0]
        fbo_vertical.use()
        fbo_vertical.clear(0.0, 0.0, 0.0)

        fbo_horizontal = self.fbos_blur[1]
        fbo_horizontal.use()
        fbo_horizontal.clear(0.0, 0.0, 0.0)
        self.texture_panda.use()
        self.vao_render_texture.render(moderngl.TRIANGLE_STRIP)

        self.cur_time = 0
        self.prev_time = time.time()

    def render_blur(self, tex_in, radius=1):
        """

        :param radius:
        :return:
        """
        # first pass
        fbo_blur_vertical = self.fbos_blur[0]
        tex_vertical = self.tex_for_blurs[0]
        fbo_blur_vertical.use()
        # set in texture for first pass
        tex_in.use(0)
        try:
            self.prog_cur_filter['Direction'].value = (0, radius)
        except:
            pass
        #
        self.vao_blur13.render(moderngl.TRIANGLE_STRIP)

        # second pass
        fbo_blur_horizontal = self.fbos_blur[1]
        fbo_blur_horizontal.use()
        tex_vertical.use(0)
        #
        try:
            self.prog_cur_filter['Direction'].value = (radius, 0)
        except:
            pass
        #
        self.vao_blur13.render(moderngl.TRIANGLE_STRIP)

        # return result of the second pass
        return self.tex_for_blurs[1]

    def one_shot_blur(self, radius):
        nb_iteration = 8
        #
        first_blur = self.render_blur(tex_in=self.texture_panda, radius=radius)
        final_blur = first_blur
        for _ in range(nb_iteration - 1):
            final_blur = self.render_blur(tex_in=final_blur, radius=radius)
        return final_blur

    def continuous_blur(self, radius):
        #
        return self.render_blur(tex_in=self.tex_for_blurs[1], radius=radius)

    def render(self):
        # OpenGL Timer Query
        q_for_timer = self.ctx.query(time=True)
        with q_for_timer:
            radius = abs(sin(self.cur_time * 0.5) * 16.0)
            # radius = 3.0
            # print(f"radius: {radius}")

            final_blur = self.one_shot_blur(radius)
            # final_blur = self.continuous_blur(radius)

            self.ctx.screen.use()
            self.ctx.viewport = self.wnd.viewport
            self.ctx.clear(1.0, 1.0, 1.0)
            final_blur.use(0)
            self.vao_render_texture.render(moderngl.TRIANGLE_STRIP)
        logger.info(f"Query on time elapsed (GPU side): {q_for_timer.elapsed/1000000.0} ms")

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.cur_time += dt
        self.prev_time = cur_time

        # logger.info(f"fps={1.0/dt}")


if __name__ == '__main__':
    logging.basicConfig(
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        level=logging.DEBUG
    )
    run_example(Blur)
