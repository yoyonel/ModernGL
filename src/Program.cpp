#include "Program.hpp"

#include "Error.hpp"
#include "InvalidObject.hpp"
#include "Shader.hpp"
#include "Uniform.hpp"
#include "Attribute.hpp"
#include "Subroutine.hpp"
#include "Varying.hpp"

PyObject * MGLProgram_tp_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	MGLProgram * self = (MGLProgram *)type->tp_alloc(type, 0);

	#ifdef MGL_VERBOSE
	printf("MGLProgram_tp_new %p\n", self);
	#endif

	if (self) {
		self->shaders = 0;

		self->uniforms = 0;
		self->attributes = 0;
		self->subroutines = 0;
		self->varyings = 0;

		self->uniforms_proxy = 0;
		self->attributes_proxy = 0;
		self->subroutines_proxy = 0;
		self->varyings_proxy = 0;

		self->geometry_input = 0;
		self->geometry_output = 0;
	}

	return (PyObject *)self;
}

void MGLProgram_tp_dealloc(MGLProgram * self) {

	#ifdef MGL_VERBOSE
	printf("MGLProgram_tp_dealloc %p\n", self);
	#endif

	MGLProgram_Type.tp_free((PyObject *)self);
}

int MGLProgram_tp_init(MGLProgram * self, PyObject * args, PyObject * kwargs) {
	return -1;
}

PyObject * MGLProgram_tp_str(MGLProgram * self) {
	return PyUnicode_FromFormat("<ModernGL.Program>");
}

PyObject * MGLProgram_release(MGLProgram * self) {
	MGLProgram_Invalidate(self);
	Py_RETURN_NONE;
}

char MGLProgram_release_doc[] = R"(
	release()

	Release the program object.
)";

PyMethodDef MGLProgram_tp_methods[] = {
	{"release", (PyCFunction)MGLProgram_release, METH_NOARGS, MGLProgram_release_doc},
	{0},
};

PyObject * MGLProgram_get_shaders(MGLProgram * self, void * closure) {
	Py_INCREF(self->shaders);
	return self->shaders;
}

char MGLProgram_shaders_doc[] = R"(
	shaders

	The shaders.
	The return value is a tuple.
)";

PyObject * MGLProgram_get_varyings(MGLProgram * self, void * closure) {
	Py_INCREF(self->varyings_proxy);
	return self->varyings_proxy;
}

char MGLProgram_varyings_doc[] = R"(
	varyings

	The program's varyings.
	The return value is a dictinary.
	It can be used to access varyings by name.
)";

PyObject * MGLProgram_get_uniforms(MGLProgram * self, void * closure) {
	Py_INCREF(self->uniforms_proxy);
	return self->uniforms_proxy;
}

char MGLProgram_uniforms_doc[] = R"(
	uniforms

	The program's uniforms.
	The return value is a dictinary.
	It can be used to access uniforms by name.
)";

PyObject * MGLProgram_get_attributes(MGLProgram * self, void * closure) {
	Py_INCREF(self->attributes_proxy);
	return self->attributes_proxy;
}

char MGLProgram_attributes_doc[] = R"(
	attributes

	The program's attributes.
	The return value is a dictinary.
	It can be used to access attributes by name.
)";

PyObject * MGLProgram_get_subroutines(MGLProgram * self, void * closure) {
	Py_INCREF(self->subroutines_proxy);
	return self->subroutines_proxy;
}

char MGLProgram_subroutines_doc[] = R"(
	subroutines

	The program's subroutines.
	The return value is a dictinary.
	It can be used to access subroutines by name.
)";

PyObject * MGLProgram_get_geometry_input(MGLProgram * self, void * closure) {
	if (self->geometry_input) {
		Py_INCREF(self->geometry_input);
		return (PyObject *)self->geometry_input;
	} else {
		Py_RETURN_NONE;
	}
}

char MGLProgram_geometry_input_doc[] = R"(
	geometry_input

	The geometry input primitive.
	The GeometryShader's input primitive if the GeometryShader is present otherwise ``None``.
	The geometry input primitive will be used for validation when rendering.
)";

