#include "texture_array.hpp"
#include "buffer.hpp"
#include "context.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"
#include "internal/data_type.hpp"

/* MGLContext.texture_array(size, components, data, levels, alignment, dtype)
 */
PyObject * MGLContext_meth_texture_array(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 6) {
        // TODO: error
        return 0;
    }

    PyObject * size = args[0];
    int components = PyLong_AsLong(args[1]);
    PyObject * data = args[2];
    int levels = PyLong_AsLong(args[3]);
    int alignment = PyLong_AsLong(args[4]);
    MGLDataType * data_type = from_dtype(args[5]);

    size = PySequence_Fast(size, "size is not iterable");
    if (!size) {
        return 0;
    }

    int dims = (int)PySequence_Fast_GET_SIZE(size);
    if (dims != 3) {
        return 0;
    }

    int width = PyLong_AsLong(PySequence_Fast_GET_ITEM(size, 0));
    int height = PyLong_AsLong(PySequence_Fast_GET_ITEM(size, 1));
    int array_size = PyLong_AsLong(PySequence_Fast_GET_ITEM(size, 2));

    Py_DECREF(size);

    if (!data_type) {
        PyErr_Format(moderngl_error, "invalid dtype");
        return 0;
    }

    int max_levels = -1;
    {
        int size = width > height ? width : height;
        while (size) {
            max_levels += 1;
            size >>= 1;
        }
    }

    if (levels < 0 || levels > max_levels) {
        levels = max_levels;
    }

    int expected_size = width * components * data_type->size;
    expected_size = (expected_size + alignment - 1) / alignment * alignment;
    expected_size = expected_size * height * array_size;

    int texture_target = GL_TEXTURE_2D_ARRAY;
    int pixel_type = data_type->gl_type;
    int base_format = data_type->base_format[components];
    int internal_format = data_type->internal_format[components];

    MGLTextureArray * texture = MGLContext_new_object(self, TextureArray);

    texture->data_type = data_type;
    texture->texture_target = texture_target;
    texture->width = width;
    texture->height = height;
    texture->array_size = array_size;
    texture->components = components;
    texture->levels = levels;

    const GLMethods & gl = self->gl;
    gl.GenTextures(1, (GLuint *)&texture->texture_obj);

    if (!texture->texture_obj) {
        // TODO: error
        return 0;
    }

    self->bind_temp_texture(texture_target, texture->texture_obj);

    if (data != Py_None) {
        Py_buffer view = {};
        if (prepare_buffer(data, &view) < 0) {
            return 0;
        }
        void * buf = view.buf;
        bool contiguos = PyBuffer_IsContiguous(&view, 'C');
        self->set_alignment(alignment);
        if (!contiguos) {
            buf = malloc(expected_size);
            PyBuffer_ToContiguous(buf, &view, view.len, 'C');
        }
        if (gl.TexStorage3D) {
            gl.TexStorage3D(texture_target, levels, internal_format, width, height, array_size);
            gl.TexSubImage3D(texture_target, 0, 0, 0, 0, width, height, array_size, base_format, pixel_type, buf);
        } else {
            gl.TexImage3D(texture_target, 0, internal_format, width, height, array_size, 0, base_format, pixel_type, buf);
        }
    } else {
        gl.TexImage3D(texture_target, 0, internal_format, width, height, array_size, 0, base_format, pixel_type, 0);
    }

    return NEW_REF(texture->wrapper);
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLTextureArray_methods[] = {
    {0},
};

#else

PyMethodDef MGLTextureArray_methods[] = {
    {0},
};

#endif

PyGetSetDef MGLTextureArray_getset[] = {
    {0},
};

PyType_Slot MGLTextureArray_slots[] = {
    {Py_tp_methods, MGLTextureArray_methods},
    {Py_tp_getset, MGLTextureArray_getset},
    {0},
};

PyType_Spec MGLTextureArray_spec = {
    mgl_ext ".Texture",
    sizeof(MGLTextureArray),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLTextureArray_slots,
};
