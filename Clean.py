import shutil, os

if os.path.isdir('Bin'):
	shutil.rmtree('Bin')

if os.path.isdir('Temp'):
	shutil.rmtree('Temp')

if os.path.isdir('Build'):
	shutil.rmtree('Build')

if os.path.isdir('Dist'):
	shutil.rmtree('Dist')

if os.path.isdir('__pycache__'):
	shutil.rmtree('__pycache__')

if os.path.isdir('ModernGL/__pycache__'):
	shutil.rmtree('ModernGL/__pycache__')

if os.path.isdir('ModernGL.egg-info'):
	shutil.rmtree('ModernGL.egg-info')

if os.path.isfile('cccompiler.pyc'):
	os.remove('cccompiler.pyc')

if os.path.isfile('files.txt'):
	os.remove('files.txt')

if os.path.isfile('log.txt'):
	os.remove('log.txt')
