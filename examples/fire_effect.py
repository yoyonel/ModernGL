"""

"""
import logging
import operator
import os
import time
from typing import _alias, T

import numpy as np
from PIL import Image

import moderngl
from particle_system_advanced import Particles
#
from warp_grid import WarpGrid
#
from window import Example, run_example

logger = logging.getLogger(__name__)


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


TCircularList = _alias(list, T, inst=False)


class CircularList(list):
    """
    https://stackoverflow.com/a/47606550
    """

    def __getitem__(self, x):
        if isinstance(x, slice):
            return [self[x] for x in self._rangeify(x)]

        index = operator.index(x)
        try:
            return super().__getitem__(index % len(self))
        except ZeroDivisionError:
            raise IndexError('list index out of range')

    def _rangeify(self, slice_):
        start, stop, step = slice_.start, slice_.stop, slice_.step
        if start is None:
            start = 0
        if stop is None:
            stop = len(self)
        if step is None:
            step = 1
        return range(start, stop, step)


class Fire(Example):
    gl_version = (3, 3)
    title = "Fire rendering"
    window_size = (512, 512)
    aspect_ratio = 1
    resizable = False

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

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

        self.render_final_fire = self.ctx.program(
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
                uniform sampler2D tex_lut;

                in vec2 v_text;
                out vec4 f_color;

                void main() {
                    float fire = texture(Texture, v_text).r;
                    f_color = texture(tex_lut, vec2(fire, 1));
                }
            ''',
        )

        self.update_frame = self.ctx.program(
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

                        uniform sampler2D tex_prev_frame;
                        uniform sampler2D tex_fire;
                        uniform sampler2D tex_cooling_map;
                        uniform sampler2D tex_warp_grid;

                        uniform vec2 OffsetXY;

                        uniform float time;

                        in vec2 v_text;
                        out vec4 f_color;

                        float PHI = 1.61803398874989484820459 * 00000.1; // Golden Ratio   
                        float PI  = 3.14159265358979323846264 * 00000.1; // PI
                        float SQ2 = 1.41421356237309504880169 * 10000.0; // Square Root of Two

                        // https://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl
                        float gold_noise(in vec2 coordinate, in float seed){
                            return fract(sin(dot(coordinate*(seed+PHI), vec2(PHI, PI)))*SQ2);
                        }

                        vec3 compute_filter_firemap(sampler2D t, vec2 v_t) {
                            // Vertical filtering + Up Scroll
                            vec3 c1 = texture(t, v_t + vec2(0, -0.500*OffsetXY.y)).rgb;
                            vec3 c3 = texture(t, v_t + vec2(0, -1.500*OffsetXY.y)).rgb;
                            vec3 c5 = texture(t, v_t + vec2(0, -2.500*OffsetXY.y)).rgb;
                            // (Light) Horizontal filtering
                            vec3 c6 = texture(t, v_t + vec2(+0.500*OffsetXY.x, 0)).rgb;
                            vec3 c7 = texture(t, v_t + vec2(-0.500*OffsetXY.x, 0)).rgb;
                            vec3 c8 = texture(t, v_t + vec2(+1.500*OffsetXY.x, 0)).rgb;
                            vec3 c9 = texture(t, v_t + vec2(-1.500*OffsetXY.x, 0)).rgb;

                            return (c1 + c3 + c5 + c6 + c7 + c8 + c9) * (1.0/7.0);
                        }

                        vec3 compute_cooling_with_warpgrid() {
                            vec2 v_text_scrolled = v_text;
                            v_text_scrolled += vec2(0.0, -time);
                            v_text_scrolled += vec2(cos(time)*0.5, 0.0);

                            float cooling_value = texture(tex_warp_grid, v_text_scrolled).r;
                            // https://khronos.org/opengl/wiki/Fragment_Shader#System_inputs
                            // https://khronos.org/registry/OpenGL-Refpages/gl4/html/gl_FragCoord.xhtml
                            float r = gold_noise(gl_FragCoord.xy, time) * 0.015;
                            return vec3(cooling_value) * 1.50 + vec3(r);
                        }
                        
                        void main() {                                                    
                            // Source fire
                            vec3 src_fire = texture(tex_fire, v_text).rgb;

                            // Filter (+ scroll) fire map
                            vec3 filter_fire = compute_filter_firemap(tex_prev_frame, v_text);                            

                            // Cooling map/attenuation
                            vec3 cooling = compute_cooling_with_warpgrid();

                            vec4 new_fire_color = vec4((src_fire + filter_fire) - cooling, 1.0); 

                            f_color = new_fire_color;
                        }
                    ''',
        )

        self.transform = self.ctx.program(
            vertex_shader='''
                    #version 330
                    #define M_PI 3.14159265358979323846

                    uniform vec2 Acc;
                    uniform float Time;

                    uniform sampler2D tex_fire;

                    in vec2 in_pos;
                    in float in_hot;
                    in vec2 in_vel;
                    in float in_id;

                    out vec2 out_pos;
                    out float out_hot;
                    out vec2 out_vel;
                    out float out_id;

                    float PHI = 1.61803398874989484820459 * 00000.1; // Golden Ratio   
                    float PI  = 3.14159265358979323846264 * 00000.1; // PI
                    float SQ2 = 1.41421356237309504880169 * 10000.0; // Square Root of Two

                    float gold_noise(in vec2 coordinate, in float seed){
                        return fract(sin(dot(coordinate*(seed+PHI), vec2(PHI, PI)))*SQ2);
                    }

                    float map(float value, float inMin, float inMax, float outMin, float outMax) {
                      return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
                    }

                    void respawn() {                        
                        float pos_x = gold_noise(vec2(in_id, Time), 0);
                        float pos_y = gold_noise(vec2(in_id, Time), 50);
                        
                        out_hot = map(gold_noise(vec2(in_id, Time), 25), 0.0, 1.0, 0.4, 1.0);
                        out_hot *= texture(tex_fire, vec2(pos_x, pos_y)).r;
                         
                        out_pos = vec2(
                            map(pos_x, 0, 1, -1, +1) * 1.0, 
                            map(pos_y, 0, 1, -1, +1) * 1.0
                        );                        

                        float r = gold_noise(vec2(in_id, Time), 100) * 0.015;
                        float vel_x =  map(gold_noise(vec2(in_id, Time), 105), 0, 1, -1, 1) * 0.005;
                        out_vel = vec2(vel_x, r);
                    }

                    void update() {
                        out_hot = in_hot - 0.015;
                        out_pos = in_pos + in_vel + Acc;
                        out_vel = in_vel * 0.95;
                    }

                    void main() {
                        if(in_hot <= 0.0) respawn();
                        else if(abs(in_pos.x) > 1.0) respawn();
                        else if(abs(in_pos.y) > 1.0) respawn();
                        else update();

                        out_id = in_id;
                    }
                ''',
            varyings=['out_pos', 'out_hot', 'out_vel', 'out_id']
        )

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao_final_render = self.ctx.simple_vertex_array(
            self.render_final_fire, self.vbo, 'in_vert')
        self.vao_update_frame = self.ctx.simple_vertex_array(self.update_frame,
                                                             self.vbo,
                                                             'in_vert')
        self.vao_render_tex = self.ctx.simple_vertex_array(self.render_tex,
                                                           self.vbo, 'in_vert')

        map_fire_lut = self.map_fire_lut = {
            'fire_colors': ('lut/fire_colors.png', False),
            'nih-image-fire1': ('lut/nih-image-fire1.png', True),
            'HotRed': ('lut/HotRed.png', False),
            'Amber': ('lut/Amber-1.png', True),
            'fire-ncsa': ('lut/fire-ncsa.png', True),
            'GreenFire': ('lut/GreenFire.png', False),
        }
        self.cl_fire_lut = CircularList(map_fire_lut.keys())
        self.current_id_lut = 0
        self.textures_fire_lut = {}
        for lut_name, (fire_lut_fn, transpose_img) in map_fire_lut.items():
            fire_lut_fn = local('data', fire_lut_fn)
            logger.info(f"Load Fire LUT: {fire_lut_fn}")
            fire_lut_img = Image.open(fire_lut_fn).convert('RGB')
            if transpose_img:
                fire_lut_img = fire_lut_img.transpose(Image.FLIP_LEFT_RIGHT)

            self.textures_fire_lut[lut_name] = self.ctx.texture(
                fire_lut_img.size, 3,
                fire_lut_img.tobytes())
            self.textures_fire_lut[lut_name].repeat_x = False
            self.textures_fire_lut[lut_name].repeat_y = False

        fire_map_fn = local('data', 'fire_src_map.png')
        logger.info(f"Load Fire Source Map: {fire_map_fn}")
        img = (
            Image.open(fire_map_fn)
            .transpose(Image.FLIP_TOP_BOTTOM)
            .convert('RGB')
        )

        self.texture_src_fire_map = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture_fire_map = self.ctx.texture(img.size, 1, dtype='f1')
        self.vbo_fire_map = self.ctx.framebuffer(self.texture_fire_map)
        self.vbo_fire_map.use()

        cooling_map_fn = local('data', 'fire_cooling_map.png')
        logger.info(f"Load Cooling Map: {cooling_map_fn}")
        img = Image.open(cooling_map_fn).transpose(Image.FLIP_TOP_BOTTOM)
        self.texture_cooling_map = self.ctx.texture(img.size, 1, img.tobytes())

        self.update_frame['OffsetXY'].value = (1.0 / img.size[0],
                                               1.0 / img.size[1])

        fire_size = np.array(self.wnd.size) >> 1

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

        self.update_frame['tex_prev_frame'].value = 0
        self.update_frame['tex_fire'].value = 1
        self.update_frame['tex_warp_grid'].value = 2

        self.render_final_fire['Texture'].value = 0
        self.render_final_fire['tex_lut'].value = 1

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

        self.cur_time = 0
        self.prev_time = time.time()

        # Init Warp Grid
        self.warp_grid = WarpGrid(self.ctx)

        # Init Particles system
        self.texture_src_fire_map.use(0)
        self.transform['tex_fire'].value = 0
        self.particles = Particles(self.ctx,
                                   shader_transform=self.transform,
                                   nb_max_particles=64)
        #
        self.ctx.point_size = 9.0

    def update_fire(self, app_time) -> moderngl.Texture:
        # update warp grid
        self.warp_grid.update_grid(app_time)

        # update particles system
        self.texture_src_fire_map.use(0)
        self.particles.update_particles(app_time)

        id_prev_frame = self.id_buffer
        id_cur_frame = 1 - id_prev_frame

        fbo_cur_frame = self.fbos[id_cur_frame]
        #
        tex_prev_frame = self.textures[id_prev_frame]
        tex_cur_frame = self.textures[id_cur_frame]

        fbo_cur_frame.use()
        # set textures for shader
        tex_prev_frame.use(0)
        self.texture_fire_map.use(1)
        self.warp_grid.tex_rtt.use(2)
        # render full screen quad
        self.vao_update_frame.render(moderngl.TRIANGLE_STRIP)

        # Ping Pong strategy
        # for swapping previous and current frames (buffers/textures)
        self.id_buffer = 1 - self.id_buffer

        # Render fire on output buffer
        return tex_cur_frame

    def key_event(self, key, action):
        """
        Handle key events in a generic way
        supporting all window types.
        """
        if action == self.wnd.keys.ACTION_PRESS:
            if key == self.wnd.keys.LEFT:
                self.current_id_lut += 1
            elif key == self.wnd.keys.RIGHT:
                self.current_id_lut -= 1

    def render(self, app_time, frame_time):
        self.update_frame['time'].value = app_time

        # update/render source fire map
        self.vbo_fire_map.use()
        # static sources fires
        self.texture_src_fire_map.use(0)
        # particles system for Sparkles fire
        self.vao_render_tex.render(moderngl.TRIANGLE_STRIP)

        self.particles.render_particles()

        # update/render fire effect
        tex_on_fire_updated = self.update_fire(app_time)

        # show the result on 'screen' (main context)
        self.ctx.screen.use()
        tex_on_fire_updated.use(0)
        self.textures_fire_lut[self.cl_fire_lut[self.current_id_lut]].use(1)
        self.vao_final_render.render(moderngl.TRIANGLE_STRIP)


if __name__ == '__main__':
    logging.basicConfig(
        format='%(asctime)s %(threadName)s %(message)s',
        level=logging.DEBUG
    )
    run_example(Fire)
