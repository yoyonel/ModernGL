#pragma once

#include <Python.h>

struct MGLObject {
	PyObject_HEAD
};

extern PyTypeObject MGLObject_Type;
