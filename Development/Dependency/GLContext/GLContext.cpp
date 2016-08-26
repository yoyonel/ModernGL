#include "Python.h"

#include <Windows.h>
#include <cstdio>

PIXELFORMATDESCRIPTOR pfd = {
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	24,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	32,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
};

HDC loader_hdc;
HGLRC loader_hglrc;
bool set = false;

PyObject * Context(PyObject * self, PyObject * args) {
	bool on;
	if (!PyArg_ParseTuple(args, "p:Context", &on)) {
		return 0;
	}
	if (set != on) {
		if (on) {
			if (!wglMakeCurrent(loader_hdc, loader_hglrc)) {
				PyErr_SetString(PyExc_Exception, "wglMakeCurrent failed.");
				return 0;
			}
		} else {
			if (!wglMakeCurrent(0, 0)) {
				PyErr_SetString(PyExc_Exception, "wglMakeCurrent failed.");
				return 0;
			}
		}
		set = on;
	}
	Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
	{"Context", Context, METH_VARARGS, 0},
	{0, 0, 0, 0},
};

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "GLContext", 0, -1, methods, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_GLContext();
}

PyObject * PyInit_GLContext() {

	HMODULE hinst = GetModuleHandle(0);

	if (!hinst) {
		PyErr_SetString(PyExc_Exception, "GetModuleHandle failed.");
		return 0;
	}

	WNDCLASS extClass = {
		CS_OWNDC,						// style
		DefWindowProc,					// lpfnWndProc
		0,								// cbClsExtra
		0,								// cbWndExtra
		hinst,							// hInstance
		0,								// hIcon
		0,								// hCursor
		0,								// hbrBackground
		0,								// lpszMenuName
		"ExtOpenGL",					// lpszClassName
	};

	if (!RegisterClass(&extClass)) {
		PyErr_SetString(PyExc_Exception, "RegisterClass failed.");
		return 0;
	}

	HWND loader_hwnd = CreateWindowEx(
		0,
		"ExtOpenGL",					// lpClassName
		0,								// lpWindowName
		0,								// dwStyle
		0,								// x
		0,								// y
		0,								// nWidth
		0,								// nHeight
		0,								// hWndParent
		0,								// hMenu
		hinst,							// hInstance
		0								// lpParam
	);

	if (!loader_hwnd) {
		PyErr_SetString(PyExc_Exception, "CreateWindowEx failed.");
		return 0;
	}

	loader_hdc = GetDC(loader_hwnd);

	if (!loader_hdc) {
		PyErr_SetString(PyExc_Exception, "GetDC failed.");
		return 0;
	}

	int loader_pixelformat = ChoosePixelFormat(loader_hdc, &pfd);

	if (!loader_pixelformat) {
		PyErr_SetString(PyExc_Exception, "ChoosePixelFormat failed.");
		return 0;
	}

	if (!SetPixelFormat(loader_hdc, loader_pixelformat, &pfd)) {
		PyErr_SetString(PyExc_Exception, "SetPixelFormat failed.");
		return 0;
	}

	loader_hglrc = wglCreateContext(loader_hdc);

	if (!loader_hglrc) {
		PyErr_SetString(PyExc_Exception, "wglCreateContext failed.");
		return 0;
	}

	return PyModule_Create(&moduledef);
}
