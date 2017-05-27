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

    def test_renderbuffer(self):
        rbo = self.ctx.renderbuffer((64, 64))

    def test_multisample_renderbuffer(self):
        rbo = self.ctx.renderbuffer((64, 64), samples=2)

    def test_depth_renderbuffer(self):
        rbo = self.ctx.depth_renderbuffer((64, 64))

    def test_multisample_depth_renderbuffer(self):
        rbo = self.ctx.depth_renderbuffer((64, 64), samples=2)

    def test_renderbuffer_invalid_samples(self):
        with self.assertRaisesRegex(ModernGL.Error, 'sample'):
            rbo = self.ctx.renderbuffer((64, 64), samples=3)


if __name__ == '__main__':
    unittest.main()
