#include "ModernGL-Program.hpp"

#include "ModernGL-Types.hpp"
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

	if (!PyArg_ParseTuple(args, "O!:NewProgram", &PyList_Type, &shaders)) {
		return 0;
	}

	int count = (int)PyList_Size(shaders);

	int category[NUM_SHADER_CATEGORIES] = {};
	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);

		CHECK_AND_REPORT_ELEMENT_TYPE_ERROR("shaders", shader, ShaderType, i);

		if (shader->attached) {
			PyErr_Format(ModuleCompileError, "NewProgram() shaders[%d] is already attached to another program", i);
			return 0;
		}

		++category[shader->category];
	}

	for (int i = 0; i < NUM_SHADER_CATEGORIES; ++i) {
		if (category[i] > 1) {
			PyErr_Format(ModuleCompileError, "NewProgram() duplicate %s in `shaders`", categoryNames[i]);
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
		PyErr_SetObject(ModuleCompileError, content);
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
		int size = 0;
		int length = 0;
		unsigned type = 0;
		OpenGL::glGetActiveUniform(program, i, 64, &length, &size, &type, name);
		int location = OpenGL::glGetUniformLocation(program, name);
		name[length] = 0;

		if (type == OpenGL::GL_SAMPLER_2D) {
			type = OpenGL::GL_INT;
		}

		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformLocationType(location, program, type));
		}
	}

	int uniformBlocks = 0;
	OpenGL::glGetProgramiv(program, OpenGL::GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlocks);
	for (int i = 0; i < uniformBlocks; ++i) {
		char name[64 + 1];
		int size = 0;
		int length = 0;
		int location = -1;
		OpenGL::glGetActiveUniformBlockName(program, i, 64, &length, name);
		OpenGL::glGetActiveUniformBlockiv(program, i, OpenGL::GL_UNIFORM_BLOCK_BINDING, &location);
		OpenGL::glGetActiveUniformBlockiv(program, i, OpenGL::GL_UNIFORM_BLOCK_DATA_SIZE, &size);
		name[length] = 0;

		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformBufferLocationType(location, program, size));
		}
	}

	return PyTuple_Pack(2, CreateProgramType(program), dict);
}

PyObject * NewTransformProgram(PyObject * self, PyObject * args) {
	PyObject * shaders;
	PyObject * outputs;

	if (!PyArg_ParseTuple(args, "O!O!:NewTransformProgram", &PyList_Type, &shaders, &PyList_Type, &outputs)) {
		return 0;
	}

	int count = (int)PyList_Size(shaders);

	int category[NUM_SHADER_CATEGORIES] = {};
	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);

		CHECK_AND_REPORT_ELEMENT_TYPE_ERROR("shaders", shader, ShaderType, i);

		if (shader->attached) {
			PyErr_Format(ModuleCompileError, "NewTransformProgram() shaders[%d] is already attached to another program", i);
			return 0;
		}

		++category[shader->category];
	}

	for (int i = 0; i < NUM_SHADER_CATEGORIES; ++i) {
		if (category[i] > 1) {
			PyErr_Format(ModuleCompileError, "NewTransformProgram() duplicate %s in `shaders`", categoryNames[i]);
			return 0;
		}
	}

	int program = OpenGL::glCreateProgram();

	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(shaders, i);
		OpenGL::glAttachShader(program, shader->shader);
	}

	int size = PyList_Size(outputs);
	const char * feedbackVaryings[1024];

	for (int i = 0; i < size; ++i) {
		feedbackVaryings[i] = PyUnicode_AsUTF8(PyList_GET_ITEM(outputs, i));
	}

	OpenGL::glTransformFeedbackVaryings(program, size, feedbackVaryings, OpenGL::GL_INTERLEAVED_ATTRIBS);

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
		PyErr_SetObject(ModuleCompileError, content);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GET_ITEM(shaders, i);
		shader->attached = true;
	}

	PyObject * dict = PyDict_New();

	int uniforms = 0;
	OpenGL::glGetProgramiv(program, OpenGL::GL_ACTIVE_UNIFORMS, &uniforms);
	for (int i = 0; i < uniforms; ++i) {
		char name[64 + 1];
		int size = 0;
		int length = 0;
		unsigned type = 0;
		OpenGL::glGetActiveUniform(program, i, 64, &length, &size, &type, name);
		int location = OpenGL::glGetUniformLocation(program, name);
		name[length] = 0;

		if (type == OpenGL::GL_SAMPLER_2D) {
			type = OpenGL::GL_INT;
		}

		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformLocationType(location, program, type));
		}
	}

	int uniformBlocks = 0;
	OpenGL::glGetProgramiv(program, OpenGL::GL_ACTIVE_UNIFORM_BLOCKS, &uniformBlocks);
	for (int i = 0; i < uniformBlocks; ++i) {
		char name[64 + 1];
		int size = 0;
		int length = 0;
		int location = -1;
		OpenGL::glGetActiveUniformBlockName(program, i, 64, &length, name);
		OpenGL::glGetActiveUniformBlockiv(program, i, OpenGL::GL_UNIFORM_BLOCK_BINDING, &location);
		OpenGL::glGetActiveUniformBlockiv(program, i, OpenGL::GL_UNIFORM_BLOCK_DATA_SIZE, &size);
		name[length] = 0;

		if (location >= 0) {
			PyDict_SetItemString(dict, name, CreateUniformBufferLocationType(location, program, size));
		}
	}

	return PyTuple_Pack(2, CreateProgramType(program), dict);
}

