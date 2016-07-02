import os, sys, unittest, importlib

class Importable(unittest.TestCase):
	def test_import(self):
		import ModernGL

	def test_init_fail(self):
		import ModernGL as GL

		self.assertEqual(GL.GetError(), 'Not initialized.')

		GL.InitializeModernGL()

		self.assertEqual(GL.GetError(), 'InitializeOpenGL failed.') 
		self.assertEqual(GL.ExtensionActive(), False) 
		
		with self.assertRaises(GL.Error):
			GL.GetInfo()

if __name__ == '__main__':
	major = sys.hexversion >> 24
	if major >= 3:
		unittest.main(verbosity = 2, warnings = False)
	else:
		unittest.main(verbosity = 2)
