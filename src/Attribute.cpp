#include "Attribute.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"

PyObject * MGLAttribute_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLAttribute * self = (MGLAttribute *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_tp_new %p\n", self);
	#endif

	if (self) {
		self->name = 0;

		self->gl_attrib_ptr_proc = 0;
	}

	return (PyObject *)self;
}

void MGLAttribute_tp_dealloc(MGLAttribute * self) {

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_tp_dealloc %p\n", self);
	#endif

	MGLAttribute_Type.tp_free((PyObject *)self);
}

int MGLAttribute_tp_init(MGLAttribute * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLAttribute_tp_str(MGLAttribute * self) {
	return PyUnicode_FromFormat("<ModernGL.Attribute>");
}

PyMethodDef MGLAttribute_tp_methods[] = {
	{0},
};

PyObject * MGLAttribute_get_name(MGLAttribute * self, void * closure) {
	Py_INCREF(self->name);
	return self->name;
}

char MGLAttribute_name_doc[] = R"(
	name
)";

PyObject * MGLAttribute_get_location(MGLAttribute * self, void * closure) {
	return PyLong_FromLong(self->location);
}

char MGLAttribute_location_doc[] = R"(
	location
)";

PyObject * MGLAttribute_get_array_length(MGLAttribute * self, void * closure) {
	return PyLong_FromLong(self->array_length);
}

char MGLAttribute_array_length_doc[] = R"(
	array_length
)";

PyObject * MGLAttribute_get_dimension(MGLAttribute * self, void * closure) {
	return PyLong_FromLong(self->dimension);
}

char MGLAttribute_dimension_doc[] = R"(
	dimension
)";

PyObject * MGLAttribute_get_shape(MGLAttribute * self, void * closure) {
	return PyUnicode_FromFormat("%c", self->shape);
}

char MGLAttribute_shape_doc[] = R"(
	shape
)";

PyGetSetDef MGLAttribute_tp_getseters[] = {
	{(char *)"name", (getter)MGLAttribute_get_name, 0, MGLAttribute_name_doc, 0},
	{(char *)"location", (getter)MGLAttribute_get_location, 0, MGLAttribute_location_doc, 0},
	{(char *)"array_length", (getter)MGLAttribute_get_array_length, 0, MGLAttribute_array_length_doc, 0},
	{(char *)"dimension", (getter)MGLAttribute_get_dimension, 0, MGLAttribute_dimension_doc, 0},
	{(char *)"shape", (getter)MGLAttribute_get_shape, 0, MGLAttribute_shape_doc, 0},
	{0},
};

const char * MGLAttribute_tp_doc = R"(
	Attribute
)";

PyTypeObject MGLAttribute_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Attribute",                                   // tp_name
	sizeof(MGLAttribute),                                   // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLAttribute_tp_dealloc,                    // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLAttribute_tp_str,                          // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLAttribute_tp_str,                          // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLAttribute_tp_doc,                                    // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLAttribute_tp_methods,                                // tp_methods
	0,                                                      // tp_members
	MGLAttribute_tp_getseters,                              // tp_getset
	&MGLProgramMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLAttribute_tp_init,                         // tp_init
	0,                                                      // tp_alloc
	MGLAttribute_tp_new,                                    // tp_new
};

MGLAttribute * MGLAttribute_New() {
	MGLAttribute * self = (MGLAttribute *)MGLAttribute_tp_new(&MGLAttribute_Type, 0, 0);
	return self;
}

void MGLAttribute_Invalidate(MGLAttribute * attribute) {

	#ifdef MGL_VERBOSE
	printf("MGLAttribute_Invalidate %p\n", attribute);
	#endif

	Py_DECREF(attribute->name);

	attribute->ob_base.ob_type = &MGLInvalidObject_Type;
	attribute->initial_type = &MGLAttribute_Type;

	Py_DECREF(attribute);
}

