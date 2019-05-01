#include "program.hpp"
#include "context.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"
#include "internal/uniform.hpp"

const char * SHADER_NAME[] = {
    "vertex_shader",
    "fragment_shader",
    "geometry_shader",
    "tess_control_shader",
    "tess_evaluation_shader",
};

const int SHADER_TYPE[] = {
    GL_VERTEX_SHADER,
    GL_FRAGMENT_SHADER,
    GL_GEOMETRY_SHADER,
    GL_TESS_CONTROL_SHADER,
    GL_TESS_EVALUATION_SHADER,
};

/* MGLContext.program(vertex_shader, fragment_shader, geometry_shader, tess_control_shader, tess_evaluation_shader, varyings)
 */
PyObject * MGLContext_meth_program(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(6);

    MGLProgram * program = MGLContext_new_object(self, Program);

    const GLMethods & gl = self->gl;

    int program_obj = gl.CreateProgram();
    if (!program_obj) {
        PyErr_Format(moderngl_error, "cannot create program");
        Py_DECREF(program);
        return 0;
    }

    program->program_obj = program_obj;

    for (int i = 0; i < 5; ++i) {
        if (args[i] == Py_None) {
            continue;
        }

        if (!PyUnicode_Check(args[i])) {
            PyErr_Format(PyExc_TypeError, "%s must be a str not %s", SHADER_NAME[i], args[i]->ob_type->tp_name);
            // Py_DECREF(program);
            return 0;
        }

        int shader_obj = gl.CreateShader(SHADER_TYPE[i]);
        if (!shader_obj) {
            PyErr_Format(moderngl_error, "cannot create shader");
            // Py_DECREF(program);
            return 0;
        }

        program->shader_obj[i] = shader_obj;

        int compiled = GL_FALSE;
        const char * source_str = PyUnicode_AsUTF8(args[i]);
        gl.ShaderSource(shader_obj, 1, &source_str, 0);
        gl.CompileShader(shader_obj);
        gl.GetShaderiv(shader_obj, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            int log_len = 0;
            gl.GetShaderiv(shader_obj, GL_INFO_LOG_LENGTH, &log_len);

            char * log_text = (char *)malloc(log_len + 1);
            gl.GetShaderInfoLog(shader_obj, log_len, 0, log_text);
            PyObject * name = PyUnicode_FromString(SHADER_NAME[i]);
            PyObject * info = PyUnicode_FromStringAndSize(log_text, log_len);
            call_function(self->glsl_compiler_error, name, args[i], info);
            Py_DECREF(name);
            Py_DECREF(info);
            // Py_DECREF(program);
            free(log_text);
            return 0;
        }

        gl.AttachShader(program_obj, shader_obj);
    }

    PyObject * varyings = args[5];
    if (PyUnicode_Check(varyings)) {
        varyings = PyTuple_Pack(1, varyings);
    } else {
        varyings = PySequence_Fast(varyings, "varyings is not iterable");
        if (!varyings) {
            return 0;
        }
    }

    int varyings_len = (int)PySequence_Fast_GET_SIZE(varyings);

    if (varyings_len) {
        const char ** varyings_str = new const char * [varyings_len];
        for (int i = 0; i < varyings_len; ++i) {
            PyObject * varying = PySequence_Fast_GET_ITEM(varyings, i);
            if (!PyUnicode_Check(varying)) {
                PyErr_Format(PyExc_TypeError, "expected str, got %s", varying->ob_type->tp_name);
                Py_DECREF(varyings);
                Py_DECREF(program);
                delete[] varyings_str;
                return 0;
            }
            varyings_str[i] = PyUnicode_AsUTF8(varying);
        }
        gl.TransformFeedbackVaryings(program_obj, varyings_len, varyings_str, GL_INTERLEAVED_ATTRIBS);
        delete[] varyings_str;
    }

    Py_DECREF(varyings);

    int linked = GL_FALSE;
    gl.LinkProgram(program_obj);
    gl.GetProgramiv(program_obj, GL_LINK_STATUS, &linked);

    if (!linked) {
        int log_len = 0;
        gl.GetProgramiv(program_obj, GL_INFO_LOG_LENGTH, &log_len);
        char * log_text = (char *)malloc(log_len + 1);
        gl.GetProgramInfoLog(program_obj, log_len, 0, log_text);
        PyObject * info = PyUnicode_FromStringAndSize(log_text, log_len);
        call_function(self->glsl_linker_error, info);
        Py_DECREF(info);
        // Py_DECREF(program);
        free(log_text);
        return 0;
    }

    for (int i = 0; i < 5; ++i) {
        if (program->shader_obj[i]) {
            gl.DeleteShader(program->shader_obj[i]);
        }
    }

    self->use_program(program_obj);

    PyObject * uniforms = PyDict_New();
    PyObject * attributes = PyDict_New();

    int attributes_len = 0;
    int uniforms_len = 0;
    int uniform_blocks_len = 0;

    gl.GetProgramiv(program_obj, GL_ACTIVE_ATTRIBUTES, &attributes_len);
    gl.GetProgramiv(program_obj, GL_ACTIVE_UNIFORMS, &uniforms_len);
    gl.GetProgramiv(program_obj, GL_ACTIVE_UNIFORM_BLOCKS, &uniform_blocks_len);

    for (int i = 0; i < attributes_len; ++i) {
        int type = 0;
        int size = 0;
        int name_len = 0;
        char name[256];

        gl.GetActiveAttrib(program_obj, i, 256, &name_len, &size, (GLenum *)&type, name);
        int location = gl.GetAttribLocation(program_obj, name);
        clean_glsl_name(name, name_len);

        GLTypeInfo info = type_info(type);

        PyObject * attrib = new_object(PyObject, Attribute_class);
        SLOT(attrib, PyObject, Attribute_class_type) = PyLong_FromLong(type);
        SLOT(attrib, PyObject, Attribute_class_location) = PyLong_FromLong(location);
        SLOT(attrib, PyObject, Attribute_class_cols) = PyLong_FromLong(info.cols);
        SLOT(attrib, PyObject, Attribute_class_rows) = PyLong_FromLong(info.rows);
        SLOT(attrib, PyObject, Attribute_class_size) = PyLong_FromLong(size);
        SLOT(attrib, PyObject, Attribute_class_shape) = PyLong_FromLong(info.shape);
        PyDict_SetItemString(attributes, name, attrib);
    }

    for (int i = 0; i < uniforms_len; ++i) {
        int type = 0;
        int size = 0;
        int name_len = 0;
        char name[256];

        gl.GetActiveUniform(program->program_obj, i, 256, &name_len, &size, (GLenum *)&type, name);
        int location = gl.GetUniformLocation(program->program_obj, name);
        clean_glsl_name(name, name_len);

        if (location < 0) {
            continue;
        }

        GLTypeInfo info = type_info(type);

        PyObject * uniform = new_object(PyObject, Uniform_class);
        SLOT(uniform, PyObject, Uniform_class_type) = PyLong_FromLong(type);
        SLOT(uniform, PyObject, Uniform_class_location) = PyLong_FromLong(location);
        SLOT(uniform, PyObject, Uniform_class_cols) = PyLong_FromLong(info.cols);
        SLOT(uniform, PyObject, Uniform_class_rows) = PyLong_FromLong(info.rows);
        SLOT(uniform, PyObject, Uniform_class_size) = PyLong_FromLong(size);
        SLOT(uniform, PyObject, Uniform_class_shape) = PyLong_FromLong(info.shape);
        PyDict_SetItemString(uniforms, name, uniform);
    }

    for (int i = 0; i < uniform_blocks_len; ++i) {
        int size = 0;
        int name_len = 0;
        char name[256];

        gl.GetActiveUniformBlockName(program->program_obj, i, 256, &name_len, name);
        int index = gl.GetUniformBlockIndex(program->program_obj, name);
        gl.GetActiveUniformBlockiv(program->program_obj, index, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
        clean_glsl_name(name, name_len);

        PyObject * uniform = new_object(PyObject, Uniform_class);
        SLOT(uniform, PyObject, Uniform_class_type) = 0;
        SLOT(uniform, PyObject, Uniform_class_location) = PyLong_FromLong(index);
        SLOT(uniform, PyObject, Uniform_class_cols) = 0;
        SLOT(uniform, PyObject, Uniform_class_rows) = 0;
        SLOT(uniform, PyObject, Uniform_class_size) = PyLong_FromLong(size);
        SLOT(uniform, PyObject, Uniform_class_shape) = PyLong_FromLong(0);
        PyDict_SetItemString(uniforms, name, uniform);
    }

    SLOT(program->wrapper, PyObject, Program_class_attributes) = attributes;
    SLOT(program->wrapper, PyObject, Program_class_uniforms) = uniforms;
    return NEW_REF(program->wrapper);
}

/* MGLProgram.uniform(uniform, value)
 */
PyObject * MGLProgram_meth_uniform(MGLProgram * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 1 && nargs != 2) {
        PyErr_Format(moderngl_error, "num args");
        return 0;
    }
    const GLMethods & gl = self->context->gl;
    self->context->use_program(self->program_obj);
    return getset_uniform(gl, self->program_obj, args[0], nargs == 2 ? args[1] : 0);
}

void MGLProgram_dealloc(MGLProgram * self) {
    Py_TYPE(self)->tp_free(self);
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLProgram_methods[] = {
    {"uniform", (PyCFunction)MGLProgram_meth_uniform, METH_FASTCALL, 0},
    {0},
};

#else

PyObject * MGLProgram_meth_uniform_va(MGLProgram * self, PyObject * args) {
    return MGLProgram_meth_uniform(self, ((PyTupleObject *)args)->ob_item, ((PyVarObject *)args)->ob_size);
}

PyMethodDef MGLProgram_methods[] = {
    {"uniform", (PyCFunction)MGLProgram_meth_uniform_va, METH_VARARGS, 0},
    {0},
};

#endif

PyType_Slot MGLProgram_slots[] = {
    {Py_tp_methods, MGLProgram_methods},
    {Py_tp_dealloc, (void *)MGLProgram_dealloc},
    {0},
};

PyType_Spec MGLProgram_spec = {
    "moderngl.mgl.new.MGLProgram",
    sizeof(MGLProgram),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLProgram_slots,
};