PyObject * MGLProgram_get_geometry_output(MGLProgram * self, void * closure) {
	if (self->geometry_output) {
		Py_INCREF(self->geometry_output);
		return (PyObject *)self->geometry_output;
	} else {
		Py_RETURN_NONE;
	}
}

char MGLProgram_geometry_output_doc[] = R"(
	geometry_output

	The geometry output primitive.
	The GeometryShader's output primitive if the GeometryShader is present otherwise ``None``.
)";

PyGetSetDef MGLProgram_tp_getseters[] = {
	{(char *)"shaders", (getter)MGLProgram_get_shaders, 0, MGLProgram_shaders_doc, 0},
	{(char *)"varyings", (getter)MGLProgram_get_varyings, 0, MGLProgram_varyings_doc, 0},
	{(char *)"uniforms", (getter)MGLProgram_get_uniforms, 0, MGLProgram_uniforms_doc, 0},
	{(char *)"attributes", (getter)MGLProgram_get_attributes, 0, MGLProgram_attributes_doc, 0},
	{(char *)"subroutines", (getter)MGLProgram_get_subroutines, 0, MGLProgram_subroutines_doc, 0},
	{(char *)"geometry_input", (getter)MGLProgram_get_geometry_input, 0, MGLProgram_geometry_input_doc, 0},
	{(char *)"geometry_output", (getter)MGLProgram_get_geometry_output, 0, MGLProgram_geometry_output_doc, 0},
	{0},
};

// PyObject * Program_get_item(Program * self, PyObject * key) {
// }

// int Program_set_item(Program * self, PyObject * key, PyObject * value) {
// }

PyMappingMethods Program_map = {
	0,
	// (binaryfunc)Program_get_item,
	// (objobjargproc)Program_set_item,
};

const char * MGLProgram_tp_doc = R"(
)";

PyTypeObject MGLProgram_Type = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Program",                                     // tp_name
	sizeof(MGLProgram),                                     // tp_basicsize
	0,                                                      // tp_itemsize
	(destructor)MGLProgram_tp_dealloc,                      // tp_dealloc
	0,                                                      // tp_print
	0,                                                      // tp_getattr
	0,                                                      // tp_setattr
	0,                                                      // tp_reserved
	(reprfunc)MGLProgram_tp_str,                            // tp_repr
	0,                                                      // tp_as_number
	0,                                                      // tp_as_sequence
	&Program_map,                                           // tp_as_mapping
	0,                                                      // tp_hash
	0,                                                      // tp_call
	(reprfunc)MGLProgram_tp_str,                            // tp_str
	0,                                                      // tp_getattro
	0,                                                      // tp_setattro
	0,                                                      // tp_as_buffer
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,               // tp_flags
	MGLProgram_tp_doc,                                      // tp_doc
	0,                                                      // tp_traverse
	0,                                                      // tp_clear
	0,                                                      // tp_richcompare
	0,                                                      // tp_weaklistoffset
	0,                                                      // tp_iter
	0,                                                      // tp_iternext
	MGLProgram_tp_methods,                                  // tp_methods
	0,                                                      // tp_members
	MGLProgram_tp_getseters,                                // tp_getset
	&MGLContextMember_Type,                                 // tp_base
	0,                                                      // tp_dict
	0,                                                      // tp_descr_get
	0,                                                      // tp_descr_set
	0,                                                      // tp_dictoffset
	(initproc)MGLProgram_tp_init,                           // tp_init
	0,                                                      // tp_alloc
	MGLProgram_tp_new,                                      // tp_new
};

MGLProgram * MGLProgram_New() {
	MGLProgram * self = (MGLProgram *)MGLProgram_tp_new(&MGLProgram_Type, 0, 0);
	return self;
}

