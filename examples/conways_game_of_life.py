import moderngl
import numpy as np

from example_window import Example, run_example


class Conway(Example):
    WINDOW_SIZE = (512, 512)

    def __init__(self):
        self.ctx = moderngl.create_context()

        width, height = (128, 128)
        # width, height = self.wnd.size

        canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
        pixels = np.round(np.random.rand(width, height)).astype('f4')
        grid = np.dstack(np.mgrid[0:height, 0:width][::-1]).astype('i4')

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

                in ivec2 in_text;
                out float out_vert;

                #define LIVING 0.0
                #define DEAD 1.0

                bool cell(int x, int y) {
                    return texelFetch(Texture, ivec2((x + Width) % Width, (y + Height) % Height), 0).r < 0.5;
                }

                void main() {
                    bool living = cell(in_text.x, in_text.y);

                    int neighbours = 0;
                    if (cell(in_text.x - 1, in_text.y - 1)) neighbours++;
                    if (cell(in_text.x - 1, in_text.y + 0)) neighbours++;
                    if (cell(in_text.x - 1, in_text.y + 1)) neighbours++;
                    if (cell(in_text.x + 1, in_text.y - 1)) neighbours++;
                    if (cell(in_text.x + 1, in_text.y + 0)) neighbours++;
                    if (cell(in_text.x + 1, in_text.y + 1)) neighbours++;
                    if (cell(in_text.x + 0, in_text.y + 1)) neighbours++;
                    if (cell(in_text.x + 0, in_text.y - 1)) neighbours++;

                    if (living) {
                        out_vert = (neighbours == 2 || neighbours == 3) ? LIVING : DEAD;
                    } else {
                        out_vert = (neighbours == 3) ? LIVING : DEAD;
                    }
                }
            ''',
            varyings=['out_vert']
        )

        self.transform['Width'].value = width
        self.transform['Height'].value = height

        self.texture = self.ctx.texture((width, height), 1, pixels.tobytes(), dtype='f4')
        self.texture.filter = (moderngl.NEAREST, moderngl.NEAREST)
        self.texture.swizzle = 'RRR1'
        self.texture.use()

        self.vbo = self.ctx.buffer(canvas.tobytes())
        self.vao = self.ctx.simple_vertex_array(self.prog, self.vbo, 'in_vert')

        self.text = self.ctx.buffer(grid.tobytes())
        self.tao = self.ctx.simple_vertex_array(self.transform, self.text, 'in_text')
        self.pbo = self.ctx.buffer(reserve=pixels.nbytes)

    def render(self):
        self.ctx.viewport = self.wnd.viewport
        self.ctx.clear(1.0, 1.0, 1.0)

        self.tao.transform(self.pbo)
        self.texture.write(self.pbo)
        
        self.vao.render(moderngl.TRIANGLE_STRIP)


run_example(Conway)
