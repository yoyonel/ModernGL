#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLGenericProgram : public MGLContextMember {
	int obj;
};

extern PyTypeObject MGLGenericProgram_Type;
