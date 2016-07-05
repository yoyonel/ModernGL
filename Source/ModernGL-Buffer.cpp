#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	const void * data;
	int size;
	bool dynamic = false;

	static const char * kwlist[] = {"data", "dynamic", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y#|p:NewVertexBuffer", (char **)kwlist, &data, &size, &dynamic)) {
		return 0;
	}

	int vbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&vbo);
	OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo);
	OpenGL::glBufferData(OpenGL::GL_ARRAY_BUFFER, size, data, dynamic ? OpenGL::GL_DYNAMIC_DRAW : OpenGL::GL_STATIC_DRAW);
	return CreateVertexBufferType(vbo, size);
}

PyObject * NewIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	const void * data;
	int size;
	bool dynamic = false;

	static const char * kwlist[] = {"data", "dynamic", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y#|p:NewIndexBuffer", (char **)kwlist, &data, &size, &dynamic)) {
		return 0;
	}

	int ibo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ibo);
	OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo);
	OpenGL::glBufferData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, size, data, dynamic ? OpenGL::GL_DYNAMIC_DRAW : OpenGL::GL_STATIC_DRAW);
	return CreateIndexBufferType(ibo, size);
}

PyObject * NewUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	const void * data;
	int size;
	bool dynamic = false;

	static const char * kwlist[] = {"data", "dynamic", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y#|p:NewUniformBuffer", (char **)kwlist, &data, &size, &dynamic)) {
		return 0;
	}

	int ubo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ubo);
	OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, ubo);
	OpenGL::glBufferData(OpenGL::GL_UNIFORM_BUFFER, size, data, dynamic ? OpenGL::GL_DYNAMIC_DRAW : OpenGL::GL_STATIC_DRAW);
	return CreateUniformBufferType(ubo, size);
}

PyObject * NewStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	const void * data;
	int size;
	bool dynamic = false;

	static const char * kwlist[] = {"data", "dynamic", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "y#|p:NewStorageBuffer", (char **)kwlist, &data, &size, &dynamic)) {
		return 0;
	}

	int sbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&sbo);
	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, sbo);
	OpenGL::glBufferData(OpenGL::GL_SHADER_STORAGE_BUFFER, size, data, dynamic ? OpenGL::GL_DYNAMIC_DRAW : OpenGL::GL_STATIC_DRAW);
	return CreateStorageBufferType(sbo, size);
}

PyObject * DeleteVertexBuffer(PyObject * self, PyObject * args) {
	VertexBuffer * vbo;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexBuffer", &vbo)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("vbo", vbo, VertexBufferType);

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&vbo->vbo);
	Py_RETURN_NONE;
}

PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args) {
	IndexBuffer * ibo;

	if (!PyArg_ParseTuple(args, "O:DeleteIndexBuffer", &ibo)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("ibo", ibo, IndexBufferType);

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ibo->ibo);
	Py_RETURN_NONE;
}

PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args) {
	UniformBuffer * ubo;

	if (!PyArg_ParseTuple(args, "O:DeleteUniformBuffer", &ubo)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("ubo", ubo, UniformBufferType);

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ubo->ubo);
	Py_RETURN_NONE;
}

PyObject * DeleteStorageBuffer(PyObject * self, PyObject * args) {
	StorageBuffer * sbo;

	if (!PyArg_ParseTuple(args, "O:DeleteStorageBuffer", &sbo)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("sbo", sbo, StorageBufferType);

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&sbo->sbo);
	Py_RETURN_NONE;
}

PyObject * UpdateVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"vbo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiy#:UpdateVertexBuffer", (char **)kwlist, &vbo, &offset, &data, &size)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("vbo", vbo, VertexBufferType);

	if (offset < 0 || offset + size > vbo->size) {
		PyErr_SetString(PyExc_TypeError, "UpdateVertexBuffer() `offset` and `size` error");
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo->vbo);
	OpenGL::glBufferSubData(OpenGL::GL_ARRAY_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UpdateIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	IndexBuffer * ibo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"ibo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiy#:UpdateIndexBuffer", (char **)kwlist, &ibo, &offset, &data, &size)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("ibo", ibo, IndexBufferType);

	if (offset < 0 || offset + size > ibo->size) {
		PyErr_SetString(PyExc_TypeError, "UpdateIndexBuffer() `offset` and `size` error");
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo->ibo);
	OpenGL::glBufferSubData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UpdateUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	UniformBuffer * ubo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"ubo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiy#:UpdateUniformBuffer", (char **)kwlist, &ubo, &offset, &data, &size)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("ubo", ubo, UniformBufferType);

	if (offset < 0 || offset + size > ubo->size) {
		PyErr_SetString(PyExc_TypeError, "UpdateUniformBuffer() `offset` and `size` error");
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, ubo->ubo);
	OpenGL::glBufferSubData(OpenGL::GL_UNIFORM_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UpdateStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * sbo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"sbo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiy#:UpdateStorageBuffer", (char **)kwlist, &sbo, &offset, &data, &size)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("sbo", sbo, StorageBufferType);

	if (offset < 0 || offset + size > sbo->size) {
		PyErr_SetString(PyExc_TypeError, "UpdateStorageBuffer() `offset` and `size` error");
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, sbo->sbo);
	OpenGL::glBufferSubData(OpenGL::GL_SHADER_STORAGE_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * sbo;
	int binding = 0;

	static const char * kwlist[] = {"sbo", "binding", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|i:UseStorageBuffer", (char **)kwlist, &sbo, &binding)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("sbo", sbo, StorageBufferType);

	OpenGL::glBindBufferBase(OpenGL::GL_SHADER_STORAGE_BUFFER, binding, sbo->sbo);
	Py_RETURN_NONE;
}

PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * sbo;
	int offset;
	int size;

	static const char * kwlist[] = {"sbo", "offset", "size", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oii:ReadStorageBuffer", (char **)kwlist, &sbo, &offset, &size)) {
		return 0;
	}

	REPORT_ARG_TYPE_ERROR("sbo", sbo, StorageBufferType);

	if (size == 0) {
		size = sbo->size - offset;
	}

	if (size < 0 || offset < 0 || offset + size > sbo->size) {
		PyErr_SetString(ModuleError, "ReadStorageBuffer() offset` and `size` error");
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, sbo->sbo);
	void * map = OpenGL::glMapBufferRange(OpenGL::GL_SHADER_STORAGE_BUFFER, offset, size, OpenGL::GL_MAP_READ_BIT);
	if (!map) {
		PyErr_SetString(ModuleError, "ReadStorageBuffer() cannot map the buffer");
		return 0;
	}

	PyObject * data = PyBytes_FromStringAndSize((const char *)map, size);

	OpenGL::glUnmapBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER);
	return data;
}
