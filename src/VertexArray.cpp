#include "VertexArray.hpp"

#include "Primitive.hpp"

MGLVertexArray * MGLVertexArray_New() {
	MGLVertexArray * self = (MGLVertexArray *)MGLVertexArray_Type.tp_alloc(&MGLVertexArray_Type, 0);
	return self;
}

PyObject * MGLVertexArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArray * self = (MGLVertexArray *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArray_tp_dealloc(MGLVertexArray * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLVertexArray_tp_init(MGLVertexArray * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLVertexArray_tp_str(MGLVertexArray * self) {
	return PyUnicode_FromFormat("<ModernGL.VertexArray>");
}

PyObject * MGLVertexArray_render(MGLVertexArray * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"mode", "vertices", "first", "instances", 0};

	MGLPrimitive * mode; // TODO: default value
	int vertices = -1;
	int first = 0;
	int instances = 1;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O!|I$II",
		(char **)kwlist,
		&MGLPrimitive_Type,
		&mode,
		&vertices,
		&first,
		&instances
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (vertices < 0) {
		if (self->num_vertices < 0) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		vertices = self->num_vertices;
	}

	GLMethods & gl = self->ctx->gl;

	gl.UseProgram(self->program->obj);
	gl.BindVertexArray(self->obj);

	if (self->indexed) {
		const void * ptr = (const void *)((GLintptr)first * 4);
		gl.DrawElementsInstanced(mode->primitive, vertices, GL_UNSIGNED_INT, ptr, instances);
	} else {
		gl.DrawArraysInstanced(mode->primitive, first, vertices, instances);
	}

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_release(MGLVertexArray * self) {
	if (self->ob_base.ob_refcnt != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO: release

	// Py_DECREF((PyObject *)self);

	Py_RETURN_NONE;
}

PyMethodDef MGLVertexArray_tp_methods[] = {
	{"render", (PyCFunction)MGLVertexArray_render, METH_VARARGS | METH_KEYWORDS, 0},
	{"release", (PyCFunction)MGLVertexArray_release, METH_NOARGS, 0},
	{0},
};

MGLProgram * MGLVertexArray_get_program(MGLVertexArray * self) {
	Py_INCREF(self->program);
	return self->program;
}

PyObject * MGLVertexArray_get_content(MGLVertexArray * self) {
	Py_INCREF(self->content);
	return self->content;
}

PyObject * MGLVertexArray_get_indexed(MGLVertexArray * self) {
	return PyBool_FromLong(self->indexed);
}

PyObject * MGLVertexArray_get_vertices(MGLVertexArray * self) {
	return PyLong_FromLong(self->num_vertices);
}

PyGetSetDef MGLVertexArray_tp_getseters[] = {
	{(char *)"program", (getter)MGLVertexArray_get_program, 0, 0, 0},
	{(char *)"content", (getter)MGLVertexArray_get_content, 0, 0, 0},
	{(char *)"indexed", (getter)MGLVertexArray_get_indexed, 0, 0, 0},
	{(char *)"vertices", (getter)MGLVertexArray_get_vertices, 0, 0, 0},
	{0},
};

const char * MGLVertexArray_tp_doc = R"(
)";

PyTypeObject MGLVertexArray_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexArray",                                 // tp_name
	sizeof(MGLVertexArray),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArray_tp_dealloc,                  // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLVertexArray_tp_str,                        // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLVertexArray_tp_str,                        // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLVertexArray_tp_doc,                                  // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLVertexArray_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLVertexArray_tp_getseters,                            // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLVertexArray_tp_init,                       // tp_init
	0,                                                      // tp_alloc
	MGLVertexArray_tp_new,                                  // tp_new
};
