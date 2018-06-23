"""

"""
import logging
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


class Fire(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')

        self.prog = self.ctx.program(
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

        self.filter = self.ctx.program(
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

                        uniform sampler2D tex_ping;
                        uniform sampler2D tex_fire;
                        
                        uniform vec2 OffsetXY;
                        
                        uniform float time;

                        in vec2 v_text;
                        out vec4 f_color;
                        
                        // 2D Random
                        float random (in vec2 st) {
                            return fract(sin(dot(st.xy,
                                                 vec2(12.9898,78.233)))
                                         * 43758.5453123);
                        }
                        
                        // 2D Noise based on Morgan McGuire @morgan3d
                        // https://www.shadertoy.com/view/4dS3Wd
                        float noise (in vec2 st) {
                            vec2 i = floor(st);
                            vec2 f = fract(st);
                        
                            // Four corners in 2D of a tile
                            float a = random(i);
                            float b = random(i + vec2(1.0, 0.0));
                            float c = random(i + vec2(0.0, 1.0));
                            float d = random(i + vec2(1.0, 1.0));
                        
                            // Smooth Interpolation
                        
                            // Cubic Hermine Curve.  Same as SmoothStep()
                            vec2 u = f*f*(3.0-2.0*f);
                            // u = smoothstep(0.,1.,f);
                        
                            // Mix 4 coorners percentages
                            return mix(a, b, u.x) +
                                    (c - a)* u.y * (1.0 - u.x) +
                                    (d - b) * u.x * u.y;
                        }

                        void main() {
                            vec3 c1 = texture(tex_ping, v_text + vec2(0, -1*OffsetXY.y)).rgb;
                            vec3 c2 = texture(tex_ping, v_text + vec2(0, -2*OffsetXY.y)).rgb;
                            vec3 c3 = texture(tex_ping, v_text + vec2(+1*OffsetXY.x, -1*OffsetXY.y)).rgb;
                            vec3 c4 = texture(tex_ping, v_text + vec2(-1*OffsetXY.x, -1*OffsetXY.y)).rgb;
                            
                            vec3 newC = (c1 + c2 + c3 + c4) * 0.250;
                            
                            float n = clamp(pow(noise((v_text + vec2(0, -time)) * 10.00), 3.0), 0.0, 1.0);
                            vec3 fire = texture(tex_fire, v_text).rgb * 1;
                            
                            newC -= vec3(n)*0.25;
                            
                            f_color = vec4(newC, 1.0) + vec4(fire, 1.0);
                        }
                    ''',
        )

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')
        self.vao2 = self.ctx.simple_vertex_array(self.filter, self.vbo, 'in_vert')

        img = Image.open(local('data', 'fire.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture_img = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture_img.build_mipmaps()

        try:
            self.filter['OffsetXY'].value = (1.0 / img.size[0], 1.0 / img.size[1])
        except KeyError:
            logger.warning("", exc_info=True)

        self.textures = [
            self.ctx.texture(self.wnd.size, 3, dtype='f1')
            for _ in range(2)
        ]

        try:
            self.filter['tex_ping'].value = 0
            self.filter['tex_fire'].value = 1
        except:
            logger.warning("", exc_info=True)

        self.fbos = [
            self.ctx.framebuffer(tex)
            for tex in self.textures
        ]

        self.id_buffer = 0

        fbo_ping = self.fbos[self.id_buffer]
        fbo_ping.use()
        self.texture_img.use()
        self.vao.render(moderngl.TRIANGLE_STRIP)

        self.time = 0
        self.prev_time = time.time()

    def render(self):
        self.ctx.screen.use()
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)

        try:
            self.filter['time'].value = self.time
        except:
            pass

        fbo_pong = self.fbos[1 - self.id_buffer]
        #
        tex_pong = self.textures[1 - self.id_buffer]
        tex_ping = self.textures[self.id_buffer]

        fbo_pong.use()
        tex_ping.use(0)
        self.texture_img.use(1)
        self.vao2.render(moderngl.TRIANGLE_STRIP)

        self.ctx.screen.use()
        tex_pong.use()
        self.vao.render(moderngl.TRIANGLE_STRIP)

        self.id_buffer = 1 - self.id_buffer

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.time += dt
        self.prev_time = cur_time


logging.basicConfig(
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        level=logging.DEBUG
    )
run_example(Fire)
