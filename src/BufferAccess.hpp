#pragma once

#include <Python.h>

#include "Buffer.hpp"

struct MGLBufferAccess : public MGLObject {
	MGLBuffer * buffer;

	void * ptr;

	int obj;
	int offset;
	int size;
	int access;
};

extern PyTypeObject MGLBufferAccess_Type;

MGLBufferAccess * MGLBufferAccess_New();
