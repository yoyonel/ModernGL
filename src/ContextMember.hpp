#pragma once

#include <Python.h>

#include "Object.hpp"
#include "Context.hpp"

struct MGLContextMember : public MGLObject {
	union {
		PyTypeObject * initial_type;
		MGLContext * context;
	};
};

extern PyTypeObject MGLContextMember_Type;
