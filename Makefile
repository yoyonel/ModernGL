A32 = nasm -f win32
A64 = nasm -f win64

C32 = g++ -std=c++11 -I Temp
C64 = x64_g++ -std=c++11 -I Temp

L32 = g++ -O3
L64 = x64_g++ -O3

PY = python
MK = make

all: clean ModernGL32 ModernGL64

ModernGL32:
	$(MK) Bin\ModernGL32.dll

ModernGL64:
	$(MK) Bin\ModernGL64.dll

Bin\ModernGL32.dll: prepare Temp\OpenGL32-cpp.o Temp\OpenGL32-asm.o Temp\ModernGL32.o Source\ModernGL.def
	$(L32) -shared Temp\OpenGL32-cpp.o Temp\OpenGL32-asm.o Temp\ModernGL32.o Source\ModernGL.def -o Bin\ModernGL32.dll

Temp\OpenGL32.asm: prepare Data\OpenGL.json
	$(PY) Source\OpenGL.py asm32

Temp\ModernGL32.o: prepare Source\ModernGL.cpp Source\ModernGL.h Temp\OpenGL.h Temp\DroidSansMono.h
	$(C32) -c Source\ModernGL.cpp -o Temp\ModernGL32.o

Temp\OpenGL32-asm.o: prepare Temp\OpenGL32.asm
	$(A32) Temp\OpenGL32.asm -o Temp\OpenGL32-asm.o

Temp\OpenGL32-cpp.o: prepare Source\OpenGL.cpp Temp\OpenGL.h
	$(C32) -c Source\OpenGL.cpp -o Temp\OpenGL32-cpp.o

Bin\ModernGL64.dll: prepare Temp\OpenGL64-cpp.o Temp\OpenGL64-asm.o Temp\ModernGL64.o Source\ModernGL.def
	$(L64) -shared Temp\OpenGL64-cpp.o Temp\OpenGL64-asm.o Temp\ModernGL64.o Source\ModernGL.def -o Bin\ModernGL64.dll

Temp\OpenGL64.asm: prepare Data\OpenGL.json Source\OpenGL.py
	$(PY) Source\OpenGL.py asm64

Temp\ModernGL64.o: prepare Source\ModernGL.cpp Source\ModernGL.h Temp\OpenGL.h Temp\DroidSansMono.h
	$(C64) -c Source\ModernGL.cpp -o Temp\ModernGL64.o

Temp\OpenGL64-asm.o: prepare Temp\OpenGL64.asm
	$(A64) Temp\OpenGL64.asm -o Temp\OpenGL64-asm.o

Temp\OpenGL64-cpp.o: prepare Source\OpenGL.cpp Temp\OpenGL.h
	$(C64) -c Source\OpenGL.cpp -o Temp\OpenGL64-cpp.o

Temp\DroidSansMono.h: prepare Source\OpenGL.py
	$(PY) Source\Font.py > Temp\DroidSansMono.h

Temp\OpenGL.h: prepare Data\OpenGL.json Source\OpenGL.py
	$(PY) Source\OpenGL.py header

prepare:
	$(PY) Prepare.py

clean:
	$(PY) Clear.py

Run: