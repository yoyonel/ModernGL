#pragma once

#include <Python.h>

#include "ProgramMember.hpp"
#include "Program.hpp"

struct MGLVarying : public MGLProgramMember {
	PyObject * name;

	void * value_getter;
	void * value_setter;
	void * gl_value_reader_proc;
	void * gl_value_writer_proc;

	int index;
	int type;

	int dimension;
	int element_size;
	int array_length;

	bool matrix;
};

extern PyTypeObject MGLVarying_Type;

MGLVarying * MGLVarying_New();
void MGLVarying_Invalidate(MGLVarying * varying);
void MGLVarying_Complete(MGLVarying * varying);