PyObject * DeleteProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O!:DeleteProgram", &ProgramType, &program)) {
		return 0;
	}

	int shaders[8] = {};
	int numShaders = 0;

	OpenGL::glGetAttachedShaders(program->program, 8, &numShaders, (OpenGL::GLuint *)shaders);
	for (int i = 0; i < numShaders; ++i) {
		OpenGL::glDeleteShader(shaders[i]);
	}
	OpenGL::glDeleteProgram(program->program);
	Py_RETURN_NONE;
}

PyObject * SetUniform(PyObject * self, PyObject * args) {
	int size = PyTuple_GET_SIZE(args);
	if (size < 1) {
		return 0;
	}

	UniformLocation * location = (UniformLocation *)PyTuple_GET_ITEM(args, 0);

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_Format(PyExc_TypeError, "SetUniform() argument `location` must be UniformLocationType, not %s", GET_OBJECT_TYPENAME(location));
		return 0;
	}

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	switch (location->type) {
		case OpenGL::GL_FLOAT: {
			if (size != 2) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 1 additional float argument for uniform '%s'", size, "uniform name");
			}
			float v0 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 1));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform1f(location->location, v0);
			break;
		}

		case OpenGL::GL_FLOAT_VEC2: {
			if (size != 3) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 2 additional float arguments for uniform '%s'", size, "uniform name");
			}
			float v0 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 1));
			float v1 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 2));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform2f(location->location, v0, v1);
			break;
		}

		case OpenGL::GL_FLOAT_VEC3: {
			if (size != 4) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 3 additional float arguments for uniform '%s'", size, "uniform name");
			}
			float v0 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 1));
			float v1 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 2));
			float v2 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 3));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform3f(location->location, v0, v1, v2);
			break;
		}

		case OpenGL::GL_FLOAT_VEC4: {
			if (size != 5) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 3 additional float arguments for uniform '%s'", size, "uniform name");
			}
			float v0 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 1));
			float v1 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 2));
			float v2 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 3));
			float v3 = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(args, 4));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform4f(location->location, v0, v1, v2, v3);
			break;
		}

		case OpenGL::GL_INT: {
			if (size != 2) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 1 additional int argument for uniform '%s'", size, "uniform name");
			}
			int v0 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 1));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform1i(location->location, v0);
			break;
		}

		case OpenGL::GL_INT_VEC2: {
			if (size != 3) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 2 additional int arguments for uniform '%s'", size, "uniform name");
			}
			int v0 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 1));
			int v1 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 2));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform2i(location->location, v0, v1);
			break;
		}

		case OpenGL::GL_INT_VEC3: {
			if (size != 4) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 3 additional int arguments for uniform '%s'", size, "uniform name");
			}
			int v0 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 1));
			int v1 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 2));
			int v2 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 3));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform3i(location->location, v0, v1, v2);
			break;
		}

		case OpenGL::GL_INT_VEC4: {
			if (size != 5) {
				PyErr_Format(PyExc_TypeError, "SetUniform() takes 3 additional int arguments for uniform '%s'", size, "uniform name");
			}
			int v0 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 1));
			int v1 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 2));
			int v2 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 3));
			int v3 = (int)PyLong_AsLong(PyTuple_GET_ITEM(args, 4));

			if (PyErr_Occurred()) {
				return 0;
			}

			OpenGL::glUniform4i(location->location, v0, v1, v2, v3);
			break;
		}

		default:
			PyErr_SetString(ModuleError, "SetUniform() failed");
			return 0;
	}

	Py_RETURN_NONE;
}

