#pragma once

#include <Python.h>

#include "Object.hpp"
#include "Program.hpp"

struct MGLProgramMember : public MGLObject {
	int program_obj;
};

extern PyTypeObject MGLProgramMember_Type;
