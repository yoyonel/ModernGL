#include "Framebuffer.hpp"

MGLFramebuffer * MGLFramebuffer_New() {
	MGLFramebuffer * self = (MGLFramebuffer *)MGLFramebuffer_Type.tp_alloc(&MGLFramebuffer_Type, 0);
	return self;
}

PyObject * MGLFramebuffer_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLFramebuffer * self = (MGLFramebuffer *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLFramebuffer_tp_dealloc(MGLFramebuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLFramebuffer_tp_init(MGLFramebuffer * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLFramebuffer_tp_str(MGLFramebuffer * self) {
	return PyUnicode_FromFormat("<ModernGL.Framebuffer>");
}

PyObject * MGLFramebuffer_release(MGLFramebuffer * self) {
	if (self->ob_base.ob_refcnt != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO: release

	// Py_DECREF((PyObject *)self);

	Py_RETURN_NONE;
}

PyMethodDef MGLFramebuffer_tp_methods[] = {
	{"release", (PyCFunction)MGLFramebuffer_release, METH_NOARGS, 0},
	{0},
};

PyGetSetDef MGLFramebuffer_tp_getseters[] = {
	{0},
};

const char * MGLFramebuffer_tp_doc = R"(
)";

PyTypeObject MGLFramebuffer_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Framebuffer",                                 // tp_name
	sizeof(MGLFramebuffer),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLFramebuffer_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLFramebuffer_tp_str,                        // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLFramebuffer_tp_doc,                                  // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLFramebuffer_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLFramebuffer_tp_getseters,                            // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLFramebuffer_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLFramebuffer_tp_new,                                  // tp_new
};
