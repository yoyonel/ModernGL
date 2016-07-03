#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * RenderTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangles", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleFan", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_FAN, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLines", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineLoop", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_LOOP, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderPoints", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_POINTS, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLinesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES_ADJACENCY, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTrianglesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, first, count, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangles", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleFan", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_FAN, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLines", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineLoop", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_LOOP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedPoints", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_POINTS, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLineStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedLinesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTriangleStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * RenderIndexedTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	int count;
	int first = 0;
	int instances = 1;

	static const char * kwlist[] = {"vao", "count", "first", "instances", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderIndexedTrianglesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		PyErr_SetString(PyExc_TypeError, "Expected VertexArray, got ...");
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
	OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}
