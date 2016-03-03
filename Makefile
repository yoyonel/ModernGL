ASM = nasm -f win32
CXX = g++ -std=c++11 -I Temp
LNK = g++ -O3
PY = python
MK = make

all:
	$(PY) Prepare.py
	$(MK) Bin\ModernGL.dll

Bin\ModernGL.dll: Temp\OpenGL-cpp.o Temp\OpenGL-asm.o Temp\ModernGL.o
	$(LNK) -shared Temp\OpenGL-cpp.o Temp\OpenGL-asm.o Temp\ModernGL.o -o Bin\ModernGL.dll

Temp\DroidSansMono.h:
	$(PY) Font.py

Temp\OpenGL.h: OpenGL.json
	$(PY) OpenGL.py header

Temp\OpenGL.asm: OpenGL.json
	$(PY) OpenGL.py asm

Temp\ModernGL.o: ModernGL.cpp ModernGL.h Temp\OpenGL.h Temp\DroidSansMono.h
	$(CXX) -c ModernGL.cpp -o Temp\ModernGL.o

Temp\OpenGL-asm.o: Temp\OpenGL.asm
	$(ASM) Temp\OpenGL.asm -o Temp\OpenGL-asm.o

Temp\OpenGL-cpp.o: OpenGL.cpp
	$(CXX) -c OpenGL.cpp -o Temp\OpenGL-cpp.o

clean:
	$(PY) Clear.py
