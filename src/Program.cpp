#include "Program.hpp"

#include "Shader.hpp"
#include "Uniform.hpp"

MGLProgram * MGLProgram_New() {
	MGLProgram * self = (MGLProgram *)MGLProgram_Type.tp_alloc(&MGLProgram_Type, 0);
	return self;
}

void MGLProgram_Compile(MGLProgram * program) {
	GLMethods & gl = program->ctx->gl;

	int obj = gl.CreateProgram();

	int num_shaders = PyList_GET_SIZE(program->shaders);
	for (int i = 0; i < num_shaders; ++i) {
		MGLShader * shader = (MGLShader *)PyList_GET_ITEM(program->shaders, i);
		gl.AttachShader(obj, shader->obj);
	}

	// int num_varyings = PyList_GET_SIZE(program->varyings);
	// if (varyings_len) {
	// 	gl.TransformFeedbackVaryings(obj, varyings_len, varyings, GL_INTERLEAVED_ATTRIBS);
	// }

	int linked = GL_FALSE;
	gl.LinkProgram(obj);
	gl.GetProgramiv(obj, GL_LINK_STATUS, &linked);

	if (!linked) {
		static const char * logTitle = "GLSL Linker failed\n";
		static int logTitleLength = strlen(logTitle);

		int logLength = 0;
		gl.GetProgramiv(obj, GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			gl.DeleteProgram(obj);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		gl.GetProgramInfoLog(obj, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		gl.DeleteProgram(obj);
		PyErr_SetObject(PyExc_RuntimeError, content);
		return;
	}

	PyObject * uniforms = PyDict_New();

	int num_uniforms = 0;
	gl.GetProgramiv(obj, GL_ACTIVE_UNIFORMS, &num_uniforms);

	// printf("num_uniforms: %d\n", num_uniforms);

	for (int i = 0; i < num_uniforms; ++i) {
		MGLUniform * uniform = MGLUniform_New();

		int name_len = 0;
		char name[256];

		gl.GetActiveUniform(obj, i, 256, &name_len, &uniform->array_len, (GLenum *)&uniform->type, name);
		name[name_len] = 0;

		// printf("name: %s\n", name);

		// TODO:

		// if (info.name[info.name_len - 1] == ']') {
		// 	while (info.name_len && info.name[info.name_len] != '[') {
		// 		--info.name_len;
		// 	}
		// }

		// info.name[info.name_len] = 0;

		switch (uniform->type) {
			case GL_BOOL:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_bool_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_bool_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_bool_value_getter;
					uniform->value_setter = (void *)MGLUniform_bool_value_setter;
				}
				break;

			case GL_BOOL_VEC2:
				uniform->matrix = false;
				uniform->dimension = 2;
				uniform->element_size = 8;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform2iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_bvec2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_bvec2_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec2_value_setter;
				}
				break;

			case GL_BOOL_VEC3:
				uniform->matrix = false;
				uniform->dimension = 3;
				uniform->element_size = 12;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform3iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_bvec3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_bvec3_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec3_value_setter;
				}
				break;

			case GL_BOOL_VEC4:
				uniform->matrix = false;
				uniform->dimension = 4;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform4iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_bvec4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_bvec4_value_getter;
					uniform->value_setter = (void *)MGLUniform_bvec4_value_setter;
				}
				break;

			case GL_INT:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_int_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_int_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_int_value_getter;
					uniform->value_setter = (void *)MGLUniform_int_value_setter;
				}
				break;

			case GL_INT_VEC2:
				uniform->matrix = false;
				uniform->dimension = 2;
				uniform->element_size = 8;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform2iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_ivec2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_ivec2_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec2_value_setter;
				}
				break;

			case GL_INT_VEC3:
				uniform->matrix = false;
				uniform->dimension = 3;
				uniform->element_size = 12;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform3iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_ivec3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_ivec3_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec3_value_setter;
				}
				break;

			case GL_INT_VEC4:
				uniform->matrix = false;
				uniform->dimension = 4;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform4iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_ivec4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_ivec4_value_getter;
					uniform->value_setter = (void *)MGLUniform_ivec4_value_setter;
				}
				break;

			case GL_UNSIGNED_INT:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformuiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1uiv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_uint_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_uint_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_uint_value_getter;
					uniform->value_setter = (void *)MGLUniform_uint_value_setter;
				}
				break;

			case GL_UNSIGNED_INT_VEC2:
				uniform->matrix = false;
				uniform->dimension = 2;
				uniform->element_size = 8;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformuiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform2uiv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_uvec2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_uvec2_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec2_value_setter;
				}
				break;

			case GL_UNSIGNED_INT_VEC3:
				uniform->matrix = false;
				uniform->dimension = 3;
				uniform->element_size = 12;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformuiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform3uiv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_uvec3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_uvec3_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec3_value_setter;
				}
				break;

			case GL_UNSIGNED_INT_VEC4:
				uniform->matrix = false;
				uniform->dimension = 4;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformuiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform4uiv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_uvec4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_uvec4_value_getter;
					uniform->value_setter = (void *)MGLUniform_uvec4_value_setter;
				}
				break;

			case GL_FLOAT:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_value_setter;
				}
				break;

			case GL_FLOAT_VEC2:
				uniform->matrix = false;
				uniform->dimension = 2;
				uniform->element_size = 8;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform2fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_vec2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_vec2_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec2_value_setter;
				}
				break;

			case GL_FLOAT_VEC3:
				uniform->matrix = false;
				uniform->dimension = 3;
				uniform->element_size = 12;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform3fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_vec3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_vec3_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec3_value_setter;
				}
				break;

			case GL_FLOAT_VEC4:
				uniform->matrix = false;
				uniform->dimension = 4;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform4fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_vec4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_vec4_value_getter;
					uniform->value_setter = (void *)MGLUniform_vec4_value_setter;
				}
				break;

			case GL_DOUBLE:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 8;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_value_setter;
				}
				// TODO: continue here
				break;

			case GL_DOUBLE_VEC2:
				uniform->matrix = false;
				uniform->dimension = 2;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform2dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_dvec2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_dvec2_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec2_value_setter;
				}
				break;

			case GL_DOUBLE_VEC3:
				uniform->matrix = false;
				uniform->dimension = 3;
				uniform->element_size = 24;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform3dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_dvec3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_dvec3_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec3_value_setter;
				}
				break;

			case GL_DOUBLE_VEC4:
				uniform->matrix = false;
				uniform->dimension = 4;
				uniform->element_size = 32;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform4dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_dvec4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_dvec4_value_getter;
					uniform->value_setter = (void *)MGLUniform_dvec4_value_setter;
				}
				break;

			case GL_SAMPLER_2D:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_sampler_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_sampler_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_value_setter;
				}
				break;

			case GL_SAMPLER_2D_SHADOW:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_sampler_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_sampler_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_value_setter;
				}
				break;

			case GL_SAMPLER_2D_MULTISAMPLE:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_sampler_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_sampler_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_value_setter;
				}
				break;

			case GL_SAMPLER_CUBE:
				uniform->matrix = false;
				uniform->dimension = 1;
				uniform->element_size = 4;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformiv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniform1iv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_sampler_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_sampler_value_getter;
					uniform->value_setter = (void *)MGLUniform_sampler_value_setter;
				}
				break;

			case GL_FLOAT_MAT2:
				uniform->matrix = true;
				uniform->dimension = 4;
				uniform->element_size = 16;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x2_value_setter;
				}
				break;

			case GL_FLOAT_MAT2x3:
				uniform->matrix = true;
				uniform->dimension = 6;
				uniform->element_size = 24;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2x3fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x3_value_setter;
				}
				break;

			case GL_FLOAT_MAT2x4:
				uniform->matrix = true;
				uniform->dimension = 8;
				uniform->element_size = 32;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2x4fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_2x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_2x4_value_setter;
				}
				break;

			case GL_FLOAT_MAT3x2:
				uniform->matrix = true;
				uniform->dimension = 6;
				uniform->element_size = 24;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3x2fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x2_value_setter;
				}
				break;

			case GL_FLOAT_MAT3:
				uniform->matrix = true;
				uniform->dimension = 9;
				uniform->element_size = 36;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x3_value_setter;
				}
				break;

			case GL_FLOAT_MAT3x4:
				uniform->matrix = true;
				uniform->dimension = 12;
				uniform->element_size = 48;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3x4fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_3x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_3x4_value_setter;
				}
				break;

			case GL_FLOAT_MAT4x2:
				uniform->matrix = true;
				uniform->dimension = 8;
				uniform->element_size = 32;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4x2fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x2_value_setter;
				}
				break;

			case GL_FLOAT_MAT4x3:
				uniform->matrix = true;
				uniform->dimension = 12;
				uniform->element_size = 48;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4x3fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x3_value_setter;
				}
				break;

			case GL_FLOAT_MAT4:
				uniform->matrix = true;
				uniform->dimension = 16;
				uniform->element_size = 64;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformfv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4fv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_float_matrix_4x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_float_matrix_4x4_value_setter;
				}
				break;

			case GL_DOUBLE_MAT2:
				uniform->matrix = true;
				uniform->dimension = 4;
				uniform->element_size = 32;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x2_value_setter;
				}
				break;

			case GL_DOUBLE_MAT2x3:
				uniform->matrix = true;
				uniform->dimension = 6;
				uniform->element_size = 48;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2x3dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x3_value_setter;
				}
				break;

			case GL_DOUBLE_MAT2x4:
				uniform->matrix = true;
				uniform->dimension = 8;
				uniform->element_size = 64;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix2x4dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_2x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_2x4_value_setter;
				}
				break;

			case GL_DOUBLE_MAT3x2:
				uniform->matrix = true;
				uniform->dimension = 6;
				uniform->element_size = 48;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3x2dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x2_value_setter;
				}
				break;

			case GL_DOUBLE_MAT3:
				uniform->matrix = true;
				uniform->dimension = 9;
				uniform->element_size = 72;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x3_value_setter;
				}
				break;

			case GL_DOUBLE_MAT3x4:
				uniform->matrix = true;
				uniform->dimension = 12;
				uniform->element_size = 96;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix3x4dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_3x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_3x4_value_setter;
				}
				break;

			case GL_DOUBLE_MAT4x2:
				uniform->matrix = true;
				uniform->dimension = 8;
				uniform->element_size = 64;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4x2dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x2_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x2_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x2_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x2_value_setter;
				}
				break;

			case GL_DOUBLE_MAT4x3:
				uniform->matrix = true;
				uniform->dimension = 12;
				uniform->element_size = 96;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4x3dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x3_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x3_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x3_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x3_value_setter;
				}
				break;

			case GL_DOUBLE_MAT4:
				uniform->matrix = true;
				uniform->dimension = 16;
				uniform->element_size = 128;
				uniform->gl_value_reader_proc = (void *)program->ctx->gl.GetUniformdv;
				uniform->gl_value_writer_proc = (void *)program->ctx->gl.ProgramUniformMatrix4dv;
				if (uniform->array_len > 1) {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x4_array_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x4_array_value_setter;
				} else {
					uniform->value_getter = (void *)MGLUniform_double_matrix_4x4_value_getter;
					uniform->value_setter = (void *)MGLUniform_double_matrix_4x4_value_setter;
				}
				break;

			default:
				uniform->value_getter = (void *)MGLUniform_invalid_getter;
				uniform->value_setter = (void *)MGLUniform_invalid_setter;
				break;
		}

		// TODO: check shadow and sampler cube

		uniform->location = gl.GetUniformLocation(obj, name);
		uniform->name = PyUnicode_FromStringAndSize(name, name_len);

		Py_INCREF((PyObject *)uniform->name);
		Py_INCREF((PyObject *)uniform);

		PyDict_SetItem(uniforms, uniform->name, (PyObject *)uniform);

		if (uniform->location < 0) {
			Py_DECREF((PyObject *)uniform);
			continue;
		}

		Py_INCREF((PyObject *)program);
		uniform->program = program;
	}

	// TODO:
	// int num_attributes = 0;
	// gl.GetProgramiv(obj, GL_ACTIVE_ATTRIBUTES, &num_attributes);

	// TODO:
	// int num_uniform_blocks = 0;
	// gl.GetProgramiv(obj, GL_ACTIVE_UNIFORM_BLOCKS, &num_uniform_blocks);

	// TODO:
	// int num_uniform_blocks = 0;
	// gl.GetProgramiv(obj, GL_ACTIVE_UNIFORM_BLOCKS, &num_uniform_blocks);

	// TODO:
	// glGetProgramStageiv
	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgramStage.xhtml

	program->uniforms = uniforms;
	program->obj = obj;
}

