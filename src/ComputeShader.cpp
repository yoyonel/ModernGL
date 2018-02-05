#include "Types.hpp"

#include "InlineMethods.hpp"

PyObject * MGLComputeShader_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLComputeShader * self = (MGLComputeShader *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLComputeShader_tp_dealloc(MGLComputeShader * self) {
	Py_TYPE(self)->tp_free((PyObject *)self);
}

PyObject * MGLComputeShader_run(MGLComputeShader * self, PyObject * args) {
	unsigned x;
	unsigned y;
	unsigned z;

	int args_ok = PyArg_ParseTuple(
		args,
		"III",
		&x,
		&y,
		&z
	);

	if (!args_ok) {
		return 0;
	}

	const GLMethods & gl = self->context->gl;

	gl.UseProgram(self->program_obj);
	gl.DispatchCompute(x, y, z);

	Py_RETURN_NONE;
}

PyMethodDef MGLComputeShader_tp_methods[] = {
	{"run", (PyCFunction)MGLComputeShader_run, METH_VARARGS, 0},
	// // {"release", (PyCFunction)MGLComputeShader_release, METH_VARARGS, 0},
	{0},
};

PyGetSetDef MGLComputeShader_tp_getseters[] = {
	{0},
};

PyTypeObject MGLComputeShader_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.ComputeShader",                                    // tp_name
	sizeof(MGLComputeShader),                               // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLComputeShader_tp_dealloc,                // tp_dealloc
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
	MGLComputeShader_tp_methods,                            // tp_methods
	0,                                                      // tp_members
	MGLComputeShader_tp_getseters,                          // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	0,                                                      // tp_init
	0,                                                      // tp_alloc
	MGLComputeShader_tp_new,                                // tp_new
};
