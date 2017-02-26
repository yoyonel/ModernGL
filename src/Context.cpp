#include "Context.hpp"

#include "Buffer.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Program.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"
#include "EnableFlag.hpp"

#include "BufferFormat.hpp"

MGLContext * MGLContext_New() {
	MGLContext * self = (MGLContext *)MGLContext_Type.tp_alloc(&MGLContext_Type, 0);
	return self;
}

void MGLContext_Initialize(MGLContext * self) {
	self->gl.load();

	self->gl.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	self->gl.Enable(GL_PRIMITIVE_RESTART_FIXED_INDEX);
	self->gl.Enable(GL_PRIMITIVE_RESTART);
	self->gl.PrimitiveRestartIndex(-1);
}

PyObject * MGLContext_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLContext * self = (MGLContext *)type->tp_alloc(type, 0);

	if (self) {
	}

	return (PyObject *)self;
}

void MGLContext_tp_dealloc(MGLContext * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

int MGLContext_tp_init(MGLContext * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLContext_tp_str(MGLContext * self) {
	return PyUnicode_FromFormat("<ModernGL.Context>");
}

PyObject * MGLContext_make_current(MGLContext * self) {
	if (!oglMakeCurrent(self->dc_handle, self->rc_handle)) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	Py_RETURN_NONE;
}

const char * MGLContext_make_current_doc = R"(
)";

PyObject * MGLContext_clear(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"r", "g", "b", "a", 0};

	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|BBBB",
		(char **)kwlist,
		&r,
		&g,
		&b,
		&a
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	GLMethods & gl = self->gl;

	const float c = 1.0f / 255.0f;
	gl.ClearColor(r * c, g * c, b * c, a * c);
	gl.Clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	Py_RETURN_NONE;
}

const char * MGLContext_clear_doc = R"(
)";

PyObject * MGLContext_enable(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"flags", 0};

	MGLEnableFlag * flags;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O!",
		(char **)kwlist,
		&MGLEnableFlag_Type,
		&flags
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	self->gl.Enable(flags->flag);

	Py_RETURN_NONE;
}

const char * MGLContext_enable_doc = R"(
)";

PyObject * MGLContext_disable(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"flags", 0};

	MGLEnableFlag * flags;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O!",
		(char **)kwlist,
		&MGLEnableFlag_Type,
		&flags
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	self->gl.Disable(flags->flag);

	Py_RETURN_NONE;
}

const char * MGLContext_disable_doc = R"(
)";

PyObject * MGLContext_finish(MGLContext * self) {
	self->gl.Finish();
	Py_RETURN_NONE;
}

const char * MGLContext_finish_doc = R"(
)";

PyObject * MGLContext_info(MGLContext * self) {
	return 0;
}

const char * MGLContext_info_doc = R"(
)";

PyObject * MGLContext_line_width(MGLContext * self) {
	return 0;
}

const char * MGLContext_line_width_doc = R"(
)";

PyObject * MGLContext_point_size(MGLContext * self) {
	return 0;
}

const char * MGLContext_point_size_doc = R"(
)";

PyObject * MGLContext_copy_buffer(MGLContext * self) {
	return 0;
}

const char * MGLContext_copy_buffer_doc = R"(
)";

PyObject * MGLContext_viewport(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"value", 0};

	int x;
	int y;
	int width;
	int height;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|i",
		(char **)kwlist,
		&x,
		&y,
		&width,
		&height
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	self->gl.Viewport(x, y, width, height);
	Py_RETURN_NONE;
}

const char * MGLContext_viewport_doc = R"(
)";

MGLBuffer * MGLContext_Buffer(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"data", "reserve", "dynamic", 0};

	PyObject * data = Py_None;
	int reserve = 0;
	int dynamic = false;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|O$Ip",
		(char **)kwlist,
		&data,
		&reserve,
		&dynamic
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if ((data != Py_None && reserve) || (data == Py_None && !reserve)) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO: incref self to avoid GC

	Py_buffer buffer_view;

	if (data != Py_None) {
		int get_buffer = PyObject_GetBuffer(data, &buffer_view, PyBUF_SIMPLE);
		if (get_buffer < 0) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}
	} else {
		buffer_view.len = reserve;
		buffer_view.buf = 0;
	}

	if (!buffer_view.len) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	MGLBuffer * buffer = MGLBuffer_New();

	buffer->size = buffer_view.len;
	buffer->dynamic = dynamic ? true : false;

	buffer->obj = 0;

	GLMethods & gl = self->gl;

	// printf("%p\n", gl.GenBuffers);

	gl.GenBuffers(1, (GLuint *)&buffer->obj);
	gl.BindBuffer(GL_ARRAY_BUFFER, buffer->obj);
	gl.BufferData(GL_ARRAY_BUFFER, buffer->size, buffer_view.buf, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

	Py_INCREF((PyObject *)self);
	buffer->ctx = self;

	if (data != Py_None) {
		PyBuffer_Release(&buffer_view);
	}

	return buffer;
}

