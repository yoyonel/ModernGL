#pragma once

#include "Common.h"

struct VertexArray {
	PyObject_HEAD
	int vao;
	bool indexed;
	int program;
};

extern PyTypeObject VertexArrayType;

PyObject * CreateVertexArrayType(int vao, int program, bool indexed);
