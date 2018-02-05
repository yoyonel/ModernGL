#include "Types.hpp"

PyObject * MGLVertexArray_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLVertexArray * self = (MGLVertexArray *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLVertexArray_tp_dealloc(MGLVertexArray * self) {
	MGLVertexArray_Type.tp_free((PyObject *)self);
}

PyObject * MGLVertexArray_render(MGLVertexArray * self, PyObject * args) {
	int mode;
	int vertices;
	int first;
	int instances;

	int args_ok = PyArg_ParseTuple(
		args,
		"IIII",
		&mode,
		&vertices,
		&first,
		&instances
	);

	if (!args_ok) {
		return 0;
	}

	if (vertices < 0) {
		if (self->num_vertices < 0) {
			MGLError_Set("cannot detect the number of vertices");
			return 0;
		}

		vertices = self->num_vertices;
	}

	const GLMethods & gl = self->context->gl;

	gl.UseProgram(self->program->program_obj);
	gl.BindVertexArray(self->vertex_array_obj);

	if (self->index_buffer != (MGLBuffer *)Py_None) {
		const void * ptr = (const void *)((GLintptr)first * 4);
		gl.DrawElementsInstanced(mode, vertices, GL_UNSIGNED_INT, ptr, instances);
	} else {
		gl.DrawArraysInstanced(mode, first, vertices, instances);
	}

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_transform(MGLVertexArray * self, PyObject * args) {
	MGLBuffer * output;
	int mode;
	int vertices;
	int first;
	int instances;

	int args_ok = PyArg_ParseTuple(
		args,
		"O!IIII",
		&MGLBuffer_Type,
		&output,
		&mode,
		&vertices,
		&first,
		&instances
	);

	if (!args_ok) {
		return 0;
	}

	if (!self->program->num_varyings) {
		MGLError_Set("the program has no varyings");
		return 0;
	}

	if (vertices < 0) {
		if (self->num_vertices < 0) {
			MGLError_Set("cannot detect the number of vertices");
			return 0;
		}

		vertices = self->num_vertices;
	}

	const GLMethods & gl = self->context->gl;

	gl.UseProgram(self->program->program_obj);
	gl.BindVertexArray(self->vertex_array_obj);

	gl.BindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, output->buffer_obj);

	gl.Enable(GL_RASTERIZER_DISCARD);
	gl.BeginTransformFeedback(mode);

	if (self->subroutines) {

		unsigned * subroutines = self->subroutines;

		if (self->program->num_vertex_shader_subroutines) {
			gl.UniformSubroutinesuiv(
				GL_VERTEX_SHADER,
				self->program->num_vertex_shader_subroutines,
				subroutines
			);
			subroutines += self->program->num_vertex_shader_subroutines;
		}

		if (self->program->num_fragment_shader_subroutines) {
			gl.UniformSubroutinesuiv(
				GL_FRAGMENT_SHADER,
				self->program->num_fragment_shader_subroutines,
				subroutines
			);
			subroutines += self->program->num_fragment_shader_subroutines;
		}

		if (self->program->num_geometry_shader_subroutines) {
			gl.UniformSubroutinesuiv(
				GL_GEOMETRY_SHADER,
				self->program->num_geometry_shader_subroutines,
				subroutines
			);
			subroutines += self->program->num_geometry_shader_subroutines;
		}

		if (self->program->num_tess_evaluation_shader_subroutines) {
			gl.UniformSubroutinesuiv(
				GL_TESS_EVALUATION_SHADER,
				self->program->num_tess_evaluation_shader_subroutines,
				subroutines
			);
			subroutines += self->program->num_tess_evaluation_shader_subroutines;
		}

		if (self->program->num_tess_control_shader_subroutines) {
			gl.UniformSubroutinesuiv(
				GL_TESS_CONTROL_SHADER,
				self->program->num_tess_control_shader_subroutines,
				subroutines
			);
		}
	}

	if (self->index_buffer != (MGLBuffer *)Py_None) {
		const void * ptr = (const void *)((GLintptr)first * 4);
		gl.DrawElementsInstanced(mode, vertices, GL_UNSIGNED_INT, ptr, instances);
	} else {
		gl.DrawArraysInstanced(mode, first, vertices, instances);
	}

	gl.EndTransformFeedback();
	gl.Disable(GL_RASTERIZER_DISCARD);
	gl.Flush();

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_bind(MGLVertexArray * self, PyObject * args) {
	MGLAttribute * attribute;
	MGLBuffer * buffer;
	Py_ssize_t offset;
	int stride;
	int divisor;

	int args_ok = PyArg_ParseTuple(
		args,
		"O!O!nII",
		&MGLAttribute_Type,
		&attribute,
		&MGLBuffer_Type,
		&buffer,
		&offset,
		&stride,
		&divisor
	);

	if (!args_ok) {
		return 0;
	}

	char * ptr = (char *)offset;

	const GLMethods & gl = self->context->gl;

	gl.BindVertexArray(self->vertex_array_obj);
	gl.BindBuffer(GL_ARRAY_BUFFER, buffer->buffer_obj);

	for (int r = 0; r < attribute->rows_length; ++r) {
		int location = attribute->location + r;

		if (attribute->normalizable) {
			((gl_attribute_normal_ptr_proc)attribute->gl_attrib_ptr_proc)(location, attribute->row_length, attribute->scalar_type, false, stride, ptr);
		} else {
			((gl_attribute_ptr_proc)attribute->gl_attrib_ptr_proc)(location, attribute->row_length, attribute->scalar_type, stride, ptr);
		}

		gl.VertexAttribDivisor(location, divisor);

		gl.EnableVertexAttribArray(location);

		ptr += attribute->row_size;
	}

	Py_RETURN_NONE;
}

PyObject * MGLVertexArray_release(MGLVertexArray * self) {
	MGLVertexArray_Invalidate(self);
	Py_RETURN_NONE;
}

PyMethodDef MGLVertexArray_tp_methods[] = {
	{"render", (PyCFunction)MGLVertexArray_render, METH_VARARGS, 0},
	{"transform", (PyCFunction)MGLVertexArray_transform, METH_VARARGS, 0},
	{"bind", (PyCFunction)MGLVertexArray_bind, METH_VARARGS, 0},
	{"release", (PyCFunction)MGLVertexArray_release, METH_NOARGS, 0},
	{0},
};

int MGLVertexArray_set_index_buffer(MGLVertexArray * self, PyObject * value, void * closure) {
	if (Py_TYPE(value) != &MGLBuffer_Type) {
		MGLError_Set("the index_buffer must be a Buffer not %s", Py_TYPE(value)->tp_name);
		return -1;
	}

	Py_INCREF(value);
	Py_DECREF(self->index_buffer);
	self->index_buffer = (MGLBuffer *)value;
	self->num_vertices = (int)(self->index_buffer->size / 4);

	return 0;
}

PyObject * MGLVertexArray_get_vertices(MGLVertexArray * self, void * closure) {
	return PyLong_FromLong(self->num_vertices);
}

int MGLVertexArray_set_vertices(MGLVertexArray * self, PyObject * value, void * closure) {
	int vertices = PyLong_AsUnsignedLong(value);

	if (PyErr_Occurred()) {
		MGLError_Set("invalid value for vertices");
		return -1;
	}

	self->num_vertices = vertices;

	return 0;
}

int MGLVertexArray_set_subroutines(MGLVertexArray * self, PyObject * value, void * closure) {
	if (PyTuple_GET_SIZE(value) != self->num_subroutines) {
		MGLError_Set("the number of subroutines is %d not %d", self->num_subroutines, PyTuple_GET_SIZE(value));
		return -1;
	}

	for (int i = 0; i < self->num_subroutines; ++i) {
		PyObject * obj = PyTuple_GET_ITEM(value, i);
		if (Py_TYPE(obj) == &PyLong_Type) {
			self->subroutines[i] = PyLong_AsUnsignedLong(obj);
		} else {
			PyObject * int_cast = PyNumber_Long(obj);
			if (!int_cast) {
				MGLError_Set("invalid values in subroutines");
				return -1;
			}
			self->subroutines[i] = PyLong_AsUnsignedLong(int_cast);
			Py_DECREF(int_cast);
		}
	}

	if (PyErr_Occurred()) {
		MGLError_Set("invalid values in subroutines");
		return -1;
	}

	return 0;
}

PyGetSetDef MGLVertexArray_tp_getseters[] = {
	{(char *)"index_buffer", 0, (setter)MGLVertexArray_set_index_buffer, 0, 0},
	{(char *)"vertices", (getter)MGLVertexArray_get_vertices, (setter)MGLVertexArray_set_vertices, 0, 0},
	{(char *)"subroutines", 0, (setter)MGLVertexArray_set_subroutines, 0, 0},
	{0},
};

PyTypeObject MGLVertexArray_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"mgl.VertexArray",                                      // tp_name
	sizeof(MGLVertexArray),                                 // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLVertexArray_tp_dealloc,                  // tp_dealloc
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
	MGLVertexArray_tp_methods,                              // tp_methods
	0,                                                      // tp_members
	MGLVertexArray_tp_getseters,                            // tp_getset
	0,                                                      // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	0,                                                      // tp_init
	0,                                                      // tp_alloc
	MGLVertexArray_tp_new,                                  // tp_new
};

void MGLVertexArray_Invalidate(MGLVertexArray * array) {
	if (Py_TYPE(array) == &MGLInvalidObject_Type) {
		return;
	}

	// TODO: decref

	const GLMethods & gl = array->context->gl;
	gl.DeleteVertexArrays(1, (GLuint *)&array->vertex_array_obj);

	Py_TYPE(array) = &MGLInvalidObject_Type;
	Py_DECREF(array);
}

void MGLVertexArray_Complete(MGLVertexArray * vertex_array) {
	const GLMethods & gl = vertex_array->context->gl;

	vertex_array->num_subroutines = 0;
	vertex_array->num_subroutines += vertex_array->program->num_vertex_shader_subroutines;
	vertex_array->num_subroutines += vertex_array->program->num_fragment_shader_subroutines;
	vertex_array->num_subroutines += vertex_array->program->num_geometry_shader_subroutines;
	vertex_array->num_subroutines += vertex_array->program->num_tess_evaluation_shader_subroutines;
	vertex_array->num_subroutines += vertex_array->program->num_tess_control_shader_subroutines;

	if (vertex_array->num_subroutines) {
		vertex_array->subroutines = new unsigned[vertex_array->num_subroutines];
	} else {
		vertex_array->subroutines = 0;
	}
}
