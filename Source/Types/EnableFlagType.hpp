#pragma once

#include "Common.h"

struct EnableFlag {
	PyObject_HEAD
	unsigned value;
};

extern PyTypeObject EnableFlagType;

PyObject * CreateEnableFlagType(unsigned value);
