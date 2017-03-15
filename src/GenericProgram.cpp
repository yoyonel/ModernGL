#include "GenericProgram.hpp"

#include "Error.hpp"


PyObject * MGLGenericProgram_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLGenericProgram * self = (MGLGenericProgram *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLGenericProgram_tp_dealloc(MGLGenericProgram * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLGenericProgram_tp_init(MGLGenericProgram * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_New(TRACE, "Cannot create ModernGL.GenericProgram manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLGenericProgram_tp_str(MGLGenericProgram * self) {
	return PyUnicode_FromFormat("<ModernGL.GenericProgram>");
}

PyMethodDef MGLGenericProgram_tp_methods[] = {
	{0},
};

PyGetSetDef MGLGenericProgram_tp_getseters[] = {
	{0},
};

const char * MGLGenericProgram_tp_doc = R"(
	GenericProgram
)";

PyTypeObject MGLGenericProgram_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.GenericProgram",                              // tp_name
	sizeof(MGLGenericProgram),                              // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLGenericProgram_tp_dealloc,               // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLGenericProgram_tp_str,                     // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLGenericProgram_tp_str,                     // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLGenericProgram_tp_doc,                               // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLGenericProgram_tp_methods,                           // tp_methods
	0,                                                      // tp_members
	MGLGenericProgram_tp_getseters,                         // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLGenericProgram_tp_init,                    // tp_init
	0,                                                      // tp_alloc
	MGLGenericProgram_tp_new,                               // tp_new
};
