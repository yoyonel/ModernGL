import shutil, os

if not os.path.isdir('Bin'):
	os.mkdir('Bin')
	
if not os.path.isdir('Temp'):
	os.mkdir('Temp')

if not os.path.isdir('Build'):
	os.mkdir('Build')

if not os.path.isdir('Dist'):
	os.mkdir('Dist')
