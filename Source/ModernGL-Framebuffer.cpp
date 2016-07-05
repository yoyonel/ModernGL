#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width = 0;
	int height = 0;
	int colors = 1;
	bool depth = true;

	static const char * kwlist[] = {"width", "height", "colors", "depth", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|iiip:NewFramebuffer", (char **)kwlist, &width, &height, &colors, &depth)) {
		return 0;
	}

	if (!width && !height) {
		width = activeViewportWidth;
		height = activeViewportHeight;
	}

	CHECK_AND_REPORT_ARG_VALUE_ERROR(width < 1, "width", width);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(height < 1, "height", height);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(colors < 0 || colors > 8, "colors", colors);

	int framebuffer = 0;
	OpenGL::glGenFramebuffers(1, (OpenGL::GLuint *)&framebuffer);
	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, framebuffer);

	int depthTex = 0;
	OpenGL::glGenTextures(1, (OpenGL::GLuint *)&depthTex);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, depthTex);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, OpenGL::GL_DEPTH_COMPONENT, width, height, 0, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, 0);
	OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_DEPTH_ATTACHMENT, OpenGL::GL_TEXTURE_2D, depthTex, 0);

	int colorTex[8] = {};
	OpenGL::glGenTextures(colors, (OpenGL::GLuint *)colorTex);
	for (int i = 0; i < colors; ++i) {
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, colorTex);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, OpenGL::GL_RGBA, width, height, 0, OpenGL::GL_RGBA, OpenGL::GL_FLOAT, 0);
		OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_COLOR_ATTACHMENT0 + i, OpenGL::GL_TEXTURE_2D, colorTex, 0);
	}

	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);

	PyObject * tuple = PyTuple_New(2 + colors);
	PyTuple_SET_ITEM(tuple, 0, CreateFramebufferType(framebuffer, colorTex, depthTex));
	for (int i = 0; i < colors; ++i) {
		PyObject * colorTexture = CreateTextureType(colorTex[i], width, height, 4);
		PyTuple_SET_ITEM(tuple, i + 1, colorTexture);
	}
	PyTuple_SET_ITEM(tuple, colors + 1, CreateTextureType(depthTex, width, height, 1));

	return tuple;
}

PyObject * DeleteFramebuffer(PyObject * self, PyObject * args) {
	Framebuffer * fbo;

	if (!PyArg_ParseTuple(args, "O:DeleteFramebuffer", &fbo)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("fbo", fbo, FramebufferType);

	OpenGL::glDeleteFramebuffers(1, (OpenGL::GLuint *)&fbo->fbo);
	OpenGL::glDeleteTextures(1, (OpenGL::GLuint *)&fbo->color);
	OpenGL::glDeleteTextures(1, (OpenGL::GLuint *)&fbo->depth);
	Py_RETURN_NONE;
}

PyObject * UseFramebuffer(PyObject * self, PyObject * args) {
	Framebuffer * fbo;

	if (!PyArg_ParseTuple(args, "O:UseFramebuffer", &fbo)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("fbo", fbo, FramebufferType);

	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, fbo->fbo);
	activeProgram = fbo->fbo;
	Py_RETURN_NONE;
}

PyObject * GetDefaultFramebuffer(PyObject * self) {
	OpenGL::glGetIntegerv(OpenGL::GL_DRAW_FRAMEBUFFER_BINDING, (OpenGL::GLint *)&defaultFramebuffer);
	Py_RETURN_NONE;
}

PyObject * UseDefaultFramebuffer(PyObject * self) {
	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);
	Py_RETURN_NONE;
}

PyObject * ReadPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;
	int components = 3;

	static const char * kwlist[] = {"x", "y", "width", "height", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii|i:ReadPixels", (char **)kwlist, &x, &y, &width, &height, &components)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_VALUE_ERROR(width < 1, "width", width);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(height < 1, "height", height);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(components < 1 || components > 4, "components", components);

	int size = height * ((width * components + 3) & ~3);

	const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
	int format = formats[components];

	PyObject * bytes = PyBytes_FromStringAndSize(0, size);
	char * data = PyBytes_AS_STRING(bytes);

	OpenGL::glReadPixels(x, y, width, height, format, OpenGL::GL_UNSIGNED_BYTE, data);
	data[size] = 0;
	
	return bytes;
}

PyObject * ReadDepthPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;

	static const char * kwlist[] = {"x", "y", "width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:ReadDepthPixels", (char **)kwlist, &x, &y, &width, &height)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_VALUE_ERROR(width < 1, "width", width);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(height < 1, "height", height);

	int size = height * height * 4;
	float * pixels = ModernGL::ReadDepthPixels(x, y, width, height);
	PyObject * data = PyBytes_FromStringAndSize((const char *)pixels, size);
	free(pixels);

	PyObject * bytes = PyBytes_FromStringAndSize(0, size);
	char * data = PyBytes_AS_STRING(bytes);
	OpenGL::glReadPixels(x, y, width, height, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, data);
	data[size] = 0;

	return bytes;
}

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;

	static const char * kwlist[] = {"x", "y", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadPixel", (char **)kwlist, &x, &y)) {
		return 0;
	}

	unsigned rgba = 0;
	OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_RGBA, OpenGL::GL_UNSIGNED_BYTE, &rgba);
	return PyLong_FromUnsignedLong(rgba);
}

PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;

	static const char * kwlist[] = {"x", "y", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadDepthPixel", (char **)kwlist, &x, &y)) {
		return 0;
	}

	float depth = 0.0;
	OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, &depth);
	return PyFloat_FromDouble(depth);
}
