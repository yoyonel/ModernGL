#pragma once

#include <Python.h>

#include "GenericProgram.hpp"

struct MGLComputeShader : public MGLGenericProgram {
	int shader;

	// TODO:
};

extern PyTypeObject MGLComputeShader_Type;

MGLComputeShader * MGLComputeShader_New();
void MGLComputeShader_Invalidate(MGLComputeShader * program);
