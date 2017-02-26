#pragma once

#include <Python.h>

#include "ContextMember.hpp"

// TODO:

struct MGLRenderbuffer : public MGLContextMember {
	int obj;
};

extern PyTypeObject MGLRenderbuffer_Type;

MGLRenderbuffer * MGLRenderbuffer_New();
