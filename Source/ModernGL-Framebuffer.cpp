#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width = 0;
	int height = 0;

	static const char * kwlist[] = {"width", "height", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|ii:NewFramebuffer", (char **)kwlist, &width, &height)) {
		return 0;
	}

	int framebuffer = 0;
	int color = 0;
	int depth = 0;

	OpenGL::glGenFramebuffers(1, (OpenGL::GLuint *)&framebuffer);
	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, framebuffer);

	if (!width && !height) {
		int viewport[4] = {};
		OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewport);
		width = viewport[2];
		height = viewport[3];
	}

	OpenGL::glGenTextures(1, (OpenGL::GLuint *)&color);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, color);

	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, OpenGL::GL_RGBA, width, height, 0, OpenGL::GL_RGBA, OpenGL::GL_FLOAT, 0);
	OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_COLOR_ATTACHMENT0, OpenGL::GL_TEXTURE_2D, color, 0);

	OpenGL::glGenTextures(1, (OpenGL::GLuint *)&depth);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, depth);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, OpenGL::GL_DEPTH_COMPONENT, width, height, 0, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, 0);
	OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_DEPTH_ATTACHMENT, OpenGL::GL_TEXTURE_2D, depth, 0);

	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);

	PyObject * fbo = CreateFramebufferType(framebuffer, color, depth);
	PyObject * colorTexture = CreateTextureType(color, width, height, 4);
	PyObject * depthTexture = CreateTextureType(depth, width, height, 1);

	return Py_BuildValue("OOO", fbo, colorTexture, depthTexture);
}

PyObject * DeleteFramebuffer(PyObject * self, PyObject * args) {
	Framebuffer * fbo;

	if (!PyArg_ParseTuple(args, "O:DeleteFramebuffer", &fbo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)fbo, &PyList_Type)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)fbo))->tp_name;
		PyErr_Format(PyExc_TypeError, "DeleteFramebuffer() argument `fbo` must be Framebuffer, not %s", got);
		return 0;
	}

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

	if (!PyObject_TypeCheck((PyObject *)fbo, &PyList_Type)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)fbo))->tp_name;
		PyErr_Format(PyExc_TypeError, "UseFramebuffer() argument `fbo` must be Framebuffer, not %s", got);
		return 0;
	}

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

	if (components < 1 || components > 4) {
		PyErr_Format(ModuleError, "ReadPixels() argument `components` must be in range 1 to 4, not %d", components);
		return 0;
	}

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
	PyErr_SetString(ModuleError, "No Imp.");
	return 0;
	// int x;
	// int y;
	// int width;
	// int height;

	// static const char * kwlist[] = {"x", "y", "width", "height", 0};

	// if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii:ReadDepthPixels", (char **)kwlist, &x, &y, &width, &height)) {
	// 	return 0;
	// }

	// int size = height * height * 4;
	// float * pixels = ModernGL::ReadDepthPixels(x, y, width, height);
	// PyObject * data = PyBytes_FromStringAndSize((const char *)pixels, size);
	// free(pixels);

	// return data;
}

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "No Imp.");
	return 0;
	// int x;
	// int y;

	// static const char * kwlist[] = {"x", "y", 0};

	// if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadPixel", (char **)kwlist, &x, &y)) {
	// 	return 0;
	// }

	// return PyLong_FromUnsignedLong(ModernGL::ReadPixel(x, y));
}

PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "No Imp.");
	return 0;
	// int x;
	// int y;

	// static const char * kwlist[] = {"x", "y", 0};

	// if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii:ReadDepthPixel", (char **)kwlist, &x, &y)) {
	// 	return 0;
	// }

	// return PyFloat_FromDouble(ModernGL::ReadDepthPixel(x, y));
}
