#ifdef MGL_DEBUG

#include "GLMethods.hpp"

#include "Attribute.hpp"
#include "Uniform.hpp"

void GLMethodsDebug_attrib_ptr(MGLAttribute * attribute, GLuint index, GLsizei stride, const GLvoid * pointer) {
	const GLMethodsImpl & gl = attribute->context->gl.gl;

	if (attribute->gl_attrib_ptr_proc == gl.VertexAttribPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribPointer(%u, %d, 0x%0x, %d, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, false, stride, pointer);
	} else if (attribute->gl_attrib_ptr_proc == gl.VertexAttribIPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribIPointer(%u, %d, 0x%0x, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, stride, pointer);
	} else if (attribute->gl_attrib_ptr_proc == gl.VertexAttribLPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribLPointer(%u, %d, 0x%0x, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, stride, pointer);
	}

	fflush(GLMethodsDebugFile);
}

void GLMethodsDebug_uniform_reader(MGLUniform * uniform, GLint location, GLvoid * params) {
	const GLMethodsImpl & gl = uniform->context->gl.gl;

	if (uniform->gl_value_reader_proc == (MGLProc)gl.GetUniformiv) {
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformiv(%u, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, params);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.GetUniformuiv) {
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformuiv(%u, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, params);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.GetUniformfv) {
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformfv(%u, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, params);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.GetUniformdv) {
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformdv(%u, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, params);
	}

	fflush(GLMethodsDebugFile);
}

void GLMethodsDebug_uniform_writer(MGLUniform * uniform, GLint location, GLsizei count, const GLvoid * values) {
	const GLMethodsImpl & gl = uniform->context->gl.gl;

	if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform1iv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1iv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform2iv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2iv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform3iv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3iv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform4iv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4iv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform1uiv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1uiv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform2uiv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2uiv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform3uiv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3uiv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform4uiv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4uiv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform1fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform2fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform3fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform4fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform1dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform2dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform3dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniform4dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2x3fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2x4fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3x2fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3x4fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4x2fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4x3fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4fv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4fv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2x3dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix2x4dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3x2dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix3x4dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4x2dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4x3dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	} else if (uniform->gl_value_reader_proc == (MGLProc)gl.ProgramUniformMatrix4dv) {
		fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4dv(%u, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), uniform->program_obj, location, count, false, values);
	}

	fflush(GLMethodsDebugFile);
}

#endif