const char * MGLContext_Buffer_doc = R"(
)";

MGLTexture * MGLContext_Texture(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"size", "components", "data", "floats", 0};

	int width;
	int height;

	int components = 3;

	PyObject * data = Py_None;

	int floats = false;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"(II)|IO$p",
		(char **)kwlist,
		&width,
		&height,
		&components,
		&data,
		&floats
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (components < 1 || components > 4) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	int expected_size = floats ? (width * height * components * 4) : (height * ((width * components + 3) & ~3));

	Py_buffer buffer_view;

	if (data != Py_None) {
		PyObject_GetBuffer(data, &buffer_view, PyBUF_SIMPLE);
	} else {
		buffer_view.len = expected_size;
		buffer_view.buf = 0;
	}

	if (buffer_view.len != expected_size) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		if (data != Py_None) {
			PyBuffer_Release(&buffer_view);
		}
		return 0;
	}

	const int formats[] = {0, GL_RED, GL_RG, GL_RGB, GL_RGBA};

	int pixel_type = floats ? GL_FLOAT : GL_UNSIGNED_BYTE;
	int format = formats[components];

	GLMethods & gl = self->gl;

	gl.ActiveTexture(GL_TEXTURE0 + self->default_texture_unit);

	MGLTexture * texture = MGLTexture_New();

	gl.GenTextures(1, (GLuint *)&texture->obj);
	gl.BindTexture(GL_TEXTURE_2D, texture->obj);
	gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gl.TexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixel_type, buffer_view.buf);

	if (data != Py_None) {
		PyBuffer_Release(&buffer_view);
	}

	texture->width = width;
	texture->height = height;
	texture->components = components;
	texture->floats = floats ? true : false; // TODO:
	texture->depth = false;

	Py_INCREF((PyObject *)self);
	texture->ctx = self;

	return texture;
}

const char * MGLContext_Texture_doc = R"(
)";

MGLTexture * MGLContext_DepthTexture(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"size", "data", 0};

	int width;
	int height;

	PyObject * data = Py_None;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"(II)|O",
		(char **)kwlist,
		&width,
		&height,
		&data
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	int expected_size = width * height * 4;

	Py_buffer buffer_view;

	if (data != Py_None) {
		PyObject_GetBuffer(data, &buffer_view, PyBUF_SIMPLE);
	} else {
		buffer_view.len = expected_size;
		buffer_view.buf = 0;
	}

	if (buffer_view.len != expected_size) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		if (data != Py_None) {
			PyBuffer_Release(&buffer_view);
		}
		return 0;
	}

	int pixel_type = GL_FLOAT;
	int format = GL_RED;

	GLMethods & gl = self->gl;

	gl.ActiveTexture(GL_TEXTURE0 + self->default_texture_unit);

	MGLTexture * texture = MGLTexture_New();

	gl.GenTextures(1, (GLuint *)&texture->obj);
	gl.BindTexture(GL_TEXTURE_2D, texture->obj);
	gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	gl.TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	gl.TexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, pixel_type, buffer_view.buf);

	if (data != Py_None) {
		PyBuffer_Release(&buffer_view);
	}

	texture->width = width;
	texture->height = height;
	texture->components = 1;
	texture->floats = true;
	texture->depth = true;

	Py_INCREF((PyObject *)self);
	texture->ctx = self;

	return texture;
}

const char * MGLContext_DepthTexture_doc = R"(
)";

