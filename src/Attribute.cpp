#include "Attribute.hpp"

#include "InvalidObject.hpp"

PyObject * MGLAttribute_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLAttribute * self = (MGLAttribute *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_tp_new %p\n", self);
	#endif

	if (self) {
		self->name = 0;

		self->value_getter = 0;
		self->value_setter = 0;

		self->gl_value_reader_proc = 0;
		self->gl_value_writer_proc = 0;
	}

	return (PyObject *)self;
}

void MGLAttribute_tp_dealloc(MGLAttribute * self) {

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLAttribute_tp_init(MGLAttribute * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLAttribute_tp_str(MGLAttribute * self) {
	return PyUnicode_FromFormat("<ModernGL.Attribute>");
}

PyMethodDef MGLAttribute_tp_methods[] = {
	{0},
};

PyObject * MGLAttribute_get_name(MGLAttribute * self, void * closure) {
	Py_INCREF(self->name);
	return self->name;
}

char MGLAttribute_name_doc[] = R"(
	name
)";

PyObject * MGLAttribute_get_location(MGLAttribute * self, void * closure) {
	return PyLong_FromLong(self->location);
}

char MGLAttribute_location_doc[] = R"(
	location
)";

PyObject * MGLAttribute_get_default(MGLAttribute * self, void * closure) {
	// TODO:
	PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	return 0;
}

int MGLAttribute_set_default(MGLAttribute * self, PyObject * value, void * closure) {
	// TODO:
	PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	return 0;
}

char MGLAttribute_default_doc[] = R"(
	default
)";

PyGetSetDef MGLAttribute_tp_getseters[] = {
	{(char *)"name", (getter)MGLAttribute_get_name, 0, MGLAttribute_name_doc, 0},
	{(char *)"location", (getter)MGLAttribute_get_location, 0, MGLAttribute_location_doc, 0},
	{(char *)"default", (getter)MGLAttribute_get_default, (setter)MGLAttribute_set_default, MGLAttribute_default_doc, 0},
	{0},
};

const char * MGLAttribute_tp_doc = R"(
	Attribute
)";

PyTypeObject MGLAttribute_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Attribute",                                   // tp_name
	sizeof(MGLAttribute),                                   // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLAttribute_tp_dealloc,                    // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLAttribute_tp_str,                          // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLAttribute_tp_str,                          // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLAttribute_tp_doc,                                    // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLAttribute_tp_methods,                                // tp_methods
	0,                                                      // tp_members
	MGLAttribute_tp_getseters,                              // tp_getset
	&MGLProgramMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLAttribute_tp_init,                         // tp_init
	0,                                                      // tp_alloc
	MGLAttribute_tp_new,                                    // tp_new
};

MGLAttribute * MGLAttribute_New() {
	MGLAttribute * self = (MGLAttribute *)MGLAttribute_tp_new(&MGLAttribute_Type, 0, 0);
	return self;
}

void MGLAttribute_Invalidate(MGLAttribute * attribute) {

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_Invalidate %p\n", attribute);
	#endif

	Py_DECREF(attribute->name);

	attribute->ob_base.ob_type = &MGLInvalidObject_Type;
	attribute->initial_type = &MGLAttribute_Type;

	Py_DECREF(attribute);
}
