#pragma once

#include <Python.h>

#include "Object.hpp"
#include "Context.hpp"

struct MGLContextMember : public MGLObject {
	MGLContext * ctx;
};

extern PyTypeObject MGLContextMember_Type;

MGLContextMember * MGLContextMember_New();
