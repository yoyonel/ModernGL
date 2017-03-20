#pragma once

#include <Python.h>

#include "GenericProgram.hpp"

struct MGLComputeShader : public MGLGenericProgram {
	int program_obj;
	int shader_obj;

	PyObject * source;
};

extern PyTypeObject MGLComputeShader_Type;

MGLComputeShader * MGLComputeShader_New();
void MGLComputeShader_Invalidate(MGLComputeShader * program);
