#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * TransformTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_TRIANGLES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_TRIANGLES, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_TRIANGLES, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_TRIANGLES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_TRIANGLE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_TRIANGLE_STRIP, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_TRIANGLES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_TRIANGLE_FAN, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_TRIANGLE_FAN, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_LINES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_LINES, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_LINES, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_LINES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_LINE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_LINE_STRIP, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_LINES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_LINE_LOOP, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_LINE_LOOP, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_POINTS);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_POINTS, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_POINTS, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_LINES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_LINE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_LINE_STRIP_ADJACENCY, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_LINES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_LINES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_LINES_ADJACENCY, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_TRIANGLES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexBuffer * vbo;
	VertexArray * vao;
	int count;
	int first = 0;

	static const char * kwlist[] = {"vao", "output", "count", "first", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!O!i|i:RunTransformShader", (char **)kwlist, &VertexArrayType, &vao, &VertexBufferType, &vbo, &count, &first)) {
		return 0;
	}

	if (activeProgram != vao->program) {
		OpenGL::glUseProgram(vao->program);
		activeProgram = vao->program;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glBindBufferBase(OpenGL::GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo->vbo);

	OpenGL::glEnable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glBeginTransformFeedback(OpenGL::GL_TRIANGLES);

	if (vao->indexed) {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_TRIANGLES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr);
	} else {
		OpenGL::glDrawArrays(OpenGL::GL_TRIANGLES_ADJACENCY, first, count);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}
