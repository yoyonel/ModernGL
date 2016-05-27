#include <Windows.h>
#include <cstdio>

#include <WindowsGL.h>

#include "ModernGL.h"

HGLRC hglrc;
HWND hwnd;
HDC hdc;

PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),	// nSize
	1,								// nVersion
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_GENERIC_ACCELERATED |
	PFD_DOUBLEBUFFER,				// dwFlags
	0,								// iPixelType
	32,								// cColorBits
	0,								// cRedBits
	0,								// cRedShift
	0,								// cGreenBits
	0,								// cGreenShift
	0,								// cBlueBits
	0,								// cBlueShift
	0,								// cAlphaBits
	0,								// cAlphaShift
	0,								// cAccumBits
	0,								// cAccumRedBits
	0,								// cAccumGreenBits
	0,								// cAccumBlueBits
	0,								// cAccumAlphaBits
	32,								// cDepthBits
	0,								// cStencilBits
	0,								// cAuxBuffers
	0,								// iLayerType
	0,								// bReserved
	0,								// dwLayerMask
	0,								// dwVisibleMask
	0								// dwDamageMask
};

bool CreateGLContext(int major, int minor) {
	if (!WindowsGL::InitializeWindowsGL()) {
		printf("Code: 1\n");
		return false;
	}

	HMODULE hinst = GetModuleHandle(0);

	if (!hinst) {
		printf("Code: 2\n");
		return false;
	}

	WNDCLASS wndClass = {
		CS_OWNDC,						// style
		DefWindowProc,					// lpfnWndProc
		0,								// cbClsExtra
		0,								// cbWndExtra
		hinst,							// hInstance
		0,								// hIcon
		LoadCursor(0, IDC_ARROW),		// hCursor
		0,								// hbrBackground
		0,								// lpszMenuName
		"OpenGL",						// lpszClassName
	};

	if (!RegisterClass(&wndClass)) {
		printf("Code: 3\n");
		return false;
	}

	hwnd = CreateWindowEx(
		0,
		"OpenGL",						// lpClassName
		0,								// lpWindowName
		WS_POPUP,						// dwStyle
		0,								// x
		0,								// y
		0,								// nWidth
		0,								// nHeight
		0,								// hWndParent
		0,								// hMenu
		hinst,							// hInstance
		0								// lpParam
	);

	if (!hwnd) {
		printf("Code: 4\n");
		return false;
	}

	hdc = GetDC(hwnd);

	if (!hdc) {
		printf("Code: 5\n");
		return false;
	}

	int pixelformat = 0;
	int samples = 2;

	while (true) {
		int attributes[] = {
			WindowsGL::WGL_SUPPORT_OPENGL, 1,
			WindowsGL::WGL_DRAW_TO_WINDOW, 1,
			WindowsGL::WGL_DOUBLE_BUFFER, 1,
			WindowsGL::WGL_ACCELERATION, WindowsGL::WGL_FULL_ACCELERATION,
			WindowsGL::WGL_PIXEL_TYPE, WindowsGL::WGL_TYPE_RGBA,
			WindowsGL::WGL_COLOR_BITS, 24,
			WindowsGL::WGL_DEPTH_BITS, 24,
			WindowsGL::WGL_SAMPLES, samples,
			0, 0,
		};

		unsigned numFormats = 0;

		if (!WindowsGL::wglChoosePixelFormat(hdc, attributes, 0, 1, &pixelformat, &numFormats)) {
			printf("Code: 6\n");
			return false;
		}
		if (numFormats) {
			break;
		}
		if (!samples) {
			printf("Code: 7\n");
			return false;
		}
		samples /= 2;
	}

	if (!WindowsGL::SetPixelFormat(hdc, pixelformat, &pfd)) {
		return false;
	}

	int attriblist[] = {
		WindowsGL::WGL_CONTEXT_MAJOR_VERSION, major,
		WindowsGL::WGL_CONTEXT_MINOR_VERSION, minor,
		0, 0,
	};

	hglrc = WindowsGL::wglCreateContextAttribs(hdc, 0, attriblist);

	if (!hglrc) {
		return false;
	}

	if (!WindowsGL::wglMakeCurrent(hdc, hglrc)) {
		return false;
	}

	return true;
}

int main() {
	if (!CreateGLContext(3, 3)) {
		printf("Cannot Create GL Context.\n");
		return 1;
	}

	if (!ModernGL::InitializeModernGL()) {
		printf("InitializeModernGL failed.\n");
		return 1;
	}

	printf("TEST PASSED.\n");
	return 0;
}
