#include "Context.hpp"
#include "Buffer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"
#include "Object.hpp"
#include "InvalidObject.hpp"
#include "Primitive.hpp"
#include "Uniform.hpp"
#include "BufferAccess.hpp"
#include "EnableFlag.hpp"

#include <Python.h>
#include <Windows.h>

MGLContext * create_standalone_context(PyObject * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"size", 0};

	int width = 256;
	int height = 256;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|(II)",
		(char **)kwlist,
		&width,
		&height
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	/*

	HDC dc = CreateCompatibleDC(0);

	// printf("dc = %p\n", dc);
	// printf("GetLastError = %d\n", GetLastError());

	if (!dc) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	unsigned char pixel_bits = 24; // TODO: alpha not rendered (remains 0x00)

	BITMAPINFO info = {
		{
			sizeof(BITMAPINFOHEADER),   // DWORD biSize;
			width,                      // LONG biWidth;
			height,                     // LONG biHeight;
			1,                          // WORD biPlanes;
			pixel_bits,                 // WORD biBitCount;
			BI_RGB,                     // DWORD biCompression;
			0,                          // DWORD biSizeImage;
			0,                          // LONG biXPelsPerMeter;
			0,                          // LONG biYPelsPerMeter;
			0,                          // DWORD biClrUsed;
			0,                          // DWORD biClrImportant;
		}
	};

	void * bits;
	HBITMAP bitmap = CreateDIBSection(dc, &info, DIB_RGB_COLORS, &bits, 0, 0);

	// printf("bitmap = %p\n", bitmap);
	// printf("GetLastError = %d\n", GetLastError());

	if (!bitmap) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	void * select_object = SelectObject(dc, bitmap);

	// printf("select_object = %p\n", select_object);
	// printf("GetLastError = %d\n", GetLastError());

	if (!select_object) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	*/

	// TODO: clean

	HINSTANCE inst = GetModuleHandle(0);

	static bool registered = false;

	if (!registered) {
		WNDCLASS wndClass = {
			CS_OWNDC,                            // style
			DefWindowProc,                       // lpfnWndProc
			0,                                   // cbClsExtra
			0,                                   // cbWndExtra
			inst,                                // hInstance
			0,                                   // hIcon
			0,                                   // hCursor
			0,                                   // hbrBackground
			0,                                   // lpszMenuName
			"standalone_context_class",          // lpszClassName
		};

		if (!RegisterClass(&wndClass)) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		registered = true;
	}

	HWND hwnd = CreateWindowEx(
		0,                                   // exStyle
		"standalone_context_class",          // lpClassName
		0,                                   // lpWindowName
		0,                                   // dwStyle
		0,                                   // x
		0,                                   // y
		0,                                   // nWidth
		0,                                   // nHeight
		0,                                   // hWndParent
		0,                                   // hMenu
		inst,                                // hInstance
		0                                    // lpParam
	);

	if (!hwnd) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	HDC dc = GetDC(hwnd);

	if (!dc) {
		return 0;
	}

	BYTE pixel_bits = 32;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // nSize
		1,                               // nVersion
		// PFD_DOUBLEBUFFER |
		// PFD_DRAW_TO_WINDOW |
		PFD_GENERIC_ACCELERATED |
		// PFD_SUPPORT_GDI |
		// PFD_DRAW_TO_BITMAP |
		PFD_SUPPORT_OPENGL,              // dwFlags
		PFD_TYPE_RGBA,                   // iPixelType
		pixel_bits,                      // cColorBits
		0,                               // cRedBits
		0,                               // cRedShift
		0,                               // cGreenBits
		0,                               // cGreenShift
		0,                               // cBlueBits
		0,                               // cBlueShift
		0,                               // cAlphaBits
		0,                               // cAlphaShift
		0,                               // cAccumBits
		0,                               // cAccumRedBits
		0,                               // cAccumGreenBits
		0,                               // cAccumBlueBits
		0,                               // cAccumAlphaBits
		24,                              // cDepthBits
		0,                               // cStencilBits
		0,                               // cAuxBuffers
		0,                               // iLayerType
		0,                               // bReserved
		0,                               // dwLayerMask
		0,                               // dwVisibleMask
		0,                               // dwDamageMask
	};

	int pf = ChoosePixelFormat(dc, &pfd);

	// printf("pf = %p\n", pf);
	// printf("GetLastError = %d\n", GetLastError());

	if (!pf) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	int set_pixel_format = SetPixelFormat(dc, pf, &pfd);

	// printf("set_pixel_format = %p\n", set_pixel_format);
	// printf("GetLastError = %d\n", GetLastError());

	if (!set_pixel_format) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	HGLRC rc = wglCreateContext(dc);

	// printf("rc = %p\n", rc);
	// printf("GetLastError = %d\n", GetLastError());

	if (!rc) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	int make_current = wglMakeCurrent(dc, rc);

	// printf("make_current = %p\n", make_current);
	// printf("GetLastError = %d\n", GetLastError());

	if (!make_current) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	MGLContext * ctx = MGLContext_New();

	// TODO: fill data

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ctx;
}

