BITS ?= 32

GIT = git
ASM = nasm
CXX = g++
AR = ar
PY = python
MK = make

CXX += -m$(BITS)
ASM += -f win$(BITS)

COMPILE = $(CXX) -std=c++11 -I Temp -c
LINK = $(CXX) -O3

all: Temp/prepare Bin/ModernGL.dll Bin/libModernGL.a Temp/finish

test: Temp/prepare Bin/Test.exe
	Bin/Test.exe

clean:
	$(PY) Clean.py
	cd libOpenGL.a && $(MK) clean

libOpenGL.a/Makefile:
	$(GIT) submodule init
	$(GIT) submodule update

libOpenGL.a/Temp/finish: libOpenGL.a/Makefile
	cd libOpenGL.a && $(MK) MAJOR=3 MINOR=3

Bin/ModernGL.dll: Temp/prepare Temp/libOpenGL.a Temp/ModernGL.o
	$(LINK) -shared Temp/ModernGL.o Temp/libOpenGL.a -o Bin/ModernGL.dll

Bin/libModernGL.a: Temp/prepare Temp/libOpenGL.a Temp/ModernGL.o
	$(AR) rcs Bin/libModernGL.a Temp/ModernGL.o

Bin/Test.exe: Temp/prepare Temp/Test.o Bin/libModernGL.a
	$(LINK) Temp/Test.o Bin/libModernGL.a Temp/libOpenGL.a -o Bin/Test.exe

Temp/Test.o: Temp/prepare Source/Test.cpp
	$(COMPILE) Source/Test.cpp -o Temp/Test.o

Temp/ModernGL.o: Temp/prepare Source/ModernGL.cpp Source/ModernGL.h Temp/OpenGL.h
	$(COMPILE) Source/ModernGL.cpp -o Temp/ModernGL.o

Temp/prepare: libOpenGL.a/Temp/finish
	$(PY) Prepare.py

Temp/finish:
	$(PY) Finish.py
