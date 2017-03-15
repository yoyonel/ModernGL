#pragma once

#include <Python.h>

#include "Object.hpp"
#include "Program.hpp"

struct MGLProgramMember : public MGLObject {
	MGLProgram * program;
};

extern PyTypeObject MGLProgramMember_Type;
