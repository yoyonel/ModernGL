#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewTexture(PyObject * self, PyObject * args, PyObject * kwargs) {
	int width;
	int height;
	const void * data;
	int components = 3;
	int size;

	static const char * kwlist[] = {"width", "height", "data", "components", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "iiy#|i:NewTexture", (char **)kwlist, &width, &height, &data, &size, &components)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_VALUE_ERROR(width < 1, "width", width);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(height < 1, "height", height);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(components < 1 || components > 4, "components", components);

	int expected_size = height * ((width * components + 3) & ~3);

	if (size != expected_size) {
		PyErr_Format(ModuleError, "NewTexture() expected size is %d, not %d", expected_size, size);
		return 0;
	}

	const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
	int format = formats[components];

	if (!width && !height) {
		int viewportValue[4];
		OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewportValue);
		width = viewportValue[2];
		height = viewportValue[3];
	}

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);

	int texture = 0;
	OpenGL::glGenTextures(1, (OpenGL::GLuint *)&texture);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, format, width, height, 0, format, OpenGL::GL_UNSIGNED_BYTE, data);
	return CreateTextureType(texture, width, height, components);
}

PyObject * DeleteTexture(PyObject * self, PyObject * args) {
	Texture * texture;

	if (!PyArg_ParseTuple(args, "O:DeleteTexture", &texture)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glDeleteTextures(1, (OpenGL::GLuint *)&texture->texture);
	Py_RETURN_NONE;
}

PyObject * UpdateTexture(PyObject * self, PyObject * args, PyObject * kwargs) {
	Texture * texture;
	int x;
	int y;
	int width;
	int height;
	const void * data;
	int size;

	static const char * kwlist[] = {"texture", "x", "y", "width", "height", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiiiiy#|i:UpdateTexture", (char **)kwlist, &texture, &x, &y, &width, &height, &data, &size)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(x < 1 || x > texture->width - 1, "x", x);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(y < 1 || y > texture->height - 1, "y", y);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(width < 1 || x + width > texture->width, "width", width);
	CHECK_AND_REPORT_ARG_VALUE_ERROR(height < 1 || y + height > texture->height, "height", height);

	const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
	int format = formats[texture->components];
	
	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	OpenGL::glTexSubImage2D(OpenGL::GL_TEXTURE_2D, 0, x, y, width, height, format, OpenGL::GL_UNSIGNED_BYTE, data);
	Py_RETURN_NONE;
}

PyObject * UseTexture(PyObject * self, PyObject * args) {
	Texture * texture;
	int location = 0;

	if (!PyArg_ParseTuple(args, "O|i:UseTexture", &texture, &location)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + location);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	Py_RETURN_NONE;
}

PyObject * SetTexturePixelated(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTexturePixelated", &texture)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_NEAREST);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_NEAREST);
	Py_RETURN_NONE;
}

PyObject * SetTextureFiltered(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTextureFiltered", &texture)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	Py_RETURN_NONE;
}

PyObject * SetTextureMipmapped(PyObject * self, PyObject * args) {
	Texture * texture;
	
	if (!PyArg_ParseTuple(args, "O:SetTextureMipmapped", &texture)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR_MIPMAP_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	Py_RETURN_NONE;
}

PyObject * BuildMipmap(PyObject * self, PyObject * args, PyObject * kwargs) {
	Texture * texture;
	int base = 0;
	int max = 1000;

	static const char * kwlist[] = {"texture", "base", "max", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|ii:BuildMipmap", (char **)kwlist, &texture, &base, &max)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
	OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture->texture);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_BASE_LEVEL, base);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAX_LEVEL, max);
	OpenGL::glGenerateMipmap(OpenGL::GL_TEXTURE_2D);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR_MIPMAP_LINEAR);
	OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	Py_RETURN_NONE;
}

PyObject * UseTextureAsImage(PyObject * self, PyObject * args, PyObject * kwargs) {
	Texture * texture;
	int binding = 0;

	static const char * kwlist[] = {"texture", "binding", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|ii:UseTextureAsImage", (char **)kwlist, &texture, &binding)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("texture", texture, TextureType);

	const int formats[] = {0, OpenGL::GL_R8UI, OpenGL::GL_RG8UI, OpenGL::GL_RGB8UI, OpenGL::GL_RGBA8UI};
	int format = formats[texture->components];
	
	OpenGL::glBindImageTexture(binding, texture->texture, 0, false, 0, OpenGL::GL_READ_WRITE, format);
	Py_RETURN_NONE;
}
