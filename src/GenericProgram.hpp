#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLGenericProgram : public MGLContextMember {
	int program_obj;

	PyObject * uniforms;
	PyObject * uniforms_proxy;
};

extern PyTypeObject MGLGenericProgram_Type;
