#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width = 0;
	int height = 0;

	int components = 4;

	bool floats = false;
	bool depth = true;

	static const char * kwlist[] = {"width", "height", "components", "floats", "depth", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|iiip:NewFramebuffer", (char **)kwlist, &width, &height, &components, &floats, &depth)) {
		return 0;
	}

	if (!width && !height) {
		width = activeViewportWidth; // todo query with glGet (slower but ok)
		height = activeViewportHeight;
	}

	if (width < 0 || height < 0) {
		PyErr_Format(ModuleRangeError, "NewFramebuffer() width = %d height = %d", width, height);
	}

	const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};

	int pixel_type = floats ? OpenGL::GL_FLOAT : OpenGL::GL_UNSIGNED_BYTE;
	int format = formats[components];

	int framebuffer = 0;
	int colorTexture = 0;
	int depthTexture = 0;

	OpenGL::glGenFramebuffers(1, (OpenGL::GLuint *)&framebuffer);
	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, framebuffer);

	OpenGL::glGenTextures(1, (OpenGL::GLuint *)&colorTexture);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, colorTexture);

	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, format, width, height, 0, format, pixel_type, 0);
	OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_COLOR_ATTACHMENT0, OpenGL::GL_TEXTURE_2D, colorTexture, 0);

	if (depth) {
		OpenGL::glGenTextures(1, (OpenGL::GLuint *)&depthTexture);
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, depthTexture);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, OpenGL::GL_DEPTH_COMPONENT, width, height, 0, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, 0);
		OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_DEPTH_ATTACHMENT, OpenGL::GL_TEXTURE_2D, depthTexture, 0);
	}

	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);

	PyObject * tuple = PyTuple_New(floats ? 3 : 2);

	PyTuple_SET_ITEM(tuple, 0, CreateFramebufferType(framebuffer, colorTexture, depthTexture));
	PyTuple_SET_ITEM(tuple, 1, CreateTextureType(colorTexture, width, height, 4, floats));

	if (depth) {
		PyTuple_SET_ITEM(tuple, 2, CreateTextureType(depthTexture, width, height, 1, true));
	}

	// validate fbo (https://www.opengl.org/wiki/Framebuffer_Object) (Framebuffer Completeness)

	return tuple;
}

PyObject * DeleteFramebuffer(PyObject * self, PyObject * args) {
	Framebuffer * fbo;

	if (!PyArg_ParseTuple(args, "O!:DeleteFramebuffer", &FramebufferType, &fbo)) {
		return 0;
	}

	OpenGL::glDeleteFramebuffers(1, (OpenGL::GLuint *)&fbo->fbo);

	if (fbo->color) {
		OpenGL::glDeleteTextures(1, (OpenGL::GLuint *)&fbo->color);
	}

	if (fbo->depth) {
		OpenGL::glDeleteTextures(1, (OpenGL::GLuint *)&fbo->depth);
	}

	Py_RETURN_NONE;
}

PyObject * UseFramebuffer(PyObject * self, PyObject * args) {
	Framebuffer * fbo;

	if (!PyArg_ParseTuple(args, "O!:UseFramebuffer", &FramebufferType, &fbo)) {
		return 0;
	}

	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, fbo->fbo);

	Py_RETURN_NONE;
}

PyObject * SetDefaultFramebuffer(PyObject * self, PyObject * args) { // TODO: mark as deprecated allow: def_fbo = Framebuffer(2) # QT
	int fbo;

	if (!PyArg_ParseTuple(args, "i:SetDefaultFramebuffer", &fbo)) {
		return 0;
	}

	defaultFramebuffer = fbo;
	Py_RETURN_NONE;
}

PyObject * UseDefaultFramebuffer(PyObject * self) { // TODO: mark as deprecated
	OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);
	Py_RETURN_NONE;
}

PyObject * ReadPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;
	int components = 3;
	bool floats = false;

	static const char * kwlist[] = {"x", "y", "width", "height", "components", "floats", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii|ip:ReadPixels", (char **)kwlist, &x, &y, &width, &height, &components, &floats)) {
		return 0;
	}

	if (width <= 0 || height <= 0 || components < 1 || components > 4) {
		PyErr_Format(ModuleRangeError, "ReadPixels() width = %d height = %d components = %d", width, height, components);
	}

	int size = floats ? (width * height * 4) : (height * ((width * components + 3) & ~3));
	int pixel_type = floats ? OpenGL::GL_FLOAT : OpenGL::GL_UNSIGNED_BYTE;

	const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
	int format = formats[components];

	PyObject * bytes = PyBytes_FromStringAndSize(0, size);
	char * data = PyBytes_AS_STRING(bytes);

	OpenGL::glReadPixels(x, y, width, height, format, pixel_type, data);
	data[size] = 0;
	
	return bytes;
}

PyObject * ReadDepthPixels(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int width;
	int height;
	bool floats = true;

	static const char * kwlist[] = {"x", "y", "width", "height", "floats", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiii|p:ReadDepthPixels", (char **)kwlist, &x, &y, &width, &height, &floats)) {
		return 0;
	}

	if (width < 0 || height < 0) {
		PyErr_Format(ModuleRangeError, "ReadDepthPixels() width = %d height = %d", width, height);
	}

	int size = floats ? (width * height * 4) : (height * ((width + 3) & ~3));
	int pixel_type = floats ? OpenGL::GL_FLOAT : OpenGL::GL_UNSIGNED_BYTE;

	PyObject * bytes = PyBytes_FromStringAndSize(0, size);
	char * data = PyBytes_AS_STRING(bytes);
	OpenGL::glReadPixels(x, y, width, height, OpenGL::GL_DEPTH_COMPONENT, pixel_type, data);
	data[size] = 0;

	return bytes;
}

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	int components = 3;
	bool floats = false;

	static const char * kwlist[] = {"x", "y", "components", "floats", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii|ip:ReadPixel", (char **)kwlist, &x, &y, &components, &floats)) {
		return 0;
	}

	if (components < 1 || components > 4) {
		// TODO:
	}
	
	PyObject * tuple = PyTuple_New(components);

	if (floats) {
		float rgba[4];
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_RGBA, OpenGL::GL_FLOAT, &rgba);
		for (int i = 0; i < components; ++i) {
			PyTuple_SET_ITEM(tuple, i, PyFloat_FromDouble(rgba[i]));
		}
	} else {
		unsigned char rgba[4];
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_RGBA, OpenGL::GL_UNSIGNED_BYTE, &rgba);
		for (int i = 0; i < components; ++i) {
			PyTuple_SET_ITEM(tuple, i, PyLong_FromUnsignedLong(rgba[i]));
		}
	}

	return tuple;
}

PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs) {
	int x;
	int y;
	bool floats = true;

	static const char * kwlist[] = {"x", "y", "floats", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "ii|p:ReadDepthPixel", (char **)kwlist, &x, &y, &floats)) {
		return 0;
	}

	if (floats) {
		float depth = 0.0;
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, &depth);
		return PyFloat_FromDouble(depth);
	} else {
		unsigned depth = 0;
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_UNSIGNED_BYTE, &depth);
		return PyLong_FromUnsignedLong(depth);
	}
}
