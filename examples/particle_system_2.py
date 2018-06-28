import moderngl
import numpy as np
import time

from examples.example_window import Example, run_example


def particle(i: int, angle_main_axis: float = np.pi / 2.0):
    a = np.random.uniform(angle_main_axis - np.pi / 8.0, angle_main_axis + np.pi / 8.0)
    r = np.random.uniform(0.0, 0.02)
    xv = np.cos(a) * r
    yv = np.sin(a) * r
    return np.array([0.0, 0.0, 1.0, xv, yv, float(i)]).astype('f4').tobytes()


class Particles(Example):
    def __init__(self):
        self.ctx = moderngl.create_context()

        self.prog = self.ctx.program(
            vertex_shader='''
                #version 330

                in vec2 in_vert;
                in float in_hot;
                in vec2 in_vel;

                out vec4 in_color;
                                

                void main() {
                    in_color = vec4(vec2(abs(in_vel))*100, in_hot*0.1, 1.0);
                    gl_Position = vec4(in_vert.xy, in_vel.x, 1.0);
                }
            ''',
            fragment_shader='''
                #version 330

                in vec4 in_color;

                out vec4 f_color;

                void main() {
                    f_color = in_color;
                }
            ''',
        )

        self.transform = self.ctx.program(
            vertex_shader='''
            #version 330
            #define M_PI 3.14159265358979323846

            uniform vec2 Acc;
            uniform float Time;

            in vec2 in_pos;
            in float in_hot;
            in vec2 in_vel;
            in float in_id;

            out vec2 out_pos;
            out float out_hot;
            out vec2 out_vel;
            out float out_id;
            
            float rand(float n){return fract(sin(n) * 43758.5453123);}
            
            float map(float value, float inMin, float inMax, float outMin, float outMax) {
              return outMin + (outMax - outMin) * (value - inMin) / (inMax - inMin);
            }

            void respawn(in float seed) {
                float rand_seed = rand(seed);
                
                out_hot = map(rand_seed, 0.0, 1.0, 0.4, 1.0);

                float a = map(rand(Time), 0.0, 1.0, 0.0, 2*M_PI);                    
                out_pos = vec2(cos(a), sin(a)) * 0.1;
                                                    
                float angle_main_axis = M_PI/2.0 - Time; 
                a = map(rand(in_id), 0.0, 1.0, angle_main_axis - M_PI / 8.0, angle_main_axis + M_PI / 8.0);
                float r = rand_seed * 0.015;
                out_vel = vec2(cos(a), sin(a)) * r;
            }
                        
            void update() {
                out_hot = in_hot - 0.020;
                out_pos = in_pos + in_vel;                
                out_vel = in_vel * 0.98 + Acc;
            }
            
            void main() {
                float seed = in_id + Time;
                                                
                if((out_hot < 0.0) || (abs(in_pos.x) > 0.5) || (abs(in_pos.y) > 0.5)) {
                    respawn(seed);
                }
                else {
                    update();
                }
                out_id = in_id;
            }
        ''',
            varyings=['out_pos',
                      'out_hot',
                      'out_vel',
                      'out_id',
                      ]
        )

        try:
            self.acc = self.transform['Acc']
            self.acc.value = (0.0, 0.0002)
        except:
            pass

        self.nb_particles = int(2 << 12)

        self.vbo1 = self.ctx.buffer(b''.join(particle(i) for i in range(self.nb_particles)))
        self.vbo2 = self.ctx.buffer(reserve=self.vbo1.size)

        self.vao1 = self.ctx.simple_vertex_array(self.transform, self.vbo1,
                                                 'in_pos', 'in_hot', 'in_vel', 'in_id')

        self.render_vao = self.ctx.vertex_array(
            self.prog,
            [
                # interpretation:
                # - '2f' => 2 floats: in_vert
                # - '1f' => 1 float: in_hot
                # - '2x4' => drop 2 * 4bytes = 2 floats: in_vel
                # (self.vbo1, '2f 1f 2x4', 'in_vert', 'in_hot'),

                #
                (
                    self.vbo1, '2f 1f 2f 1x4',
                    'in_vert', 'in_hot', 'in_vel'
                ),
            ]
        )

        self.idx = 0

        self.angle_main_axis = np.pi / 2.0

        self.time_from_start = 0
        self.prev_time = time.time()

        try:
            self.u_time = self.transform['Time']
            self.u_time.value = time.time()
        except:
            pass

    def render(self):
        q_for_timer = self.ctx.query(time=True)
        with q_for_timer:
            self.ctx.viewport = self.wnd.viewport
            self.ctx.clear(1.0, 1.0, 1.0)
            self.ctx.point_size = 2.0

            # size_particle = len(particle())
            # for i in range(8):
            #     p = particle(self.angle_main_axis)
            #     self.vbo1.write(p, offset=self.idx * size_particle)
            #     self.idx = (self.idx + 1) % self.nb_particles
            try:
                self.u_time.value = self.time_from_start
            except:
                pass

            self.render_vao.render(moderngl.POINTS, self.nb_particles)
            self.vao1.transform(self.vbo2, moderngl.POINTS, self.nb_particles)
            self.ctx.copy_buffer(self.vbo1, self.vbo2)
        print(f"Query on time elapsed (GPU side): {q_for_timer.elapsed/1000000.0} ms")

        self.angle_main_axis += 0.01

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.time_from_start += dt
        self.prev_time = cur_time


run_example(Particles)
