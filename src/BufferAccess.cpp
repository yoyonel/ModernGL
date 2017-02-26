#include "BufferAccess.hpp"

MGLBufferAccess * MGLBufferAccess_New() {
	MGLBufferAccess * self = (MGLBufferAccess *)MGLBufferAccess_Type.tp_alloc(&MGLBufferAccess_Type, 0);
	return self;
}

PyObject * MGLBufferAccess_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLBufferAccess * self = (MGLBufferAccess *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLBufferAccess_tp_dealloc(MGLBufferAccess * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLBufferAccess_tp_init(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLBufferAccess_tp_str(MGLBufferAccess * self) {
	return PyUnicode_FromFormat("<ModernGL.BufferAccess>");
}

MGLBufferAccess * MGLBufferAccess_open(MGLBufferAccess * self) {
	if (self->ptr) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	GLMethods & gl = self->buffer->ctx->gl;
	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	self->ptr = gl.MapBufferRange(GL_ARRAY_BUFFER, self->offset, self->size, self->access);

	if (!self->ptr) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	Py_INCREF((PyObject *)self);
	return self;
}

PyObject * MGLBufferAccess_close(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
	// static const char * kwlist[] = {"type", "value", "traceback", 0};

	// PyObject * exc_type = 0;
	// PyObject * exc_value = 0;
	// PyObject * exc_traceback = 0;

	// int args_ok = PyArg_ParseTupleAndKeywords(
	// 	args,
	// 	kwargs,
	// 	"|OOO",
	// 	(char **)kwlist,
	// 	&exc_type,
	// 	&exc_value,
	// 	&exc_traceback
	// );

	// if (!args_ok) {
	// 	// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	// 	return 0;
	// }

	// if (!self->ptr) {
	// 	PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	// 	return 0;
	// }

	// TODO: check silent fail

	if (self->ptr) {
		GLMethods & gl = self->buffer->ctx->gl;
		gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
		gl.UnmapBuffer(GL_ARRAY_BUFFER);
	}

	Py_RETURN_NONE;
}

PyObject * MGLBufferAccess_read(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"size", "offset", 0};

	int size = -1;
	int offset = 0;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|I$I",
		(char **)kwlist,
		&size,
		&offset
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (size == -1) {
		size = self->size - offset;
	}

	if (offset < 0 || size < 0 || size + offset > self->size) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (!self->ptr) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return PyBytes_FromStringAndSize((const char *)self->ptr, size);
}

PyObject * MGLBufferAccess_write(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"data", "offset", 0};

	const char * data = 0;
	int size = 0;
	int offset = 0;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"y#|$I",
		(char **)kwlist,
		&data,
		&size,
		&offset
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (offset < 0 || size + offset > self->size) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (!self->ptr) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	memcpy(self->ptr, data, size);

	Py_RETURN_NONE;
}

// PyObject * MGLBufferAccess_write_chunks(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
// 	return 0;
// }

// PyObject * MGLBufferAccess_write_many(MGLBufferAccess * self, PyObject * args, PyObject * kwargs) {
// 	return 0;
// }

PyMethodDef MGLBufferAccess_tp_methods[] = {
	{"open", (PyCFunction)MGLBufferAccess_open, METH_NOARGS, 0},
	{"close", (PyCFunction)MGLBufferAccess_close, METH_VARARGS | METH_KEYWORDS, 0},

	{"__enter__", (PyCFunction)MGLBufferAccess_open, METH_NOARGS, 0},
	{"__exit__", (PyCFunction)MGLBufferAccess_close, METH_VARARGS | METH_KEYWORDS, 0},

	{"read", (PyCFunction)MGLBufferAccess_read, METH_VARARGS | METH_KEYWORDS, 0},
	{"write", (PyCFunction)MGLBufferAccess_write, METH_VARARGS | METH_KEYWORDS, 0},
	// {"write_chunks", (PyCFunction)MGLBufferAccess_write_chunks, METH_VARARGS | METH_KEYWORDS, 0},
	// {"write_many", (PyCFunction)MGLBufferAccess_write_many, METH_VARARGS | METH_KEYWORDS, 0},
	{0},
};

PyGetSetDef MGLBufferAccess_tp_getseters[] = {
	{(char *)"buffer", 0, 0, 0, 0},
	{(char *)"offset", 0, 0, 0, 0},
	{(char *)"size", 0, 0, 0, 0},
	{(char *)"readonly", 0, 0, 0, 0},
	{0},
};

const char * MGLBufferAccess_tp_doc = R"(
)";

PyTypeObject MGLBufferAccess_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.BufferAccess",                                // tp_name
	sizeof(MGLBufferAccess),                                // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLBufferAccess_tp_dealloc,                 // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLBufferAccess_tp_str,                       // tp_repr
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
	MGLBufferAccess_tp_doc,                                 // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLBufferAccess_tp_methods,                             // tp_methods
	0,                                                      // tp_members
	MGLBufferAccess_tp_getseters,                           // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLBufferAccess_tp_init,                      // tp_init
	0,                                                      // tp_alloc
	MGLBufferAccess_tp_new,                                 // tp_new
};