void MGLProgram_Invalidate(MGLProgram * program) {
	if (Py_TYPE(program) == &MGLInvalidObject_Type) {

		#ifdef MGL_VERBOSE
		printf("MGLProgram_Invalidate %p already released\n", program);
		#endif

		return;
	}

	#ifdef MGL_VERBOSE
	printf("MGLProgram_Invalidate %p\n", program);
	#endif

	const GLMethods & gl = program->context->gl;

	gl.DeleteProgram(program->obj);

	{
		MGLUniform * uniform = 0;
		Py_ssize_t pos = 0;

		while (PyDict_Next(program->uniforms, &pos, 0, (PyObject **)&uniform)) {
			MGLUniform_Invalidate(uniform);
		}

		Py_DECREF(program->uniforms);
	}

	{
		MGLAttribute * attribute = 0;
		Py_ssize_t pos = 0;

		while (PyDict_Next(program->attributes, &pos, 0, (PyObject **)&attribute)) {
			MGLAttribute_Invalidate(attribute);
		}

		Py_DECREF(program->attributes);
	}

	{
		MGLSubroutine * subroutine = 0;
		Py_ssize_t pos = 0;

		while (PyDict_Next(program->subroutines, &pos, 0, (PyObject **)&subroutine)) {
			MGLSubroutine_Invalidate(subroutine);
		}

		Py_DECREF(program->subroutines);
	}

	{
		MGLVarying * varying = 0;
		Py_ssize_t pos = 0;

		while (PyDict_Next(program->varyings, &pos, 0, (PyObject **)&varying)) {
			MGLVarying_Invalidate(varying);
		}

		Py_DECREF(program->varyings);
	}

	int shaders_len = PyTuple_GET_SIZE(program->shaders);

	for (int i = 0; i < shaders_len; ++i) {
		MGLShader * shader = (MGLShader *)PyTuple_GET_ITEM(program->shaders, i);
		if (Py_REFCNT(shader) == 2) {
			MGLShader_Invalidate(shader);
		}
	}

	Py_DECREF(program->uniforms_proxy);
	Py_DECREF(program->attributes_proxy);
	Py_DECREF(program->subroutines_proxy);
	Py_DECREF(program->varyings_proxy);

	Py_XDECREF(program->geometry_input);
	Py_XDECREF(program->geometry_output);

	Py_DECREF(program->shaders);

	Py_DECREF(program->context);

	program->ob_base.ob_type = &MGLInvalidObject_Type;
	program->initial_type = &MGLProgram_Type;

	Py_DECREF(program);
}

