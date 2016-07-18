open('Makefile', 'w').write('''
all: clean install

clean:
	python Clean.py

install:
	install.bat
'''.strip())

open('Source/Makefile', 'w').write('''
all:
	cd .. && make
'''.strip())

open('multi_install.bat', 'w').write('''
call python Clean.py
SET CUSTOM_GCC=YES
call pythons.bat setup.py install
'''.strip())

open('multi_upload.bat', 'w').write('''
SET CUSTOM_GCC=YES
call python setup.py sdist upload 
call pythons setup.py bdist_wheel upload
call pythons setup.py bdist_egg upload
call pythons setup.py bdist_wininst upload
'''.strip())

open('install.bat', 'w').write('call python setup.py install --record files.txt')
