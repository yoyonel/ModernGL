import shutil, os

if os.path.isdir('build'):
	shutil.rmtree('build')

if os.path.isdir('dist'):
	shutil.rmtree('dist')

if os.path.isdir('__pycache__'):
	shutil.rmtree('__pycache__')

if os.path.isdir('ModernGL/__pycache__'):
	shutil.rmtree('ModernGL/__pycache__')

if os.path.isdir('External/__pycache__'):
	shutil.rmtree('External/__pycache__')

if os.path.isfile('External/cccompiler.pyc'):
	os.remove('External/cccompiler.pyc')

if os.path.isdir('ModernGL.egg-info'):
	shutil.rmtree('ModernGL.egg-info')

if os.path.isfile('files.txt'):
	os.remove('files.txt')

if os.path.isfile('log.txt'):
	os.remove('log.txt')
