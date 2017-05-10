import unittest, importlib


class TestCase(unittest.TestCase):

	def test_import(self):
		importlib.import_module('ModernGL')


if __name__ == '__main__':
	unittest.main()
