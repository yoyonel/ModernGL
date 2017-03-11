#include "VertexArrayAttribute.hpp"

PyObject * MGLVertexArrayAttribute_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArrayAttribute * self = (MGLVertexArrayAttribute *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArrayAttribute_tp_dealloc(MGLVertexArrayAttribute * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLVertexArrayAttribute_tp_init(MGLVertexArrayAttribute * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLVertexArrayAttribute_tp_str(MGLVertexArrayAttribute * self) {
	return PyUnicode_FromFormat("<ModernGL.VertexArrayAttribute>");
}

PyMethodDef MGLVertexArrayAttribute_tp_methods[] = {
	{0},
};

PyGetSetDef MGLVertexArrayAttribute_tp_getseters[] = {
	{0},
};

const char * MGLVertexArrayAttribute_tp_doc = R"(
	VertexArrayAttribute
)";

PyTypeObject MGLVertexArrayAttribute_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexArrayAttribute",                        // tp_name
	sizeof(MGLVertexArrayAttribute),                        // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArrayAttribute_tp_dealloc,         // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVertexArrayAttribute_tp_str,               // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVertexArrayAttribute_tp_str,               // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLVertexArrayAttribute_tp_doc,                         // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLVertexArrayAttribute_tp_methods,                     // tp_methods
	0,                                                      // tp_members
	MGLVertexArrayAttribute_tp_getseters,                   // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVertexArrayAttribute_tp_init,              // tp_init
	0,                                                      // tp_alloc
	MGLVertexArrayAttribute_tp_new,                         // tp_new
};
