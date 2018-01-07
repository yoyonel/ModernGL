import unittest

from common import get_context
import ModernGL


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.ctx = get_context()

    def test_program(self):

        vertex_shader = self.ctx.vertex_shader('''
            #version 330

            uniform vec2 pos;
            uniform float scale;

            in vec2 vert;
            out vec2 v_vert;

            void main() {
                gl_Position = vec4(pos + vert * scale, 0.0, 1.0);
                v_vert = vert;
            }
        ''')

        fragment_shader = self.ctx.fragment_shader('''
            #version 330

            in vec2 v_vert;
            out vec4 color;

            void main() {
                color = vec4(v_vert, 0.0, 1.0);
            }
        ''')

        program = self.ctx.program([vertex_shader, fragment_shader])

        self.assertIn('vert', program)
        self.assertIn('pos', program)
        self.assertIn('scale', program)

        self.assertIsInstance(program['vert'], ModernGL.Attribute)
        self.assertIsInstance(program['pos'], ModernGL.Uniform)
        self.assertIsInstance(program['scale'], ModernGL.Uniform)


if __name__ == '__main__':
    unittest.main()
