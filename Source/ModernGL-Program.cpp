#include "ModernGL.hpp"

#include "OpenGL.hpp"

const char * categoryNames[] = {
	"VertexShader",
	"FragmentShader",
	"GeometryShader",
	"TessEvaluationShader",
	"TessControlShader",
};

PyObject * NewProgram(PyObject * self, PyObject * args) {
	PyObject * shaders;

	if (!PyArg_ParseTuple(args, "O:NewProgram", &shaders)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("shaders", shaders, PyList_Type);

	int count = (int)PyList_Size(shaders);

	int category[NUM_SHADER_CATEGORIES] = {};
	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);
		
		CHECK_AND_REPORT_ELEMENT_TYPE_ERROR("shaders", shader, ShaderType, i);
		
		if (shader->attached) {
			PyErr_Format(ModuleError, "NewProgram() shaders[%d] is already attached to another program", i);
			return 0;
		}

		++category[shader->category];
	}

	for (int i = 0; i < NUM_SHADER_CATEGORIES; ++i) {
		if (category[i] > 1) {
			PyErr_Format(ModuleError, "NewProgram() duplicate %s in `shaders`", categoryNames[i]);
			return 0;
		}
	}
	
	int program = OpenGL::glCreateProgram();

	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);
		OpenGL::glAttachShader(program, shader->shader);
	}

	int linked = OpenGL::GL_FALSE;
	OpenGL::glLinkProgram(program);
	OpenGL::glGetProgramiv(program, OpenGL::GL_LINK_STATUS, &linked);

	if (!linked) {
		static const char * logTitle = "NewProgram() linking failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetProgramiv(program, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteProgram(program);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetProgramInfoLog(program, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteProgram(program);
		PyErr_SetObject(ModuleError, content);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);
		shader->attached = true;
	}

	PyObject * dict = PyDict_New();

	int uniforms = 0;
	OpenGL::glGetProgramiv(program, OpenGL::GL_ACTIVE_UNIFORMS, &uniforms);
	for (int i = 0; i < uniforms; ++i) {
		char name[64 + 1];
		int size;
		int length;
		unsigned type;
		OpenGL::glGetActiveUniform(program, i, 64, &length, &size, &type, name);
		int location = OpenGL::glGetUniformLocation(program, name);
		name[length] = 0;
		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformLocationType(location, program));
		}
	}

	int uniformBlocks = 0;
	OpenGL::glGetProgramiv(program, OpenGL::GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlocks);
	for (int i = 0; i < uniformBlocks; ++i) {
		char name[64 + 1];
		int length;
		int location = -1;
		OpenGL::glGetActiveUniformBlockName(program, i, 64, &length, name);
		OpenGL::glGetActiveUniformBlockiv(program, i, OpenGL::GL_UNIFORM_BLOCK_BINDING, &location);
		name[length] = 0;
		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformBufferLocationType(location, program));
		}
	}

	return PyTuple_Pack(2, CreateProgramType(program), dict);
}

PyObject * DeleteProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O:DeleteProgram", &program)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("program", program, ProgramType);

	int shaders[8] = {};
	int numShaders = 0;

	OpenGL::glGetAttachedShaders(program->program, 8, &numShaders, (OpenGL::GLuint *)shaders);
	for (int i = 0; i < numShaders; ++i) {
		OpenGL::glDeleteShader(shaders[i]);
	}
	OpenGL::glDeleteProgram(program->program);
	Py_RETURN_NONE;
}

PyObject * Uniform1f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;

	if (!PyArg_ParseTuple(args, "Of:Uniform1f", &location, &v0)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform1f(location->location, v0);
	Py_RETURN_NONE;
}

PyObject * Uniform2f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;

	if (!PyArg_ParseTuple(args, "Off:Uniform2f", &location, &v0, &v1)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform2f(location->location, v0, v1);
	Py_RETURN_NONE;
}

PyObject * Uniform3f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;
	float v2;

	if (!PyArg_ParseTuple(args, "Offf:Uniform3f", &location, &v0, &v1, &v2)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform3f(location->location, v0, v1, v2);
	Py_RETURN_NONE;
}

PyObject * Uniform4f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;
	float v1;
	float v2;
	float v3;

	if (!PyArg_ParseTuple(args, "Offff:Uniform4f", &location, &v0, &v1, &v2, &v3)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform4f(location->location, v0, v1, v2, v3);
	Py_RETURN_NONE;
}

PyObject * Uniform1i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;

	if (!PyArg_ParseTuple(args, "Oi:Uniform1i", &location, &v0)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform1i(location->location, v0);
	Py_RETURN_NONE;
}

PyObject * Uniform2i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;

	if (!PyArg_ParseTuple(args, "Oii:Uniform2i", &location, &v0, &v1)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform2i(location->location, v0, v1);
	Py_RETURN_NONE;
}

PyObject * Uniform3i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;
	int v2;

	if (!PyArg_ParseTuple(args, "Oiii:Uniform3i", &location, &v0, &v1, &v2)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform3i(location->location, v0, v1, v2);
	Py_RETURN_NONE;
}

PyObject * Uniform4i(PyObject * self, PyObject * args) {
	UniformLocation * location;
	int v0;
	int v1;
	int v2;
	int v3;

	if (!PyArg_ParseTuple(args, "Oiiii:Uniform4i", &location, &v0, &v1, &v2, &v3)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	OpenGL::glUniform4i(location->location, v0, v1, v2, v3);
	Py_RETURN_NONE;
}

PyObject * UniformMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * matrix;

	if (!PyArg_ParseTuple(args, "OO:UniformMatrix", &location, &matrix)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("matrix", matrix, PyList_Type);

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	float matrix_data[16];

	int count = (int)PyList_Size(matrix);
	
	if (count != 16) {
		PyErr_Format(ModuleError, "UniformMatrix() matrix length must be 16, not %d", count);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		PyObject * item = PyList_GET_ITEM(matrix, i);
		matrix_data[i] = (float)PyFloat_AsDouble(item);
	}

	OpenGL::glUniformMatrix4fv(location->location, 1, false, matrix_data);
	Py_RETURN_NONE;
}

PyObject * UniformTransposeMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * matrix;

	if (!PyArg_ParseTuple(args, "OO:UniformTransposeMatrix", &location, &matrix)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("location", location, UniformLocationType);
	CHECK_AND_REPORT_ARG_TYPE_ERROR("matrix", matrix, PyList_Type);
	
	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	float matrix_data[16];

	int count = (int)PyList_Size(matrix);
	
	if (count != 16) {
		PyErr_Format(ModuleError, "UniformTransposeMatrix() matrix length must be 16, not %d", count);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		PyObject * item = PyList_GET_ITEM(matrix, i);
		matrix_data[i] = (float)PyFloat_AsDouble(item);
	}

	OpenGL::glUniformMatrix4fv(location->location, 1, true, matrix_data);
	Py_RETURN_NONE;
}
