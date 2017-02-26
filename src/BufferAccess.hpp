#pragma once

#include <Python.h>

#include "Buffer.hpp"

struct MGLBufferAccess : public MGLObject {
	MGLBuffer * buffer;

	int obj;
	int offset;
	int size;
	int access;

	void * ptr;
};

extern PyTypeObject MGLBufferAccess_Type;

MGLBufferAccess * MGLBufferAccess_New();
