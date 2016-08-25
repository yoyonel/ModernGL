#include "ModernGL.hpp"

#include "ModernGL-Types.hpp"
#include "ModernGL-Errors.hpp"
#include "ModernGL-Constants.hpp"
#include "ModernGL-Methods.hpp"

#include "OpenGL.hpp"

bool initialized;

int defaultTextureUnit;
int defaultVertexArray;
int defaultFramebuffer;

int activeFramebuffer;
int activeProgram;

int activeViewportWidth;
int activeViewportHeight;
int versionNumber;

int maxTextureUnits;

bool PreInitModule() {
	if (!TypeReadyCheck()) {
		return false;
	}

	InitMethods();

	return true;
}

PyObject * InitModule(PyObject * module) {
	if (!module) {
		return module;
	}

	RegisterErrors(module);
	RegisterTypes(module);
	RegisterConstants(module);

	return module;
}

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "ModernGL", 0, -1, moduleMethod, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_ModernGL();
}

PyObject * PyInit_ModernGL() {
	if (!PreInitModule()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}

	return InitModule(PyModule_Create(&moduledef));
}

#else

extern "C" {
	PyObject * initModernGL();
}

PyObject * initModernGL() {
	if (!PreInitModule()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}

	return InitModule(Py_InitModule("ModernGL", methods));
}

#endif
