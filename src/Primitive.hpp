#pragma once

#include <Python.h>

#include "Object.hpp"

struct MGLPrimitive : public MGLObject {
	const char * name;

	int primitive;
	int transform_primitive;
};

extern PyTypeObject MGLPrimitive_Type;

MGLPrimitive * MGLPrimitive_New();
