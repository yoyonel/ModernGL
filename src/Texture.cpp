#include "Texture.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"

PyObject * MGLTexture_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLTexture * self = (MGLTexture *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLTexture_tp_new %p\n", self);
	#endif

	if (self) {
	}

	return (PyObject *)self;
}

void MGLTexture_tp_dealloc(MGLTexture * self) {

	#ifdef MGL_VERBOSE
	printf("MGLTexture_tp_dealloc %p\n", self);
	#endif

	MGLTexture_Type.tp_free((PyObject *)self);
}

int MGLTexture_tp_init(MGLTexture * self, PyObject * args, PyObject * kwargs) {
	MGLError * error = MGLError_New(TRACE, "Cannot create ModernGL.Texture manually");
	PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
	return -1;
}

PyObject * MGLTexture_tp_str(MGLTexture * self) {
	return PyUnicode_FromFormat("<ModernGL.Texture>");
}

PyObject * MGLTexture_update(MGLTexture * self, PyObject * args) {


	PyObject * data;
	PyObject * size = Py_None;
	PyObject * offset = Py_None;

	int args_ok = PyArg_ParseTuple(
		args,

		"O|OO",

		&data,
		&size,
		&offset
	);

	if (!args_ok) {
		return 0;
	}

	int x;
	int y;

	int width;
	int height;

	Py_buffer buffer_view;

	if (size != Py_None) {
		if (Py_TYPE(size) != &PyTuple_Type) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		if (PyTuple_GET_SIZE(size) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		width = PyLong_AsLong(PyTuple_GET_ITEM(size, 0));
		height = PyLong_AsLong(PyTuple_GET_ITEM(size, 1));

		if (PyErr_Occurred()) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}
	} else {
		width = self->width;
		height = self->height;
	}

	if (offset != Py_None) {
		if (Py_TYPE(offset) != &PyTuple_Type) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		if (PyTuple_GET_SIZE(offset) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		x = PyLong_AsLong(PyTuple_GET_ITEM(offset, 0));
		y = PyLong_AsLong(PyTuple_GET_ITEM(offset, 1));

		if (PyErr_Occurred()) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}
	} else {
		x = 0;
		y = 0;
	}

	int expected_size = self->floats ? (width * height * self->components * 4) : (height * ((width * self->components + 3) & ~3));

	PyObject_GetBuffer(data, &buffer_view, PyBUF_SIMPLE);

	if (buffer_view.len != expected_size) {
		MGLError * error = MGLError_New(TRACE, "data size mismatch %d != %d", buffer_view.len, expected_size);
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);
		if (data != Py_None) {
			PyBuffer_Release(&buffer_view);
		}
		return 0;
	}

	const int formats[] = {0, GL_RED, GL_RG, GL_RGB, GL_RGBA};

	int pixel_type = self->floats ? GL_FLOAT : GL_UNSIGNED_BYTE;
	int format = formats[self->components];

	const GLMethods & gl = self->context->gl;

	gl.ActiveTexture(GL_TEXTURE0 + self->context->default_texture_unit);
	gl.BindTexture(GL_TEXTURE_2D, self->texture_obj);

	gl.TexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, format, pixel_type, buffer_view.buf);

	PyBuffer_Release(&buffer_view);

	Py_RETURN_NONE;
}

PyObject * MGLTexture_use(MGLTexture * self, PyObject * args) {


	int index = 0;

	int args_ok = PyArg_ParseTuple(
		args,

		"|I",

		&index
	);

	if (!args_ok) {
		return 0;
	}

	const GLMethods & gl = self->context->gl;
	gl.ActiveTexture(GL_TEXTURE0 + index);
	gl.BindTexture(GL_TEXTURE_2D, self->texture_obj);

	Py_RETURN_NONE;
}

PyObject * MGLTexture_release(MGLTexture * self) {
	MGLTexture_Invalidate(self);
	Py_RETURN_NONE;
}

PyMethodDef MGLTexture_tp_methods[] = {
	{"update", (PyCFunction)MGLTexture_update, METH_VARARGS | METH_KEYWORDS, 0},
	{"use", (PyCFunction)MGLTexture_use, METH_VARARGS | METH_KEYWORDS, 0},
	{"release", (PyCFunction)MGLTexture_release, METH_NOARGS, 0},
	{0},
};

PyObject * MGLTexture_get_width(MGLTexture * self, void * closure) {
	return PyLong_FromLong(self->width);
}

PyObject * MGLTexture_get_height(MGLTexture * self, void * closure) {
	return PyLong_FromLong(self->height);
}

PyGetSetDef MGLTexture_tp_getseters[] = {
	{(char *)"width", (getter)MGLTexture_get_width, 0, 0, 0},
	{(char *)"height", (getter)MGLTexture_get_height, 0, 0, 0},
	{0},
};

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
	0,                                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLTexture_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLTexture_tp_getseters,                                // tp_getset
	&MGLFramebufferAttachment_Type,                         // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLTexture_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLTexture_tp_new,                                      // tp_new
};

MGLTexture * MGLTexture_New() {
	MGLTexture * self = (MGLTexture *)MGLTexture_tp_new(&MGLTexture_Type, 0, 0);
	return self;
}

void MGLTexture_Invalidate(MGLTexture * texture) {
	if (Py_TYPE(texture) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLTexture_Invalidate %p already released\n", texture);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLTexture_Invalidate %p\n", texture);
	#endif

	texture->context->gl.DeleteTextures(1, (GLuint *)&texture->texture_obj);

	Py_DECREF(texture->context);

	Py_TYPE(texture) = &MGLInvalidObject_Type;

	Py_DECREF(texture);
}
