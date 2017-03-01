#pragma once

#include <Python.h>

#include "ContextMember.hpp"
#include "Primitive.hpp"

struct MGLProgram : public MGLContextMember {
	PyObject * shaders; // TODO: tuple

	PyObject * uniforms;
	PyObject * attributes;
	PyObject * subroutines;
	PyObject * varyings;

	PyObject * uniforms_proxy;
	PyObject * attributes_proxy;
	PyObject * subroutines_proxy;
	PyObject * varyings_proxy;

	MGLPrimitive * geometry_input;
	MGLPrimitive * geometry_output;

	int obj;
};

extern PyTypeObject MGLProgram_Type;

MGLProgram * MGLProgram_New();
void MGLProgram_Invalidate(MGLProgram * program);
void MGLProgram_Compile(MGLProgram * program, PyObject * varyings);

void MGLProgram_LoadUniforms(MGLProgram * program);
void MGLProgram_LoadAttributes(MGLProgram * program);
void MGLProgram_LoadSubroutines(MGLProgram * program);
void MGLProgram_LoadVaryings(MGLProgram * program);
