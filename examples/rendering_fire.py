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
                uniform sampler2D tex_fire_colors;

                in vec2 v_text;
                out vec4 f_color;

                void main() {
                    float fire = texture(Texture, v_text).r;
                    f_color = texture(tex_fire_colors, vec2(fire, 1));
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
                        uniform sampler2D tex_cooling_map;
                        
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
                            vec3 c1 = texture(tex_ping, v_text + vec2(0, -0.5*OffsetXY.y)).rgb;
                            vec3 c2 = texture(tex_ping, v_text + vec2(0, -1.5*OffsetXY.y)).rgb;
                            vec3 c3 = texture(tex_ping, v_text + vec2(+0.5*OffsetXY.x, -0.5*OffsetXY.y)).rgb;
                            vec3 c4 = texture(tex_ping, v_text + vec2(-0.5*OffsetXY.x, -1.5*OffsetXY.y)).rgb;
                            
                            vec3 newC = (c1 + c2 + c3 + c4) * 0.250;

                            vec2 v_text_scolled = v_text + vec2(cos(time)*0.1, -time);
                            
                            float final_noise = 0.0;
                            
                            float noise_rand = (
                                random(v_text_scolled + vec2(-1*OffsetXY.x, 0*OffsetXY.y)) +
                                random(v_text_scolled + vec2(+1*OffsetXY.x, 0*OffsetXY.y)) + 
                                random(v_text_scolled + vec2(0*OffsetXY.x, -1*OffsetXY.y)) + 
                                random(v_text_scolled + vec2(0*OffsetXY.x, +1*OffsetXY.y))
                            ) * 0.25;
                            //float noise_perlin = pow(noise((v_text_scolled) * 10.00), 3.0);
                            //final_noise = noise_rand*0.025 + noise_perlin*0.0815;
                            //final_noise = noise_rand*0.015;
                            
                            float cooling_value = texture(tex_cooling_map, v_text_scolled).r;
                            cooling_value += final_noise;
                            
                            vec3 fire = texture(tex_fire, v_text).rgb * 1;
                            
                            newC -= vec3(cooling_value) * 3.0;
                            
                            newC += vec3(fire);                                                        
                            
                            f_color = clamp(vec4(newC, 1.0), 0, 1);
                        }
                    ''',
        )

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')
        self.vao2 = self.ctx.simple_vertex_array(self.filter, self.vbo, 'in_vert')

        img = Image.open(local('data', 'fire_colors.png')).transpose(Image.FLIP_TOP_BOTTOM)
        self.texture_fire_colors = self.ctx.texture(img.size, 3, img.tobytes())

        img = Image.open(local('data', 'fire.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture_img = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture_img.build_mipmaps()

        img = Image.open(local('data', 'fire_cooling_map.png')).transpose(Image.FLIP_TOP_BOTTOM)
        self.texture_cooling_map = self.ctx.texture(img.size, 1, img.tobytes())

        FireRed = (
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4,
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4,
            0 * 4, 0 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4,
            2 * 4, 3 * 4, 3 * 4, 3 * 4, 3 * 4, 4 * 4, 4 * 4, 4 * 4, 4 * 4, 5 * 4, 5 * 4, 5 * 4, 6 * 4,
            6 * 4, 6 * 4, 7 * 4, 7 * 4, 8 * 4, 8 * 4, 8 * 4, 9 * 4, 9 * 4, 10 * 4, 10 * 4, 11 * 4,
            11 * 4, 12 * 4, 12 * 4, 13 * 4, 13 * 4, 14 * 4, 14 * 4, 15 * 4, 15 * 4, 16 * 4, 17 * 4, 17 * 4,
            18 * 4, 18 * 4, 19 * 4, 20 * 4, 20 * 4, 21 * 4, 22 * 4, 22 * 4, 23 * 4, 23 * 4, 24 * 4, 25 * 4,
            25 * 4, 26 * 4, 27 * 4, 27 * 4, 28 * 4, 29 * 4, 30 * 4, 30 * 4, 31 * 4, 32 * 4, 32 * 4, 33 * 4,
            34 * 4, 34 * 4, 35 * 4, 36 * 4, 36 * 4, 37 * 4, 38 * 4, 38 * 4, 39 * 4, 40 * 4, 40 * 4, 41 * 4,
            41 * 4, 42 * 4, 43 * 4, 43 * 4, 44 * 4, 44 * 4, 45 * 4, 46 * 4, 46 * 4, 47 * 4, 47 * 4, 48 * 4,
            48 * 4, 49 * 4, 49 * 4, 50 * 4,
            50 * 4, 51 * 4, 51 * 4, 52 * 4, 52 * 4, 52 * 4, 53 * 4, 53 * 4, 54 * 4, 54 * 4, 54 * 4, 55 * 4,
            55 * 4, 55 * 4, 56 * 4, 56 * 4, 56 * 4, 57 * 4, 57 * 4, 57 * 4, 57 * 4, 58 * 4, 58 * 4, 58 * 4,
            58 * 4, 59 * 4, 59 * 4, 59 * 4, 59 * 4, 59 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4,
            60 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 61 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4, 62 * 4,
            62 * 4, 62 * 4, 62 * 4, 62 * 4
        )

        FireGreen = (
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4,
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4,
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4,
            0 * 4, 0 * 4, 0 * 4, 0 * 4, 0 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4, 1 * 4,
            1 * 4, 1 * 4, 1 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4, 2 * 4,
            3 * 4, 3 * 4, 3 * 4, 3 * 4, 3 * 4, 3 * 4, 4 * 4, 4 * 4, 4 * 4, 4 * 4, 4 * 4, 4 * 4, 5 * 4,
            5 * 4, 5 * 4, 5 * 4, 5 * 4, 6 * 4, 6 * 4, 6 * 4, 6 * 4, 7 * 4, 7 * 4, 7 * 4, 7 * 4, 8 * 4,
            8 * 4, 8 * 4, 8 * 4, 9 * 4, 9 * 4, 9 * 4, 9 * 4, 10 * 4, 10 * 4, 10 * 4, 11 * 4, 11 * 4,
            11 * 4, 12 * 4, 12 * 4, 12 * 4, 13 * 4, 13 * 4, 13 * 4, 14 * 4, 14 * 4, 14 * 4, 15 * 4,
            15 * 4, 15 * 4, 16 * 4, 16 * 4, 16 * 4, 17 * 4, 17 * 4, 18 * 4, 18 * 4, 18 * 4, 19 * 4,
            19 * 4, 19 * 4, 20 * 4, 20 * 4,
            21 * 4, 21 * 4, 21 * 4, 22 * 4, 22 * 4, 23 * 4, 23 * 4, 23 * 4, 24 * 4, 24 * 4, 25 * 4,
            25 * 4, 26 * 4, 26 * 4, 26 * 4, 27 * 4, 27 * 4, 28 * 4, 28 * 4, 29 * 4, 29 * 4, 29 * 4,
            30 * 4, 30 * 4, 31 * 4, 31 * 4, 32 * 4, 32 * 4, 32 * 4, 33 * 4, 33 * 4, 34 * 4, 34 * 4,
            35 * 4, 35 * 4, 35 * 4, 36 * 4, 36 * 4, 37 * 4, 37 * 4, 37 * 4, 38 * 4, 38 * 4, 39 * 4,
            39 * 4, 40 * 4, 40 * 4, 40 * 4, 41 * 4, 41 * 4, 42 * 4, 42 * 4, 42 * 4, 43 * 4, 43 * 4,
            43 * 4, 44 * 4, 44 * 4, 45 * 4, 45 * 4, 45 * 4, 46 * 4, 46 * 4, 46 * 4,
            47 * 4, 47 * 4, 47 * 4, 48 * 4, 48 * 4, 48 * 4, 49 * 4, 49 * 4, 49 * 4, 50 * 4, 50 * 4,
            50 * 4, 50 * 4, 51 * 4, 51 * 4, 51 * 4, 52 * 4, 52 * 4, 52 * 4, 52 * 4, 53 * 4, 53 * 4,
            53 * 4, 53 * 4, 54 * 4, 54 * 4, 54 * 4, 54 * 4, 55 * 4, 55 * 4, 55 * 4, 55 * 4, 55 * 4,
            56 * 4, 56 * 4, 56 * 4, 56 * 4, 56 * 4, 57 * 4, 57 * 4, 57 * 4, 57 * 4, 57 * 4, 57 * 4,
            58 * 4, 58 * 4, 58 * 4, 58 * 4, 58 * 4, 58 * 4, 59 * 4, 59 * 4, 59 * 4, 59 * 4, 59 * 4,
            59 * 4, 59 * 4, 59 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4, 60 * 4
        )

        FireBlue = (
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8,
            0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 0 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8,
            1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8,
            1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 1 * 8, 2 * 8, 2 * 8,
            2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8,
            2 * 8, 2 * 8, 2 * 8, 2 * 8, 2 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8,
            3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 3 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8,
            4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 4 * 8, 5 * 8, 5 * 8,
            5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 5 * 8, 6 * 8, 6 * 8, 6 * 8,
            6 * 8, 6 * 8, 6 * 8, 6 * 8, 6 * 8, 6 * 8, 6 * 8, 6 * 8, 6 * 8, 7 * 8, 7 * 8, 7 * 8, 7 * 8,
            7 * 8, 7 * 8, 7 * 8, 7 * 8, 7 * 8, 7 * 8, 8 * 8, 8 * 8, 8 * 8, 8 * 8, 8 * 8, 8 * 8, 8 * 8,
            8 * 8, 8 * 8, 8 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 9 * 8, 10 * 8,
            10 * 8, 10 * 8, 10 * 8, 10 * 8, 10 * 8, 10 * 8, 10 * 8, 11 * 8, 11 * 8, 11 * 8, 11 * 8,
            11 * 8
        )

        FireColors = list(zip(FireRed, FireGreen, FireBlue))
        img_fire_colors = Image.new('RGB', (len(FireColors), 1))
        img_fire_colors.putdata(FireColors)
        self.texture_fire_colors = self.ctx.texture(img_fire_colors.size, 3, img_fire_colors.tobytes())
        self.texture_fire_colors.repeat_x = False
        self.texture_fire_colors.repeat_y = False

        try:
            self.filter['OffsetXY'].value = (1.0 / img.size[0], 1.0 / img.size[1])
        except KeyError:
            logger.warning("", exc_info=True)

        fire_size = self.wnd.size

        # Ping Pong Buffers
        self.textures = [
            self.ctx.texture(fire_size, 1, dtype='f1')
            for _ in range(2)
        ]
        # Textures (attach to ping-pong frame buffer object) attributes
        for tex in self.textures:
            tex.filter = (moderngl.LINEAR, moderngl.LINEAR)
            tex.repeat_x = False
            tex.repeat_y = False

        try:
            self.filter['tex_ping'].value = 0
            self.filter['tex_fire'].value = 1
            self.filter['tex_cooling_map'].value = 2
        except:
            logger.warning("", exc_info=True)

        try:
            self.prog['Texture'].value = 0
            self.prog['tex_fire_colors'].value = 1
        except:
            logger.warning("", exc_info=True)

        # Init Frame Buffer Object from textures attachment
        self.fbos = [
            self.ctx.framebuffer(tex)
            for tex in self.textures
        ]

        self.id_buffer = 0
        id_buffer_ping = self.id_buffer
        id_buffer_pong = 1 - id_buffer_ping

        fbo_pong = self.fbos[id_buffer_pong]
        fbo_pong.use()
        fbo_pong.clear(0.0, 0.0, 0.0)

        fbo_ping = self.fbos[id_buffer_ping]
        fbo_ping.use()
        fbo_ping.clear(0.0, 0.0, 0.0)
        self.texture_img.use()
        self.vao.render(moderngl.TRIANGLE_STRIP)

        self.time = 0
        self.prev_time = time.time()

    def render(self):
        try:
            self.filter['time'].value = self.time
        except:
            pass

        fbo_pong = self.fbos[1 - self.id_buffer]
        #
        tex_pong = self.textures[1 - self.id_buffer]
        tex_ping = self.textures[self.id_buffer]

        fbo_pong.use()
        # set textures for shader
        tex_ping.use(0)
        self.texture_img.use(1)
        self.texture_cooling_map.use(2)
        self.texture_fire_colors.use(3)
        # render full screen quad
        self.vao2.render(moderngl.TRIANGLE_STRIP)

        # Ping Pong swap (ids) buffers
        self.id_buffer = 1 - self.id_buffer

        self.ctx.screen.use()
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)
        tex_pong.use(0)
        self.texture_fire_colors.use(1)
        self.vao.render(moderngl.TRIANGLE_STRIP)

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.time += dt
        self.prev_time = cur_time


logging.basicConfig(
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    level=logging.DEBUG
)
run_example(Fire)
