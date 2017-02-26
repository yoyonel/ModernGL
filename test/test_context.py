import os; os.chdir(os.path.dirname(__file__))
import unittest

import ModernGL as GL

class TestContext(unittest.TestCase):

	def test_context(self):
		GL.create_standalone_context()

if __name__ == '__main__':
	unittest.main()
