#include "Varying.hpp"

#include "InvalidObject.hpp"

PyObject * MGLVarying_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVarying * self = (MGLVarying *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLVarying_tp_new %p\n", self);
	#endif

	if (self) {
		self->name = 0;
	}

	return (PyObject *)self;
}

void MGLVarying_tp_dealloc(MGLVarying * self) {

	#ifdef MGL_VERBOSE
	printf("MGLVarying_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLVarying_tp_init(MGLVarying * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLVarying_tp_str(MGLVarying * self) {
	return PyUnicode_FromFormat("<ModernGL.Varying>");
}

PyMethodDef MGLVarying_tp_methods[] = {
	{0},
};

PyObject * MGLVarying_get_name(MGLVarying * self, void * closure) {
	Py_INCREF(self->name);
	return self->name;
}

char MGLVarying_name_doc[] = R"(
	name
)";

PyObject * MGLVarying_get_index(MGLVarying * self, void * closure) {
	return PyLong_FromLong(self->index);
}

char MGLVarying_index_doc[] = R"(
	index
)";

PyGetSetDef MGLVarying_tp_getseters[] = {
	{(char *)"name", (getter)MGLVarying_get_name, 0, MGLVarying_name_doc, 0},
	{(char *)"index", (getter)MGLVarying_get_index, 0, MGLVarying_index_doc, 0},
	{0},
};

const char * MGLVarying_tp_doc = R"(
	Varying
)";

PyTypeObject MGLVarying_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Varying",                                     // tp_name
	sizeof(MGLVarying),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVarying_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVarying_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVarying_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLVarying_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLVarying_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLVarying_tp_getseters,                                // tp_getset
	&MGLProgramMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVarying_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLVarying_tp_new,                                      // tp_new
};

MGLVarying * MGLVarying_New() {
	MGLVarying * self = (MGLVarying *)MGLVarying_tp_new(&MGLVarying_Type, 0, 0);
	return self;
}

void MGLVarying_Invalidate(MGLVarying * varying) {

	#ifdef MGL_VERBOSE
	printf("MGLVarying_Invalidate %p\n", varying);
	#endif

	Py_DECREF(varying->name);

	varying->ob_base.ob_type = &MGLInvalidObject_Type;
	varying->initial_type = &MGLVarying_Type;

	Py_DECREF(varying);
}
