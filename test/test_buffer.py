import os; os.chdir(os.path.dirname(__file__))
import unittest

import ModernGL as GL

ctx = GL.create_standalone_context()

class TestBuffer(unittest.TestCase):

	def test_buffer_1(self):
		buf = ctx.Buffer(data = b'\xAA\x55' * 10)
		self.assertEqual(buf.read(), b'\xAA\x55' * 10)
		buf.release()

	def test_buffer_2(self):
		buf = ctx.Buffer(reserve = 10)
		buf.write(b'abcd')
		self.assertEqual(buf.read(4), b'abcd')
		buf.write(b'abcd', offset = 3)
		self.assertEqual(buf.read(4, offset = 1), b'bcab')
		buf.write(b'abcd', offset = 6)
		self.assertEqual(buf.read(), b'abcabcabcd')
		self.assertEqual(buf.read(offset = 3), b'abcabcd')
		buf.release()

	def test_buffer_3(self):
		buf = ctx.Buffer(reserve = 1024)
		buf.orphan()
		buf.release()

		self.assertEqual(type(buf), GL.InvalidObject)

		with self.assertRaises(Exception):
			buf.read()

	def test_buffer_4(self):
		buf = ctx.Buffer(reserve = 1024)
		with buf.access() as a:
			a.read(3)
			pass

	# def test_buffer_4(self):
	# 	buf = ctx.Buffer(reserve = 1024)
	# 	buf.release()

if __name__ == '__main__':
	unittest.main()
