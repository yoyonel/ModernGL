#pragma once

#include "Common.hpp"

struct Program {
	PyObject_HEAD
	int program;
};

extern PyTypeObject ProgramType;

PyObject * CreateProgramType(int program);