PyObject * SetUniformMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * matrix;
	bool transpose = false;

	if (!PyArg_ParseTuple(args, "O!O!|p:SetUniformMatrix", &UniformLocationType, &location, &PyList_Type, &matrix, &transpose)) {
		return 0;
	}

	int limit = 0;
	switch (location->type) {
		case OpenGL::GL_FLOAT_MAT2:
			limit = 4;
			break;

		case OpenGL::GL_FLOAT_MAT3:
			limit = 9;
			break;

		case OpenGL::GL_FLOAT_MAT4:
			limit = 16;
			break;

		default:
			PyErr_SetString(ModuleError, "SetUniformMatrix() failed");
			return 0;

	}

	int count = (int)PyList_Size(matrix);

	if (count != limit) {
		PyErr_Format(ModuleError, "SetUniformMatrix() expected %d got %d", limit, count);
		return 0;
	}

	float matrix_data[16];

	for (int i = 0; i < count; ++i) {
		PyObject * item = PyList_GET_ITEM(matrix, i);
		matrix_data[i] = (float)PyFloat_AsDouble(item);

		if (PyErr_Occurred()) {
			return 0;
		}
	}

	if (activeProgram != location->program) {
		OpenGL::glUseProgram(location->program);
		activeProgram = location->program;
	}

	switch (location->type) {
		case OpenGL::GL_FLOAT_MAT2:
			OpenGL::glUniformMatrix2fv(location->location, 1, transpose, matrix_data);
			break;

		case OpenGL::GL_FLOAT_MAT3:
			OpenGL::glUniformMatrix3fv(location->location, 1, transpose, matrix_data);
			break;

		case OpenGL::GL_FLOAT_MAT4:
			OpenGL::glUniformMatrix4fv(location->location, 1, transpose, matrix_data);
			break;
	}

	Py_RETURN_NONE;
}


PyObject * Dummy_NewProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTransformProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTransformProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTransformProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetUniform(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetUniform() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetUniform() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetUniformMatrix(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetUniformMatrix() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetUniformMatrix() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}


PythonMethod ProgramMethods[] = {
	{
		301,
		(PyCFunction)NewProgram,
		(PyCFunction)Dummy_NewProgram,
		METH_VARARGS,
		"NewProgram",
		"Create a program object from a list of ModernGL.Shader objects.\n"
		"There must be only one shader for each shader types.\n"
		"\n"

		"Parameters:\n"
		"\tshaders (list) List containing shader objects.\n"
		"\n"

		"Returns:\n"
		"\tprogram (ModernGL.Program) The new program object.\n"
		"\tinterface (dict) The active uniforms and uniform buffers.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.CompileError) Linking error or duplicate shaders of the same type.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteProgram,
		(PyCFunction)Dummy_DeleteProgram,
		METH_VARARGS,
		"DeleteProgram",
		"Delete a program objects and all the attached shaders.\n"
		"A shader must be attached only to a single program object.\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.Program) A program object returned by the ModernGL.NewProgram function.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniform,
		(PyCFunction)Dummy_SetUniform,
		METH_VARARGS,
		"SetUniform",
		"Set the value of the uniform (except for matrices).\n"
		"The number of parameters depends on the uniform type.\n"
		"The location of active uniforms is always accessable from the program interface.\n"
		"The program interface is the second value returned by the ModernGL.NewProgram.\n"
		"\n"

		"Parameters:\n"
		"\tlocation (ModernGL.UniformLocation) Location of the uniform.\n"
		"\tv0 (float or int) Value to set.\n"
		"\tv1 (float or int) Value to set.\n"
		"\tv2 (float or int) Value to set.\n"
		"\tv3 (float or int) Value to set.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(TypeError) The dimension or the type of the uniform is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniformMatrix,
		(PyCFunction)Dummy_SetUniformMatrix,
		METH_VARARGS,
		"SetUniformMatrix",
		"Set the value of the uniform matrix.\n"
		"The matrix type must be either mat2, mat3 or mat4.\n"
		"\n"

		"Parameters:\n"
		"\tlocation (ModernGL.UniformLocation) Location of the uniform.\n"
		"\tmatrix (list) List containing 4x4=16 float values.\n"
		"\ttranspose (bool) Transpose matrix.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(TypeError) The dimension or the type of the matrix is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewTransformProgram,
		(PyCFunction)Dummy_NewTransformProgram,
		METH_VARARGS | METH_KEYWORDS,
		"NewTransformProgram",
		""
	},
};
