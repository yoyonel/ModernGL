"""

"""
import moderngl
import numpy as np
import struct
import time
#
from examples.example_window import Example, run_example


class WarpGrid(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

        self.width, self.height = (17, 17)
        width = self.width
        height = self.height

        # width, height = self.wnd.size

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
        # pixels = np.round(np.random.rand(width, height, 2)).astype('f4')
        nx = np.linspace(0, 1, width)
        ny = np.linspace(0, 1, height)
        pixels = np.stack(np.meshgrid(nx, ny), axis=-1).astype('f4')
        # pixels_rand_offsets = (np.random.rand(height, width, 2) - (0.5, 0.5)) * (1/height, 1/width) * 0.010
        # pixels += pixels_rand_offsets
        grid = np.dstack(np.mgrid[0:height, 0:width][::-1]).astype('i4')
        #
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

        self.transform = self.ctx.program(
            vertex_shader='''
                #version 330

                uniform sampler2D Texture;
                uniform int Width;
                uniform int Height;
                uniform float time;

                in ivec2 in_text;
                out vec2 out_vert;
                
                float PHI = 1.61803398874989484820459 * 00000.1; // Golden Ratio   
                float PI  = 3.14159265358979323846264 * 00000.1; // PI
                float SQ2 = 1.41421356237309504880169 * 10000.0; // Square Root of Two
                
                float gold_noise(in vec2 coordinate, in float seed){
                    return fract(sin(dot(coordinate*(seed+PHI), vec2(PHI, PI)))*SQ2);
                }

                vec2 cell(int x, int y) {
                    return texelFetch(Texture, ivec2((x + Width) % Width, (y + Height) % Height), 0).rg;
                }

                void main() {
                    float norm;
                    vec2 spring;
                    vec2 force = vec2(0, 0);
                    float friction = 0.01; 
                    
                    vec2 cell_00 = cell(in_text.x, in_text.y);
                    
                    if (in_text.x > 0 && in_text.x < (Width-1) && in_text.y > 0 && in_text.y < (Height-1)) {
                        float inv_Width = 1.0 / Width;
                        float inv_Height = 1.0 / Height;
                        
                        vec2 cell_neighboor = cell(in_text.x, in_text.y + 1) + (gold_noise(vec2(in_text.x, in_text.y + 1), time) - 0.5) * 0.01;
                        norm = sqrt(0*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x, in_text.y - 1) + (gold_noise(vec2(in_text.x, in_text.y - 1), time) - 0.5) * 0.01;
                        norm = sqrt(0*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x + 1, in_text.y) + (gold_noise(vec2(in_text.x + 1, in_text.y), time) - 0.5) * 0.01;
                        norm = sqrt(1*inv_Width*inv_Width + 0*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x - 1, in_text.y) + (gold_noise(vec2(in_text.x - 1, in_text.y), time) - 0.5) * 0.01;
                        norm = sqrt(1*inv_Width*inv_Width + 0*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x + 1, in_text.y + 1);
                        norm = sqrt(1*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x + 1, in_text.y - 1);
                        norm = sqrt(1*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x - 1, in_text.y + 1);
                        norm = sqrt(1*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        cell_neighboor = cell(in_text.x - 1, in_text.y - 1);
                        norm = sqrt(1*inv_Width*inv_Width + 1*inv_Height*inv_Height);
                        spring = cell_neighboor - cell_00;
                        force += spring * (norm - length(spring)) * friction;
                        
                        //force = normalize(force) * 0.001;
                    }
                    out_vert = cell_00 + force;             
                }
            ''',
            varyings=['out_vert']
        )

        self.transform['Width'].value = width
        self.transform['Height'].value = height

        self.texture = self.ctx.texture(size=(width, height), components=2, data=pixels.tobytes(), dtype='f4')
        self.texture.filter = (moderngl.NEAREST, moderngl.NEAREST)
        self.texture.swizzle = 'RG01'
        self.texture.use()

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')

        self.text = self.ctx.buffer(grid.tobytes())
        self.tao = self.ctx.simple_vertex_array(self.transform, self.text, 'in_text')
        self.pbo = self.ctx.buffer(reserve=pixels.nbytes)

        self.time = 0
        self.prev_time = time.time()

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(0.0, 0.0, 0.0)

        try:
            self.transform['time'].value = self.time
        except:
            pass

        self.tao.transform(self.pbo)
        self.texture.write(self.pbo)

        vertex_grid = struct.unpack(f'{self.width*self.height*2}f', self.pbo.read())
        i, j = (self.width//2, self.height//2)
        # i, j = (3, 3)
        x_on_grid = vertex_grid[(i + j * self.width)*2]
        y_on_grid = vertex_grid[(i + j * self.width)*2 + 1]
        print(f"(x, y)=({x_on_grid - (j*1.0/(self.height-1)):.4f}, {(y_on_grid - i*1.0/(self.width-1)):.4f})")

        self.vao.render(moderngl.TRIANGLE_STRIP)

        cur_time = time.time()
        dt = cur_time - self.prev_time
        self.time += dt
        self.prev_time = cur_time


run_example(WarpGrid)
