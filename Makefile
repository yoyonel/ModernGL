A32 = nasm -f win32
A64 = nasm -f win64

C32 = g++ -std=c++11 -I Temp
C64 = x64_g++ -std=c++11 -I Temp

L32 = g++ -O3
L64 = x64_g++ -O3

AR32 = ar
AR64 = x64_ar

PY = python
MK = make

all: clean ModernGL32 # ModernGL64

ModernGL32:
	$(MK) Bin\ModernGL32.dll
#	$(MK) Bin\libModernGL32.a

Bin\ModernGL32.dll: prepare Temp\libOpenGL.a Temp\ModernGL32.o
	$(L32) -shared Temp\ModernGL32.o Temp\libOpenGL.a -o Bin\ModernGL32.dll

# Bin\libModernGL32.a: prepare Temp\libOpenGL.a Temp\ModernGL32.o
#	$(AR32) rcs Bin\libModernGL32.a Temp\ModernGL32.o Temp\libOpenGL.a

Temp\ModernGL32.o: prepare Source\ModernGL.cpp Source\ModernGL.h Temp\OpenGL.h
	$(C32) -c Source\ModernGL.cpp -o Temp\ModernGL32.o

build-libOpenGL.a:
	cd libOpenGL.a && make MAJOR=3 MINOR=3

Temp\libOpenGL.a: build-libOpenGL.a
	python -c "import shutil; shutil.copyfile('libOpenGL.a/Bin/x86/libOpenGL.a', 'Temp/libOpenGL.a')"

Temp\OpenGL.h: build-libOpenGL.a
	python -c "import shutil; shutil.copyfile('libOpenGL.a/Bin/x86/OpenGL.h', 'Temp/OpenGL.h')"


prepare:
	$(PY) Prepare.py

clean:
	$(PY) Clear.py

Run: