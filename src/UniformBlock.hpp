#pragma once

#include <Python.h>

#include "ProgramMember.hpp"

struct MGLUniformBlock : public MGLProgramMember {
};

extern PyTypeObject MGLUniformBlock_Type;

MGLUniformBlock * MGLUniformBlock_New();
