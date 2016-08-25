#pragma once

#include "Common.h"

struct ComputeShader {
	PyObject_HEAD
	int shader;
	int program;
};

extern PyTypeObject ComputeShaderType;

PyObject * CreateComputeShaderType(int shader, int program);
