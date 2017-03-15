#pragma once

#include <Python.h>

#include "Object.hpp"
#include "GLMethods.hpp"

struct MGLContext : public MGLObject {
	PyObject * default_framebuffer;

	void * rc_handle;
	void * dc_handle;

	int max_texture_units;
	int default_texture_unit;

	bool standalone;

	GLMethods gl;
};

extern PyTypeObject MGLContext_Type;

MGLContext * MGLContext_New();
void MGLContext_Invalidate(MGLContext * context);
void MGLContext_Initialize(MGLContext * self);
