#pragma once

#include "Python.hpp"

#include "Program.hpp"

struct MGLUniformBlock : public MGLObject {
	MGLProgram * program;
	PyObject * name;

	int index;
	int size;
};

extern PyTypeObject MGLUniformBlock_Type;

MGLUniformBlock * MGLUniformBlock_New();
void MGLUniformBlock_Complete(MGLUniformBlock * uniform_block, const GLMethods & gl);
