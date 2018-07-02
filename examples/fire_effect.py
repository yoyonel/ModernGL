"""

"""
import logging
import moderngl
import numpy as np
import os
from PIL import Image
import time
#
from examples.warp_grid_with_texture3D import WarpGridTex3D
from examples.particle_system_2 import Particles
#
from examples.example_window import Example, run_example

logger = logging.getLogger(__name__)

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


def generate_image_fire_colors():
    fire_colors = list(zip(FireRed, FireGreen, FireBlue))
    img_fire_colors = Image.new('RGB', (len(fire_colors), 1))
    img_fire_colors.putdata(fire_colors)
    return img_fire_colors


def local(*path):
    return os.path.join(os.path.dirname(__file__), *path)


class Fire(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

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
                uniform sampler2D tex_fire_colors;

                in vec2 v_text;
                out vec4 f_color;

                void main() {
                    float fire = texture(Texture, v_text).r;

                    f_color = texture(tex_fire_colors, vec2(fire, 1));

                    //f_color = texture(Texture, v_text);
                    //f_color = vec4(vec3(f_color.r), 1.0);
                    //f_color = vec4(1.0 - abs(vec3(fire) - vec3(f_color.r)), 1.0);
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
                        
                        vec3 compute_cooling() {
                            vec2 v_text_scrolled = v_text;
                            v_text_scrolled += vec2(0.0, -time);
                            v_text_scrolled += vec2(cos(time)*0.5, 0.0);
                            
                            float cooling_value = texture(tex_cooling_map, v_text_scrolled).r;
                            return vec3(cooling_value) * 2.00;
                        }
                        
                        /**/
                        vec3 compute_cooling_with_warpgrid() {
                            vec2 v_text_scrolled = v_text;
                            v_text_scrolled += vec2(0.0, -time);
                            v_text_scrolled += vec2(cos(time)*0.5, 0.0);
                            
                            float cooling_value = texture(tex_warp_grid, v_text_scrolled).r;
                            float r = gold_noise(gl_FragCoord.xy, time) * 0.015;
                            return vec3(cooling_value) * 1.50 + vec3(r);
                        }
                        /**/
                        
                        void main() {                                                    
                            // Source fire
                            vec3 src_fire = texture(tex_fire, v_text).rgb;
                            
                            // Filter (+ scroll) fire map
                            vec3 filter_fire = compute_filter_firemap(tex_prev_frame, v_text);                            
                            
                            // Cooling map/attenuation
                            //vec3 cooling = compute_cooling();
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
                        out_pos = vec2(
                            map(pos_x, 0, 1, -1, +1) * 1.0, 
                            map(pos_y, 0, 1, -1, +1) * 1.0
                        );
                        
                        out_hot = map(gold_noise(vec2(in_id, Time), 25), 0.0, 1.0, 0.4, 1.0);
                        out_hot *= texture(tex_fire, vec2(pos_x, pos_y)).r;

                        float r = gold_noise(vec2(in_id, Time), 100) * 0.015;
                        float vel_x =  map(gold_noise(vec2(in_id, Time), 105), 0, 1, -1, 1) * 0.005;
                        //out_vel = vec2(0.0, r);
                        out_vel = vec2(vel_x, r);
                    }

                    void update() {
                        //out_hot = in_hot - map(gold_noise(vec2(in_id, Time), 125), 0.0, 1.0, 0.0075, 0.01);
                        //out_hot = in_hot - 0.003;
                        out_hot = in_hot - 0.015;
                        out_pos = in_pos + in_vel + Acc;
                        //out_vel = in_vel * map(gold_noise(vec2(in_id, Time), 150), 0.0, 1.0, 0.95, 1.00) + Acc;
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
            varyings=['out_pos',
                      'out_hot',
                      'out_vel',
                      'out_id',
                      ]
        )

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao_final_render = self.ctx.simple_vertex_array(self.render_final_fire, self.vbo, 'in_vert')
        self.vao_update_frame = self.ctx.simple_vertex_array(self.update_frame, self.vbo, 'in_vert')
        self.vao_render_tex = self.ctx.simple_vertex_array(self.render_tex, self.vbo, 'in_vert')

        img = Image.open(local('data', 'fire_colors.png')).transpose(Image.FLIP_TOP_BOTTOM)
        self.texture_fire_colors = self.ctx.texture(img.size, 3, img.tobytes())

        img = Image.open(local('data', 'fire.jpg')).transpose(Image.FLIP_TOP_BOTTOM).convert('RGB')
        self.texture_src_fire_map = self.ctx.texture(img.size, 3, img.tobytes())
        self.texture_fire_map = self.ctx.texture(img.size, 1, dtype='f1')
        # self.texture_fire_map.build_mipmaps()
        self.vbo_fire_map = self.ctx.framebuffer(self.texture_fire_map)
        self.vbo_fire_map.use()
        # self.vbo_fire_map.clear(0.0, 0.0, 0.0)

        img = Image.open(local('data', 'fire_cooling_map.png')).transpose(Image.FLIP_TOP_BOTTOM)
        self.texture_cooling_map = self.ctx.texture(img.size, 1, img.tobytes())

        img_fire_colors = generate_image_fire_colors()
        self.texture_fire_colors = self.ctx.texture(img_fire_colors.size, 3, img_fire_colors.tobytes())
        self.texture_fire_colors.repeat_x = False
        self.texture_fire_colors.repeat_y = False

        try:
            self.update_frame['OffsetXY'].value = (1.0 / img.size[0], 1.0 / img.size[1])
        except KeyError:
            logger.warning("", exc_info=True)

        # fire_size = self.wnd.size
        fire_size = np.array(self.wnd.size) >> 1
        # fire_size = (64, 64)

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
            self.update_frame['tex_prev_frame'].value = 0
            self.update_frame['tex_fire'].value = 1
            # self.update_frame['tex_cooling_map'].value = 2
            self.update_frame['tex_warp_grid'].value = 2
        except:
            logger.warning("", exc_info=True)

        try:
            self.render_final_fire['Texture'].value = 0
            self.render_final_fire['tex_fire_colors'].value = 1
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
        # self.texture_fire_map.use()
        # self.vao_final_render.render(moderngl.TRIANGLE_STRIP)

        self.cur_time = 0
        self.prev_time = time.time()

        self.warp_grid = WarpGridTex3D(self.ctx)

        self.particles = Particles(self.ctx,
                                   shader_transform=self.transform,
                                   nb_max_particles=32)

    def update_fire(self) -> moderngl.Texture:

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
        # self.texture_cooling_map.use(2)
        self.warp_grid.tex_final_render.use(2)
        # render full screen quad
        self.vao_update_frame.render(moderngl.TRIANGLE_STRIP)

        # Ping Pong strategy for swapping previous and current frames (buffers/textures)
        self.id_buffer = 1 - self.id_buffer

        # Render fire on output buffer
        return tex_cur_frame

    def render(self):
        # OpenGL Timer Query
        q_for_timer = self.ctx.query(time=True)
        with q_for_timer:
            try:
                self.update_frame['time'].value = self.cur_time
            except:
                pass

            # update warp grid
            self.warp_grid.update_grid(self.wnd.time)

            # update particles system
            self.texture_fire_map.use()
            self.particles.update()

            # update/render source fire map
            self.vbo_fire_map.use()
            self.vbo_fire_map.clear(0.0, 0.0, 0.0)
            # static sources fires
            self.texture_src_fire_map.use()
            # particles system for Sparkles fire
            self.vao_render_tex.render(moderngl.TRIANGLE_STRIP)
            self.ctx.point_size = 9.0
            self.particles.render_particles()

            # update/render fire effect
            tex_on_fire_updated = self.update_fire()

            # show the result on 'screen' (main context)
            self.ctx.screen.use()
            self.ctx.viewport = self.wnd.viewport
            self.ctx.clear(1.0, 1.0, 1.0)
            # self.warp_grid.tex_final_render.use(0)    # Work
            tex_on_fire_updated.use(0)
            self.texture_fire_colors.use(1)
            self.vao_final_render.render(moderngl.TRIANGLE_STRIP)
        #
        # logger.info(f"Query on time elapsed (GPU side): {q_for_timer.elapsed/1000000.0} ms")

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.cur_time += dt
        self.prev_time = cur_time

        # logger.info(f"fps={1.0/dt}")


if __name__ == '__main__':
    run_example(Fire)
