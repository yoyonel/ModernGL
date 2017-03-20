#pragma once

#include <Python.h>

#include "Object.hpp"
#include "ProgramStage.hpp"

struct MGLProgramStageMember : public MGLObject {
	int program_obj;
	int shader_type;
};

extern PyTypeObject MGLProgramStageMember_Type;
