# pylint: disable=import-error
# pylint: disable=line-too-long
# pylint: disable=wildcard-import
# pylint: disable=mixed-indentation
# pylint: disable=bad-whitespace

'''
	ModernGL
'''

version = '3.1.5'

from ModernGL.ModernGL import *

def detect_format(program, attributes):
	'''
		detect_format(program, attributes)
	'''

	return ''.join('%d%s' % (program.attributes[a].array_length * program.attributes[a].dimension, program.attributes[a].shape) for a in attributes)
