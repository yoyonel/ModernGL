import unittest

from common import get_context


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        # raise unittest.SkipTest('NYI')
        cls.ctx = get_context(require=430)

    def test_compute_shader(self):
        if self.ctx.version_code < 430:
            self.skipTest('OpenGL 4.3 is not supported')

        src = '''
            #version 430
            layout (local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
            void main() {
            }
        '''

        compute_shader = self.ctx.compute_shader(src)
        self.assertEqual(compute_shader.source, src)
        compute_shader.release()


if __name__ == '__main__':
    unittest.main()
