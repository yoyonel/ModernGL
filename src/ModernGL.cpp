#include "Types.hpp"

#include "GLContext.hpp"

PyObject * strsize(PyObject * self, PyObject * args) {
	const char * str;

	int args_ok = PyArg_ParseTuple(
		args,
		"s",
		&str
	);

	if (!args_ok) {
		return 0;
	}

	char first_chr = *str++;
	if (first_chr < '1' || first_chr > '9') {
		return 0;
	}

	long long value = first_chr - '0';

	while (char chr = *str++) {
		if (chr < '0' || chr > '9') {
			switch (chr) {
				case 'G':
					value *= 1024;

				case 'M':
					value *= 1024;

				case 'K':
					value *= 1024;

					if (*str++ != 'B') {
						return 0;
					}

				case 'B':
					if (*str++) {
						return 0;
					}

				case 0:
					break;

				default:
					return 0;
			}
			break;
		}

		value = value * 10 + chr - '0';
	}

	return PyLong_FromLongLong(value);
}

PyObject * set_error_class(PyObject * self, PyObject * args) {
	PyObject * error_class;

	int args_ok = PyArg_ParseTuple(
		args,
		"O",
		&error_class
	);

	if (!args_ok) {
		return 0;
	}

	Py_INCREF(error_class);
	MGLError_TypePtr = error_class;
	Py_RETURN_NONE;
}

PyObject * create_standalone_context(PyObject * self, PyObject * args) {
	PyObject * settings;

	int args_ok = PyArg_ParseTuple(
		args,
		"O",
		&settings
	);

	if (!args_ok) {
		return 0;
	}

	MGLContext * ctx = (MGLContext *)MGLContext_Type.tp_alloc(&MGLContext_Type, 0);

	ctx->gl_context = CreateGLContext(settings);
	ctx->wireframe = false;

	if (PyErr_Occurred()) {
		return 0;
	}

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		return 0;
	}

	Py_INCREF(ctx);
	Py_INCREF(ctx->screen);

	PyObject * result = PyTuple_New(3);
	PyTuple_SET_ITEM(result, 0, (PyObject *)ctx);
	PyTuple_SET_ITEM(result, 1, (PyObject *)ctx->screen);
	PyTuple_SET_ITEM(result, 2, PyLong_FromLong(ctx->version_code));
	return result;
}

PyObject * create_context(PyObject * self) {
	MGLContext * ctx = (MGLContext *)MGLContext_Type.tp_alloc(&MGLContext_Type, 0);

	ctx->gl_context = LoadCurrentGLContext();
	ctx->wireframe = false;

	if (PyErr_Occurred()) {
		return 0;
	}

	MGLContext_Initialize(ctx);

	if (PyErr_Occurred()) {
		return 0;
	}

	Py_INCREF(ctx);
	Py_INCREF(ctx->screen);

	PyObject * result = PyTuple_New(3);
	PyTuple_SET_ITEM(result, 0, (PyObject *)ctx);
	PyTuple_SET_ITEM(result, 1, (PyObject *)ctx->screen);
	PyTuple_SET_ITEM(result, 2, PyLong_FromLong(ctx->version_code));
	return result;
}

PyMethodDef MGL_module_methods[] = {
	{"create_standalone_context", (PyCFunction)create_standalone_context, METH_VARARGS, 0},
	{"create_context", (PyCFunction)create_context, METH_NOARGS, 0},
	{"set_error_class", (PyCFunction)set_error_class, METH_VARARGS, 0},
	{"strsize", (PyCFunction)strsize, METH_VARARGS, 0},
	{0},
};

