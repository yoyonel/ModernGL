#include "TextureWrap.hpp"

#include "Error.hpp"

PyObject * MGLTextureWrap_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLTextureWrap * self = (MGLTextureWrap *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLTextureWrap_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLTextureWrap_tp_dealloc(MGLTextureWrap * self) {

	#ifdef MGL_VERBOSE
	printf("MGLTextureWrap_tp_dealloc %p\n", self);
	#endif

	Py_TYPE(self)->tp_free((PyObject *)self);
}

int MGLTextureWrap_tp_init(MGLTextureWrap * self, PyObject * args, PyObject * kwargs) {
	MGLError_Set("cannot create mgl.TextureWrap manually");
	return -1;
}

PyMethodDef MGLTextureWrap_tp_methods[] = {
	{0},
};

int MGLTextureWrap_set_wrapper(MGLTextureWrap * self, PyObject * value, void * closure) {
	// if (self->wrapper) {
	// 	MGLError_Set("wrapper already set");
	// 	return -1;
	// }

	// Missing Py_INCREF is on purpose.
	self->wrapper = value;
	return 0;
}

PyGetSetDef MGLTextureWrap_tp_getseters[] = {
	{(char *)"wrapper", 0, (setter)MGLTextureWrap_set_wrapper, 0, 0},
	{0},
};

PyTypeObject MGLTextureWrap_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.TextureWrap",                                      // tp_name
	sizeof(MGLTextureWrap),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLTextureWrap_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	0,                                                      // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	0,                                                      // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT,                                     // tp_flags
	0,                                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLTextureWrap_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLTextureWrap_tp_getseters,                            // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLTextureWrap_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLTextureWrap_tp_new,                                  // tp_new
};

MGLTextureWrap * MGLTextureWrap_New() {
	MGLTextureWrap * self = (MGLTextureWrap *)MGLTextureWrap_tp_new(&MGLTextureWrap_Type, 0, 0);
	return self;
}

MGLTextureWrap * MGL_CLAMP_TO_EDGE;
MGLTextureWrap * MGL_REPEAT;
