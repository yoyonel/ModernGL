#pragma once

#include <Python.h>

#include "ProgramStageMember.hpp"

struct MGLSubroutineUniform : public MGLProgramStageMember {
};

extern PyTypeObject MGLSubroutineUniform_Type;

MGLSubroutineUniform * MGLUniform_New();