void MGLProgram_Compile(MGLProgram * program, PyObject * varyings) {
	const GLMethods & gl = program->context->gl;

	int obj = gl.CreateProgram();

	bool has_geometry_shader = false;

	int num_shaders = PyTuple_GET_SIZE(program->shaders);

	for (int i = 0; i < num_shaders; ++i) {
		MGLShader * shader = (MGLShader *)PyTuple_GET_ITEM(program->shaders, i);
		if (shader->shader_slot == GEOMETRY_SHADER_SLOT) {
			has_geometry_shader = true;
		}
		gl.AttachShader(obj, shader->obj);
	}

	if (varyings != Py_None) {
		int varyings_len = PyList_GET_SIZE(varyings);

		if (varyings_len) {
			char ** varyings_array = new char * [varyings_len];

			for (int i = 0; i < varyings_len; ++i) {
				varyings_array[i] = PyUnicode_AsUTF8(PyList_GET_ITEM(varyings, i));
			}

			gl.TransformFeedbackVaryings(obj, varyings_len, varyings_array, GL_INTERLEAVED_ATTRIBS);

			delete[] varyings_array;
		}
	}

	gl.LinkProgram(obj);

	int linked = GL_FALSE;
	gl.GetProgramiv(obj, GL_LINK_STATUS, &linked);

	if (!linked) {
		const char * message = "GLSL Compiler failed";
		const char * title = "Program";
		const char * underline = "=======";

		int log_len = 0;
		gl.GetProgramiv(obj, GL_INFO_LOG_LENGTH, &log_len);

		char * log = new char[log_len];
		gl.GetProgramInfoLog(obj, log_len, &log_len, log);

		gl.DeleteProgram(obj);

		MGLError * error = MGLError_New(TRACE, "%s\n\n%s\n%s\n%s\n", message, title, underline, log);
		PyErr_SetObject((PyObject *)&MGLError_Type, (PyObject *)error);

		delete[] log;
		return;
	}

	program->obj = obj;

	MGLProgram_LoadUniforms(program);
	MGLProgram_LoadAttributes(program);
	MGLProgram_LoadVaryings(program);
	MGLProgram_LoadSubroutines(program);

	// TODO:
	// int num_uniform_blocks = 0;
	// gl.GetProgramiv(obj, GL_ACTIVE_UNIFORM_BLOCKS, &num_uniform_blocks);

	// TODO:
	// glGetProgramStageiv
	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glGetProgramStage.xhtml

	// Py_INCREF(...);

	int geometry_in = 0;
	int geometry_out = 0;

	if (has_geometry_shader) {
		gl.GetProgramiv(obj, GL_GEOMETRY_INPUT_TYPE, &geometry_in);
		gl.GetProgramiv(obj, GL_GEOMETRY_OUTPUT_TYPE, &geometry_out);

		switch (geometry_in) {
			case GL_TRIANGLES:
				program->geometry_input = MGL_TRIANGLES;
				break;

			case GL_TRIANGLE_STRIP:
				program->geometry_input = MGL_TRIANGLE_STRIP;
				break;

			case GL_TRIANGLE_FAN:
				program->geometry_input = MGL_TRIANGLE_FAN;
				break;

			case GL_LINES:
				program->geometry_input = MGL_LINES;
				break;

			case GL_LINE_STRIP:
				program->geometry_input = MGL_LINE_STRIP;
				break;

			case GL_LINE_LOOP:
				program->geometry_input = MGL_LINE_LOOP;
				break;

			case GL_POINTS:
				program->geometry_input = MGL_POINTS;
				break;

			case GL_LINE_STRIP_ADJACENCY:
				program->geometry_input = MGL_LINE_STRIP_ADJACENCY;
				break;

			case GL_LINES_ADJACENCY:
				program->geometry_input = MGL_LINES_ADJACENCY;
				break;

			case GL_TRIANGLE_STRIP_ADJACENCY:
				program->geometry_input = MGL_TRIANGLE_STRIP_ADJACENCY;
				break;

			case GL_TRIANGLES_ADJACENCY:
				program->geometry_input = MGL_TRIANGLES_ADJACENCY;
				break;

			default:
				program->geometry_input = 0;
				break;
		}

		switch (geometry_out) {
			case GL_TRIANGLES:
				program->geometry_output = MGL_TRIANGLES;
				break;

			case GL_TRIANGLE_STRIP:
				program->geometry_output = MGL_TRIANGLE_STRIP;
				break;

			case GL_TRIANGLE_FAN:
				program->geometry_output = MGL_TRIANGLE_FAN;
				break;

			case GL_LINES:
				program->geometry_output = MGL_LINES;
				break;

			case GL_LINE_STRIP:
				program->geometry_output = MGL_LINE_STRIP;
				break;

			case GL_LINE_LOOP:
				program->geometry_output = MGL_LINE_LOOP;
				break;

			case GL_POINTS:
				program->geometry_output = MGL_POINTS;
				break;

			case GL_LINE_STRIP_ADJACENCY:
				program->geometry_output = MGL_LINE_STRIP_ADJACENCY;
				break;

			case GL_LINES_ADJACENCY:
				program->geometry_output = MGL_LINES_ADJACENCY;
				break;

			case GL_TRIANGLE_STRIP_ADJACENCY:
				program->geometry_output = MGL_TRIANGLE_STRIP_ADJACENCY;
				break;

			case GL_TRIANGLES_ADJACENCY:
				program->geometry_output = MGL_TRIANGLES_ADJACENCY;
				break;

			default:
				program->geometry_output = 0;
				break;
		}
	}

	if (program->geometry_input) {
		Py_INCREF(program->geometry_input);
	}

	if (program->geometry_output) {
		Py_INCREF(program->geometry_output);
	}
}

void clean_program_member_name(char * name, int & name_len) {
	if (name_len && name[name_len - 1] == ']') {
		name_len -= 1;
		while (name_len && name[name_len] != '[') {
			name_len -= 1;
		}
	}
	name[name_len] = 0;
}

