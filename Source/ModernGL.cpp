#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * ModuleError;
PyObject * ModuleRangeError;
PyObject * ModuleCompileError;
PyObject * ModuleInvalidFormat;
PyObject * ModuleAttributeNotFound;
PyObject * ModuleNotInitialized;
PyObject * ModuleNotSupported;

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

PyObject * InitializeModernGL(PyObject * self, PyObject * args) {
	if (initialized) {
		Py_RETURN_NONE;
	}

	if (!PyArg_ParseTuple(args, ":InitializeModernGL")) {
		return 0;
	}

	// Initialize OpenGL
	if (!OpenGL::InitializeOpenGL()) {
		PyErr_SetString(ModuleNotInitialized, "InitializeOpenGL failed.");
		return 0;
	}

	if (OpenGL::isglGetIntegerv()) {
		int major = 0;
		int minor = 0;

		OpenGL::glGetIntegerv(OpenGL::GL_MAJOR_VERSION, &major);
		OpenGL::glGetIntegerv(OpenGL::GL_MINOR_VERSION, &minor);

		versionNumber = major * 100 + minor;
	}

	if (versionNumber < 301) {
		PyErr_SetString(ModuleNotInitialized, "Not enough OpenGL support.");
		return 0;
	}

	LoadMethods();
	
	// Default blending
	OpenGL::glBlendFunc(OpenGL::GL_SRC_ALPHA, OpenGL::GL_ONE_MINUS_SRC_ALPHA);

	// Default primitive restart index
	OpenGL::glEnable(OpenGL::GL_PRIMITIVE_RESTART);
	OpenGL::glPrimitiveRestartIndex(-1);

	// Default VAO for GL_ELEMENT_ARRAY_BUFFER operations
	OpenGL::glGenVertexArrays(1, (OpenGL::GLuint *)&defaultVertexArray);
	OpenGL::glBindVertexArray(defaultVertexArray);

	// Default FBO and program
	OpenGL::glGetIntegerv(OpenGL::GL_DRAW_FRAMEBUFFER_BINDING, (OpenGL::GLint *)&defaultFramebuffer);
	OpenGL::glGetIntegerv(OpenGL::GL_CURRENT_PROGRAM, (OpenGL::GLint *)&activeProgram);

	// Default texture unit for texture operations
	OpenGL::glGetIntegerv(OpenGL::GL_MAX_TEXTURE_IMAGE_UNITS, (OpenGL::GLint *)&maxTextureUnits);
	defaultTextureUnit = maxTextureUnits - 1;

	activeFramebuffer = defaultFramebuffer;

	int viewport[4] = {};
	OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewport);
	activeViewportWidth = viewport[2];
	activeViewportHeight = viewport[3];

	initialized = true;
	Py_RETURN_NONE;
}

bool ModuleReady() {
	if (PyType_Ready(&FramebufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexArrayType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&IndexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&StorageBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&TextureType) < 0) {
		return false;
	}

	if (PyType_Ready(&ShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&ProgramType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBufferLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&ComputeShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&TransformShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&TransformArrayType) < 0) {
		return false;
	}

	if (PyType_Ready(&EnableFlagType) < 0) {
		return false;
	}

	return true;
}

#define STR_VERSION(ver) # ver

