#include "Buffer.hpp"

#include "InvalidObject.hpp"
#include "BufferAccess.hpp"

MGLBuffer * MGLBuffer_New() {
	MGLBuffer * self = (MGLBuffer *)MGLBuffer_Type.tp_alloc(&MGLBuffer_Type, 0);
	return self;
}

PyObject * MGLBuffer_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLBuffer * self = (MGLBuffer *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLBuffer_tp_dealloc(MGLBuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLBuffer_tp_init(MGLBuffer * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLBuffer_tp_str(MGLBuffer * self) {
	return PyUnicode_FromFormat("<ModernGL.Buffer>");
}

MGLBufferAccess * MGLBuffer_access(MGLBuffer * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"offset", "size", "readonly", 0};

	int offset = 0;
	int size = -1;
	int readonly = false;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|$iip",
		(char **)kwlist,
		&offset,
		&size,
		&readonly
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (size == -1) {
		size = self->size - offset;
	}

	if (offset < 0 || size > self->size - offset) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	MGLBufferAccess * access = MGLBufferAccess_New();

	Py_INCREF((PyObject *)self);
	access->buffer = self;
	access->obj = self->obj;
	access->offset = offset;
	access->size = size;
	access->access = readonly ? GL_MAP_READ_BIT : (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);
	access->ptr = 0;

	return access;
}

PyObject * MGLBuffer_read(MGLBuffer * self, PyObject * args, PyObject * kwargs) {
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

	// printf("%d %d %d\n", self->obj, offset, size);

	GLMethods & gl = self->ctx->gl;

	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	void * map = gl.MapBufferRange(GL_ARRAY_BUFFER, offset, size, GL_MAP_READ_BIT);

	if (!map) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * data = PyBytes_FromStringAndSize((const char *)map, size);

	gl.UnmapBuffer(GL_ARRAY_BUFFER);

	return data;
}

PyObject * MGLBuffer_write(MGLBuffer * self, PyObject * args, PyObject * kwargs) {
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

	GLMethods & gl = self->ctx->gl;
	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	gl.BufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, size, data);
	Py_RETURN_NONE;
}

PyObject * MGLBuffer_orphan(MGLBuffer * self) {
	GLMethods & gl = self->ctx->gl;
	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	gl.BufferData(GL_ARRAY_BUFFER, self->size, 0, self->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	Py_RETURN_NONE;
}

PyObject * MGLBuffer_release(MGLBuffer * self) {
	if (self->ob_base.ob_refcnt != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	GLMethods & gl = self->ctx->gl;
	gl.DeleteBuffers(1, (GLuint *)&self->obj);

	// TODO: call python destructor

	self->ob_base.ob_type = &MGLInvalidObject_Type;

	// Py_ssize_t ob_refcnt;
	// struct _typeobject *ob_type;
	self->obj = 0;

	Py_RETURN_NONE;
}

PyMethodDef MGLBuffer_tp_methods[] = {
	{"access", (PyCFunction)MGLBuffer_access, METH_VARARGS | METH_KEYWORDS},
	{"read", (PyCFunction)MGLBuffer_read, METH_VARARGS | METH_KEYWORDS},
	{"write", (PyCFunction)MGLBuffer_write, METH_VARARGS | METH_KEYWORDS},
	{"orphan", (PyCFunction)MGLBuffer_orphan, METH_NOARGS},
	{"release", (PyCFunction)MGLBuffer_release, METH_NOARGS},
	{0},
};

PyGetSetDef MGLBuffer_tp_getseters[] = {
	{(char *)"size", 0, 0, 0, 0},
	{(char *)"dynamic", 0, 0, 0, 0},
	{0},
};

int MGLBuffer_tp_as_buffer_get_vew(MGLBuffer * self, Py_buffer * view, int flags) {
	int access = (flags == PyBUF_SIMPLE) ? GL_MAP_READ_BIT : (GL_MAP_READ_BIT | GL_MAP_WRITE_BIT);

	GLMethods & gl = self->ctx->gl;
	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	void * map = gl.MapBufferRange(GL_ARRAY_BUFFER, 0, self->size, access);

	if (!map) {
		PyErr_Format(PyExc_BufferError, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		view->obj = 0;
		return -1;
	}

	view->buf = map;
	view->len = self->size;
	view->itemsize = 1;

	view->format = 0;
	view->ndim = 0;
	view->shape = 0;
	view->strides = 0;
	view->suboffsets = 0;

	// view->readonly = <auto>;
	// view->internal = <auto>;

	Py_INCREF((PyObject *)self);
	view->obj = (PyObject *)self;
	return 0;
}

void MGLBuffer_tp_as_buffer_release_view(MGLBuffer * self, Py_buffer * view) {
	GLMethods & gl = self->ctx->gl;
	gl.BindBuffer(GL_ARRAY_BUFFER, self->obj);
	gl.UnmapBuffer(GL_ARRAY_BUFFER);
}

PyBufferProcs MGLBuffer_tp_as_buffer = {
	(getbufferproc)MGLBuffer_tp_as_buffer_get_vew,                  // getbufferproc bf_getbuffer
	(releasebufferproc)MGLBuffer_tp_as_buffer_release_view,         // releasebufferproc bf_releasebuffer
};

const char * MGLBuffer_tp_doc = R"(
)";

PyTypeObject MGLBuffer_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Buffer",                                      // tp_name
	sizeof(MGLBuffer),                                      // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLBuffer_tp_dealloc,                       // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLBuffer_tp_str,                             // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLBuffer_tp_str,                             // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLBuffer_tp_doc,                                       // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLBuffer_tp_methods,                                   // tp_methods
	0,                                                      // tp_members
	MGLBuffer_tp_getseters,                                 // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLBuffer_tp_init,                            // tp_init
	0,                                                      // tp_alloc
	MGLBuffer_tp_new,                                       // tp_new
};
