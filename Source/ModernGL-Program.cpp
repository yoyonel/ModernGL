#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewProgram(PyObject * self, PyObject * args) {
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "O:NewProgram", &lst)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	int program = OpenGL::glCreateProgram();

	int count = (int)PyList_Size(lst);
	for (int i = 0; i < count; ++i) {
		Shader * shader = (Shader *)PyList_GetItem(lst, i);
		if (!PyObject_TypeCheck((PyObject *)shader, &ShaderType)) {
			PyErr_SetString(PyExc_TypeError, "fexnjdzq");
			return 0;
		}
		OpenGL::glAttachShader(program, shader->shader);
	}

	int linked = OpenGL::GL_FALSE;
	OpenGL::glLinkProgram(program);
	OpenGL::glGetProgramiv(program, OpenGL::GL_LINK_STATUS, &linked);

	if (!linked) {
		int logSize = 0;
		static const char * logTitle = "Program:\n";
		static int logTitleSize = strlen(logTitle);
		memcpy(compilerLog, logTitle, logTitleSize);
		OpenGL::glGetProgramInfoLog(program, maxCompilerLog - logTitleSize, &logSize, compilerLog + logTitleSize);
		compilerLog[logTitleSize + logSize] = 0;
		OpenGL::glDeleteProgram(program);
		program = 0;
	} else {
		compilerLog[0] = 0;
		OpenGL::glUseProgram(program);
	}

	if (!program) {
		PyErr_SetString(PyExc_TypeError, compilerLog);
		return 0;
	}
	
	return CreateProgramType(program);
}

PyObject * DeleteProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O:DeleteProgram", &program)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(PyExc_TypeError, "tnapjoqu");
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

PyObject * UseProgram(PyObject * self, PyObject * args) {
	Program * program;

	if (!PyArg_ParseTuple(args, "O:UseProgram", &program)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(PyExc_TypeError, "lalsmrdz");
		return 0;
	}

	OpenGL::glUseProgram(program->program);
	Py_RETURN_NONE;
}

PyObject * UseDefaultProgram(PyObject * self) {
	OpenGL::glUseProgram(defaultProgram);
	Py_RETURN_NONE;
}

PyObject * GetAttributeLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;
	bool strict = false;

	static const char * kwlist[] = {"program", "name", "strict", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os|p:GetAttributeLocation", (char **)kwlist, &program, &name, &strict)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	int location = OpenGL::glGetAttribLocation(program->program, name);
	if (strict && location < 0) {
		PyErr_SetString(ModuleError, "asd");
		return 0;
	}

	return CreateAttributeLocationType(location);
}

PyObject * GetUniformLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;
	bool strict = false;

	static const char * kwlist[] = {"program", "name", "strict", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os|p:GetUniformLocation", (char **)kwlist, &program, &name, &strict)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	int location = OpenGL::glGetUniformLocation(program->program, name);
	if (strict && location < 0) {
		PyErr_SetString(ModuleError, "asd");
		return 0;
	}

	return CreateUniformLocationType(location);
}

PyObject * GetUniformBufferLocation(PyObject * self, PyObject * args, PyObject * kwargs) {
	Program * program;
	const char * name;
	bool strict = false;

	static const char * kwlist[] = {"program", "name", "strict", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "Os|p:GetUniformBufferLocation", (char **)kwlist, &program, &name, &strict)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)program, &ProgramType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	int location = OpenGL::glGetUniformBlockIndex(program->program, name);
	if (strict && location < 0) {
		PyErr_SetString(ModuleError, "asd");
		return 0;
	}

	return CreateUniformBufferLocationType(location);
}

PyObject * Uniform1f(PyObject * self, PyObject * args) {
	UniformLocation * location;
	float v0;

	if (!PyArg_ParseTuple(args, "Of:Uniform1f", &location, &v0)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
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

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glUniform4i(location->location, v0, v1, v2, v3);
	Py_RETURN_NONE;
}

PyObject * UniformMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "OO:UniformMatrix", &location, &lst)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	float matrix[16];

	int count = (int)PyList_Size(lst);
	
	if (count != 16) {
		PyErr_SetString(ModuleError, "acoypwfb");
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		PyObject * item = PyList_GET_ITEM(lst, i);

		if (!PyObject_TypeCheck((PyObject *)item, &PyFloat_Type)) {
			PyErr_SetString(PyExc_TypeError, "caoypwbf");
			return 0;
		}

		matrix[i] = (float)PyFloat_AsDouble(item);
	}

	OpenGL::glUniformMatrix4fv(location->location, 1, false, matrix);
	Py_RETURN_NONE;
}

PyObject * UniformTransposeMatrix(PyObject * self, PyObject * args) {
	UniformLocation * location;
	PyObject * lst;

	if (!PyArg_ParseTuple(args, "OO:UniformTransposeMatrix", &location, &lst)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	float matrix[16];

	int count = (int)PyList_Size(lst);
	
	if (count != 16) {
		PyErr_SetString(ModuleError, "acoypwfb");
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		PyObject * item = PyList_GET_ITEM(lst, i);

		if (!PyObject_TypeCheck((PyObject *)item, &PyFloat_Type)) {
			PyErr_SetString(PyExc_TypeError, "caoypwbf");
			return 0;
		}

		matrix[i] = (float)PyFloat_AsDouble(item);
	}

	OpenGL::glUniformMatrix4fv(location->location, 1, true, matrix);
	Py_RETURN_NONE;
}

PyObject * UseUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs) {
	UniformBufferLocation * location;
	UniformBuffer * ubo;

	static const char * kwlist[] = {"location", "ubo", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:UseUniformBuffer", (char **)kwlist, &location, &ubo)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &UniformBufferLocationType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)ubo, &UniformBufferType)) {
		PyErr_SetString(PyExc_TypeError, "caoypwbf");
		return 0;
	}

	OpenGL::glBindBufferBase(OpenGL::GL_UNIFORM_BUFFER, location->location, ubo->ubo);
	Py_RETURN_NONE;
}
