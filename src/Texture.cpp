#include "Texture.hpp"

MGLTexture * MGLTexture_New() {
	MGLTexture * self = (MGLTexture *)MGLTexture_Type.tp_alloc(&MGLTexture_Type, 0);
	return self;
}

PyObject * MGLTexture_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLTexture * self = (MGLTexture *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLTexture_tp_dealloc(MGLTexture * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLTexture_tp_init(MGLTexture * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLTexture_tp_str(MGLTexture * self) {
	return PyUnicode_FromFormat("<ModernGL.Texture>");
}

PyObject * MGLTexture_use(MGLTexture * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"index", 0};

	int index = 0;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|i",
		(char **)kwlist,
		&index
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	GLMethods & gl = self->ctx->gl;
	gl.ActiveTexture(GL_TEXTURE0 + index);
	gl.BindTexture(GL_TEXTURE_2D, self->obj);

	Py_RETURN_NONE;
}

PyObject * MGLTexture_release(MGLTexture * self) {
	if (self->ob_base.ob_refcnt != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO: release

	// Py_DECREF((PyObject *)self);

	Py_RETURN_NONE;
}

PyMethodDef MGLTexture_tp_methods[] = {
	{"use", (PyCFunction)MGLTexture_use, METH_VARARGS | METH_KEYWORDS, 0},
	{"release", (PyCFunction)MGLTexture_release, METH_NOARGS, 0},
	{0},
};

PyGetSetDef MGLTexture_tp_getseters[] = {
	{0},
};

const char * MGLTexture_tp_doc = R"(
)";

PyTypeObject MGLTexture_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Texture",                                     // tp_name
	sizeof(MGLTexture),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLTexture_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLTexture_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLTexture_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLTexture_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLTexture_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLTexture_tp_getseters,                                // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLTexture_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLTexture_tp_new,                                      // tp_new
};
