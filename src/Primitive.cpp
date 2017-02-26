#include "Primitive.hpp"

MGLPrimitive * MGLPrimitive_New() {
	MGLPrimitive * self = (MGLPrimitive *)MGLPrimitive_Type.tp_alloc(&MGLPrimitive_Type, 0);
	return self;
}

PyObject * MGLPrimitive_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLPrimitive * self = (MGLPrimitive *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLPrimitive_tp_dealloc(MGLPrimitive * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLPrimitive_tp_init(MGLPrimitive * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLPrimitive_tp_str(MGLPrimitive * self) {
	return PyUnicode_FromFormat("<ModernGL.Primitive>");
}

PyMethodDef MGLPrimitive_tp_methods[] = {
	{0},
};

PyGetSetDef MGLPrimitive_tp_getseters[] = {
	{0},
};

const char * MGLPrimitive_tp_doc = R"(
)";

PyTypeObject MGLPrimitive_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Primitive",                                   // tp_name
	sizeof(MGLPrimitive),                                   // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLPrimitive_tp_dealloc,                    // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLPrimitive_tp_str,                          // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	0,                                                      // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLPrimitive_tp_doc,                                    // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLPrimitive_tp_methods,                                // tp_methods
	0,                                                      // tp_members
	MGLPrimitive_tp_getseters,                              // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLPrimitive_tp_init,                         // tp_init
	0,                                                      // tp_alloc
	MGLPrimitive_tp_new,                                    // tp_new
};
