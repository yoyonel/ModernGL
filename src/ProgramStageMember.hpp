#pragma once

#include <Python.h>

#include "Object.hpp"
#include "ProgramStage.hpp"

struct MGLProgramStageMember : public MGLObject {
	union {
		PyTypeObject * initial_type;
		MGLProgramStage * program_stage;
	};
};

extern PyTypeObject MGLProgramStageMember_Type;
