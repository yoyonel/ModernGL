#include "ModernGL.hpp"

#include "OpenGL.hpp"

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
		OpenGL::glDrawArrays(OpenGL::GL_POINTS, first, count);
	} else {
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElements(OpenGL::GL_POINTS, count, OpenGL::GL_UNSIGNED_INT, ptr);
	}

	OpenGL::glEndTransformFeedback();
	OpenGL::glDisable(OpenGL::GL_RASTERIZER_DISCARD);
	OpenGL::glFlush();

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * TransformTriangles(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformLines(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformLineStrip(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformLineLoop(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

// PyObject * TransformPoints(PyObject * self, PyObject * args, PyObject * kwargs) {
// 	Py_RETURN_NONE;
// }

PyObject * TransformLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}

PyObject * TransformTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs) {
	Py_RETURN_NONE;
}