MGLVertexArray * MGLContext_VertexArray(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"program", "content", "index_buffer", 0};

	MGLProgram * program;
	PyObject * content;
	MGLBuffer * index_buffer = (MGLBuffer *)Py_None;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O!O|O!",
		(char **)kwlist,
		&MGLProgram_Type,
		&program,
		&content,
		&MGLBuffer_Type,
		&index_buffer
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * content_iterator = PyObject_GetIter(content);

	if (!content_iterator) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * vertex_array_content = PyList_New(0);

	while (PyObject * item = PyIter_Next(content_iterator)) {
		if (!PyTuple_Check(item)) {
			Py_DECREF(item);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		int size = PyTuple_GET_SIZE(item);

		if (size != 3) {
			Py_DECREF(item);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		PyObject * buffer = PyTuple_GET_ITEM(item, 0);
		PyObject * format = PyTuple_GET_ITEM(item, 1);
		PyObject * attributes = PyTuple_GET_ITEM(item, 2);

		PyObject * attributes_iterator = PyObject_GetIter(attributes);

		if (!attributes_iterator) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		PyObject * content_attributes = PyList_New(0);

		while (PyObject * item = PyIter_Next(attributes_iterator)) {
			if (!PyUnicode_Check(item)) {
				Py_DECREF(item);
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				return 0;
			}

			PyList_Append(content_attributes, item);
		}

		PyObject * tuple = PyTuple_New(3);

		Py_INCREF(buffer);
		Py_INCREF(format);

		PyTuple_SET_ITEM(tuple, 0, buffer);
		PyTuple_SET_ITEM(tuple, 1, format);
		PyTuple_SET_ITEM(tuple, 2, content_attributes);

		PyList_Append(vertex_array_content, tuple);
	}

	if (PyErr_Occurred()) {
		return 0;
	}

	GLMethods & gl = self->gl;

	MGLVertexArray * array = MGLVertexArray_New();

	Py_INCREF(program);
	array->program = program;

	array->obj = 0;
	gl.GenVertexArrays(1, (GLuint *)&array->obj);
	gl.BindVertexArray(array->obj);

	if (index_buffer != (MGLBuffer *)Py_None) {
		array->indexed = true;
		array->num_vertices = index_buffer->size / 4;
		gl.BindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->obj);
	} else {
		array->indexed = false;
		array->num_vertices = -1;
	}

	int vertex_array_content_len = PyList_GET_SIZE(vertex_array_content);
	for (int i = 0; i < vertex_array_content_len; ++i) {
		PyObject * item = PyList_GET_ITEM(vertex_array_content, i);

		MGLBuffer * buffer = (MGLBuffer *)PyTuple_GET_ITEM(item, 0);
		char * format = PyUnicode_AsUTF8(PyTuple_GET_ITEM(item, 1));
		PyObject * attributes = PyTuple_GET_ITEM(item, 2);

		// printf("format: %s\n", format);

		FormatIterator it = FormatIterator(format);
		FormatInfo format_info = it.info();

		if (!format_info.valid) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		int buf_vertices = buffer->size / format_info.size;
		if (!format_info.per_instance && !array->indexed && (!i || array->num_vertices > buf_vertices)) {
			array->num_vertices = buf_vertices;
		}

		int attributes_len = PyList_GET_SIZE(attributes);

		gl.BindBuffer(GL_ARRAY_BUFFER, buffer->obj);

		char * ptr = 0;

		for (int j = 0; j < attributes_len; ++j) {
			char * attribute = PyUnicode_AsUTF8(PyList_GET_ITEM(attributes, j));

			int location = gl.GetAttribLocation(program->obj, attribute);

			if (location < 0) {
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				return 0;
			}

			FormatNode * node = it.next();

			if (node->type == GL_INT) {
				gl.VertexAttribIPointer(location, node->count, node->type, format_info.size, ptr);
			} else {
				gl.VertexAttribPointer(location, node->count, node->type, false, format_info.size, ptr);
			}

			if (format_info.per_instance) {
				gl.VertexAttribDivisor(location, 1);
			}

			gl.EnableVertexAttribArray(location);

			ptr += node->count * node->size;
		}
	}

	Py_INCREF((PyObject *)self);
	array->ctx = self;

	return array;
}

const char * MGLContext_VertexArray_doc = R"(
)";

MGLVertexArray * MGLContext_SimpleVertexArray(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"program", "content", "index_buffer", 0};

	MGLProgram * program;
	PyObject * buffer;
	PyObject * format;
	PyObject * attributes;
	MGLBuffer * index_buffer = (MGLBuffer *)Py_None;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O!O!OO|O!",
		(char **)kwlist,
		&MGLProgram_Type,
		&program,
		&MGLBuffer_Type,
		&buffer,
		&format,
		&attributes,
		&MGLBuffer_Type,
		&index_buffer
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	// TODO:

	return 0;
}

const char * MGLContext_SimpleVertexArray_doc = R"(
)";

