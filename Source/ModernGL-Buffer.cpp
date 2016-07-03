#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewVertexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewVertexBuffer", &data, &size)) {
		return 0;
	}

	int vbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&vbo);
	OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo);
	OpenGL::glBufferData(OpenGL::GL_ARRAY_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
	return CreateVertexBufferType(vbo);
}

PyObject * NewIndexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewIndexBuffer", &data, &size)) {
		return 0;
	}

	int ibo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ibo);
	OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo);
	OpenGL::glBufferData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
	return CreateIndexBufferType(ibo);
}

PyObject * NewUniformBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewUniformBuffer", &data, &size)) {
		return 0;
	}

	int ubo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ubo);
	OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, ubo);
	OpenGL::glBufferData(OpenGL::GL_UNIFORM_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
	return CreateUniformBufferType(ubo);
}

PyObject * NewStorageBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewStorageBuffer", &data, &size)) {
		return 0;
	}

	int ssbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ssbo);
	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, ssbo);
	OpenGL::glBufferData(OpenGL::GL_SHADER_STORAGE_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
	return CreateStorageBufferType(ssbo, size);
}

PyObject * NewDynamicVertexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicVertexBuffer", &data, &size)) {
		return 0;
	}

	int vbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&vbo);
	OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo);
	OpenGL::glBufferData(OpenGL::GL_ARRAY_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
	return CreateVertexBufferType(vbo);
}

PyObject * NewDynamicIndexBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicIndexBuffer", &data, &size)) {
		return 0;
	}

	int ibo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ibo);
	OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo);
	OpenGL::glBufferData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
	return CreateIndexBufferType(ibo);
}

PyObject * NewDynamicUniformBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicUniformBuffer", &data, &size)) {
		return 0;
	}

	int ubo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ubo);
	OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, ubo);
	OpenGL::glBufferData(OpenGL::GL_UNIFORM_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
	return CreateUniformBufferType(ubo);
}

PyObject * NewDynamicStorageBuffer(PyObject * self, PyObject * args) {
	const void * data;
	int size;

	if (!PyArg_ParseTuple(args, "y#:NewDynamicStorageBuffer", &data, &size)) {
		return 0;
	}

	int ssbo = 0;
	OpenGL::glGenBuffers(1, (OpenGL::GLuint *)&ssbo);
	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, ssbo);
	OpenGL::glBufferData(OpenGL::GL_SHADER_STORAGE_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
	return CreateStorageBufferType(ssbo, size);
}

PyObject * DeleteVertexBuffer(PyObject * self, PyObject * args) {
	VertexBuffer * vbo;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexBuffer", &vbo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vbo, &VertexBufferType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&vbo->vbo);
	Py_RETURN_NONE;
}

PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args) {
	IndexBuffer * ibo;

	if (!PyArg_ParseTuple(args, "O:DeleteIndexBuffer", &ibo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)ibo, &IndexBufferType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ibo->ibo);
	Py_RETURN_NONE;
}

PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args) {
	UniformBuffer * ubo;

	if (!PyArg_ParseTuple(args, "O:DeleteUniformBuffer", &ubo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)ubo, &UniformBufferType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ubo->ubo);
	Py_RETURN_NONE;
}

PyObject * DeleteStorageBuffer(PyObject * self, PyObject * args) {
	StorageBuffer * ssbo;

	if (!PyArg_ParseTuple(args, "O:DeleteStorageBuffer", &ssbo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)ssbo, &StorageBufferType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ssbo->ssbo);
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

	OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, ubo->ubo);
	OpenGL::glBufferSubData(OpenGL::GL_UNIFORM_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UpdateStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * ssbo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"ssbo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oiy#:UpdateStorageBuffer", (char **)kwlist, &ssbo, &offset, &data, &size)) {
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, ssbo->ssbo);
	OpenGL::glBufferSubData(OpenGL::GL_SHADER_STORAGE_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * ssbo;
	int binding = 0;

	static const char * kwlist[] = {"ssbo", "binding", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|i:UseStorageBuffer", (char **)kwlist, &ssbo, &binding)) {
		return 0;
	}

	OpenGL::glBindBufferBase(OpenGL::GL_SHADER_STORAGE_BUFFER, binding, ssbo->ssbo);
	Py_RETURN_NONE;
}

PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * ssbo;
	int offset;
	int size;

	static const char * kwlist[] = {"ssbo", "offset", "size", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oii:ReadStorageBuffer", (char **)kwlist, &ssbo, &offset, &size)) {
		return 0;
	}

	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, ssbo->ssbo);
	if (size == 0) {
		size = ssbo->size - offset;
	}

	void * map = OpenGL::glMapBufferRange(OpenGL::GL_SHADER_STORAGE_BUFFER, offset, size, OpenGL::GL_MAP_READ_BIT);
	if (!map) {
		PyErr_SetString(ModuleError, "Cannot map the buffer.");
		return 0;
	}

	PyObject * data = PyBytes_FromStringAndSize((const char *)map, size);

	OpenGL::glUnmapBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER);
	return data;
}
