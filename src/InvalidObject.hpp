#pragma once

#include <Python.h>

#include "Object.hpp"

struct MGLInvalidObject : public MGLObject {
};

extern PyTypeObject MGLInvalidObject_Type;
