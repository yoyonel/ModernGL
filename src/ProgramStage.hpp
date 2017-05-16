#pragma once

#include "Python.hpp"

#include "ProgramMember.hpp"
#include "Shader.hpp"

struct MGLProgramStage : public MGLProgramMember {
	PyObject * subroutines;
	PyObject * subroutine_uniforms;
	int shader_type;
};

extern PyTypeObject MGLProgramStage_Type;

MGLProgramStage * MGLProgramStage_New();
void MGLProgramStage_Complete(MGLProgramStage * program_stage, int shader_type, int program_obj, const GLMethods & gl);
