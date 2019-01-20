#include "buffer.hpp"
#include "compute_shader.hpp"
#include "context.hpp"
#include "framebuffer.hpp"
#include "program.hpp"
#include "query.hpp"
#include "renderbuffer.hpp"
#include "sampler.hpp"
#include "scope.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

#include "internal/wrapper.hpp"
#include "internal/tools.hpp"

inline void dict_set_item(PyObject * dict, const char * key, PyObject * value) {
    if (value) {
        PyDict_SetItemString(dict, key, value);
    }
}

inline void dict_set_item(PyObject * dict, const char * key, int value) {
    PyObject * item = PyLong_FromLong(value);
    PyDict_SetItemString(dict, key, item);
    Py_DECREF(item);
}

inline void dict_set_item(PyObject * dict, const char * key, unsigned long long value) {
    PyObject * item = PyLong_FromUnsignedLongLong(value);
    PyDict_SetItemString(dict, key, item);
    Py_DECREF(item);
}

inline void dict_set_item(PyObject * dict, const char * key, Py_ssize_t value) {
    PyObject * item = PyLong_FromSsize_t(value);
    PyDict_SetItemString(dict, key, item);
    Py_DECREF(item);
}

inline void dict_set_item(PyObject * dict, const char * key, bool value) {
    PyObject * item = PyBool_FromLong(value);
    PyDict_SetItemString(dict, key, item);
    Py_DECREF(item);
}

inline void dict_set_item(PyObject * dict, const char * key, const char * value, int length) {
    PyObject * item = PyUnicode_FromStringAndSize(value, length);
    PyDict_SetItemString(dict, key, item);
    Py_DECREF(item);
}

// inline void add_dict_non_null(PyObject * dict, const char * key, PyObject * value) {
//     if (value) {
//         PyDict_SetItemString(dict, key, value);
//     }
// }

// struct MGLProgram {
//     PyObject_HEAD
//     PyObject * wrapper;
//     MGLContext * context;
//     int program_obj;
//     int shader_obj[5];
// };

/* moderngl.core.inspect(obj)
 */
