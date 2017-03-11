#pragma once

#include <Python.h>

#include "ProgramMember.hpp"

struct MGLSubroutineUniform : public MGLProgramMember {
};

extern PyTypeObject MGLSubroutineUniform_Type;

MGLSubroutineUniform * MGLUniform_New();
