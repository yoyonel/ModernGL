#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayMatrixAttribute : public MGLVertexArrayMember {
};

extern PyTypeObject MGLVertexArrayMatrixAttribute_Type;
