#pragma once

#include <Python.h>

#include "Object.hpp"
#include "Program.hpp"

struct MGLProgramMember : public MGLObject {
	union {
		PyTypeObject * initial_type;
		MGLProgram * program;
	};
};

extern PyTypeObject MGLProgramMember_Type;