MGLProgram * MGLContext_Program(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"shaders", "varyings", 0};

	PyObject * shaders;
	PyObject * varyings = Py_None;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O|O",
		(char **)kwlist,
		&shaders,
		&varyings
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * program_varyings = PyList_New(0);

	if (varyings != Py_None) {
		PyObject * varyings_iterator = PyObject_GetIter(varyings);

		if (!varyings_iterator) {
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			return 0;
		}

		while (PyObject * item = PyIter_Next(varyings_iterator)) {
			if (PyType_IsSubtype(Py_TYPE(item), &PyUnicode_Type)) {
				PyList_Append(program_varyings, item);

			} else {
				Py_DECREF(item);
				PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
			}
		}

		if (PyErr_Occurred()) {
			Py_DECREF(program_varyings);
			return 0;
		}
	}

	PyObject * shaders_iterator = PyObject_GetIter(shaders);

	if (!shaders_iterator) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * program_shaders = PyList_New(0);

	// check duplicate types

	while (PyObject * item = PyIter_Next(shaders_iterator)) {
		// if (PyType_IsSubtype(Py_TYPE(item), &MGLShader_Type)) {
		if (Py_TYPE(item) == &MGLShader_Type) {
			MGLShader * shader = (MGLShader *)item;

			// shader->subtype

			// shader ctx == program ctx

			PyList_Append(program_shaders, item);

		} else {
			Py_DECREF(item);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		}
	}

	if (PyErr_Occurred()) {
		Py_DECREF(program_varyings);
		Py_DECREF(program_shaders);
		return 0;
	}

	GLMethods & gl = self->gl;

	MGLProgram * program = MGLProgram_New();

	program->shaders = program_shaders;
	program->varyings = program_varyings;

	Py_INCREF((PyObject *)self);
	program->ctx = self;

	MGLProgram_Compile(program);

	if (PyErr_Occurred()) {
		Py_DECREF(program);
		return 0;
	}

	return program;
}

const char * MGLContext_Program_doc = R"(
)";

template <int ShaderType>
MGLShader * MGLContext_Shader(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"source", 0};

	PyObject * source;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O",
		(char **)kwlist,
		&source
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	if (!PyUnicode_Check(source)) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	MGLShader * shader = MGLShader_New();

	shader->shader_type = ShaderType;

	Py_INCREF(source);
	shader->source = source;

	Py_INCREF((PyObject *)self);
	shader->ctx = self;

	MGLShader_Compile(shader);

	if (PyErr_Occurred()) {
		Py_DECREF(shader);
		return 0;
	}

	return shader;
}

const char * MGLContext_Shader_doc = R"(
)";

MGLFramebuffer * MGLContext_Framebuffer(MGLContext * self, PyObject * args, PyObject * kwargs) {
	static const char * kwlist[] = {"attachments", 0};

	PyObject * attachments;

	int args_ok = PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"O",
		(char **)kwlist,
		&attachments
	);

	if (!args_ok) {
		// PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	PyObject * iterator = PyObject_GetIter(attachments);

	if (!iterator) {
		PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		return 0;
	}

	int num_color_attachments = 0;
	PyObject * color_attachments = PyList_New(0);
	PyObject * depth_attachment = 0;

	while (PyObject * item = PyIter_Next(iterator)) {
		if (Py_TYPE(item) == &MGLTexture_Type) {
			MGLTexture * texture = (MGLTexture *)item;

			if (texture->depth) {

				if (depth_attachment) {
					Py_DECREF(depth_attachment);
					PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
				}

				depth_attachment = item;

			} else {
				PyList_Append(color_attachments, item);
				num_color_attachments += 1;
			}

		} else {
			Py_DECREF(item);
			PyErr_Format(PyExc_Exception, "Unknown error in %s (%s:%d)", __FUNCTION__, __FILE__, __LINE__);
		}
	}

	if (PyErr_Occurred()) {
		return 0;
	}

	GLMethods & gl = self->gl;

	// int defaultFramebuffer = 0;
	// gl.GetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, (GLint *)&defaultFramebuffer);

	MGLFramebuffer * framebuffer = MGLFramebuffer_New();

	gl.GenFramebuffers(1, (GLuint *)&framebuffer->obj);
	gl.BindFramebuffer(GL_FRAMEBUFFER, framebuffer->obj);

	for (int i = 0; i < num_color_attachments; ++i) {
		PyObject * item = PyList_GET_ITEM(color_attachments, i);
		if (Py_TYPE(item) == &MGLTexture_Type) {
			MGLTexture * texture = (MGLTexture *)item;

			gl.FramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_COLOR_ATTACHMENT0 + i,
				GL_TEXTURE_2D,
				texture->obj,
				0
			);
		} else {
			// Renderbuffer
		}
	}

	if (depth_attachment) {
		if (Py_TYPE(depth_attachment) == &MGLTexture_Type) {
			MGLTexture * texture = (MGLTexture *)depth_attachment;
			gl.FramebufferTexture2D(
				GL_FRAMEBUFFER,
				GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D,
				texture->obj,
				0
			);
		} else {
			// Renderbuffer
		}
	}

	framebuffer->color_attachments = color_attachments;
	framebuffer->depth_attachment = depth_attachment;

	Py_INCREF((PyObject *)self);
	framebuffer->ctx = self;

	// Validate
	// Bind old framebuffer

	return framebuffer;
}