bool MGL_InitializeModule(PyObject * module) {
	{
		if (PyType_Ready(&MGLAttribute_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Attribute in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLAttribute_Type);

		PyModule_AddObject(module, "Attribute", (PyObject *)&MGLAttribute_Type);
	}

	{
		if (PyType_Ready(&MGLBuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Buffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLBuffer_Type);

		PyModule_AddObject(module, "Buffer", (PyObject *)&MGLBuffer_Type);
	}

	{
		if (PyType_Ready(&MGLComputeShader_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register ComputeShader in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLComputeShader_Type);

		PyModule_AddObject(module, "ComputeShader", (PyObject *)&MGLComputeShader_Type);
	}

	{
		if (PyType_Ready(&MGLContext_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Context in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLContext_Type);

		PyModule_AddObject(module, "Context", (PyObject *)&MGLContext_Type);
	}

	{
		if (PyType_Ready(&MGLFramebuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Framebuffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLFramebuffer_Type);

		PyModule_AddObject(module, "Framebuffer", (PyObject *)&MGLFramebuffer_Type);
	}

	{
		if (PyType_Ready(&MGLInvalidObject_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register InvalidObject in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLInvalidObject_Type);

		PyModule_AddObject(module, "InvalidObject", (PyObject *)&MGLInvalidObject_Type);
	}

	{
		if (PyType_Ready(&MGLPrimitive_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Primitive in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLPrimitive_Type);

		PyModule_AddObject(module, "Primitive", (PyObject *)&MGLPrimitive_Type);
	}

	{
		if (PyType_Ready(&MGLProgram_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Program in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLProgram_Type);

		PyModule_AddObject(module, "Program", (PyObject *)&MGLProgram_Type);
	}

	{
		if (PyType_Ready(&MGLQuery_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Query in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLQuery_Type);

		PyModule_AddObject(module, "Query", (PyObject *)&MGLQuery_Type);
	}

	{
		if (PyType_Ready(&MGLRenderbuffer_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Renderbuffer in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLRenderbuffer_Type);

		PyModule_AddObject(module, "Renderbuffer", (PyObject *)&MGLRenderbuffer_Type);
	}

	{
		if (PyType_Ready(&MGLScope_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Scope in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLScope_Type);

		PyModule_AddObject(module, "Scope", (PyObject *)&MGLScope_Type);
	}

	{
		if (PyType_Ready(&MGLShader_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Shader in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLShader_Type);

		PyModule_AddObject(module, "Shader", (PyObject *)&MGLShader_Type);
	}

	{
		if (PyType_Ready(&MGLTexture_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Texture in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLTexture_Type);

		PyModule_AddObject(module, "Texture", (PyObject *)&MGLTexture_Type);
	}

	{
		if (PyType_Ready(&MGLTextureCube_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register TextureCube in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLTextureCube_Type);

		PyModule_AddObject(module, "TextureCube", (PyObject *)&MGLTextureCube_Type);
	}

	{
		if (PyType_Ready(&MGLTexture3D_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Texture3D in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLTexture3D_Type);

		PyModule_AddObject(module, "Texture3D", (PyObject *)&MGLTexture3D_Type);
	}

	{
		if (PyType_Ready(&MGLUniform_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register Uniform in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLUniform_Type);

		PyModule_AddObject(module, "Uniform", (PyObject *)&MGLUniform_Type);
	}

	{
		if (PyType_Ready(&MGLUniformBlock_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register UniformBlock in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLUniformBlock_Type);

		PyModule_AddObject(module, "UniformBlock", (PyObject *)&MGLUniformBlock_Type);
	}

	{
		if (PyType_Ready(&MGLVertexArray_Type) < 0) {
			PyErr_Format(PyExc_ImportError, "Cannot register VertexArray in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return false;
		}

		Py_INCREF(&MGLVertexArray_Type);

		PyModule_AddObject(module, "VertexArray", (PyObject *)&MGLVertexArray_Type);
	}

	{
		MGL_TRIANGLES = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_TRIANGLES->wrapper = 0;
		MGL_TRIANGLES->primitive = GL_TRIANGLES;
		MGL_TRIANGLES->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLES->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES", (PyObject *)MGL_TRIANGLES);

		MGL_TRIANGLE_STRIP = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_TRIANGLE_STRIP->wrapper = 0;
		MGL_TRIANGLE_STRIP->primitive = GL_TRIANGLE_STRIP;
		MGL_TRIANGLE_STRIP->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLE_STRIP->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP", (PyObject *)MGL_TRIANGLE_STRIP);

		MGL_TRIANGLE_FAN = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_TRIANGLE_FAN->wrapper = 0;
		MGL_TRIANGLE_FAN->primitive = GL_TRIANGLE_FAN;
		MGL_TRIANGLE_FAN->geometry_primitive = GL_TRIANGLES;
		MGL_TRIANGLE_FAN->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_FAN", (PyObject *)MGL_TRIANGLE_FAN);

		MGL_LINES = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_LINES->wrapper = 0;
		MGL_LINES->primitive = GL_LINES;
		MGL_LINES->geometry_primitive = GL_LINES;
		MGL_LINES->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES", (PyObject *)MGL_LINES);

		MGL_LINE_STRIP = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_LINE_STRIP->wrapper = 0;
		MGL_LINE_STRIP->primitive = GL_LINE_STRIP;
		MGL_LINE_STRIP->geometry_primitive = GL_LINES;
		MGL_LINE_STRIP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP", (PyObject *)MGL_LINE_STRIP);

		MGL_LINE_LOOP = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_LINE_LOOP->wrapper = 0;
		MGL_LINE_LOOP->primitive = GL_LINE_LOOP;
		MGL_LINE_LOOP->geometry_primitive = GL_LINES;
		MGL_LINE_LOOP->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_LOOP", (PyObject *)MGL_LINE_LOOP);

		MGL_POINTS = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_POINTS->wrapper = 0;
		MGL_POINTS->primitive = GL_POINTS;
		MGL_POINTS->geometry_primitive = GL_POINTS;
		MGL_POINTS->transform_primitive = GL_POINTS;
		PyModule_AddObject(module, "POINTS", (PyObject *)MGL_POINTS);

		MGL_LINE_STRIP_ADJACENCY = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_LINE_STRIP_ADJACENCY->wrapper = 0;
		MGL_LINE_STRIP_ADJACENCY->primitive = GL_LINE_STRIP_ADJACENCY;
		MGL_LINE_STRIP_ADJACENCY->geometry_primitive = GL_LINES_ADJACENCY;
		MGL_LINE_STRIP_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINE_STRIP_ADJACENCY", (PyObject *)MGL_LINE_STRIP_ADJACENCY);

		MGL_LINES_ADJACENCY = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_LINES_ADJACENCY->wrapper = 0;
		MGL_LINES_ADJACENCY->primitive = GL_LINES_ADJACENCY;
		MGL_LINES_ADJACENCY->geometry_primitive = GL_LINES_ADJACENCY;
		MGL_LINES_ADJACENCY->transform_primitive = GL_LINES;
		PyModule_AddObject(module, "LINES_ADJACENCY", (PyObject *)MGL_LINES_ADJACENCY);

		MGL_TRIANGLE_STRIP_ADJACENCY = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_TRIANGLE_STRIP_ADJACENCY->wrapper = 0;
		MGL_TRIANGLE_STRIP_ADJACENCY->primitive = GL_TRIANGLE_STRIP_ADJACENCY;
		MGL_TRIANGLE_STRIP_ADJACENCY->geometry_primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLE_STRIP_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLE_STRIP_ADJACENCY", (PyObject *)MGL_TRIANGLE_STRIP_ADJACENCY);

		MGL_TRIANGLES_ADJACENCY = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_TRIANGLES_ADJACENCY->wrapper = 0;
		MGL_TRIANGLES_ADJACENCY->primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLES_ADJACENCY->geometry_primitive = GL_TRIANGLES_ADJACENCY;
		MGL_TRIANGLES_ADJACENCY->transform_primitive = GL_TRIANGLES;
		PyModule_AddObject(module, "TRIANGLES_ADJACENCY", (PyObject *)MGL_TRIANGLES_ADJACENCY);
	}

	{
		MGL_NO_PRIMITIVE = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
		MGL_NO_PRIMITIVE->wrapper = Py_None;
		MGL_NO_PRIMITIVE->primitive = 0;
		MGL_NO_PRIMITIVE->geometry_primitive = 0;
		MGL_NO_PRIMITIVE->transform_primitive = 0;
		Py_INCREF(MGL_NO_PRIMITIVE);
		Py_INCREF(Py_None);
	}

	return true;
}

PyModuleDef MGL_moduledef = {
	PyModuleDef_HEAD_INIT,
	"mgl",
	0,
	-1,
	MGL_module_methods,
	0,
	0,
	0,
	0,
};

extern "C" PyObject * PyInit_mgl() {
	PyObject * module = PyModule_Create(&MGL_moduledef);

	if (!MGL_InitializeModule(module)) {
		return 0;
	}

	return module;
}
