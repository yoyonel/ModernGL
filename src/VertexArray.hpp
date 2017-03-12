#pragma once

#include <Python.h>

#include "ContextMember.hpp"
#include "Program.hpp"
#include "Buffer.hpp"

struct MGLVertexArray : public MGLContextMember {
	MGLProgram * program;

	PyObject * content;

	MGLBuffer * index_buffer;

	// TODO:
	PyObject * attributes;

	int vertex_array_obj;
	int num_vertices;
};

extern PyTypeObject MGLVertexArray_Type;

MGLVertexArray * MGLVertexArray_New();
void MGLVertexArray_Invalidate(MGLVertexArray * array);
