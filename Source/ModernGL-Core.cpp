#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * GetInfo(PyObject * self) {
	int major = 0;
	int minor = 0;
	int samples = 0;

	OpenGL::glGetIntegerv(OpenGL::GL_MAJOR_VERSION, &major);
	OpenGL::glGetIntegerv(OpenGL::GL_MINOR_VERSION, &minor);
	OpenGL::glGetIntegerv(OpenGL::GL_MAX_SAMPLES, &samples);
	const char * vendor = (const char *)OpenGL::glGetString(OpenGL::GL_VENDOR);
	const char * renderer = (const char *)OpenGL::glGetString(OpenGL::GL_RENDERER);

	if (!vendor) {
		vendor = "";
	}
	
	if (!renderer) {
		renderer = "";
	}

	return Py_BuildValue("iiiss", major, minor, samples, vendor, renderer);
}

PyObject * Viewport(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;

	static const char * kwlist[] = {"x", "y", "width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:Viewport", (char **)kwlist, &x, &y, &width, &height)) {
		return 0;
	}

	OpenGL::glViewport(x, y, width, height);
	activeViewportWidth = width;
	activeViewportHeight = height;
	Py_RETURN_NONE;
}

PyObject * Clear(PyObject * self, PyObject * args, PyObject * kwargs) {
	unsigned char r = 0;
	unsigned char g = 0;
	unsigned char b = 0;
	unsigned char a = 255;

	static const char * kwlist[] = {"r", "g", "b", "a", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|bbbb:Clear", (char **)kwlist, &r, &g, &b, &a)) {
		return 0;
	}

	const float c = 1.0f / 255.0f;
	OpenGL::glClearColor(r * c, g * c, b * c, a * c);
	unsigned GL_ALL_BUFFER_BIT = 0;
	GL_ALL_BUFFER_BIT |= OpenGL::GL_DEPTH_BUFFER_BIT;
	GL_ALL_BUFFER_BIT |= OpenGL::GL_COLOR_BUFFER_BIT;
	OpenGL::glClear(GL_ALL_BUFFER_BIT);
	Py_RETURN_NONE;
}

PyObject * PointSize(PyObject * self, PyObject * args) {
	float size;

	if (!PyArg_ParseTuple(args, "f:PointSize", &size)) {
		return 0;
	}

	OpenGL::glPointSize(size);
	Py_RETURN_NONE;
}

PyObject * LineSize(PyObject * self, PyObject * args) {
	float size;

	if (!PyArg_ParseTuple(args, "f:LineSize", &size)) {
		return 0;
	}

	OpenGL::glLineWidth(size);
	Py_RETURN_NONE;
}

PyObject * EnableOnly(PyObject * self, PyObject * args) {
	EnableFlag * flags;

	if (!PyArg_ParseTuple(args, "O:EnableOnly", &flags)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("flags", flags, EnableFlagType);

	(flags->value & ENABLE_BLEND ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_BLEND);
	(flags->value & ENABLE_CULL_FACE ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_CULL_FACE);
	(flags->value & ENABLE_DEPTH_TEST ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_DEPTH_TEST);
	(flags->value & ENABLE_MULTISAMPLE ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_MULTISAMPLE);
	Py_RETURN_NONE;
}


PyObject * EnableBlend(PyObject * self) {
	OpenGL::glEnable(OpenGL::GL_BLEND);
	Py_RETURN_NONE;
}

PyObject * DisableBlend(PyObject * self) {
	OpenGL::glDisable(OpenGL::GL_BLEND);
	Py_RETURN_NONE;
}

PyObject * EnableCullFace(PyObject * self) {
	OpenGL::glEnable(OpenGL::GL_CULL_FACE);
	Py_RETURN_NONE;
}

PyObject * DisableCullFace(PyObject * self) {
	OpenGL::glDisable(OpenGL::GL_CULL_FACE);
	Py_RETURN_NONE;
}

PyObject * EnableDepthTest(PyObject * self) {
	OpenGL::glEnable(OpenGL::GL_DEPTH_TEST);
	Py_RETURN_NONE;
}

PyObject * DisableDepthTest(PyObject * self) {
	OpenGL::glDisable(OpenGL::GL_DEPTH_TEST);
	Py_RETURN_NONE;
}

PyObject * EnableMultisample(PyObject * self) {
	OpenGL::glEnable(OpenGL::GL_MULTISAMPLE);
	Py_RETURN_NONE;
}

PyObject * DisableMultisample(PyObject * self) {
	OpenGL::glDisable(OpenGL::GL_MULTISAMPLE);
	Py_RETURN_NONE;
}
