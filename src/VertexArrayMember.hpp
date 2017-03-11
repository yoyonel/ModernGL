#pragma once

#include <Python.h>

#include "Object.hpp"
#include "VertexArray.hpp"

struct MGLVertexArrayMember : public MGLObject {
	union {
		PyTypeObject * initial_type;
		MGLVertexArray * vertex_array;
	};
};

extern PyTypeObject MGLVertexArrayMember_Type;
