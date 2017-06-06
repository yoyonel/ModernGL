import unittest

import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.ctx = ModernGL.create_standalone_context()

    @classmethod
    def tearDownClass(cls):
        cls.ctx.release()

    def test_size(self):
        width, height = self.ctx.default_framebuffer.size
        self.assertEqual(width, 0)
        self.assertEqual(height, 0)

    def test_samples(self):
        samples = self.ctx.default_framebuffer.samples
        self.assertEqual(samples, 0)

    def test_having_color_attachments(self):
        with self.assertRaisesRegex(ModernGL.Error, 'attachment'):
            self.ctx.default_framebuffer.color_attachments

    def test_having_depth_attachment(self):
        with self.assertRaisesRegex(ModernGL.Error, 'attachment'):
            self.ctx.default_framebuffer.depth_attachment


if __name__ == '__main__':
    unittest.main()
