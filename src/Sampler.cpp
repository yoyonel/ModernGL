#include "Types.hpp"
#include "InlineMethods.hpp"

PyObject * MGLContext_sampler(MGLContext * self, PyObject * args) {
	int args_ok = PyArg_ParseTuple(
		args,
		""
	);

	if (!args_ok) {
		return 0;
	}

	const GLMethods & gl = self->gl;

	MGLSampler * sampler = (MGLSampler *)MGLSampler_Type.tp_alloc(&MGLSampler_Type, 0);

	gl.GenSamplers(1, (GLuint *)&sampler->sampler_obj);

	sampler->min_filter = GL_LINEAR;
	sampler->mag_filter = GL_LINEAR;
	sampler->anisotropy = 1.0;
	sampler->repeat_x = true;
	sampler->repeat_y = true;
	sampler->compare_func = 0;

	Py_INCREF(self);
	sampler->context = self;

	Py_INCREF(sampler);

	PyObject * result = PyTuple_New(2);
	PyTuple_SET_ITEM(result, 0, (PyObject *)sampler);
	PyTuple_SET_ITEM(result, 1, PyLong_FromLong(sampler->sampler_obj));
	return result;
}

PyObject * MGLSampler_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLSampler * self = (MGLSampler *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLSampler_tp_dealloc(MGLSampler * self) {
	MGLSampler_Type.tp_free((PyObject *)self);
}

PyObject * MGLSampler_use(MGLSampler * self, PyObject * args) {
	int index;

	int args_ok = PyArg_ParseTuple(
		args,
		"I",
		&index
	);

	if (!args_ok) {
		return 0;
	}

	const GLMethods & gl = self->context->gl;
	gl.BindSampler(index, self->sampler_obj);

	Py_RETURN_NONE;
}

PyObject * MGLSampler_clear(MGLSampler * self, PyObject * args) {
	int index;

	int args_ok = PyArg_ParseTuple(
		args,
		"I",
		&index
	);

	if (!args_ok) {
		return 0;
	}

	const GLMethods & gl = self->context->gl;
	gl.BindSampler(index, 0);

	Py_RETURN_NONE;
}

PyObject * MGLSampler_release(MGLSampler * self) {
	MGLSampler_Invalidate(self);
	Py_RETURN_NONE;
}

PyMethodDef MGLSampler_tp_methods[] = {
	{"use", (PyCFunction)MGLSampler_use, METH_VARARGS, 0},
	{"clear", (PyCFunction)MGLSampler_clear, METH_VARARGS, 0},
	{"release", (PyCFunction)MGLSampler_release, METH_NOARGS, 0},
	{0},
};

// PyObject * MGLSampler_get_bar(MGLSampler * self) {
// 	// TODO: impl sampler
// 	Py_RETURN_NONE;
// }

// int MGLSampler_set_bar(MGLSampler * self, PyObject * value) {
// 	// TODO: impl sampler
// 	return 0;
// }

PyObject * MGLSampler_get_repeat_x(MGLSampler * self) {
	return PyBool_FromLong(self->repeat_x);
}

int MGLSampler_set_repeat_x(MGLSampler * self, PyObject * value) {
	const GLMethods & gl = self->context->gl;

	if (value == Py_True) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_REPEAT);
		self->repeat_x = true;
		return 0;
	} else if (value == Py_False) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		self->repeat_x = false;
		return 0;
	} else {
		MGLError_Set("invalid value for texture_x");
		return -1;
	}
}

PyObject * MGLSampler_get_repeat_y(MGLSampler * self) {
	return PyBool_FromLong(self->repeat_y);
}

int MGLSampler_set_repeat_y(MGLSampler * self, PyObject * value) {
	const GLMethods & gl = self->context->gl;

	if (value == Py_True) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_REPEAT);
		self->repeat_y = true;
		return 0;
	} else if (value == Py_False) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		self->repeat_y = false;
		return 0;
	} else {
		MGLError_Set("invalid value for texture_x");
		return -1;
	}
}

PyObject * MGLSampler_get_filter(MGLSampler * self) {
	PyObject * res = PyTuple_New(2);
	PyTuple_SET_ITEM(res, 0, PyLong_FromLong(self->min_filter));
	PyTuple_SET_ITEM(res, 1, PyLong_FromLong(self->mag_filter));
	return res;
}

int MGLSampler_set_filter(MGLSampler * self, PyObject * value) {
	if (PyTuple_GET_SIZE(value) != 2) {
		MGLError_Set("invalid filter");
		return -1;
	}

	self->min_filter = PyLong_AsLong(PyTuple_GET_ITEM(value, 0));
	self->mag_filter = PyLong_AsLong(PyTuple_GET_ITEM(value, 1));

	const GLMethods & gl = self->context->gl;
	gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MIN_FILTER, self->min_filter);
	gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MAG_FILTER, self->mag_filter);

	return 0;
}

PyObject * MGLSampler_get_compare_func(MGLSampler * self) {
	return compare_func_to_string(self->compare_func);
}

int MGLSampler_set_compare_func(MGLSampler * self, PyObject * value) {
	const char * func = PyUnicode_AsUTF8(value);
	self->compare_func = compare_func_from_string(func);

	const GLMethods & gl = self->context->gl;

	if (self->compare_func == 0) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_MODE, GL_NONE);
	} else {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	}
	gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_FUNC, self->compare_func);

	return 0;
}

PyObject * MGLSampler_get_anisotropy(MGLSampler * self) {
	return PyFloat_FromDouble(self->anisotropy);
}

int MGLSampler_set_anisotropy(MGLSampler * self, PyObject * value) {
	self->anisotropy = fmin(fmax(PyFloat_AsDouble(value), 1.0), self->context->max_anisotropy);

	const GLMethods & gl = self->context->gl;
	gl.SamplerParameterf(self->sampler_obj, GL_TEXTURE_MAX_ANISOTROPY, self->anisotropy);

	return 0;
}

PyGetSetDef MGLSampler_tp_getseters[] = {
	{(char *)"repeat_x", (getter)MGLSampler_get_repeat_x, (setter)MGLSampler_set_repeat_x, 0, 0},
	{(char *)"repeat_y", (getter)MGLSampler_get_repeat_y, (setter)MGLSampler_set_repeat_y, 0, 0},
	{(char *)"filter", (getter)MGLSampler_get_filter, (setter)MGLSampler_set_filter, 0, 0},
	{(char *)"compare_func", (getter)MGLSampler_get_compare_func, (setter)MGLSampler_set_compare_func, 0, 0},
	{(char *)"anisotropy", (getter)MGLSampler_get_anisotropy, (setter)MGLSampler_set_anisotropy, 0, 0},
	{0},
};

PyTypeObject MGLSampler_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.Sampler",                                          // tp_name
	sizeof(MGLSampler),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLSampler_tp_dealloc,                      // tp_dealloc
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
	MGLSampler_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLSampler_tp_getseters,                                // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	0,                                                      // tp_init
	0,                                                      // tp_alloc
	MGLSampler_tp_new,                                      // tp_new
};

void MGLSampler_Invalidate(MGLSampler * sampler) {
	if (Py_TYPE(sampler) == &MGLInvalidObject_Type) {
		return;
	}

	// TODO: decref

	const GLMethods & gl = sampler->context->gl;
	gl.DeleteSamplers(1, (GLuint *)&sampler->sampler_obj);

	Py_TYPE(sampler) = &MGLInvalidObject_Type;
	Py_DECREF(sampler);
}
