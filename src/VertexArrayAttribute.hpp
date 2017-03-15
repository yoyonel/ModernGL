#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayAttribute : public MGLVertexArrayMember {
	int location;
};

extern PyTypeObject MGLVertexArrayAttribute_Type;

MGLVertexArrayAttribute * MGLVertexArrayAttribute_New();
