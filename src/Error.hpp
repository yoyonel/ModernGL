#pragma once

#include <Python.h>

#define TRACE __FILE__, __LINE__

struct MGLError {
	PyException_HEAD

	PyObject * github;
};

extern PyTypeObject MGLError_Type;

MGLError * MGLError_New(const char * filename, int line, const char * format, ...);
// void MGLError_LinkSource(MGLError * error, const char * filename, int line);
