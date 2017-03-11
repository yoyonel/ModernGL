#pragma once

#include <Python.h>

#include "ProgramMember.hpp"

struct MGLProgramStage : public MGLProgramMember {
};

extern PyTypeObject MGLProgramStage_Type;

MGLProgramStage * MGLUniform_New();
