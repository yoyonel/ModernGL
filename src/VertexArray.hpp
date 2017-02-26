#pragma once

#include <Python.h>

#include "ContextMember.hpp"
#include "Program.hpp"

struct MGLVertexArray : public MGLContextMember {
	int obj;

	MGLProgram * program;
	PyObject * content;

	int num_vertices;
	bool indexed;
};

extern PyTypeObject MGLVertexArray_Type;

MGLVertexArray * MGLVertexArray_New();
