#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayListAttribute : public MGLVertexArrayMember {
};

extern PyTypeObject MGLVertexArrayListAttribute_Type;
