import unittest

import ModernGL as GL

class TestContext(unittest.TestCase):

	def test_context(self):
		ctx = GL.create_standalone_context()
		ctx.release()


if __name__ == '__main__':
	unittest.main()
