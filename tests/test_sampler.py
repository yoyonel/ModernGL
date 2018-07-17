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
        print(sampler.compare_func)
        assert sampler.compare_func == '?'
