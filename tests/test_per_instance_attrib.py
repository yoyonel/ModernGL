import struct
import unittest

import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.ctx = ModernGL.create_standalone_context()
        ctx = self.ctx

        prog = ctx.program([
            ctx.vertex_shader('''
                #version 330

                in float v_in_1;
                in float v_in_2;
                in float v_in_3;
                out float v_out;

                void main() {
                    v_out = v_in_1 + v_in_2 + v_in_3;
                }
            '''),
        ], varyings=['v_out'])

        vbo1 = ctx.buffer(struct.pack('4f', 1.0, 2.0, 3.0, 4.0))
        vbo2 = ctx.buffer(struct.pack('4f', 10.0, 20.0, 30.0, 40.0))
        vbo3 = ctx.buffer(struct.pack('4f', 100.0, 200.0, 300.0, 400.0))

        vao1_content = [
            (vbo1, 'f', ['v_in_1']),
            (vbo2, 'f/i', ['v_in_2']),
        ]

        self.vao1 = ctx.vertex_array(prog, vao1_content)

        vao2_content = [
            (vbo1, 'f', ['v_in_1']),
            (vbo2, 'f/i', ['v_in_2']),
            (vbo3, 'f/r', ['v_in_3']),
        ]

        self.vao2 = ctx.vertex_array(prog, vao2_content)

        self.res = ctx.buffer(reserve=1024)

    @classmethod
    def tearDownClass(self):
        self.ctx.release()

    def test_vertex_attrib_per_instance_1(self):
        self.vao1.transform(self.res, ModernGL.POINTS, vertices = 4, instances = 1)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 11.0)
        self.assertAlmostEqual(b, 12.0)
        self.assertAlmostEqual(c, 13.0)
        self.assertAlmostEqual(d, 14.0)

    def test_vertex_attrib_per_instance_2(self):
        self.vao1.transform(self.res, ModernGL.POINTS, vertices = 2, instances = 2)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 11.0)
        self.assertAlmostEqual(b, 12.0)
        self.assertAlmostEqual(c, 21.0)
        self.assertAlmostEqual(d, 22.0)

    def test_vertex_attrib_per_instance_3(self):
        self.vao1.transform(self.res, ModernGL.POINTS, vertices = 1, instances = 4)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 11.0)
        self.assertAlmostEqual(b, 21.0)
        self.assertAlmostEqual(c, 31.0)
        self.assertAlmostEqual(d, 41.0)

    def test_vertex_attrib_per_render_1(self):
        self.vao2.transform(self.res, ModernGL.POINTS, vertices = 4, instances = 1)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 111.0)
        self.assertAlmostEqual(b, 112.0)
        self.assertAlmostEqual(c, 113.0)
        self.assertAlmostEqual(d, 114.0)

    def test_vertex_attrib_per_render_2(self):
        self.vao2.transform(self.res, ModernGL.POINTS, vertices = 2, instances = 2)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 111.0)
        self.assertAlmostEqual(b, 112.0)
        self.assertAlmostEqual(c, 121.0)
        self.assertAlmostEqual(d, 122.0)

    def test_vertex_attrib_per_render_3(self):
        self.vao2.transform(self.res, ModernGL.POINTS, vertices = 1, instances = 4)

        a, b, c, d = struct.unpack('4f', self.res.read(16))

        self.assertAlmostEqual(a, 111.0)
        self.assertAlmostEqual(b, 121.0)
        self.assertAlmostEqual(c, 131.0)
        self.assertAlmostEqual(d, 141.0)


if __name__ == '__main__':
    unittest.main()