PyObject * InitModule(PyObject * module) {
	if (!module) {
		return module;
	}
	
	Py_INCREF(&FramebufferType);
	Py_INCREF(&VertexArrayType);
	Py_INCREF(&VertexBufferType);
	Py_INCREF(&IndexBufferType);
	Py_INCREF(&UniformBufferType);
	Py_INCREF(&StorageBufferType);
	Py_INCREF(&TextureType);
	Py_INCREF(&ShaderType);
	Py_INCREF(&ProgramType);
	Py_INCREF(&UniformLocationType);
	Py_INCREF(&UniformBufferLocationType);
	Py_INCREF(&ComputeShaderType);
	Py_INCREF(&TransformShaderType);
	Py_INCREF(&TransformArrayType);
	Py_INCREF(&EnableFlagType);

	PyModule_AddObject(module, "Framebuffer", (PyObject *)&FramebufferType);
	PyModule_AddObject(module, "VertexArray", (PyObject *)&VertexArrayType);
	PyModule_AddObject(module, "VertexBuffer", (PyObject *)&VertexBufferType);
	PyModule_AddObject(module, "IndexBuffer", (PyObject *)&IndexBufferType);
	PyModule_AddObject(module, "UniformBuffer", (PyObject *)&UniformBufferType);
	PyModule_AddObject(module, "StorageBuffer", (PyObject *)&StorageBufferType);
	PyModule_AddObject(module, "Texture", (PyObject *)&TextureType);
	PyModule_AddObject(module, "Shader", (PyObject *)&ShaderType);
	PyModule_AddObject(module, "Program", (PyObject *)&ProgramType);
	PyModule_AddObject(module, "UniformLocation", (PyObject *)&UniformLocationType);
	PyModule_AddObject(module, "UniformBufferLocation", (PyObject *)&UniformBufferLocationType);
	PyModule_AddObject(module, "ComputeShader", (PyObject *)&ComputeShaderType);
	PyModule_AddObject(module, "TransformShader", (PyObject *)&TransformShaderType);
	PyModule_AddObject(module, "TransformArray", (PyObject *)&TransformArrayType);
	PyModule_AddObject(module, "EnableFlag", (PyObject *)&EnableFlagType);

	ModuleError = PyErr_NewException((char *)"ModernGL.Error", 0, 0);
	Py_INCREF(ModuleError);

	ModuleRangeError = PyErr_NewException((char *)"ModernGL.RangeError", ModuleError, 0);
	Py_INCREF(ModuleRangeError);

	ModuleCompileError = PyErr_NewException((char *)"ModernGL.CompileError", ModuleError, 0);
	Py_INCREF(ModuleCompileError);

	ModuleInvalidFormat = PyErr_NewException((char *)"ModernGL.InvalidFormat", ModuleError, 0);
	Py_INCREF(ModuleInvalidFormat);

	ModuleAttributeNotFound = PyErr_NewException((char *)"ModernGL.AttributeNotFound", ModuleError, 0);
	Py_INCREF(ModuleAttributeNotFound);

	ModuleNotInitialized = PyErr_NewException((char *)"ModernGL.NotInitialized", ModuleError, 0);
	Py_INCREF(ModuleNotInitialized);

	ModuleNotSupported = PyErr_NewException((char *)"ModernGL.NotSupported", ModuleError, 0);
	Py_INCREF(ModuleNotSupported);

	PyModule_AddObject(module, "Error", ModuleError);
	PyModule_AddObject(module, "RangeError", ModuleRangeError);
	PyModule_AddObject(module, "CompileError", ModuleCompileError);
	PyModule_AddObject(module, "InvalidFormat", ModuleInvalidFormat);
	PyModule_AddObject(module, "AttributeNotFound", ModuleAttributeNotFound);
	PyModule_AddObject(module, "NotInitialized", ModuleNotInitialized);
	PyModule_AddObject(module, "NotSupported", ModuleNotSupported);

	PyModule_AddObject(module, "ENABLE_NOTHING", CreateEnableFlagType(ENABLE_NOTHING));
	PyModule_AddObject(module, "ENABLE_BLEND", CreateEnableFlagType(ENABLE_BLEND));
	PyModule_AddObject(module, "ENABLE_CULL_FACE", CreateEnableFlagType(ENABLE_CULL_FACE));
	PyModule_AddObject(module, "ENABLE_DEPTH_TEST", CreateEnableFlagType(ENABLE_DEPTH_TEST));
	PyModule_AddObject(module, "ENABLE_MULTISAMPLE", CreateEnableFlagType(ENABLE_MULTISAMPLE));
	PyModule_AddObject(module, "ENABLE_ALL", CreateEnableFlagType(ENABLE_ALL));

	PyModule_AddStringConstant(module, "VERSION", STR_VERSION(MODERN_GL_VERSION));
	
	PyModule_AddStringConstant(module, "__AUTHOR_NAME__", "Szabolcs Dombi");
	PyModule_AddStringConstant(module, "__AUTHOR_EMAIL__", "cprogrammer1994@gmail.com");

	return module;
}

#undef STR_VERSION

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "ModernGL", 0, -1, methods, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_ModernGL();
}

PyObject * PyInit_ModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}

	InitMethods();

	return InitModule(PyModule_Create(&moduledef));
}

#else

extern "C" {
	PyObject * initModernGL();
}

PyObject * initModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}

	InitMethods();

	return InitModule(Py_InitModule("ModernGL", methods));
}

#endif
