#pragma once

#include "Common.h"

struct Program {
	PyObject_HEAD
	int program;
};

extern PyTypeObject ProgramType;

PyObject * CreateProgramType(int program);
