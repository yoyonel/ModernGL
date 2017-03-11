#include "ProgramStage.hpp"

PyObject * MGLProgramStage_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLProgramStage * self = (MGLProgramStage *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLProgramStage_tp_dealloc(MGLProgramStage * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLProgramStage_tp_init(MGLProgramStage * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLProgramStage_tp_str(MGLProgramStage * self) {
	return PyUnicode_FromFormat("<ModernGL.ProgramStage>");
}

PyMethodDef MGLProgramStage_tp_methods[] = {
	{0},
};

PyGetSetDef MGLProgramStage_tp_getseters[] = {
	{0},
};

const char * MGLProgramStage_tp_doc = R"(
	ProgramStage
)";

PyTypeObject MGLProgramStage_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.ProgramStage",                                // tp_name
	sizeof(MGLProgramStage),                                // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLProgramStage_tp_dealloc,                 // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLProgramStage_tp_str,                       // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLProgramStage_tp_str,                       // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLProgramStage_tp_doc,                                 // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLProgramStage_tp_methods,                             // tp_methods
	0,                                                      // tp_members
	MGLProgramStage_tp_getseters,                           // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLProgramStage_tp_init,                      // tp_init
	0,                                                      // tp_alloc
	MGLProgramStage_tp_new,                                 // tp_new
};
