#pragma once

#include <Python.h>

#include "Object.hpp"

struct MGLVersion : public MGLObject {
	const char * name;

	int major;
	int minor;
};

extern PyTypeObject MGLVersion_Type;

MGLVersion * MGLVersion_New();
