all: clean prepare Bin/ModernGL.dll

clean: Clean.py
	python Clean.py

prepare: Prepare.py
	python Prepare.py

Bin/ModernGL.dll: Source/ModernGL.cpp Source/OpenGL.cpp Source/WindowsGL.cpp Source/ModernGL.hpp Source/OpenGL.hpp Source/WindowsGL.hpp
	g++ -shared Source/ModernGL.cpp Source/OpenGL.cpp Source/WindowsGL.cpp -lgdi32 -o Bin/ModernGL.dll

Run:
