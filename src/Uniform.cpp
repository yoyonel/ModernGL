#include "Uniform.hpp"

MGLUniform * MGLUniform_New() {
	MGLUniform * self = (MGLUniform *)MGLUniform_Type.tp_alloc(&MGLUniform_Type, 0);
	return self;
}

PyObject * MGLUniform_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLUniform * self = (MGLUniform *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLUniform_tp_dealloc(MGLUniform * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLUniform_tp_init(MGLUniform * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLUniform_tp_str(MGLUniform * self) {
	return PyUnicode_FromFormat("<ModernGL.Uniform>");
}

PyObject * MGLUniform_read(MGLUniform * self) {
	// printf("self->value_reader = %p\n", self->value_reader);
	PyObject * result = PyBytes_FromStringAndSize(0, self->element_size);

	// TODO: remove
	if (!self->gl_value_reader_proc) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	((gl_uniform_reader_proc)self->gl_value_reader_proc)(self->program->obj, self->location, PyBytes_AS_STRING(result));
	return result;
}

int MGLUniform_write(MGLUniform * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"data", 0};

	const char * buffer;
	int size;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"y#",
		(char **)kwlist,
		&buffer,
		&size
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	// TODO: remove
	if (!self->gl_value_writer_proc) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (size != self->array_len * self->element_size) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	if (self->matrix) {
		((gl_uniform_matrix_writer_proc)self->gl_value_writer_proc)(self->program->obj, self->location, self->array_len, false, buffer);
	} else {
		((gl_uniform_vector_writer_proc)self->gl_value_writer_proc)(self->program->obj, self->location, self->array_len, buffer);
	}

	return 0;
}

PyMethodDef MGLUniform_tp_methods[] = {
	{"read", (PyCFunction)MGLUniform_read, METH_NOARGS, 0},
	{"write", (PyCFunction)MGLUniform_write, METH_VARARGS | METH_KEYWORDS, 0},
	{0},
};

MGLProgram * MGLUniform_get_program(MGLUniform * self, void * closure) {
	Py_INCREF((PyObject *)self->program);
	return self->program;
}

PyObject * MGLUniform_get_name(MGLUniform * self, void * closure) {
	Py_INCREF(self->name);
	return self->name;
}

PyObject * MGLUniform_get_location(MGLUniform * self, void * closure) {
	return PyLong_FromLong(self->location);
}

PyObject * MGLUniform_get_value(MGLUniform * self, void * closure) {
	// if (self->array_len > 1) {
	// 	PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	// 	return 0;
	// }

	// TODO: remove

	if (!self->value_getter) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ((MGLUniform_Getter)self->value_getter)(self);
}

int MGLUniform_set_value(MGLUniform * self, PyObject * value, void * closure) {
	// TODO: remove

	if (!self->value_setter) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	return ((MGLUniform_Setter)self->value_setter)(self, value);
}

PyGetSetDef MGLUniform_tp_getseters[] = {
	{(char *)"program", (getter)MGLUniform_get_program, 0, 0, 0},
	{(char *)"name", (getter)MGLUniform_get_name, 0, 0, 0},
	{(char *)"location", (getter)MGLUniform_get_location, 0, 0, 0},
	{(char *)"value", (getter)MGLUniform_get_value, (setter)MGLUniform_set_value, 0, 0},
	{0},
};

const char * MGLUniform_tp_doc = R"(
)";

PyTypeObject MGLUniform_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Uniform",                                     // tp_name
	sizeof(MGLUniform),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLUniform_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLUniform_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLUniform_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLUniform_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLUniform_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLUniform_tp_getseters,                                // tp_getset
	&MGLContextMember_Type, // TODO: ProgramMember                                // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLUniform_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLUniform_tp_new,                                      // tp_new
};