PyObject * meth_inspect(PyObject * self, PyObject * obj) {
    if (PyLong_CheckExact(obj)) {
        return meth_inspect(0, (PyObject *)PyLong_AsVoidPtr(obj));
    }

    if (obj->ob_type == Attribute_class) {
        PyObject * res = PyDict_New();

        dict_set_item(res, "self", obj);
        dict_set_item(res, "type", SLOT(obj, PyObject, Attribute_class_type));
        dict_set_item(res, "location", SLOT(obj, PyObject, Attribute_class_location));
        dict_set_item(res, "cols", SLOT(obj, PyObject, Attribute_class_cols));
        dict_set_item(res, "rows", SLOT(obj, PyObject, Attribute_class_rows));
        dict_set_item(res, "size", SLOT(obj, PyObject, Attribute_class_size));
        dict_set_item(res, "shape", SLOT(obj, PyObject, Attribute_class_shape));
        return res;
    }

    if (obj->ob_type == Buffer_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Buffer_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "size", SLOT(obj, PyObject, Buffer_class_size));
        return res;
    }

    if (obj->ob_type == ComputeShader_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, ComputeShader_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "uniforms", SLOT(obj, PyObject, ComputeShader_class_uniforms));
        return res;
    }

    if (obj->ob_type == Context_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Context_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "version_code", SLOT(obj, PyObject, Context_class_version_code));
        dict_set_item(res, "limits", SLOT(obj, PyObject, Context_class_limits));
        dict_set_item(res, "screen", SLOT(obj, PyObject, Context_class_screen));
        dict_set_item(res, "fbo", SLOT(obj, PyObject, Context_class_fbo));
        return res;
    }

    if (obj->ob_type == Framebuffer_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Framebuffer_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "viewport", SLOT(obj, PyObject, Framebuffer_class_viewport));
        dict_set_item(res, "size", SLOT(obj, PyObject, Framebuffer_class_size));
        return res;
    }

    if (obj->ob_type == Program_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Program_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "uniforms", SLOT(obj, PyObject, Program_class_uniforms));
        dict_set_item(res, "attributes", SLOT(obj, PyObject, Program_class_attributes));
        return res;
    }

    if (obj->ob_type == Query_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Query_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "elapsed", SLOT(obj, PyObject, Query_class_elapsed));
        dict_set_item(res, "primitives", SLOT(obj, PyObject, Query_class_primitives));
        dict_set_item(res, "samples", SLOT(obj, PyObject, Query_class_samples));
        return res;
    }

    if (obj->ob_type == Renderbuffer_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Renderbuffer_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "size", SLOT(obj, PyObject, Renderbuffer_class_size));
        return res;
    }

    if (obj->ob_type == Sampler_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Sampler_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "swizzle", SLOT(obj, PyObject, Sampler_class_swizzle));
        dict_set_item(res, "filter", SLOT(obj, PyObject, Sampler_class_filter));
        dict_set_item(res, "texture", SLOT(obj, PyObject, Sampler_class_texture));
        return res;
    }

    if (obj->ob_type == Scope_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Scope_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);
        return res;
    }

    if (obj->ob_type == Texture_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, Texture_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "level", SLOT(obj, PyObject, Texture_class_level));
        dict_set_item(res, "layer", SLOT(obj, PyObject, Texture_class_layer));
        dict_set_item(res, "size", SLOT(obj, PyObject, Texture_class_size));
        return res;
    }

    if (obj->ob_type == Uniform_class) {
        PyObject * res = PyDict_New();

        dict_set_item(res, "self", obj);
        dict_set_item(res, "type", SLOT(obj, PyObject, Uniform_class_type));
        dict_set_item(res, "location", SLOT(obj, PyObject, Uniform_class_location));
        dict_set_item(res, "cols", SLOT(obj, PyObject, Uniform_class_cols));
        dict_set_item(res, "rows", SLOT(obj, PyObject, Uniform_class_rows));
        dict_set_item(res, "size", SLOT(obj, PyObject, Uniform_class_size));
        dict_set_item(res, "shape", SLOT(obj, PyObject, Uniform_class_shape));
        return res;
    }

    if (obj->ob_type == VertexArray_class) {
        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);

        PyObject * mglo = meth_inspect(0, SLOT(obj, PyObject, VertexArray_class_mglo));
        dict_set_item(res, "mglo", mglo);
        Py_DECREF(mglo);

        dict_set_item(res, "ibo", SLOT(obj, PyObject, VertexArray_class_ibo));
        dict_set_item(res, "program", SLOT(obj, PyObject, VertexArray_class_program));
        dict_set_item(res, "mode", SLOT(obj, PyObject, VertexArray_class_mode));
        dict_set_item(res, "vertices", SLOT(obj, PyObject, VertexArray_class_vertices));
        return res;
    }

    if (obj->ob_type == MGLContext_class) {
        MGLContext * context = (MGLContext *)obj;

        PyObject * res = PyDict_New();
        dict_set_item(res, "self", obj);
        dict_set_item(res, "wrapper", context->wrapper);
        // TODO: ...
        return res;
    }

    if (starts_with(obj->ob_type->tp_name, mgl_name)) {
        MGLObject * mglo = (MGLObject *)obj;

        if (mglo->ob_base.ob_type == mglo->context->MGLBuffer_class) {
            MGLBuffer * buffer = (MGLBuffer *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", buffer->wrapper);
            dict_set_item(res, "context", (PyObject *)buffer->context);
            dict_set_item(res, "buffer_obj", buffer->buffer_obj);
            dict_set_item(res, "flags", buffer->flags);
            dict_set_item(res, "size", buffer->size);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLComputeShader_class) {
            MGLComputeShader * compute_shader = (MGLComputeShader *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", compute_shader->wrapper);
            dict_set_item(res, "context", (PyObject *)compute_shader->context);
            dict_set_item(res, "program_obj", compute_shader->program_obj);
            dict_set_item(res, "shader_obj", compute_shader->shader_obj);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLFramebuffer_class) {
            MGLFramebuffer * framebuffer = (MGLFramebuffer *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", framebuffer->wrapper);
            dict_set_item(res, "context", (PyObject *)framebuffer->context);
            dict_set_item(res, "framebuffer_obj", framebuffer->framebuffer_obj);
            dict_set_item(res, "width", framebuffer->width);
            dict_set_item(res, "height", framebuffer->height);
            dict_set_item(res, "depth", framebuffer->depth);
            dict_set_item(res, "components", framebuffer->components);
            dict_set_item(res, "levels", framebuffer->levels);
            dict_set_item(res, "samples", framebuffer->samples);

            PyObject * viewport = PyTuple_New(4);
            PyTuple_SET_ITEM(viewport, 0, PyLong_FromLong(framebuffer->viewport[0]));
            PyTuple_SET_ITEM(viewport, 1, PyLong_FromLong(framebuffer->viewport[1]));
            PyTuple_SET_ITEM(viewport, 2, PyLong_FromLong(framebuffer->viewport[2]));
            PyTuple_SET_ITEM(viewport, 3, PyLong_FromLong(framebuffer->viewport[3]));
            dict_set_item(res, "viewport", viewport);
            Py_DECREF(viewport);

            dict_set_item(res, "attachments", framebuffer->attachments);
            dict_set_item(res, "attachment_type", framebuffer->attachment_type, framebuffer->attachments);
            dict_set_item(res, "color_mask", framebuffer->color_mask);
            dict_set_item(res, "depth_mask", framebuffer->depth_mask);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLProgram_class) {
            MGLProgram * program = (MGLProgram *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", program->wrapper);
            dict_set_item(res, "context", (PyObject *)program->context);
            dict_set_item(res, "program_obj", program->program_obj);

            PyObject * shader_obj = PyTuple_New(5);
            PyTuple_SET_ITEM(shader_obj, 0, PyLong_FromLong(program->shader_obj[0]));
            PyTuple_SET_ITEM(shader_obj, 1, PyLong_FromLong(program->shader_obj[1]));
            PyTuple_SET_ITEM(shader_obj, 2, PyLong_FromLong(program->shader_obj[2]));
            PyTuple_SET_ITEM(shader_obj, 3, PyLong_FromLong(program->shader_obj[3]));
            PyTuple_SET_ITEM(shader_obj, 4, PyLong_FromLong(program->shader_obj[4]));
            dict_set_item(res, "shader_obj", shader_obj);
            Py_DECREF(shader_obj);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLQuery_class) {
            MGLQuery * query = (MGLQuery *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", query->wrapper);
            dict_set_item(res, "context", (PyObject *)query->context);

            PyObject * query_obj = PyTuple_New(4);
            PyTuple_SET_ITEM(query_obj, 0, PyLong_FromLong(query->query_obj[0]));
            PyTuple_SET_ITEM(query_obj, 1, PyLong_FromLong(query->query_obj[1]));
            PyTuple_SET_ITEM(query_obj, 2, PyLong_FromLong(query->query_obj[2]));
            PyTuple_SET_ITEM(query_obj, 3, PyLong_FromLong(query->query_obj[3]));
            dict_set_item(res, "query_obj", query_obj);
            Py_DECREF(query_obj);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLRenderbuffer_class) {
            MGLRenderbuffer * renderbuffer = (MGLRenderbuffer *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", renderbuffer->wrapper);
            dict_set_item(res, "context", (PyObject *)renderbuffer->context);
            dict_set_item(res, "renderbuffer_obj", renderbuffer->renderbuffer_obj);
            dict_set_item(res, "width", renderbuffer->width);
            dict_set_item(res, "height", renderbuffer->height);
            dict_set_item(res, "depth", renderbuffer->depth);
            dict_set_item(res, "components", renderbuffer->components);
            dict_set_item(res, "levels", renderbuffer->levels);
            dict_set_item(res, "samples", renderbuffer->samples);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLSampler_class) {
            MGLSampler * sampler = (MGLSampler *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", sampler->wrapper);
            dict_set_item(res, "context", (PyObject *)sampler->context);
            dict_set_item(res, "sampler_obj", sampler->sampler_obj);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLScope_class) {
            MGLScope * scope = (MGLScope *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", scope->wrapper);
            dict_set_item(res, "context", (PyObject *)scope->context);
            dict_set_item(res, "framebuffer", scope->framebuffer);
            dict_set_item(res, "old_framebuffer", scope->old_framebuffer);

            PyObject * bindings = PyTuple_New(3);
            PyObject * bindings_samplers = PyTuple_New(scope->num_samplers);
            MGLScopeBinding * it = scope->bindings;
            for (int i = 0; i < scope->num_samplers; ++i) {
                PyObject * binding = PyTuple_New(2);
                PyTuple_SET_ITEM(binding, 0, it->object);
                PyTuple_SET_ITEM(binding, 1, PyLong_FromLong(it->binding));
                PyTuple_SET_ITEM(bindings_samplers, 0, binding);
                it += 1;
            }
            PyObject * bindings_uniform_buffers = PyTuple_New(scope->num_uniform_buffers);
            for (int i = 0; i < scope->num_uniform_buffers; ++i) {
                PyObject * binding = PyTuple_New(2);
                PyTuple_SET_ITEM(binding, 0, it->object);
                PyTuple_SET_ITEM(binding, 1, PyLong_FromLong(it->binding));
                PyTuple_SET_ITEM(bindings_samplers, 0, binding);
                it += 1;
            }
            PyObject * bindings_storage_buffers = PyTuple_New(scope->num_storage_buffers);
            for (int i = 0; i < scope->num_storage_buffers; ++i) {
                PyObject * binding = PyTuple_New(2);
                PyTuple_SET_ITEM(binding, 0, it->object);
                PyTuple_SET_ITEM(binding, 1, PyLong_FromLong(it->binding));
                PyTuple_SET_ITEM(bindings_samplers, 0, binding);
                it += 1;
            }
            PyTuple_SET_ITEM(bindings, 0, bindings_samplers);
            PyTuple_SET_ITEM(bindings, 1, bindings_uniform_buffers);
            PyTuple_SET_ITEM(bindings, 2, bindings_storage_buffers);
            dict_set_item(res, "bindings", bindings);
            Py_DECREF(bindings);

            dict_set_item(res, "num_samplers", scope->num_samplers);
            dict_set_item(res, "num_uniform_buffers", scope->num_uniform_buffers);
            dict_set_item(res, "num_storage_buffers", scope->num_storage_buffers);
            dict_set_item(res, "enable_only", scope->enable_only);
            dict_set_item(res, "old_enable_only", scope->old_enable_only);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLTexture_class) {
            MGLTexture * texture = (MGLTexture *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", texture->wrapper);
            dict_set_item(res, "context", (PyObject *)texture->context);
            dict_set_item(res, "texture_obj", texture->texture_obj);
            dict_set_item(res, "texture_target", texture->texture_target);
            dict_set_item(res, "width", texture->width);
            dict_set_item(res, "height", texture->height);
            dict_set_item(res, "depth", texture->depth);
            dict_set_item(res, "components", texture->components);
            dict_set_item(res, "levels", texture->levels);
            dict_set_item(res, "samples", texture->samples);
            return res;
        }

        if (mglo->ob_base.ob_type == mglo->context->MGLVertexArray_class) {
            MGLVertexArray * vertex_array = (MGLVertexArray *)obj;

            PyObject * res = PyDict_New();
            dict_set_item(res, "self", obj);
            dict_set_item(res, "wrapper", vertex_array->wrapper);
            dict_set_item(res, "context", (PyObject *)vertex_array->context);
            dict_set_item(res, "vertex_array_obj", vertex_array->vertex_array_obj);
            dict_set_item(res, "max_vertices", vertex_array->max_vertices);
            return res;
        }
    }

    return 0;
}
