#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLProgram : public MGLContextMember {
	int obj;

	PyObject * shaders;
	PyObject * varyings;

	PyObject * uniforms;
};

extern PyTypeObject MGLProgram_Type;

MGLProgram * MGLProgram_New();
void MGLProgram_Compile(MGLProgram * program);
