#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLTexture : public MGLContextMember {
	int obj;

	int width;
	int height;
	int components;

	bool floats;
	bool depth;
};

extern PyTypeObject MGLTexture_Type;

MGLTexture * MGLTexture_New();
void MGLTexture_Invalidate(MGLTexture * texture);
