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
#include "Attribute.hpp"
#include "Varying.hpp"
#include "Subroutine.hpp"
#include "BufferAccess.hpp"
#include "EnableFlag.hpp"
#include "Version.hpp"

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

	unsigned char pixel_bits = 24; // alpha not rendered (remains 0x00)

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

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ctx;
}

const char * create_standalone_context_doc = R"(
	create_standalone_context(size)

	Extended description of function.

	Keyword Arguments:
		require (version): OpenGL version

	Returns:
		~ModernGL.Context: ....
)";

MGLContext * create_context(PyObject * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"require", 0};

	MGLVersion * require = (MGLVersion *)Py_None;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|$O!",
		(char **)kwlist,
		&MGLVersion_Type,
		&require
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	MGLContext * ctx = MGLContext_New();

	ctx->rc_handle = wglGetCurrentContext();
	ctx->dc_handle = wglGetCurrentDC();

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ctx;
}

const char * create_context_doc = R"(
	create_context(size)

	Extended description of function.

	Keyword Arguments:
		require (version): OpenGL version

	Returns:
		~ModernGL.Context: ....
)";

PyMethodDef MGL_module_methods[] = {
	{"create_standalone_context", (PyCFunction)create_standalone_context, METH_VARARGS | METH_KEYWORDS, create_standalone_context_doc},
	{"create_context", (PyCFunction)create_context, METH_VARARGS | METH_KEYWORDS, create_context_doc},
	{0},
};

