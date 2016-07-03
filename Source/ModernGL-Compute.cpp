#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewComputeShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewComputeShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_COMPUTE_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "ComputeShader:\n";
		static int logTitleSize = strlen(logTitle);
		memcpy(compilerLog, logTitle, logTitleSize);
		OpenGL::glGetShaderInfoLog(shader, maxCompilerLog - logTitleSize, &logSize, compilerLog + logTitleSize);
		compilerLog[logTitleSize + logSize] = 0;
		OpenGL::glDeleteShader(shader);
		shader = 0;
	} else {
		compilerLog[0] = 0;
	}

	if (!shader) {
		PyErr_SetString(ModuleError, compilerLog);
		return 0;
	}

	int program = OpenGL::glCreateProgram();

	OpenGL::glAttachShader(program, shader);

	int linked = OpenGL::GL_FALSE;
	OpenGL::glLinkProgram(program);
	OpenGL::glGetProgramiv(program, OpenGL::GL_LINK_STATUS, &linked);

	if (!linked) {
		int logSize = 0;
		static const char * logTitle = "ComputeShader:\n";
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
		PyErr_SetString(ModuleError, compilerLog);
		return 0;
	}

	return CreateComputeShaderType(shader, program);
}

PyObject * DeleteComputeShader(PyObject * self, PyObject * args) {
	ComputeShader * computeShader;

	if (!PyArg_ParseTuple(args, "O:DeleteComputeShader", &computeShader)) {
		return 0;
	}

	OpenGL::glDeleteProgram(computeShader->program);
	OpenGL::glDeleteShader(computeShader->shader);
	Py_RETURN_NONE;
}

PyObject * RunComputeShader(PyObject * self, PyObject * args, PyObject * kwargs) {
	ComputeShader * computeShader;
	int x = 1;
	int y = 1;
	int z = 1;

	static const char * kwlist[] = {"computeShader", "x", "y", "z", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O|iii:RunComputeShader", (char **)kwlist, &computeShader, &x, &y, &z)) {
		return 0;
	}

	OpenGL::glUseProgram(computeShader->program);
	OpenGL::glDispatchCompute(x, y, z);
	Py_RETURN_NONE;
}
