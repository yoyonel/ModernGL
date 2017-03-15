#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayMatrixAttribute : public MGLVertexArrayMember {
	PyObject * content;
	int location;
};

extern PyTypeObject MGLVertexArrayMatrixAttribute_Type;

MGLVertexArrayMatrixAttribute * MGLVertexArrayMatrixAttribute_New();
