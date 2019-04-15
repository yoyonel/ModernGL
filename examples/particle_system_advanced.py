import time

import moderngl
import numpy as np

from window import Example, run_example


def particle(
        angle_main_axis: float = np.pi / 2.0,
        range_angle_axis: float = np.pi / 8.0,
        id_particle: int = 0,
):
    a = np.random.uniform(angle_main_axis - range_angle_axis,
                          angle_main_axis + range_angle_axis)
    r = np.random.uniform(0.0, 0.02)
    xv = np.cos(a) * r
    yv = np.sin(a) * r
    #
    return np.array(
        [
            0.0, 0.0,               # position      [vec2]
            1.0,                    # hotness       [float]
            xv, yv,                 # velicity      [vec2]
            float(id_particle)      # id particle   [float]
        ]).astype('f4').tobytes()   # float32


class Particles(Example):
    title = "Particle System"
    gl_version = (3, 3)

    def __init__(self, nb_max_particles=1024, **kwargs):
        super().__init__(**kwargs)

        self.prog = self.ctx.program(
            vertex_shader='''
                 #version 330
                 in vec2 in_vert;
                 in float in_hot;

                 out float out_hot;
                 void main() {
                     out_hot = in_hot;
                     gl_Position = vec4(in_vert.xy, 0.0, 1.0);
                 }
             ''',
            fragment_shader='''
                 #version 330
                 uniform vec4 color_particle;

                 in float out_hot;

                 out vec4 f_color;
                 
                 void main() {
                     float d_to_center = distance(gl_PointCoord.xy, vec2(0.5, 0.5));
                     if (d_to_center > out_hot*0.5)
                        discard;
                     f_color = vec4(1.0 - vec3(d_to_center), 1.0);

                     f_color *= color_particle;
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
    
                   out_hot = map(gold_noise(vec2(in_id, Time), 25), 0.0, 1.0, 0.4, 1.0);
    
                   out_pos = vec2(
                       map(gold_noise(vec2(in_id, Time), 0), 0, 1, -1, +1), 
                       map(gold_noise(vec2(in_id, Time), 50), 0, 1, -1, +1)
                   );
    
                   float r = gold_noise(vec2(in_id, Time), 100) * 0.015;
                   out_vel = vec2(0.0, r);
               }
    
               void update() {
                   out_hot = in_hot - 0.006;
                   out_pos = in_pos + in_vel + Acc;
                   out_vel = in_vel * 0.98;
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

        try:
            self.color_particle = self.prog['color_particle']
            self.color_particle.value = (1.0, 1.0, 1.0, 1.0)
        except:
            pass

        self.nb_particles = nb_max_particles

        self.acc = self.transform['Acc']
        self.acc.value = (0.0, -0.0001)

        self.vbo1 = self.ctx.buffer(
            b''.join(
                particle(range_angle_axis=np.pi * 2.0, id_particle=i)
                for i in range(self.nb_particles)
            )
        )
        self.vbo2 = self.ctx.buffer(reserve=self.vbo1.size)

        self.vao1 = self.ctx.simple_vertex_array(
            self.transform, self.vbo1,
            'in_pos', 'in_hot', 'in_vel', 'in_id'
        )

        self.render_vao = self.ctx.vertex_array(
            self.prog,
            [
                # interpretation:
                # - '2f' => 2 floats: in_vert
                # - '1f' => 1 float: in_hot
                # - '3x4' => drop 3 * 4bytes = 3 floats: in_vel, in_id
                (
                    self.vbo1,
                    '2f 1f 3x4',
                    'in_vert', 'in_hot'
                ),
            ],
            skip_errors=False
        )

        self.idx = 0

        self.angle_main_axis = np.pi / 2.0

        self.u_time = self.transform['Time']
        self.u_time.value = time.time()

    def render(self, _time, frame_time):
        self.ctx.clear(1.0, 1.0, 1.0)
        self.ctx.point_size = 16.0

        self.u_time.value = _time

        self.render_vao.render(moderngl.POINTS, self.nb_particles)

        # Update particles system
        self.vao1.transform(self.vbo2, moderngl.POINTS, self.nb_particles)
        self.ctx.copy_buffer(self.vbo1, self.vbo2)


if __name__ == '__main__':
    run_example(Particles)
