#pragma once

#include <Python.h>

#include "VertexArrayMember.hpp"

struct MGLVertexArrayAttribute : public MGLVertexArrayMember {
	int location;

	int type;

	void * gl_attrib_ptr_proc;
	void * gl_attrib_getter_proc;
	void * gl_attrib_setter_proc;
};

extern PyTypeObject MGLVertexArrayAttribute_Type;

MGLVertexArrayAttribute * MGLVertexArrayAttribute_New();
void MGLVertexArrayAttribute_Complete(MGLVertexArrayAttribute * attribute);