void MGLProgram_LoadUniforms(MGLProgram * program) {
	const GLMethods & gl = program->context->gl;

	PyObject * uniforms = PyDict_New();

	int num_uniforms = 0;
	gl.GetProgramiv(program->obj, GL_ACTIVE_UNIFORMS, &num_uniforms);

	for (int i = 0; i < num_uniforms; ++i) {
		MGLUniform * uniform = MGLUniform_New();

		int name_len = 0;
		char name[256];

		gl.GetActiveUniform(program->obj, i, 256, &name_len, &uniform->array_length, (GLenum *)&uniform->type, name);

		uniform->location = gl.GetUniformLocation(program->obj, name);

		if (uniform->location < 0) {
			Py_DECREF((PyObject *)uniform);
			continue;
		}

		uniform->index = i;
		uniform->program = program;
		uniform->name = PyUnicode_FromStringAndSize(name, name_len);

		MGLUniform_Complete(uniform);

		clean_program_member_name(name, name_len);

		// TODO: check shadow and sampler cube

		PyDict_SetItem(uniforms, uniform->name, (PyObject *)uniform);
		Py_DECREF(uniform);
	}

	program->uniforms = uniforms;

	Py_INCREF(uniforms); // TODO: maybe not needed
	program->uniforms_proxy = PyDictProxy_New(uniforms);
}

void MGLProgram_LoadAttributes(MGLProgram * program) {
	const GLMethods & gl = program->context->gl;

	PyObject * attributes = PyDict_New();

	int num_attributes = 0;
	gl.GetProgramiv(program->obj, GL_ACTIVE_ATTRIBUTES, &num_attributes);

	for (int i = 0; i < num_attributes; ++i) {
		MGLAttribute * attribute = MGLAttribute_New();

		int name_len = 0;
		char name[256];

		gl.GetActiveAttrib(program->obj, i, 256, &name_len, &attribute->array_length, (GLenum *)&attribute->type, name);

		attribute->location = gl.GetAttribLocation(program->obj, name);

		if (attribute->location < 0) {
			Py_DECREF(attribute);
			continue;
		}

		clean_program_member_name(name, name_len);

		attribute->number = i;
		attribute->program = program;
		attribute->name = PyUnicode_FromStringAndSize(name, name_len);

		MGLAttribute_Complete(attribute);

		PyDict_SetItem(attributes, attribute->name, (PyObject *)attribute);
		Py_DECREF(attribute);
	}

	program->attributes = attributes;

	Py_INCREF(attributes); // TODO: maybe not needed
	program->attributes_proxy = PyDictProxy_New(attributes);
}

void MGLProgram_LoadVaryings(MGLProgram * program) {
	const GLMethods & gl = program->context->gl;

	PyObject * varyings = PyDict_New();

	int num_varyings = 0;
	gl.GetProgramiv(program->obj, GL_TRANSFORM_FEEDBACK_VARYINGS, &num_varyings);

	for (int i = 0; i < num_varyings; ++i) {
		MGLVarying * varying = MGLVarying_New();

		int name_len = 0;
		char name[256];

		gl.GetTransformFeedbackVarying(program->obj, i, 256, &name_len, &varying->array_length, (GLenum *)&varying->type, name);

		varying->index = i;
		varying->program = program;
		varying->name = PyUnicode_FromStringAndSize(name, name_len);

		PyDict_SetItem(varyings, varying->name, (PyObject *)varying);
		Py_DECREF(varying);
	}

	program->varyings = varyings;

	Py_INCREF(varyings); // TODO: maybe not needed
	program->varyings_proxy = PyDictProxy_New(varyings);
}

void MGLProgram_LoadSubroutines(MGLProgram * program) {
	const GLMethods & gl = program->context->gl;

	PyObject * subroutines = PyDict_New();

	program->subroutines = subroutines;

	Py_INCREF(subroutines); // TODO: maybe not needed
	program->subroutines_proxy = PyDictProxy_New(subroutines);
}
