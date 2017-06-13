import unittest

import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.ctx = ModernGL.create_standalone_context()

    @classmethod
    def tearDownClass(cls):
        cls.ctx.release()

    def tearDown(self):
        self.assertEqual(self.ctx.error, 'GL_NO_ERROR')

    def test_1(self):
        size = (4, 4)
        rbo1 = self.ctx.renderbuffer(size, floats=False)
        rbo2 = self.ctx.renderbuffer(size)
        rbo3 = self.ctx.renderbuffer(size)
        fbo1 = self.ctx.framebuffer(rbo1)
        fbo2 = self.ctx.framebuffer(rbo2)
        fbo3 = self.ctx.framebuffer(rbo3)
        fbo4 = self.ctx.framebuffer([rbo1, rbo2, rbo3])

        fbo1.clear(1.0, 0.0, 0.0, 1.0)
        fbo2.clear(0.0, 1.0, 0.0, 1.0)
        fbo3.clear(0.0, 0.0, 1.0, 1.0)

        buf = self.ctx.buffer(reserve=64)

        fbo4.read_into(buf, attachment=0, components=4, floats=False)
        self.assertEqual(buf.read(), b'\xff\x00\x00\xff' * 16)

        fbo4.read_into(buf, attachment=1, components=4, floats=False)
        self.assertEqual(buf.read(), b'\x00\xff\x00\xff' * 16)

        fbo4.read_into(buf, attachment=2, components=4, floats=False)
        self.assertEqual(buf.read(), b'\x00\x00\xff\xff' * 16)


if __name__ == '__main__':
    unittest.main()
