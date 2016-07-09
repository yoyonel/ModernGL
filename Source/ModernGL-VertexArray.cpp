#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewVertexArray(PyObject * self, PyObject * args) {
	Program * program;
	VertexBuffer * vbo;
	const char * format;
	PyObject * attributes;

	IndexBuffer * no_ibo = (IndexBuffer *)Py_None;
	IndexBuffer * ibo = no_ibo;
	bool strict = false;

	if (!PyArg_ParseTuple(args, "OOsO|Op:NewVertexArray", &program, &vbo, &format, &attributes, &ibo, &strict)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("program", program, ProgramType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("vbo", vbo, VertexBufferType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("attributes", attributes, PyList_Type);

	int length = 0;
	while (format[length]) {
		if (length % 2 == 0) {
			if (format[length] < '1' || format[length] > '4') {
				PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is invalid.");
				return 0;
			}
		} else {
			if (format[length] != 'i' && format[length] != 'f') {
				PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is invalid.");
				return 0;
			}
		}
		++length;
	}

	if (!length || length % 2) {
		PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is empty or invalid.");
		return 0;
	}

	int count = (int)PyList_Size(attributes);

	if (length / 2 != count) {
		PyErr_Format(ModuleError, "NewVertexArray() size of `format` is %d, length of `attributes` is %d", length / 2, count);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		const char * name = PyUnicode_AsUTF8(PyList_GET_ITEM(attributes, i));
		int location = OpenGL::glGetAttribLocation(program->program, name);
		if (strict && location < 0) {
			PyErr_Format(ModuleError, "ERR: 1");
			return 0;
		}
	}

	if (ibo != no_ibo) {
		CHECK_AND_REPORT_ARG_TYPE_ERROR("ibo", ibo, IndexBufferType);
	}

	int vao = 0;
	OpenGL::glGenVertexArrays(1, (OpenGL::GLuint *)&vao);
	OpenGL::glBindVertexArray(vao);

	if (ibo != no_ibo) {
		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo->ibo);
	}

	int stride = 0;
	for (int i = 0; format[i]; i += 2) {
		stride += (format[i] - '0') * 4;
	}

	OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo->vbo);

	char * ptr = 0;
	for (int i = 0; i < count; ++i) {
		const char * name = PyUnicode_AsUTF8(PyList_GET_ITEM(attributes, i));
		int location = OpenGL::glGetAttribLocation(program->program, name);

		int dimension = format[i * 2] - '0';
		switch (format[i * 2 + 1]) {
			case 'f':
				OpenGL::glVertexAttribPointer(location, dimension, OpenGL::GL_FLOAT, false, stride, ptr);
				break;
			case 'i':
				OpenGL::glVertexAttribPointer(location, dimension, OpenGL::GL_INT, false, stride, ptr);
				break;
		}
		OpenGL::glEnableVertexAttribArray(location);
		ptr += dimension * 4;
	}

	OpenGL::glBindVertexArray(defaultVertexArray);
	return CreateVertexArrayType(vao, program->program, ibo != no_ibo);
}

PyObject * DeleteVertexArray(PyObject * self, PyObject * args) {
	VertexArray * vao;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexArray", &vao)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

	OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao->vao);
	Py_RETURN_NONE;
}

PyObject * EnableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attributes;

	static const char * kwlist[] = {"vao", "attributes", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:EnableAttributes", (char **)kwlist, &vao, &attributes)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("attributes", attributes, PyList_Type);

	int count = (int)PyList_Size(attributes);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * attribute = (AttributeLocation *)PyList_GET_ITEM(attributes, i);
		CHECK_AND_REPORT_ELEMENT_TYPE_ERROR("attributes", attribute, AttributeLocationType, i);
	}
	
	OpenGL::glBindVertexArray(vao->vao);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * attribute = (AttributeLocation *)PyList_GET_ITEM(attributes, i);
		OpenGL::glEnableVertexAttribArray(attribute->location);
	}

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * DisableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attributes;

	static const char * kwlist[] = {"vao", "attributes", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:DisableAttributes", (char **)kwlist, &vao, &attributes)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("attributes", attributes, PyList_Type);

	int count = (int)PyList_Size(attributes);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * attribute = (AttributeLocation *)PyList_GET_ITEM(attributes, i);
		CHECK_AND_REPORT_ELEMENT_TYPE_ERROR("attributes", attribute, AttributeLocationType, i);
	}
	
	OpenGL::glBindVertexArray(vao->vao);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * attribute = (AttributeLocation *)PyList_GET_ITEM(attributes, i);
		OpenGL::glDisableVertexAttribArray(attribute->location);
	}

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}
