import unittest

import moderngl

from common import get_context


class TestCase(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        cls.ctx = get_context()

    def test_attributes(self):
        sampler = self.ctx.sampler()

        # Default values
        self.assertEqual(sampler.anisotropy, 1.0)
        self.assertTrue(sampler.repeat_x)
        self.assertTrue(sampler.repeat_y)
        self.assertTrue(sampler.repeat_z)
        self.assertEqual(sampler.filter, (moderngl.LINEAR, moderngl.LINEAR))
        self.assertEqual(sampler.compare_func, '?')
        self.assertEqual(sampler.border_color, (0.0, 0.0, 0.0, 0.0))

        # Change values
        sampler.anisotropy = self.ctx.max_anisotropy
        sampler.filter = (moderngl.NEAREST_MIPMAP_NEAREST, moderngl.NEAREST)
        sampler.compare_func = "<="

        self.assertEqual(sampler.anisotropy, self.ctx.max_anisotropy)
        self.assertEqual(sampler.filter, (moderngl.NEAREST_MIPMAP_NEAREST, moderngl.NEAREST))
        self.assertEqual(sampler.compare_func, "<=")

        # Ensure repeat parameters are set correctly
        sampler.repeat_x = False
        self.assertEqual((sampler.repeat_x, sampler.repeat_y, sampler.repeat_z), (False, True, True))
        sampler.repeat_y = False
        self.assertEqual((sampler.repeat_x, sampler.repeat_y, sampler.repeat_z), (False, False, True))
        sampler.repeat_z = False
        self.assertEqual((sampler.repeat_x, sampler.repeat_y, sampler.repeat_z), (False, False, False))

        # Ensure border color values are set correctly
        colors = [
            (1.0, 0.0, 0.0, 0.0),
            (0.0, 1.0, 0.0, 0.0),
            (0.0, 0.0, 1.0, 0.0),
            (0.0, 0.0, 0.0, 1.0),
        ]
        for color in colors:
            sampler.border_color = color
            self.assertEqual(sampler.border_color, color)