const char * create_standalone_context_doc = R"(
)";

MGLContext * create_context(PyObject * self) {
	MGLContext * ctx = MGLContext_New();

	ctx->rc_handle = oglGetCurrentContext();
	ctx->dc_handle = oglGetCurrentDC();

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ctx;
}

const char * create_context_doc = R"(
)";

PyMethodDef MGL_module_methods[] = {
	{"create_standalone_context", (PyCFunction)create_standalone_context, METH_VARARGS | METH_KEYWORDS, create_standalone_context_doc},
	{"create_context", (PyCFunction)create_context, METH_VARARGS | METH_KEYWORDS, create_context_doc},
	{0},
};

const char * MGL_module_doc = R"(
)";

PyModuleDef MGL_moduledef = {
	PyModuleDef_HEAD_INIT,
	"ModernGL",
	MGL_module_doc,
	-1,
	MGL_module_methods,
	0,
	0,
	0,
	0,
};

extern "C" PyObject * PyInit_ModernGL() {
	PyObject * module = PyModule_Create(&MGL_moduledef);

	{
		if (PyType_Ready(&MGLObject_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Object in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLObject_Type);

		PyModule_AddObject(module, "Object", (PyObject *)&MGLObject_Type);
	}

	{
		if (PyType_Ready(&MGLContext_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Context in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLContext_Type);

		PyModule_AddObject(module, "Context", (PyObject *)&MGLContext_Type);
	}

	{
		if (PyType_Ready(&MGLContextMember_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register ContextMember in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLContextMember_Type);

		PyModule_AddObject(module, "ContextMember", (PyObject *)&MGLContextMember_Type);
	}

	{
		if (PyType_Ready(&MGLBuffer_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Buffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLBuffer_Type);

		PyModule_AddObject(module, "Buffer", (PyObject *)&MGLBuffer_Type);
	}

	{
		if (PyType_Ready(&MGLTexture_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Texture in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLTexture_Type);

		PyModule_AddObject(module, "Texture", (PyObject *)&MGLTexture_Type);
	}

	{
		if (PyType_Ready(&MGLVertexArray_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register VertexArray in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLVertexArray_Type);

		PyModule_AddObject(module, "VertexArray", (PyObject *)&MGLVertexArray_Type);
	}

	{
		if (PyType_Ready(&MGLProgram_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Program in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLProgram_Type);

		PyModule_AddObject(module, "Program", (PyObject *)&MGLProgram_Type);
	}

	{
		if (PyType_Ready(&MGLShader_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Shader in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLShader_Type);

		PyModule_AddObject(module, "Shader", (PyObject *)&MGLShader_Type);
	}

	{
		if (PyType_Ready(&MGLFramebuffer_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Framebuffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLFramebuffer_Type);

		PyModule_AddObject(module, "Framebuffer", (PyObject *)&MGLFramebuffer_Type);
	}

	{
		if (PyType_Ready(&MGLInvalidObject_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register InvalidObject in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLInvalidObject_Type);

		PyModule_AddObject(module, "InvalidObject", (PyObject *)&MGLInvalidObject_Type);
	}

	{
		if (PyType_Ready(&MGLPrimitive_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Primitive in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLPrimitive_Type);

		PyModule_AddObject(module, "Primitive", (PyObject *)&MGLPrimitive_Type);
	}

	{
		if (PyType_Ready(&MGLUniform_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Uniform in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLUniform_Type);

		PyModule_AddObject(module, "Uniform", (PyObject *)&MGLUniform_Type);
	}

	{
		if (PyType_Ready(&MGLBufferAccess_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register BufferAccess in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLBufferAccess_Type);

		PyModule_AddObject(module, "BufferAccess", (PyObject *)&MGLBufferAccess_Type);
	}

	{
		if (PyType_Ready(&MGLEnableFlag_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register EnableFlag in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLEnableFlag_Type);

		PyModule_AddObject(module, "EnableFlag", (PyObject *)&MGLEnableFlag_Type);
	}

	{
		MGLPrimitive * TRIANGLES = MGLPrimitive_New();
		TRIANGLES->name = "TRIANGLES";
		TRIANGLES->primitive = GL_TRIANGLES;
		TRIANGLES->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES", (PyObject *)TRIANGLES);

		MGLPrimitive * TRIANGLE_STRIP = MGLPrimitive_New();
		TRIANGLE_STRIP->name = "TRIANGLE_STRIP";
		TRIANGLE_STRIP->primitive = GL_TRIANGLE_STRIP;
		TRIANGLE_STRIP->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP", (PyObject *)TRIANGLE_STRIP);

		MGLPrimitive * TRIANGLE_FAN = MGLPrimitive_New();
		TRIANGLE_FAN->name = "TRIANGLE_FAN";
		TRIANGLE_FAN->primitive = GL_TRIANGLE_FAN;
		TRIANGLE_FAN->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_FAN", (PyObject *)TRIANGLE_FAN);

		MGLPrimitive * LINES = MGLPrimitive_New();
		LINES->name = "LINES";
		LINES->primitive = GL_LINES;
		LINES->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES", (PyObject *)LINES);

		MGLPrimitive * LINE_STRIP = MGLPrimitive_New();
		LINE_STRIP->name = "LINE_STRIP";
		LINE_STRIP->primitive = GL_LINE_STRIP;
		LINE_STRIP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP", (PyObject *)LINE_STRIP);

		MGLPrimitive * LINE_LOOP = MGLPrimitive_New();
		LINE_LOOP->name = "LINE_LOOP";
		LINE_LOOP->primitive = GL_LINE_LOOP;
		LINE_LOOP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_LOOP", (PyObject *)LINE_LOOP);

		MGLPrimitive * POINTS = MGLPrimitive_New();
		POINTS->name = "POINTS";
		POINTS->primitive = GL_POINTS;
		POINTS->transform_primitive = GL_POINTS;
		PyModule_AddObject(module, "POINTS", (PyObject *)POINTS);

		MGLPrimitive * LINE_STRIP_ADJACENCY = MGLPrimitive_New();
		LINE_STRIP_ADJACENCY->name = "LINE_STRIP_ADJACENCY";
		LINE_STRIP_ADJACENCY->primitive = GL_LINE_STRIP_ADJACENCY;
		LINE_STRIP_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP_ADJACENCY", (PyObject *)LINE_STRIP_ADJACENCY);

		MGLPrimitive * LINES_ADJACENCY = MGLPrimitive_New();
		LINES_ADJACENCY->name = "LINES_ADJACENCY";
		LINES_ADJACENCY->primitive = GL_LINES_ADJACENCY;
		LINES_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES_ADJACENCY", (PyObject *)LINES_ADJACENCY);

		MGLPrimitive * TRIANGLE_STRIP_ADJACENCY = MGLPrimitive_New();
		TRIANGLE_STRIP_ADJACENCY->name = "TRIANGLE_STRIP_ADJACENCY";
		TRIANGLE_STRIP_ADJACENCY->primitive = GL_TRIANGLE_STRIP_ADJACENCY;
		TRIANGLE_STRIP_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP_ADJACENCY", (PyObject *)TRIANGLE_STRIP_ADJACENCY);

		MGLPrimitive * TRIANGLES_ADJACENCY = MGLPrimitive_New();
		TRIANGLES_ADJACENCY->name = "TRIANGLES_ADJACENCY";
		TRIANGLES_ADJACENCY->primitive = GL_TRIANGLES_ADJACENCY;
		TRIANGLES_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES_ADJACENCY", (PyObject *)TRIANGLES_ADJACENCY);
	}

	{
		MGLEnableFlag * BLEND = MGLEnableFlag_New();
		BLEND->name = "BLEND";
		BLEND->flag = GL_BLEND;
		PyModule_AddObject(module, "BLEND", (PyObject *)BLEND);
	}

	return module;
}
