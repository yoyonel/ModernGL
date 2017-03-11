#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayAttribute : public MGLVertexArrayMember {
};

extern PyTypeObject MGLVertexArrayAttribute_Type;
