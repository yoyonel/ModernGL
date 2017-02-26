#pragma once

#include <Python.h>

#include "ContextMember.hpp"

enum SHADER_SLOT_ENUM {
	VERTEX_SHADER_SLOT,
	FRAGMENT_SHADER_SLOT,
	GEOMETRY_SHADER_SLOT,
	TESSELATION_EVALUATION_SHADER_SLOT,
	TESSELATION_CONTROL_SHADER_SLOT,
	NUM_SHADER_SLOTS,
};

struct MGLShader : public MGLContextMember {
	int obj;

	int shader_type;
	PyObject * source;
};

extern PyTypeObject MGLShader_Type;

MGLShader * MGLShader_New();
void MGLShader_Compile(MGLShader * shader);
