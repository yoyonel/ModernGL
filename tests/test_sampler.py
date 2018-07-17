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
        assert sampler.anisotropy == 1.0
        assert sampler.repeat_x is True
        assert sampler.repeat_y is True
        assert sampler.filter == (moderngl.LINEAR, moderngl.LINEAR)
        assert sampler.compare_func == '?'

        # Change values
        sampler.anisotropy = 2.0
        sampler.repeat_x = False
        sampler.repeat_y = False
        sampler.filter = (moderngl.NEAREST_MIPMAP_NEAREST, moderngl.NEAREST)
        sampler.compare_func = "<="

        assert sampler.anisotropy == 2.0
        assert sampler.repeat_x is False
        assert sampler.repeat_y is False
        assert sampler.filter == (moderngl.NEAREST_MIPMAP_NEAREST, moderngl.NEAREST)
        assert sampler.compare_func == "<="
