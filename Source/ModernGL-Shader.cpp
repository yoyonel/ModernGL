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
		static const char * logTitle = "NewVertexShader() compile failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteShader(shader);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetShaderInfoLog(shader, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteShader(shader);

		PyErr_SetObject(ModuleCompileError, content);
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
		static const char * logTitle = "NewFragmentShader() compile failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteShader(shader);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetShaderInfoLog(shader, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteShader(shader);

		PyErr_SetObject(ModuleCompileError, content);
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
		static const char * logTitle = "NewGeometryShader() compile failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteShader(shader);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetShaderInfoLog(shader, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteShader(shader);

		PyErr_SetObject(ModuleCompileError, content);
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
		static const char * logTitle = "NewTessEvaluationShader() compile failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteShader(shader);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetShaderInfoLog(shader, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteShader(shader);

		PyErr_SetObject(ModuleCompileError, content);
		return 0;
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
		static const char * logTitle = "NewTessControlShader() compile failed\n";
		static int logTitleLength = strlen(logTitle);
		
		int logLength = 0;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);
		if (PyUnicode_READY(content)) {
			OpenGL::glDeleteShader(shader);
			return 0;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		OpenGL::glGetShaderInfoLog(shader, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		OpenGL::glDeleteShader(shader);

		PyErr_SetObject(ModuleCompileError, content);
		return 0;
	}

	return CreateShaderType(shader, TESS_CONTROL_SHADER);
}

PyObject * DeleteShader(PyObject * self, PyObject * args) {
	Shader * shader;

	if (!PyArg_ParseTuple(args, "O!:DeleteShader", &ShaderType, &shader)) {
		return 0;
	}

	if (shader->attached) {
		Py_RETURN_NONE;
	}

	OpenGL::glDeleteShader(shader->shader);
	Py_RETURN_NONE;
}

//


PyObject * Dummy_NewVertexShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewVertexShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewVertexShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewFragmentShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewFragmentShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewFragmentShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewGeometryShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewGeometryShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewGeometryShader() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessControlShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTessControlShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTessControlShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessEvaluationShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTessEvaluationShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTessEvaluationShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}