void MGLAttribute_Complete(MGLAttribute * self) {
	switch (self->type) {
		case GL_INT:
			self->dimension = 1;

			self->scalar_type = GL_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 1;
			self->row_size = 4;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'i';
			break;

		case GL_INT_VEC2:
			self->dimension = 2;

			self->scalar_type = GL_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'i';
			break;

		case GL_INT_VEC3:
			self->dimension = 3;

			self->scalar_type = GL_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'i';
			break;

		case GL_INT_VEC4:
			self->dimension = 4;

			self->scalar_type = GL_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'i';
			break;

		case GL_UNSIGNED_INT:
			self->dimension = 1;

			self->scalar_type = GL_UNSIGNED_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 1;
			self->row_size = 4;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'I';
			break;

		case GL_UNSIGNED_INT_VEC2:
			self->dimension = 2;

			self->scalar_type = GL_UNSIGNED_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'I';
			break;

		case GL_UNSIGNED_INT_VEC3:
			self->dimension = 3;

			self->scalar_type = GL_UNSIGNED_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'I';
			break;

		case GL_UNSIGNED_INT_VEC4:
			self->dimension = 4;

			self->scalar_type = GL_UNSIGNED_INT;

			self->rows_length = self->array_length * 1;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribIPointer;

			self->normalizable = false;
			self->shape = 'I';
			break;

		case GL_FLOAT:
			self->dimension = 1;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 1;
			self->row_length = 1;
			self->row_size = 4;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_VEC2:
			self->dimension = 2;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 1;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_VEC3:
			self->dimension = 3;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 1;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_VEC4:
			self->dimension = 4;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 1;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_DOUBLE:
			self->dimension = 1;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 1;
			self->row_length = 1;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_VEC2:
			self->dimension = 2;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 1;
			self->row_length = 2;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_VEC3:
			self->dimension = 3;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 1;
			self->row_length = 3;
			self->row_size = 24;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_VEC4:
			self->dimension = 4;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 1;
			self->row_length = 4;
			self->row_size = 32;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_FLOAT_MAT2:
			self->dimension = 4;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 2;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT2x3:
			self->dimension = 6;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 2;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT2x4:
			self->dimension = 8;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 2;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT3x2:
			self->dimension = 6;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 3;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT3:
			self->dimension = 9;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 3;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT3x4:
			self->dimension = 12;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 3;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT4x2:
			self->dimension = 8;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 4;
			self->row_length = 2;
			self->row_size = 8;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT4x3:
			self->dimension = 12;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 4;
			self->row_length = 3;
			self->row_size = 12;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_FLOAT_MAT4:
			self->dimension = 16;

			self->scalar_type = GL_FLOAT;

			self->rows_length = self->array_length * 4;
			self->row_length = 4;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribPointer;

			self->normalizable = true;
			self->shape = 'f';
			break;

		case GL_DOUBLE_MAT2:
			self->dimension = 4;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 2;
			self->row_length = 2;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT2x3:
			self->dimension = 6;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 2;
			self->row_length = 3;
			self->row_size = 24;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT2x4:
			self->dimension = 8;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 2;
			self->row_length = 4;
			self->row_size = 32;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT3x2:
			self->dimension = 6;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 3;
			self->row_length = 2;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT3:
			self->dimension = 9;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 3;
			self->row_length = 3;
			self->row_size = 24;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT3x4:
			self->dimension = 12;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 3;
			self->row_length = 4;
			self->row_size = 32;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT4x2:
			self->dimension = 8;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 4;
			self->row_length = 2;
			self->row_size = 16;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT4x3:
			self->dimension = 12;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 4;
			self->row_length = 3;
			self->row_size = 24;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		case GL_DOUBLE_MAT4:
			self->dimension = 16;

			self->scalar_type = GL_DOUBLE;

			self->rows_length = self->array_length * 4;
			self->row_length = 4;
			self->row_size = 32;

			self->gl_attrib_ptr_proc = (void *)self->program->context->gl.VertexAttribLPointer;

			self->normalizable = false;
			self->shape = 'd';
			break;

		default:
			self->gl_attrib_ptr_proc = 0; // TODO:
			break;
	}
}
