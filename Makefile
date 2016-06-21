all:
	g++ -std=c++11 -shared -m32 Source/ModernGL.cpp Source/OpenGL.cpp Source/WindowsGL.cpp -lgdi32 -o Test.dll