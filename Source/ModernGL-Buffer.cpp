

// Dummy#include "ModernGL.hpp"

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

	if (!PyArg_ParseTuple(args, "O!:DeleteVertexBuffer", &VertexBufferType, &vbo)) {
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&vbo->vbo);
	Py_RETURN_NONE;
}

PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args) {
	IndexBuffer * ibo;

	if (!PyArg_ParseTuple(args, "O!:DeleteIndexBuffer", &IndexBufferType, &ibo)) {
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ibo->ibo);
	Py_RETURN_NONE;
}

PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args) {
	UniformBuffer * ubo;

	if (!PyArg_ParseTuple(args, "O!:DeleteUniformBuffer", &UniformBufferType, &ubo)) {
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&ubo->ubo);
	Py_RETURN_NONE;
}

PyObject * DeleteStorageBuffer(PyObject * self, PyObject * args) {
	StorageBuffer * sbo;

	if (!PyArg_ParseTuple(args, "O!:DeleteStorageBuffer", &StorageBufferType, &sbo)) {
		return 0;
	}

	OpenGL::glDeleteBuffers(1, (OpenGL::GLuint *)&sbo->sbo);
	Py_RETURN_NONE;
}

PyObject * UpdateVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	int offset;
	const void * data;
	int size;

	static const char * kwlist[] = {"vbo", "offset", "data", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!iy#:UpdateVertexBuffer", (char **)kwlist, &VertexBufferType, &vbo, &offset, &data, &size)) {
		return 0;
	}

	if (offset < 0 || offset + size > vbo->size) {
		PyErr_Format(ModuleRangeError, "UpdateVertexBuffer() data.offset = %d data.size = %d vbo.size = %d", offset, size, vbo->size);
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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!iy#:UpdateIndexBuffer", (char **)kwlist, &IndexBufferType, &ibo, &offset, &data, &size)) {
		return 0;
	}

	if (offset < 0 || offset + size > ibo->size) {
		PyErr_Format(ModuleRangeError, "UpdateIndexBuffer() data.offset = %d data.size = %d ibo.size = %d", offset, size, ibo->size);
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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!iy#:UpdateUniformBuffer", (char **)kwlist, &UniformBufferType, &ubo, &offset, &data, &size)) {
		return 0;
	}

	if (offset < 0 || offset + size > ubo->size) {
		PyErr_Format(ModuleRangeError, "UpdateUniformBuffer() data.offset = %d data.size = %d ubo.size = %d", offset, size, ubo->size);
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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!iy#:UpdateStorageBuffer", (char **)kwlist, &StorageBufferType, &sbo, &offset, &data, &size)) {
		return 0;
	}

	if (offset < 0 || offset + size > sbo->size) {
		PyErr_Format(ModuleRangeError, "UpdateStorageBuffer() data.offset = %d data.size = %d sbo.size = %d", offset, size, sbo->size);
	}

	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, sbo->sbo);
	OpenGL::glBufferSubData(OpenGL::GL_SHADER_STORAGE_BUFFER, (OpenGL::GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * UseUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	UniformBuffer * ubo;
	UniformBufferLocation * location;

	static const char * kwlist[] = {"ubo", "location", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!:UseUniformBuffer", (char **)kwlist, &UniformBufferType, &ubo, &UniformBufferLocationType, &location)) {
		return 0;
	}

	// if (location->size != ubo->size) {
	// 	// TODO: SET ERROR
	// 	return 0;
	// }

	OpenGL::glBindBufferBase(OpenGL::GL_UNIFORM_BUFFER, location->location, ubo->ubo);
	Py_RETURN_NONE;
}

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * sbo;
	int binding = 0;

	static const char * kwlist[] = {"sbo", "binding", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!|i:UseStorageBuffer", (char **)kwlist, &StorageBufferType, &sbo, &binding)) {
		return 0;
	}

	OpenGL::glBindBufferBase(OpenGL::GL_SHADER_STORAGE_BUFFER, binding, sbo->sbo);
	Py_RETURN_NONE;
}

PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	StorageBuffer * sbo;
	int offset = 0;
	int size = 0;

	static const char * kwlist[] = {"sbo", "offset", "size", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!|ii:ReadStorageBuffer", (char **)kwlist, &StorageBufferType, &sbo, &offset, &size)) {
		return 0;
	}

	if (size == 0) {
		size = sbo->size - offset;
	}

	if (offset < 0 || offset + size > sbo->size) {
		PyErr_Format(ModuleRangeError, "ReadStorageBuffer() data.offset = %d data.size = %d sbo.size = %d", offset, size, sbo->size);
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

// Dummy

PyObject * Dummy_NewVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_UseStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteStorageBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}
