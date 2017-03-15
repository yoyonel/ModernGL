#include "VertexArrayListAttribute.hpp"

#include "Error.hpp"

PyObject * MGLVertexArrayListAttribute_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArrayListAttribute * self = (MGLVertexArrayListAttribute *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLVertexArrayListAttribute_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArrayListAttribute_tp_dealloc(MGLVertexArrayListAttribute * self) {

	#ifdef MGL_VERBOSE
	printf("MGLVertexArrayListAttribute_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLVertexArrayListAttribute_tp_init(MGLVertexArrayListAttribute * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_New(TRACE, "Cannot create ModernGL.VertexArrayListAttribute manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLVertexArrayListAttribute_tp_str(MGLVertexArrayListAttribute * self) {
	return PyUnicode_FromFormat("<ModernGL.VertexArrayListAttribute>");
}

PyMethodDef MGLVertexArrayListAttribute_tp_methods[] = {
	{0},
};

PyGetSetDef MGLVertexArrayListAttribute_tp_getseters[] = {
	{0},
};

const char * MGLVertexArrayListAttribute_tp_doc = R"(
	VertexArrayListAttribute
)";

PyTypeObject MGLVertexArrayListAttribute_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexArrayListAttribute",                    // tp_name
	sizeof(MGLVertexArrayListAttribute),                    // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArrayListAttribute_tp_dealloc,     // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVertexArrayListAttribute_tp_str,           // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVertexArrayListAttribute_tp_str,           // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLVertexArrayListAttribute_tp_doc,                     // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLVertexArrayListAttribute_tp_methods,                 // tp_methods
	0,                                                      // tp_members
	MGLVertexArrayListAttribute_tp_getseters,               // tp_getset
	&MGLVertexArrayMember_Type,                             // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVertexArrayListAttribute_tp_init,          // tp_init
	0,                                                      // tp_alloc
	MGLVertexArrayListAttribute_tp_new,                     // tp_new
};

MGLVertexArrayListAttribute * MGLVertexArrayListAttribute_New() {
	MGLVertexArrayListAttribute * self = (MGLVertexArrayListAttribute *)MGLVertexArrayListAttribute_tp_new(&MGLVertexArrayListAttribute_Type, 0, 0);
	return self;
}
