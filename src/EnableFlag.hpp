#pragma once

#include <Python.h>

#include "Object.hpp"

struct MGLEnableFlag : public MGLObject {
	const char * name;
	int flag;
};

extern PyTypeObject MGLEnableFlag_Type;

MGLEnableFlag * MGLEnableFlag_New();
