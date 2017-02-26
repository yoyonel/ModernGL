#pragma once

#include <Python.h>

#include "Object.hpp"
#include "GLMethods.hpp"

struct MGLContext : public MGLObject {
	void * rc_handle;
	void * dc_handle;

	int default_texture_unit;

	GLMethods gl;
};

extern PyTypeObject MGLContext_Type;

MGLContext * MGLContext_New();
void MGLContext_Initialize(MGLContext * self);