PyObject * MGLProgram_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLProgram * self = (MGLProgram *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLProgram_tp_dealloc(MGLProgram * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLProgram_tp_init(MGLProgram * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLProgram_tp_str(MGLProgram * self) {
	return PyUnicode_FromFormat("<ModernGL.Program>");
}

PyObject * MGLProgram_release(MGLProgram * self) {
	if (self->ob_base.ob_refcnt != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO: release

	// Py_DECREF((PyObject *)self);

	Py_RETURN_NONE;
}

PyMethodDef MGLProgram_tp_methods[] = {
	{"release", (PyCFunction)MGLProgram_release, METH_NOARGS, 0},
	{0},
};

PyObject * MGLProgram_get_shaders(MGLProgram * self, void * closure) {
	Py_INCREF(self->shaders);
	return self->shaders;
}

PyObject * MGLProgram_get_varyings(MGLProgram * self, void * closure) {
	Py_INCREF(self->varyings);
	return self->varyings;
}

PyObject * MGLProgram_get_uniforms(MGLProgram * self, void * closure) {
	Py_INCREF(self->uniforms);
	return self->uniforms;
}

PyGetSetDef MGLProgram_tp_getseters[] = {
	{(char *)"shaders", (getter)MGLProgram_get_shaders, 0, 0, 0},
	{(char *)"varyings", (getter)MGLProgram_get_varyings, 0, 0, 0},
	{(char *)"uniforms", (getter)MGLProgram_get_uniforms, 0, 0, 0},
	{0},
};

// PyObject * Program_get_item(Program * self, PyObject * key) {
// 	char * name = PyUnicode_AsUTF8(key);

// 	if (!name) {
// 		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
// 		return 0;
// 	}

// 	UniformMapIterator it = self->uniforms->find(name);
// 	if (it == self->uniforms->end()) {
// 		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
// 		return 0;
// 	}

// 	PyObject * uniform = (PyObject *)it->second;
// 	Py_INCREF(uniform);
// 	return uniform;
// }

// int Program_set_item(Program * self, PyObject * key, PyObject * value) {
// 	char * name = PyUnicode_AsUTF8(key);

// 	if (!name) {
// 		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
// 		return -1;
// 	}

// 	UniformMapIterator it = self->uniforms->find(name);
// 	if (it == self->uniforms->end()) {
// 		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
// 		return -1;
// 	}

// 	return it->second->setter(it->second, value);
// }

PyMappingMethods Program_map = {
	0, // TODO:
	// (binaryfunc)Program_get_item,
	// (objobjargproc)Program_set_item,
};

const char * MGLProgram_tp_doc = R"(
)";

PyTypeObject MGLProgram_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Program",                                     // tp_name
	sizeof(MGLProgram),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLProgram_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLProgram_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	&Program_map,                                           // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLProgram_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLProgram_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLProgram_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLProgram_tp_getseters,                                // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLProgram_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLProgram_tp_new,                                      // tp_new
};
