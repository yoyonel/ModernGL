#define Debug //

#include <Windows.h>
#include <cstring>
#include <cstdio>

typedef void * __stdcall (* wglGetProcAddressImplementationProc) (const char *);
typedef void * __stdcall (* wglGetCurrentContextImplementationProc) ();

wglGetProcAddressImplementationProc wglGetProcAddressImplementation;
wglGetCurrentContextImplementationProc wglGetCurrentContextImplementation;

HMODULE opengl32;

const void * wglGetProcFromModule(const char * name) {
	return (const void *)GetProcAddress(opengl32, name);
}

const void * wglGetProcFromExtension(const char * name) {
	return (const void *)wglGetProcAddressImplementation(name);
}

extern bool LoadCoreGL() asm("_LoadCoreGL");
extern const void * wglGetProcAuto(const char * name) asm("_wglGetProcAuto");
extern int wglNotImplementedSafe(const char * name, ...) asm("_wglNotImplementedSafe");
extern int wglNotImplemented() asm("_wglNotImplemented");

int wglNotImplementedSafe(const char * name, ...) {
	MessageBox(0, name, "Not Implemented!", 0);
	return 0;
}

int wglNotImplemented() {
	return 0;
}

const void * wglGetProcAuto(const char * name) {
	const void * result = wglGetProcFromModule(name);
	if (result) {
		return result;
	}

	result = wglGetProcFromExtension(name);
	if (result) {
		return result;
	}

	int length = strlen(name);
	char * guess = (char *)malloc(length + 4);
	memcpy(guess, name, length);

	guess[length + 0] = 'A';
	guess[length + 1] = 'R';
	guess[length + 2] = 'B';
	guess[length + 3] = 0;

	result = wglGetProcFromExtension(guess);
	if (result) {
		free(guess);
		return result;
	}

	guess[length + 0] = 'E';
	guess[length + 1] = 'X';
	guess[length + 2] = 'T';
	guess[length + 3] = 0;

	result = wglGetProcFromExtension(guess);
	if (result) {
		free(guess);
		return result;
	}

	free(guess);
	return(0);
}

bool LoadOpenGL32() {
	opengl32 = LoadLibrary("opengl32.dll");
	
	if (!opengl32) {
		Debug("!opengl32");
		return false;
	}

	wglGetProcAddressImplementation = (wglGetProcAddressImplementationProc)GetProcAddress(opengl32, "wglGetProcAddress");
	if (!wglGetProcAddressImplementation) {
		Debug("!wglGetProcAddressImplementation");
		return false;
	}

	wglGetCurrentContextImplementation = (wglGetCurrentContextImplementationProc)GetProcAddress(opengl32, "wglGetCurrentContext");
	if (!wglGetCurrentContextImplementation) {
		Debug("!wglGetCurrentContextImplementation");
		return false;
	}

	if (!wglGetCurrentContextImplementation()) {
		Debug("!wglGetCurrentContextImplementation()");
		return false;
	}

	return true;
}

extern "C" {
	bool Initialize();
}

bool Initialize() {
	if (!LoadOpenGL32()) {
		Debug("!LoadOpenGL32()");
		return false;
	}

	if (!LoadCoreGL()) {
		Debug("!LoadCoreGL()");
		return false;
	}

	return true;
}
