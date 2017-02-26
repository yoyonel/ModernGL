#include "Uniform.hpp"

int MGLUniform_invalid_setter(MGLUniform * self, PyObject * value) {
	PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
	return -1;
}

int MGLUniform_bool_value_setter(MGLUniform * self, PyObject * value) {
	int c_value;

	if (value == Py_True) {
		c_value = 1;
	} else if (value == Py_False) {
		c_value = 0;
	} else {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_bvec2_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[2];

	if (PyTuple_Size(value) != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		PyObject * v = PyTuple_GET_ITEM(value, i);

		if (v == Py_True) {
			c_values[i] = 1;
		} else if (v == Py_False) {
			c_values[i] = 0;
		} else {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return -1;
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_bvec3_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[3];

	if (PyTuple_Size(value) != 3) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 3; ++i) {
		PyObject * v = PyTuple_GET_ITEM(value, i);

		if (v == Py_True) {
			c_values[i] = 1;
		} else if (v == Py_False) {
			c_values[i] = 0;
		} else {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return -1;
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_bvec4_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		PyObject * v = PyTuple_GET_ITEM(value, i);

		if (v == Py_True) {
			c_values[i] = 1;
		} else if (v == Py_False) {
			c_values[i] = 0;
		} else {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return -1;
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_int_value_setter(MGLUniform * self, PyObject * value) {
	int c_value = PyLong_AsLong(value);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_ivec2_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[2];

	if (PyTuple_Size(value) != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		c_values[i] = PyLong_AsLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_ivec3_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[3];

	if (PyTuple_Size(value) != 3) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 3; ++i) {
		c_values[i] = PyLong_AsLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_ivec4_value_setter(MGLUniform * self, PyObject * value) {
	int c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = PyLong_AsLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_uint_value_setter(MGLUniform * self, PyObject * value) {
	unsigned c_value = PyLong_AsUnsignedLong(value);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_uvec2_value_setter(MGLUniform * self, PyObject * value) {
	unsigned c_values[2];

	if (PyTuple_Size(value) != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		c_values[i] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_uvec3_value_setter(MGLUniform * self, PyObject * value) {
	unsigned c_values[3];

	if (PyTuple_Size(value) != 3) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 3; ++i) {
		c_values[i] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_uvec4_value_setter(MGLUniform * self, PyObject * value) {
	unsigned c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_float_value_setter(MGLUniform * self, PyObject * value) {
	float c_value = (float)PyFloat_AsDouble(value);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_vec2_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[2];

	if (PyTuple_Size(value) != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_vec3_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[3];

	if (PyTuple_Size(value) != 3) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 3; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_vec4_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_double_value_setter(MGLUniform * self, PyObject * value) {
	double c_value = PyFloat_AsDouble(value);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_dvec2_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[2];

	if (PyTuple_Size(value) != 2) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 2; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_dvec3_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[3];

	if (PyTuple_Size(value) != 3) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 3; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_dvec4_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, c_values);

	return 0;
}

int MGLUniform_sampler_value_setter(MGLUniform * self, PyObject * value) {
	int c_value = PyLong_AsLong(value);

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, &c_value);

	return 0;
}

int MGLUniform_float_matrix_2x2_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_2x3_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[6];

	if (PyTuple_Size(value) != 6) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 6; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_2x4_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[8];

	if (PyTuple_Size(value) != 8) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 8; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_3x2_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[6];

	if (PyTuple_Size(value) != 6) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 6; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_3x3_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[9];

	if (PyTuple_Size(value) != 9) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 9; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_3x4_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[12];

	if (PyTuple_Size(value) != 12) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 12; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_4x2_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[8];

	if (PyTuple_Size(value) != 8) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 8; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_4x3_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[12];

	if (PyTuple_Size(value) != 12) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 12; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_float_matrix_4x4_value_setter(MGLUniform * self, PyObject * value) {
	float c_values[16];

	if (PyTuple_Size(value) != 16) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 16; ++i) {
		c_values[i] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_2x2_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[4];

	if (PyTuple_Size(value) != 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 4; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_2x3_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[6];

	if (PyTuple_Size(value) != 6) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 6; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_2x4_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[8];

	if (PyTuple_Size(value) != 8) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 8; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_3x2_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[6];

	if (PyTuple_Size(value) != 6) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 6; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_3x3_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[9];

	if (PyTuple_Size(value) != 9) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 9; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_3x4_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[12];

	if (PyTuple_Size(value) != 12) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 12; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_4x2_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[8];

	if (PyTuple_Size(value) != 8) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 8; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_4x3_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[12];

	if (PyTuple_Size(value) != 12) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 12; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_double_matrix_4x4_value_setter(MGLUniform * self, PyObject * value) {
	double c_values[16];

	if (PyTuple_Size(value) != 16) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	for (int i = 0; i < 16; ++i) {
		c_values[i] = PyFloat_AsDouble(PyTuple_GET_ITEM(value, i));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, 1, false, c_values);

	return 0;
}

int MGLUniform_bool_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int * c_values = new int[size];

	for (int k = 0; k < size; ++k) {
		PyObject * v = PyList_GET_ITEM(value, k);

		if (v == Py_True) {
			c_values[k] = 1;
		} else if (v == Py_False) {
			c_values[k] = 0;
		} else {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_bvec2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 2];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 2; ++i) {
			PyObject * v = PyTuple_GET_ITEM(tuple, i);

			if (v == Py_True) {
				c_values[cnt++] = 1;
			} else if (v == Py_False) {
				c_values[cnt++] = 0;
			} else {
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				delete[] c_values;
				return -1;
			}
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 2, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_bvec3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 3];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 3) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 3; ++i) {
			PyObject * v = PyTuple_GET_ITEM(tuple, i);

			if (v == Py_True) {
				c_values[cnt++] = 1;
			} else if (v == Py_False) {
				c_values[cnt++] = 0;
			} else {
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				delete[] c_values;
				return -1;
			}
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 3, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_bvec4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			PyObject * v = PyTuple_GET_ITEM(tuple, i);

			if (v == Py_True) {
				c_values[cnt++] = 1;
			} else if (v == Py_False) {
				c_values[cnt++] = 0;
			} else {
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				delete[] c_values;
				return -1;
			}
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 4, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_int_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int * c_values = new int[size];

	for (int k = 0; k < size; ++k) {
		c_values[k] = PyLong_AsLong(PyList_GET_ITEM(value, k));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		delete[] c_values;
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_ivec2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 2];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 2; ++i) {
			c_values[cnt++] = PyLong_AsLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 2, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_ivec3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 3];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 3) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 3; ++i) {
			c_values[cnt++] = PyLong_AsLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 3, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_ivec4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	int * c_values = new int[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = PyLong_AsLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 4, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_uint_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	unsigned * c_values = new unsigned[size];

	for (int k = 0; k < size; ++k) {
		c_values[k] = PyLong_AsUnsignedLong(PyList_GET_ITEM(value, k));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		delete[] c_values;
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_uvec2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	unsigned * c_values = new unsigned[size * 2];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 2; ++i) {
			c_values[cnt++] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 2, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_uvec3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	unsigned * c_values = new unsigned[size * 3];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 3) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 3; ++i) {
			c_values[cnt++] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 3, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_uvec4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	unsigned * c_values = new unsigned[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = PyLong_AsUnsignedLong(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4uiv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 4, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	float * c_values = new float[size];

	for (int k = 0; k < size; ++k) {
		c_values[k] = (float)PyFloat_AsDouble(PyList_GET_ITEM(value, k));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		delete[] c_values;
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_vec2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 2];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 2; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 2, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_vec3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 3];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 3) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 3; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 3, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_vec4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 4, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	double * c_values = new double[size];

	for (int k = 0; k < size; ++k) {
		c_values[k] = PyFloat_AsDouble(PyList_GET_ITEM(value, k));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		delete[] c_values;
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_dvec2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 2];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 2) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 2; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 2, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_dvec3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 3];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 3) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 3; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 3, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_dvec4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size * 4, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_sampler_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int * c_values = new int[size];

	for (int k = 0; k < size; ++k) {
		c_values[k] = PyLong_AsLong(PyList_GET_ITEM(value, k));
	}

	if (PyErr_Occurred()) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		delete[] c_values;
		return -1;
	}

	((gl_uniform_vector_writer_proc/*glProgramUniform1iv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_2x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_2x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 6];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 6) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 6; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_2x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 8];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 8) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 8; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_3x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 6];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 6) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 6; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_3x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 9];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 9) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 9; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_3x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 12];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 12) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 12; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_4x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 8];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 8) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 8; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x2fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_4x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 12];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 12) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 12; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x3fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_float_matrix_4x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	float * c_values = new float[size * 16];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 16) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 16; ++i) {
			c_values[cnt++] = (float)PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4fv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_2x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 4];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 4) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 4; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_2x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 6];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 6) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 6; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_2x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 8];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 8) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 8; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix2x4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_3x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 6];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 6) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 6; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_3x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 9];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 9) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 9; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_3x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 12];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 12) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 12; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix3x4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_4x2_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 8];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 8) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 8; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x2dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_4x3_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 12];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 12) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 12; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4x3dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}

int MGLUniform_double_matrix_4x4_array_value_setter(MGLUniform * self, PyObject * value) {
	int size = PyList_Size(value);

	if (PyErr_Occurred() || size != self->array_len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return -1;
	}

	int cnt = 0;
	double * c_values = new double[size * 16];

	for (int k = 0; k < size; ++k) {
		PyObject * tuple = PyList_GET_ITEM(value, k);

		if (PyTuple_Size(tuple) != 16) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			delete[] c_values;
			return -1;
		}

		for (int i = 0; i < 16; ++i) {
			c_values[cnt++] = PyFloat_AsDouble(PyTuple_GET_ITEM(tuple, i));
		}
	}

	((gl_uniform_matrix_writer_proc/*glProgramUniformMatrix4dv*/)self->gl_value_writer_proc)(self->program->obj, self->location, size, false, c_values);

	delete[] c_values;
	return 0;
}
