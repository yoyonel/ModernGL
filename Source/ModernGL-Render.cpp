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

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleFan", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLines", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStrip", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineLoop", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderPoints", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLineStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderLinesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTriangleStripAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Oi|ii:RenderTrianglesAdjacency", (char **)kwlist, &vao, &count, &first, &instances)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("vao", vao, VertexArrayType);

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
