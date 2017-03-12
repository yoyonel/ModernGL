#include "ComputeShader.hpp"

PyObject * MGLComputeShader_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLComputeShader * self = (MGLComputeShader *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLComputeShader_tp_dealloc(MGLComputeShader * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLComputeShader_tp_init(MGLComputeShader * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLComputeShader_tp_str(MGLComputeShader * self) {
	return PyUnicode_FromFormat("<ModernGL.ComputeShader>");
}

PyMethodDef MGLComputeShader_tp_methods[] = {
	{"run", 0, 0, 0},
	{0},
};

PyGetSetDef MGLComputeShader_tp_getseters[] = {
	{0},
};

const char * MGLComputeShader_tp_doc = R"(
	ComputeShader
)";

PyTypeObject MGLComputeShader_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.ComputeShader",                               // tp_name
	sizeof(MGLComputeShader),                               // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLComputeShader_tp_dealloc,                // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLComputeShader_tp_str,                      // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLComputeShader_tp_str,                      // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLComputeShader_tp_doc,                                // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLComputeShader_tp_methods,                            // tp_methods
	0,                                                      // tp_members
	MGLComputeShader_tp_getseters,                          // tp_getset
	&MGLGenericProgram_Type,                                // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLComputeShader_tp_init,                     // tp_init
	0,                                                      // tp_alloc
	MGLComputeShader_tp_new,                                // tp_new
};
