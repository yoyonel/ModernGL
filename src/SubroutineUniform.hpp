#pragma once

#include <Python.h>

#include "ProgramStageMember.hpp"

struct MGLSubroutineUniform : public MGLProgramStageMember {
	PyObject * name;

	int number;
	int index;
};

extern PyTypeObject MGLSubroutineUniform_Type;

MGLSubroutineUniform * MGLSubroutineUniform_New();
void MGLSubroutineUniform_Complete(MGLSubroutineUniform * subroutine_uniform);
