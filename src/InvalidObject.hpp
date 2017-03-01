#pragma once

#include <Python.h>

#include "Object.hpp"

struct MGLInvalidObject : public MGLObject {
	PyTypeObject * initial_type;
};

extern PyTypeObject MGLInvalidObject_Type;
