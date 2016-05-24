import os, shutil

shutil.copyfile('Source/ModernGL.h', 'Bin/ModernGL.h')
shutil.copyfile('Source/ModernGL.h', 'Bin/ModernGL')
shutil.copyfile('Temp/libOpenGL.a', 'Bin/libOpenGL.a')

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