const char * MGL_module_doc = R"(
	ModernGL
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
		if (PyType_Ready(&MGLProgramMember_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register ProgramMember in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLProgramMember_Type);

		PyModule_AddObject(module, "ProgramMember", (PyObject *)&MGLProgramMember_Type);
	}

	{
		if (PyType_Ready(&MGLVersion_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Version in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLVersion_Type);

		PyModule_AddObject(module, "Version", (PyObject *)&MGLVersion_Type);
	}

	{
		if (PyType_Ready(&MGLAttribute_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Attribute in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLAttribute_Type);

		PyModule_AddObject(module, "Attribute", (PyObject *)&MGLAttribute_Type);
	}

	{
		if (PyType_Ready(&MGLSubroutine_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Subroutine in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLSubroutine_Type);

		PyModule_AddObject(module, "Subroutine", (PyObject *)&MGLSubroutine_Type);
	}

	{
		if (PyType_Ready(&MGLVarying_Type) < 0) {
			PyErr_Format(PyExc_Exception, "Cannot register Varying in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		Py_INCREF(&MGLVarying_Type);

		PyModule_AddObject(module, "Varying", (PyObject *)&MGLVarying_Type);
	}

	{
		MGL_TRIANGLES = MGLPrimitive_New();
		MGL_TRIANGLES->name = "TRIANGLES";
		MGL_TRIANGLES->primitive = GL_TRIANGLES;
		MGL_TRIANGLES->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES", (PyObject *)MGL_TRIANGLES);

		MGL_TRIANGLE_STRIP = MGLPrimitive_New();
		MGL_TRIANGLE_STRIP->name = "TRIANGLE_STRIP";
		MGL_TRIANGLE_STRIP->primitive = GL_TRIANGLE_STRIP;
		MGL_TRIANGLE_STRIP->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP", (PyObject *)MGL_TRIANGLE_STRIP);

		MGL_TRIANGLE_FAN = MGLPrimitive_New();
		MGL_TRIANGLE_FAN->name = "TRIANGLE_FAN";
		MGL_TRIANGLE_FAN->primitive = GL_TRIANGLE_FAN;
		MGL_TRIANGLE_FAN->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_FAN", (PyObject *)MGL_TRIANGLE_FAN);

		MGL_LINES = MGLPrimitive_New();
		MGL_LINES->name = "LINES";
		MGL_LINES->primitive = GL_LINES;
		MGL_LINES->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES", (PyObject *)MGL_LINES);

		MGL_LINE_STRIP = MGLPrimitive_New();
		MGL_LINE_STRIP->name = "LINE_STRIP";
		MGL_LINE_STRIP->primitive = GL_LINE_STRIP;
		MGL_LINE_STRIP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP", (PyObject *)MGL_LINE_STRIP);

		MGL_LINE_LOOP = MGLPrimitive_New();
		MGL_LINE_LOOP->name = "LINE_LOOP";
		MGL_LINE_LOOP->primitive = GL_LINE_LOOP;
		MGL_LINE_LOOP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_LOOP", (PyObject *)MGL_LINE_LOOP);

		MGL_POINTS = MGLPrimitive_New();
		MGL_POINTS->name = "POINTS";
		MGL_POINTS->primitive = GL_POINTS;
		MGL_POINTS->transform_primitive = GL_POINTS;
		PyModule_AddObject(module, "POINTS", (PyObject *)MGL_POINTS);

		MGL_LINE_STRIP_ADJACENCY = MGLPrimitive_New();
		MGL_LINE_STRIP_ADJACENCY->name = "LINE_STRIP_ADJACENCY";
		MGL_LINE_STRIP_ADJACENCY->primitive = GL_LINE_STRIP_ADJACENCY;
		MGL_LINE_STRIP_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP_ADJACENCY", (PyObject *)MGL_LINE_STRIP_ADJACENCY);

		MGL_LINES_ADJACENCY = MGLPrimitive_New();
		MGL_LINES_ADJACENCY->name = "LINES_ADJACENCY";
		MGL_LINES_ADJACENCY->primitive = GL_LINES_ADJACENCY;
		MGL_LINES_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES_ADJACENCY", (PyObject *)MGL_LINES_ADJACENCY);

		MGL_TRIANGLE_STRIP_ADJACENCY = MGLPrimitive_New();
		MGL_TRIANGLE_STRIP_ADJACENCY->name = "TRIANGLE_STRIP_ADJACENCY";
		MGL_TRIANGLE_STRIP_ADJACENCY->primitive = GL_TRIANGLE_STRIP_ADJACENCY;
		MGL_TRIANGLE_STRIP_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP_ADJACENCY", (PyObject *)MGL_TRIANGLE_STRIP_ADJACENCY);

		MGL_TRIANGLES_ADJACENCY = MGLPrimitive_New();
		MGL_TRIANGLES_ADJACENCY->name = "TRIANGLES_ADJACENCY";
		MGL_TRIANGLES_ADJACENCY->primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLES_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES_ADJACENCY", (PyObject *)MGL_TRIANGLES_ADJACENCY);
	}

	{
		MGL_BLEND = MGLEnableFlag_New();
		MGL_BLEND->name = "BLEND";
		MGL_BLEND->flag = GL_BLEND;
		PyModule_AddObject(module, "BLEND", (PyObject *)MGL_BLEND);

		MGL_DEPTH_TEST = MGLEnableFlag_New();
		MGL_DEPTH_TEST->name = "DEPTH_TEST";
		MGL_DEPTH_TEST->flag = GL_DEPTH_TEST;
		PyModule_AddObject(module, "DEPTH_TEST", (PyObject *)MGL_DEPTH_TEST);

		MGL_CULL_FACE = MGLEnableFlag_New();
		MGL_CULL_FACE->name = "CULL_FACE";
		MGL_CULL_FACE->flag = GL_CULL_FACE;
		PyModule_AddObject(module, "CULL_FACE", (PyObject *)MGL_CULL_FACE);

		MGL_MULTISAMPLE = MGLEnableFlag_New();
		MGL_MULTISAMPLE->name = "MULTISAMPLE";
		MGL_MULTISAMPLE->flag = GL_MULTISAMPLE;
		PyModule_AddObject(module, "MULTISAMPLE", (PyObject *)MGL_MULTISAMPLE);
	}

	{
		MGLVersion * CORE_330 = MGLVersion_New();
		CORE_330->major = 3;
		CORE_330->minor = 3;
		PyModule_AddObject(module, "CORE_330", (PyObject *)CORE_330);

		MGLVersion * CORE_400 = MGLVersion_New();
		CORE_400->major = 4;
		CORE_400->minor = 0;
		PyModule_AddObject(module, "CORE_400", (PyObject *)CORE_400);

		MGLVersion * CORE_410 = MGLVersion_New();
		CORE_410->major = 4;
		CORE_410->minor = 1;
		PyModule_AddObject(module, "CORE_410", (PyObject *)CORE_410);

		MGLVersion * CORE_420 = MGLVersion_New();
		CORE_420->major = 4;
		CORE_420->minor = 2;
		PyModule_AddObject(module, "CORE_420", (PyObject *)CORE_420);

		MGLVersion * CORE_430 = MGLVersion_New();
		CORE_430->major = 4;
		CORE_430->minor = 3;
		PyModule_AddObject(module, "CORE_430", (PyObject *)CORE_430);

		MGLVersion * CORE_440 = MGLVersion_New();
		CORE_440->major = 4;
		CORE_440->minor = 4;
		PyModule_AddObject(module, "CORE_440", (PyObject *)CORE_440);

		MGLVersion * CORE_450 = MGLVersion_New();
		CORE_450->major = 4;
		CORE_450->minor = 5;
		PyModule_AddObject(module, "CORE_450", (PyObject *)CORE_450);
	}

	return module;
}
