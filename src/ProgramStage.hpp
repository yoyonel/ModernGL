#pragma once

#include <Python.h>

#include "ProgramMember.hpp"
#include "Shader.hpp"

struct MGLProgramStage : public MGLProgramMember {
	MGLShader * shader;

	PyObject * subroutines;
	PyObject * subroutine_uniforms;
};

extern PyTypeObject MGLProgramStage_Type;

MGLProgramStage * MGLProgramStage_New();
void MGLProgramStage_Complete(MGLProgramStage * program_stage);
