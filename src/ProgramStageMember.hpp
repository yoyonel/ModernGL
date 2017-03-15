#pragma once

#include <Python.h>

#include "Object.hpp"
#include "ProgramStage.hpp"

struct MGLProgramStageMember : public MGLObject {
	MGLProgramStage * program_stage;
};

extern PyTypeObject MGLProgramStageMember_Type;
