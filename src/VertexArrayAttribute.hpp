#pragma once

#include "Python.hpp"

#include "Object.hpp"
#include "GLMethods.hpp"

struct MGLVertexArrayAttribute : public MGLObject {
	const GLMethods * gl;
	
	void * gl_attrib_ptr_proc;

	int vertex_array_obj;
	int location;
	int type;

	int scalar_type;
	int row_length;

	bool normalizable;
};

extern PyTypeObject MGLVertexArrayAttribute_Type;

MGLVertexArrayAttribute * MGLVertexArrayAttribute_New();
void MGLVertexArrayAttribute_Complete(MGLVertexArrayAttribute * attribute, const GLMethods & gl);
