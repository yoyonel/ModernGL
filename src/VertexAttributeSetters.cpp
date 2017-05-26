#include "VertexArrayAttribute.hpp"

#include "Error.hpp"

int MGLVertexArrayAttribute_invalid_setter(MGLVertexArrayAttribute * self, PyObject * value) {
	MGLError_Set("cannot detect uniform type");
	return -1;
}

int MGLVertexArrayAttribute_vec2_value_setter(MGLVertexArrayAttribute * self, PyObject * value) {
	float c_values[2];

	if (Py_TYPE(value) != &PyTuple_Type) {
		MGLError_Set("the value must be a tuple not %s", Py_TYPE(value));
		return -1;
	}

	int size = (int)PyTuple_GET_SIZE(value);

	if (size != 2) {
		MGLError_Set("the value must be a tuple of size 2 not %d", size);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		MGLError_Set("cannot convert value to float");
		return -1;
	}

	self->gl->BindVertexArray(self->vertex_array_obj);
	self->gl->VertexAttrib2fv(self->location, c_values);
	printf("location: %d error: %d\n", self->location, self->gl->GetError());

	// A vertex shader can read an attribute that is not currently enabled (via glEnableVertexAttribArray).
	// The value that it gets is defined by special context state, which is *not* part of the VAO.
	// Because the attribute is defined by context state, it is constant over the course of a single draw call.
	// Each attribute index has a separate value.

	// Warning: Every time you issue a drawing command with an array enabled, the corresponding context attribute
	// values become undefined. So if you want to, for example, use the non-array attribute index 3 after previously
	// using an array in index 3, you need to repeatedly reset it to a known value.

	return 0;
}
