#pragma once

#include <Python.h>

#include "ContextMember.hpp"
#include "Primitive.hpp"

struct MGLComputeShader : public MGLContextMember {
	int program_obj;
	int shader_obj;

	// TODO:
};

extern PyTypeObject MGLComputeShader_Type;

MGLComputeShader * MGLComputeShader_New();
void MGLComputeShader_Invalidate(MGLComputeShader * program);
