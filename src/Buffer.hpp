#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLBuffer : public MGLContextMember {
	int obj;

	int size;
	bool dynamic;
};

extern PyTypeObject MGLBuffer_Type;

MGLBuffer * MGLBuffer_New();
