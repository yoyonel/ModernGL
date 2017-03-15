#include "VertexArrayMatrixAttribute.hpp"

#include "Error.hpp"

PyObject * MGLVertexArrayMatrixAttribute_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArrayMatrixAttribute * self = (MGLVertexArrayMatrixAttribute *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLVertexArrayMatrixAttribute_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArrayMatrixAttribute_tp_dealloc(MGLVertexArrayMatrixAttribute * self) {

	#ifdef MGL_VERBOSE
	printf("MGLVertexArrayMatrixAttribute_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLVertexArrayMatrixAttribute_tp_init(MGLVertexArrayMatrixAttribute * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_New(TRACE, "Cannot create ModernGL.VertexArrayMatrixAttribute manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLVertexArrayMatrixAttribute_tp_str(MGLVertexArrayMatrixAttribute * self) {
	return PyUnicode_FromFormat("<ModernGL.VertexArrayMatrixAttribute>");
}

PyMethodDef MGLVertexArrayMatrixAttribute_tp_methods[] = {
	{0},
};

PyGetSetDef MGLVertexArrayMatrixAttribute_tp_getseters[] = {
	{0},
};

const char * MGLVertexArrayMatrixAttribute_tp_doc = R"(
	VertexArrayMatrixAttribute
)";

PyTypeObject MGLVertexArrayMatrixAttribute_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexArrayMatrixAttribute",                  // tp_name
	sizeof(MGLVertexArrayMatrixAttribute),                  // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArrayMatrixAttribute_tp_dealloc,   // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVertexArrayMatrixAttribute_tp_str,         // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVertexArrayMatrixAttribute_tp_str,         // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLVertexArrayMatrixAttribute_tp_doc,                   // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLVertexArrayMatrixAttribute_tp_methods,               // tp_methods
	0,                                                      // tp_members
	MGLVertexArrayMatrixAttribute_tp_getseters,             // tp_getset
	&MGLVertexArrayMember_Type,                             // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVertexArrayMatrixAttribute_tp_init,        // tp_init
	0,                                                      // tp_alloc
	MGLVertexArrayMatrixAttribute_tp_new,                   // tp_new
};

MGLVertexArrayMatrixAttribute * MGLVertexArrayMatrixAttribute_New() {
	MGLVertexArrayMatrixAttribute * self = (MGLVertexArrayMatrixAttribute *)MGLVertexArrayMatrixAttribute_tp_new(&MGLVertexArrayMatrixAttribute_Type, 0, 0);
	return self;
}
