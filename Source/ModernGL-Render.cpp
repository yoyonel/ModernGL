#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * RenderTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderTriangles", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderTriangleStrip", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderTriangleFan", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_FAN, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_FAN, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderLines", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderLineStrip", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderLineLoop", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_LOOP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_LOOP, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderPoints", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_POINTS, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_POINTS, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderLineStripAdjacency", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderLinesAdjacency", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES_ADJACENCY, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderTriangleStripAdjacency", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!i|ii:RenderTrianglesAdjacency", (char **)kwlist, &VertexArrayType, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	} else {
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, first, count, instances);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

//


PyObject * Dummy_RenderPoints(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderPoints() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderPoints() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLines(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLines() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLines() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineLoop(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineLoop() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineLoop() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangles(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangles() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangles() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleFan(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleFan() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleFan() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLinesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLinesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLinesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTrianglesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTrianglesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTrianglesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}
