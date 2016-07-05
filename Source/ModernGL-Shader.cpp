#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewVertexShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewVertexShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_VERTEX_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "NewVertexShader() compile failed\n";
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

	return CreateShaderType(shader, VERTEX_SHADER);
}

PyObject * NewFragmentShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewFragmentShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_FRAGMENT_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "NewFragmentShader() compile failed\n";
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

	return CreateShaderType(shader, FRAGMENT_SHADER);
}

PyObject * NewGeometryShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewGeometryShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_GEOMETRY_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "NewGeometryShader() compile failed\n";
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

	return CreateShaderType(shader, GEOMETRY_SHADER);
}

PyObject * NewTessEvaluationShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewTessEvaluationShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_TESS_EVALUATION_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "NewTessEvaluationShader() compile failed\n";
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
	}

	return CreateShaderType(shader, TESS_EVALUATION_SHADER);
}

PyObject * NewTessControlShader(PyObject * self, PyObject * args) {
	const char * source;

	if (!PyArg_ParseTuple(args, "s:NewTessControlShader", &source)) {
		return 0;
	}

	int shader = OpenGL::glCreateShader(OpenGL::GL_TESS_CONTROL_SHADER);
	OpenGL::glShaderSource(shader, 1, &source, 0);
	OpenGL::glCompileShader(shader);

	int compiled = OpenGL::GL_FALSE;
	OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		static const char * logTitle = "NewTessControlShader() compile failed\n";
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
	}

	return CreateShaderType(shader, TESS_CONTROL_SHADER);
}

PyObject * DeleteShader(PyObject * self, PyObject * args) {
	Shader * shader;

	if (!PyArg_ParseTuple(args, "O:DeleteShader", &shader)) {
		return 0;
	}

	CHECK_AND_REPORT_ARG_TYPE_ERROR("shader", shader, ShaderType);

	OpenGL::glDeleteShader(shader->shader);
	Py_RETURN_NONE;
}