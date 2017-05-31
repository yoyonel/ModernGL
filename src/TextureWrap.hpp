#pragma once

#include "Python.hpp"

#include "Object.hpp"

struct MGLTextureWrap : public MGLObject {
	PyObject * wrapper;

	int wrap;
};

extern PyTypeObject MGLTextureWrap_Type;

MGLTextureWrap * MGLTextureWrap_New();

extern MGLTextureWrap * MGL_CLAMP_TO_EDGE;
extern MGLTextureWrap * MGL_REPEAT;
