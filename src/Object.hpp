#pragma once

#include <Python.h>

struct MGLObject {
	PyObject_HEAD

	// PyTypeObject * initial_type;
};

extern PyTypeObject MGLObject_Type;
