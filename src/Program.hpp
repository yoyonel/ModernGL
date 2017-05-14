#pragma once

#include "Python.hpp"

#include "ContextMember.hpp"
#include "Primitive.hpp"

struct MGLProgram : public MGLContextMember {
	PyObject * shaders;

	PyObject * vertex_shader;
	PyObject * fragment_shader;
	PyObject * geometry_shader;
	PyObject * tess_evaluation_shader;
	PyObject * tess_control_shader;

	PyObject * uniforms;
	PyObject * uniform_blocks;
	PyObject * attributes;
	PyObject * varyings;

	MGLPrimitive * geometry_input;
	MGLPrimitive * geometry_output;

	int geometry_vertices;

	int program_obj;
};

extern PyTypeObject MGLProgram_Type;

MGLProgram * MGLProgram_New();
void MGLProgram_Invalidate(MGLProgram * program);
void MGLProgram_Compile(MGLProgram * program, PyObject * outputs);
