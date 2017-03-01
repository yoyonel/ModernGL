#pragma once

#include <Python.h>

#include "ProgramMember.hpp"
#include "Program.hpp"

struct MGLAttribute : public MGLProgramMember {
	PyObject * name;

	void * value_getter;
	void * value_setter;
	void * gl_value_reader_proc;
	void * gl_value_writer_proc;

	int index;
	int location;
	int type;

	int dimension;
	int element_size;
	int array_len;

	bool matrix;
};

extern PyTypeObject MGLAttribute_Type;

MGLAttribute * MGLAttribute_New();
void MGLAttribute_Invalidate(MGLAttribute * attribute);
void MGLAttribute_Complete(MGLAttribute * attribute);
