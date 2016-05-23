BITS ?= 32

ASM = nasm
CXX = g++
AR = ar
PY = python
MK = make

CXX += -m$(BITS)
ASM += -f win$(BITS)

COMPILE = $(CXX) -std=c++11 -I Temp -c
LINK = $(CXX) -O3

all: submodules ModernGL

submodules:
	cd libOpenGL.a && $(MK) MAJOR=3 MINOR=3

ModernGL: prepare Bin/ModernGL.dll Bin/libModernGL.a finish

Bin/ModernGL.dll: Temp/libOpenGL.a Temp/ModernGL.o
	$(LINK) -shared Temp/ModernGL.o Temp/libOpenGL.a -o Bin/ModernGL.dll

Bin/libModernGL.a: Temp/libOpenGL.a Temp/ModernGL.o
	$(AR) rcs Bin/libModernGL.a Temp/ModernGL.o

Temp/ModernGL.o: Source/ModernGL.cpp Source/ModernGL.h Temp/OpenGL.h
	$(COMPILE) Source/ModernGL.cpp -o Temp/ModernGL.o

Temp/libOpenGL.a: # submodules
	$(PY) -c "import shutil; shutil.copyfile('libOpenGL.a/Bin/libOpenGL.a', 'Temp/libOpenGL.a')"

Temp/OpenGL.h: # submodules
	$(PY) -c "import shutil; shutil.copyfile('libOpenGL.a/Bin/OpenGL.h', 'Temp/OpenGL.h')"

clean:
	$(PY) Clean.py

finish:
	$(PY) Finish.py

prepare:
	$(PY) Prepare.py

Run:
