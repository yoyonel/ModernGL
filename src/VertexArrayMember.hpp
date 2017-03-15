#pragma once

#include <Python.h>

#include "Object.hpp"
#include "VertexArray.hpp"

struct MGLVertexArrayMember : public MGLObject {
	MGLVertexArray * vertex_array;
};

extern PyTypeObject MGLVertexArrayMember_Type;
