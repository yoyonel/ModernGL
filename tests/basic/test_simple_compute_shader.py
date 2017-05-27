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

    def test_compute_shader(self):
        if self.ctx.version_code < 430:
            return

        src = '''
            #version 430
            layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
            void main() {
            }
        '''

        compute_shader = self.ctx.compute_shader(src)
        self.assertEqual(compute_shader.source, src)


if __name__ == '__main__':
    unittest.main()
