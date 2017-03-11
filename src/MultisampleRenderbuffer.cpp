#include "MultisampleRenderbuffer.hpp"

PyObject * MGLMultisampleRenderbuffer_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLMultisampleRenderbuffer * self = (MGLMultisampleRenderbuffer *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLMultisampleRenderbuffer_tp_dealloc(MGLMultisampleRenderbuffer * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLMultisampleRenderbuffer_tp_init(MGLMultisampleRenderbuffer * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLMultisampleRenderbuffer_tp_str(MGLMultisampleRenderbuffer * self) {
	return PyUnicode_FromFormat("<ModernGL.MultisampleRenderbuffer>");
}

PyMethodDef MGLMultisampleRenderbuffer_tp_methods[] = {
	{0},
};

PyGetSetDef MGLMultisampleRenderbuffer_tp_getseters[] = {
	{0},
};

const char * MGLMultisampleRenderbuffer_tp_doc = R"(
	MultisampleRenderbuffer
)";

PyTypeObject MGLMultisampleRenderbuffer_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.MultisampleRenderbuffer",                     // tp_name
	sizeof(MGLMultisampleRenderbuffer),                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLMultisampleRenderbuffer_tp_dealloc,      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLMultisampleRenderbuffer_tp_str,            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLMultisampleRenderbuffer_tp_str,            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLMultisampleRenderbuffer_tp_doc,                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLMultisampleRenderbuffer_tp_methods,                  // tp_methods
	0,                                                      // tp_members
	MGLMultisampleRenderbuffer_tp_getseters,                // tp_getset
	&MGLFramebufferAttachment_Type,                         // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLMultisampleRenderbuffer_tp_init,           // tp_init
	0,                                                      // tp_alloc
	MGLMultisampleRenderbuffer_tp_new,                      // tp_new
};
