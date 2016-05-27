import os, shutil

shutil.copyfile('Source/ModernGL.h', 'Bin/ModernGL.h')
shutil.copyfile('Source/ModernGL.h', 'Bin/ModernGL')
shutil.copyfile('Temp/libOpenGL.a', 'Bin/libOpenGL.a')

if not os.path.isdir('Bin/Source'):
	os.mkdir('Bin/Source')

shutil.copyfile('Source/ModernGL.h', 'Bin/Source/ModernGL.h')
shutil.copyfile('Source/ModernGL.cpp', 'Bin/Source/ModernGL.cpp')
shutil.copyfile('libOpenGL.a/Bin/WindowsGL.h', 'Bin/Source/WindowsGL.h')
shutil.copyfile('libOpenGL.a/Bin/WindowsGL.cpp', 'Bin/Source/WindowsGL.cpp')
shutil.copyfile('libOpenGL.a/Bin/OpenGL.h', 'Bin/Source/OpenGL.h')
shutil.copyfile('libOpenGL.a/Bin/OpenGL.cpp', 'Bin/Source/OpenGL.cpp')

import zipfile

packet = zipfile.ZipFile('Bin/Release.zip', 'w')
packet.write('Bin/libModernGL.a', 'ModernGL/lib/libModernGL.a')
packet.write('Bin/libOpenGL.a', 'ModernGL/lib/libOpenGL.a')
packet.write('Bin/ModernGL.dll', 'ModernGL/bin/ModernGL.dll')
packet.write('Bin/ModernGL.h', 'ModernGL/include/ModernGL.h')
packet.write('Bin/ModernGL', 'ModernGL/include/ModernGL')
packet.write('README.md', 'ModernGL/README.md')
packet.write('LICENSE', 'ModernGL/LICENSE')

open('Temp/finish', 'w').write('done')
