INC = "c:\Program Files (x86)\Python35-32\include"
DLL = "c:\Program Files (x86)\Python35-32\python35.dll"

all:
	g++ -shared -m32 -std=c++11 -O3 -I $(INC) GLContext.cpp -lgdi32 -lopengl32 $(DLL) -o GLContext.pyd

Run:
