#include "ModernGL.hpp"

#include "OpenGL.hpp"

PyObject * NewVertexArray(PyObject * self, PyObject * args) {
	const char * format;
	PyObject * lst;

	IndexBuffer * no_ibo = (IndexBuffer *)Py_None;
	IndexBuffer * ibo = no_ibo;

	if (!PyArg_ParseTuple(args, "sO|O:NewVertexArray", &format, &lst, &ibo)) {
		return 0;
	}

	int length = 0;
	while (format[length]) {
		if (length % 2 == 0) {
			if (format[length] < '1' || format[length] > '4') {
				PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is invalid.");
				return 0;
			}
		} else {
			if (format[length] != 'i' && format[length] != 'f') {
				PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is invalid.");
				return 0;
			}
		}
		++length;
	}

	if (!length || length % 2) {
		PyErr_SetString(ModuleError, "NewVertexArray() argument `format` is empty or invalid.");
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)lst, &PyList_Type)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)lst))->tp_name;
		PyErr_Format(PyExc_TypeError, "NewVertexArray() argument `pairs` must be list, not %s", got);
		return 0;
	}

	int vao = 0;
	OpenGL::glGenVertexArrays(1, (OpenGL::GLuint *)&vao);
	OpenGL::glBindVertexArray(vao);

	if (ibo != no_ibo) {
		if (!PyObject_TypeCheck((PyObject *)ibo, &IndexBufferType)) {
			OpenGL::glBindVertexArray(defaultVertexArray);
			OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao);
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)ibo))->tp_name;
			PyErr_Format(PyExc_TypeError, "NewVertexArray() argument `ibo` must be IndexBuffer, not %s", got);
			return 0;
		}

		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, ibo->ibo);
	}

	int stride = 0;
	for (int i = 0; format[i]; i += 2) {
		stride += (format[i] - '0') * 4;
	}

	char * ptr = 0;
	int count = (int)PyList_Size(lst);

	if (length / 2 != count) {
		PyErr_Format(ModuleError, "NewVertexArray() size of `format` is %d, length of `pairs` is %d", length / 2, count);
		return 0;
	}

	for (int i = 0; i < count; ++i) {
		PyObject * tuple = PyList_GET_ITEM(lst, i);

		if (!PyObject_TypeCheck((PyObject *)tuple, &PyTuple_Type)) {
			OpenGL::glBindVertexArray(defaultVertexArray);
			OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao);
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)tuple))->tp_name;
			PyErr_Format(PyExc_TypeError, "NewVertexArray() pairs[%d] must be tuple, not %s", i, got);
			return 0;
		}

		int size = (int)PyTuple_Size(tuple);
		if (size != 2) {
			OpenGL::glBindVertexArray(defaultVertexArray);
			OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao);
			PyErr_Format(ModuleError, "NewVertexArray() size of pairs[%d] must be 2.", i);
			return 0;
		}

		VertexBuffer * vbo = (VertexBuffer *)PyTuple_GET_ITEM(tuple, 0);

		if (!PyObject_TypeCheck((PyObject *)vbo, &VertexBufferType)) {
			OpenGL::glBindVertexArray(defaultVertexArray);
			OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao);
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vbo))->tp_name;
			PyErr_Format(PyExc_TypeError, "NewVertexArray() first element of pairs[%d] must be VertexBuffer, not %s", i, got);
			return 0;
		}

		AttributeLocation * location = (AttributeLocation *)PyTuple_GET_ITEM(tuple, 1);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			OpenGL::glBindVertexArray(defaultVertexArray);
			OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao);
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)location))->tp_name;
			PyErr_Format(PyExc_TypeError, "NewVertexArray() second element of pairs[%d] must be AttributeLocation, not %s", i, got);
			return 0;
		}

		OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vbo->vbo);
		int dimension = format[i * 2] - '0';
		switch (format[i * 2 + 1]) {
			case 'f':
				OpenGL::glVertexAttribPointer(location->location, dimension, OpenGL::GL_FLOAT, false, stride, ptr);
				break;
			case 'i':
				OpenGL::glVertexAttribPointer(location->location, dimension, OpenGL::GL_INT, false, stride, ptr);
				break;
		}
		OpenGL::glEnableVertexAttribArray(location->location);
		ptr += dimension * 4;
	}

	OpenGL::glBindVertexArray(defaultVertexArray);
	return CreateVertexArrayType(vao, ibo != no_ibo);
}

PyObject * DeleteVertexArray(PyObject * self, PyObject * args) {
	VertexArray * vao;

	if (!PyArg_ParseTuple(args, "O:DeleteVertexArray", &vao)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vao))->tp_name;
		PyErr_Format(PyExc_TypeError, "DeleteVertexArray() argument `vao` must be VertexArray, not %s", got);
		return 0;
	}

	OpenGL::glDeleteVertexArrays(1, (OpenGL::GLuint *)&vao->vao);
	Py_RETURN_NONE;
}

PyObject * EnableAttribute(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	AttributeLocation * location;

	static const char * kwlist[] = {"vao", "attribute", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:EnableAttribute", (char **)kwlist, &vao, &location)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vao))->tp_name;
		PyErr_Format(PyExc_TypeError, "EnableAttribute() argument `vao` must be VertexArray, not %s", got);
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)location))->tp_name;
		PyErr_Format(PyExc_TypeError, "EnableAttribute() argument `attribute` must be AttributeLocation, not %s", got);
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glEnableVertexAttribArray(location->location);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * DisableAttribute(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	AttributeLocation * location;

	static const char * kwlist[] = {"vao", "attribute", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:DisableAttribute", (char **)kwlist, &vao, &location)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vao))->tp_name;
		PyErr_Format(PyExc_TypeError, "DisableAttribute() argument `vao` must be VertexArray, not %s", got);
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)location))->tp_name;
		PyErr_Format(PyExc_TypeError, "DisableAttribute() argument `attribute` must be AttributeLocation, not %s", got);
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	OpenGL::glDisableVertexAttribArray(location->location);
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * EnableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attributes;

	static const char * kwlist[] = {"vao", "attributes", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:EnableAttributes", (char **)kwlist, &vao, &attributes)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vao))->tp_name;
		PyErr_Format(PyExc_TypeError, "EnableAttributes() argument `vao` must be VertexArray, not %s", got);
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)attributes, &PyList_Type)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)attributes))->tp_name;
		PyErr_Format(PyExc_TypeError, "EnableAttributes() argument `attributes` must be list, not %s", got);
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	int count = (int)PyList_Size(attributes);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * location = (AttributeLocation *)PyList_GET_ITEM(attributes, i);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)location))->tp_name;
			PyErr_Format(PyExc_TypeError, "EnableAttributes() attributes[%d] must be AttributeLocation, not %s", i, got);
			OpenGL::glBindVertexArray(defaultVertexArray);
			return 0;
		}

		OpenGL::glEnableVertexAttribArray(location->location);
	}

	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}

PyObject * DisableAttributes(PyObject * self, PyObject * args, PyObject * kwargs) {
	VertexArray * vao;
	PyObject * attributes;

	static const char * kwlist[] = {"vao", "attributes", 0};

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OO:DisableAttributes", (char **)kwlist, &vao, &attributes)) {
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)vao, &VertexArrayType)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)vao))->tp_name;
		PyErr_Format(PyExc_TypeError, "DisableAttributes() argument `vao` must be VertexArray, not %s", got);
		return 0;
	}

	if (!PyObject_TypeCheck((PyObject *)attributes, &PyList_Type)) {
		const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)attributes))->tp_name;
		PyErr_Format(PyExc_TypeError, "DisableAttributes() argument `attributes` must be list, not %s", got);
		return 0;
	}

	OpenGL::glBindVertexArray(vao->vao);
	int count = (int)PyList_Size(attributes);
	for (int i = 0; i < count; ++i) {
		AttributeLocation * location = (AttributeLocation *)PyList_GET_ITEM(attributes, i);

		if (!PyObject_TypeCheck((PyObject *)location, &AttributeLocationType)) {
			const char * got = ((PyTypeObject *)PyObject_Type((PyObject *)location))->tp_name;
			PyErr_Format(PyExc_TypeError, "DisableAttributes() attributes[%d] must be AttributeLocation, not %s", i, got);
			OpenGL::glBindVertexArray(defaultVertexArray);
			return 0;
		}

		OpenGL::glDisableVertexAttribArray(location->location);
	}
	OpenGL::glBindVertexArray(defaultVertexArray);
	Py_RETURN_NONE;
}
