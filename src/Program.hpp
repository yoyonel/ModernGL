#pragma once

#include <Python.h>

#include "GenericProgram.hpp"
#include "Primitive.hpp"

struct MGLProgram : public MGLGenericProgram {
	PyObject * shaders;

	PyObject * vertex_shader;
	PyObject * fragment_shader;
	PyObject * geometry_shader;
	PyObject * tesselation_evaluation_shader;
	PyObject * tesselation_control_shader;

	PyObject * attributes;
	PyObject * attributes_proxy;

	PyObject * varyings;
	PyObject * varyings_proxy;

	MGLPrimitive * geometry_input;
	MGLPrimitive * geometry_output;

	// TODO:
	MGLPrimitive * geometry_vertices;
};

extern PyTypeObject MGLProgram_Type;

MGLProgram * MGLProgram_New();
void MGLProgram_Invalidate(MGLProgram * program);
void MGLProgram_Compile(MGLProgram * program, PyObject * outputs);
