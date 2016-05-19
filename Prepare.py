import os, shutil

if not os.path.isdir('Bin'):
	os.mkdir('Bin')

if not os.path.isdir('Temp'):
	os.mkdir('Temp')

shutil.copyfile('Source\\ModernGL.h', 'Bin\\ModernGL.h')
shutil.copyfile('Source\\ModernGL.h', 'Bin\\ModernGL')
