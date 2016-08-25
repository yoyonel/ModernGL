#pragma once

#include "Common.h"

struct VertexBuffer {
	PyObject_HEAD
	int vbo;
	int size;
};

extern PyTypeObject VertexBufferType;

PyObject * CreateVertexBufferType(int vbo, int size);
