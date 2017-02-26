#include "InvalidObject.hpp"

MGLInvalidObject * MGLInvalidObject_New() {
	MGLInvalidObject * self = (MGLInvalidObject *)MGLInvalidObject_Type.tp_alloc(&MGLInvalidObject_Type, 0);
	return self;
}

PyObject * MGLInvalidObject_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLInvalidObject * self = (MGLInvalidObject *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLInvalidObject_tp_dealloc(MGLInvalidObject * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLInvalidObject_tp_init(MGLInvalidObject * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLInvalidObject_tp_str(MGLInvalidObject * self) {
	return PyUnicode_FromFormat("<ModernGL.InvalidObject>");
}

PyMethodDef MGLInvalidObject_tp_methods[] = {
	{0},
};

PyGetSetDef MGLInvalidObject_tp_getseters[] = {
	{0},
};

const char * MGLInvalidObject_tp_doc = R"(
)";

PyTypeObject MGLInvalidObject_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.InvalidObject",                               // tp_name
	sizeof(MGLInvalidObject),                               // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLInvalidObject_tp_dealloc,                // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLInvalidObject_tp_str,                      // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLInvalidObject_tp_str,                      // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLInvalidObject_tp_doc,                                // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLInvalidObject_tp_methods,                            // tp_methods
	0,                                                      // tp_members
	MGLInvalidObject_tp_getseters,                          // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLInvalidObject_tp_init,                     // tp_init
	0,                                                      // tp_alloc
	MGLInvalidObject_tp_new,                                // tp_new
};
