import struct
import unittest

import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.ctx = ModernGL.create_standalone_context()

    @classmethod
    def tearDownClass(self):
        self.ctx.release()

    def test_1(self):
        ctx = self.ctx
        
        prog = ctx.program([
            ctx.vertex_shader('''
                #version 330
        
                in vec2 v_in_1;
                in vec2 v_in_2;

                out vec4 v_out;

                void main() {
                    v_out = vec4(v_in_1, v_in_2);
                }
            '''),
        ], varyings=['v_out'])

        vbo1 = ctx.buffer(struct.pack('2f', 1.0, 2.0))
        vbo2 = ctx.buffer(struct.pack('4f', 0.0, 0.0, 0.0, 0.0))
        vao1 = ctx.simple_vertex_array(prog, vbo1, ['v_in_1'])
        vao2 = ctx.simple_vertex_array(prog, vbo1, ['v_in_1'])

        # print(vao1.attributes)

        vao1.attributes['v_in_2'].default = (3.0, 4.0)
        # vao2.attributes['v_in_2'].default = (0.5, 0.5)

        vao1.transform(vbo2)

        print(struct.unpack('4f', vbo2.read()))

        vao2.transform(vbo2)

        print(struct.unpack('4f', vbo2.read()))

if __name__ == '__main__':
    unittest.main()
