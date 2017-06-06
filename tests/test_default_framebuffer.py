import unittest

import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.ctx = ModernGL.create_standalone_context()

    @classmethod
    def tearDownClass(cls):
        cls.ctx.release()

    def test_having_color_attachments(self):
        with self.assertRaisesRegex(ModernGL.Error, 'attachment'):
            self.ctx.default_framebuffer.color_attachments

    def test_having_depth_attachment(self):
        with self.assertRaisesRegex(ModernGL.Error, 'attachment'):
            self.ctx.default_framebuffer.depth_attachment


if __name__ == '__main__':
    unittest.main()
