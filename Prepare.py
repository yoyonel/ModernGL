import os, shutil

if not os.path.isdir('Bin'):
	os.mkdir('Bin')

if not os.path.isdir('Temp'):
	os.mkdir('Temp')

shutil.copyfile('libOpenGL.a/Bin/libOpenGL.a', 'Temp/libOpenGL.a')
shutil.copyfile('libOpenGL.a/Bin/OpenGL.h', 'Temp/OpenGL.h')
shutil.copyfile('libOpenGL.a/Bin/WindowsGL.h', 'Temp/WindowsGL.h')

open('Temp/prepare', 'w').write('done')
