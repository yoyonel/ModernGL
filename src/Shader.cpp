#include "Shader.hpp"

#include "InvalidObject.hpp"

PyObject * MGLShader_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLShader * self = (MGLShader *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLShader_tp_new %p\n", self);
	#endif

	if (self) {
		self->source = 0;
	}

	return (PyObject *)self;
}

void MGLShader_tp_dealloc(MGLShader * self) {

	#ifdef MGL_VERBOSE
	printf("MGLShader_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLShader_tp_init(MGLShader * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLShader_tp_str(MGLShader * self) {
	return PyUnicode_FromFormat("<ModernGL.Shader>");
}

PyObject * MGLShader_release(MGLShader * self) {
	MGLShader_Invalidate(self);
	Py_RETURN_NONE;
}

PyMethodDef MGLShader_tp_methods[] = {
	{"release", (PyCFunction)MGLShader_release, METH_NOARGS, 0},
	{0},
};

PyObject * MGLShader_get_source(MGLShader * self, void * closure) {
	Py_INCREF(self->source);
	return self->source;
}

PyGetSetDef MGLShader_tp_getseters[] = {
	{(char *)"source", (getter)MGLShader_get_source, 0, 0, 0},
	{0},
};

const char * MGLShader_tp_doc = R"(
)";

PyTypeObject MGLShader_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Shader",                                      // tp_name
	sizeof(MGLShader),                                      // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLShader_tp_dealloc,                       // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLShader_tp_str,                             // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLShader_tp_str,                             // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLShader_tp_doc,                                       // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLShader_tp_methods,                                   // tp_methods
	0,                                                      // tp_members
	MGLShader_tp_getseters,                                 // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLShader_tp_init,                            // tp_init
	0,                                                      // tp_alloc
	MGLShader_tp_new,                                       // tp_new
};

MGLShader * MGLShader_New() {
	MGLShader * self = (MGLShader *)MGLShader_tp_new(&MGLShader_Type, 0, 0);
	return self;
}

void MGLShader_Compile(MGLShader * shader) {
	GLMethods & gl = shader->context->gl;

	char * source = PyUnicode_AsUTF8(shader->source);

	int obj = gl.CreateShader(shader->shader_type);

	gl.ShaderSource(obj, 1, &source, 0);
	gl.CompileShader(obj);

	int compiled = GL_FALSE;
	gl.GetShaderiv(obj, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		static const char * logTitle = "GLSL Compiler failed\n";
		static int logTitleLength = strlen(logTitle);

		int logLength = 0;
		gl.GetShaderiv(obj, GL_INFO_LOG_LENGTH, &logLength);
		int logTotalLength = logLength + logTitleLength;

		PyObject * content = PyUnicode_New(logTotalLength, 255);

		if (PyUnicode_READY(content)) {
			gl.DeleteShader(obj);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return;
		}

		char * data = (char *)PyUnicode_1BYTE_DATA(content);
		memcpy(data, logTitle, logTitleLength);

		int logSize = 0;
		gl.GetShaderInfoLog(obj, logLength, &logSize, data + logTitleLength);
		data[logTitleLength] = 0;

		gl.DeleteShader(obj);

		PyErr_SetObject(PyExc_Exception, content);
		return;
	}

	shader->obj = obj;
}

void MGLShader_Invalidate(MGLShader * shader) {
	if (Py_TYPE(shader) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLShader_Invalidate %p already released\n", shader);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLShader_Invalidate %p\n", shader);
	#endif

	// TODO: release

	Py_DECREF(shader->context);
	Py_DECREF(shader->source);

	shader->ob_base.ob_type = &MGLInvalidObject_Type;
	shader->initial_type = &MGLShader_Type;

	Py_DECREF(shader);
}