const char * MGLContext_Framebuffer_doc = R"(
)";

PyMethodDef MGLContext_tp_methods[] = {
	{"make_current", (PyCFunction)MGLContext_make_current, METH_NOARGS, MGLContext_make_current_doc},

	{"clear", (PyCFunction)MGLContext_clear, METH_VARARGS | METH_KEYWORDS, MGLContext_clear_doc},
	{"enable", (PyCFunction)MGLContext_enable, METH_VARARGS | METH_KEYWORDS, MGLContext_enable_doc},
	{"disable", (PyCFunction)MGLContext_disable, METH_VARARGS | METH_KEYWORDS, MGLContext_disable_doc},
	{"finish", (PyCFunction)MGLContext_finish, METH_NOARGS, MGLContext_finish_doc},
	{"viewport", (PyCFunction)MGLContext_viewport, METH_VARARGS | METH_KEYWORDS, MGLContext_viewport_doc},

	{"Buffer", (PyCFunction)MGLContext_Buffer, METH_VARARGS | METH_KEYWORDS, MGLContext_Buffer_doc},
	{"Texture", (PyCFunction)MGLContext_Texture, METH_VARARGS | METH_KEYWORDS, MGLContext_Texture_doc},
	{"DepthTexture", (PyCFunction)MGLContext_DepthTexture, METH_VARARGS | METH_KEYWORDS, MGLContext_DepthTexture_doc},
	{"VertexArray", (PyCFunction)MGLContext_VertexArray, METH_VARARGS | METH_KEYWORDS, MGLContext_VertexArray_doc},
	{"Program", (PyCFunction)MGLContext_Program, METH_VARARGS | METH_KEYWORDS, MGLContext_Program_doc},
	{"VertexShader", (PyCFunction)MGLContext_Shader<GL_VERTEX_SHADER>, METH_VARARGS | METH_KEYWORDS, MGLContext_Shader_doc},
	{"FragmentShader", (PyCFunction)MGLContext_Shader<GL_FRAGMENT_SHADER>, METH_VARARGS | METH_KEYWORDS, MGLContext_Shader_doc},
	{"GeometryShader", (PyCFunction)MGLContext_Shader<GL_GEOMETRY_SHADER>, METH_VARARGS | METH_KEYWORDS, MGLContext_Shader_doc},
	{"TessEvaluationShader", (PyCFunction)MGLContext_Shader<GL_TESS_EVALUATION_SHADER>, METH_VARARGS | METH_KEYWORDS, MGLContext_Shader_doc},
	{"TessControlShader", (PyCFunction)MGLContext_Shader<GL_TESS_CONTROL_SHADER>, METH_VARARGS | METH_KEYWORDS, MGLContext_Shader_doc},
	{"Framebuffer", (PyCFunction)MGLContext_Framebuffer, METH_VARARGS | METH_KEYWORDS, MGLContext_Framebuffer_doc},

	{0},
};

PyGetSetDef MGLContext_tp_getseters[] = {
	{(char *)"line_width", 0, 0, 0, 0},
	{(char *)"point_size", 0, 0, 0, 0},
	{(char *)"viewport", 0, 0, 0, 0},
	{(char *)"vsync", 0, 0, 0, 0},
	{0},
};

const char * MGLContext_tp_doc = R"(
)";

PyTypeObject MGLContext_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Context",                                     // tp_name
	sizeof(MGLContext),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLContext_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLContext_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	0,                                                      // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLContext_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLContext_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLContext_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLContext_tp_getseters,                                // tp_getset
	&MGLObject_Type,                                        // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLContext_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLContext_tp_new,                                      // tp_new
};
