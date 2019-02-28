#include "texture_cube.hpp"
#include "buffer.hpp"
#include "context.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"
#include "internal/data_type.hpp"

/* MGLContext.texture_cube(size, components, data, levels, alignment, dtype)
 */
PyObject * MGLContext_meth_texture_cube(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 6) {
        // TODO: error
        return 0;
    }

    int size = PyLong_AsLong(args[0]);
    int components = PyLong_AsLong(args[1]);
    PyObject * data = args[2];
    int levels = PyLong_AsLong(args[3]);
    int alignment = PyLong_AsLong(args[4]);
    MGLDataType * data_type = from_dtype(args[5]);

    if (!data_type) {
        PyErr_Format(moderngl_error, "invalid dtype");
        return 0;
    }

    int max_levels = -1;
    {
        int tem_size = size;
        while (tem_size) {
            max_levels += 1;
            tem_size >>= 1;
        }
    }

    if (levels < 0 || levels > max_levels) {
        levels = max_levels;
    }

    int expected_size = size * components * data_type->size;
    expected_size = (expected_size + alignment - 1) / alignment * alignment;
    expected_size = expected_size * size * 6;

    int texture_target = GL_TEXTURE_CUBE_MAP;
    int pixel_type = data_type->gl_type;
    int base_format = data_type->base_format[components];
    int internal_format = data_type->internal_format[components];

    MGLTextureCube * texture = MGLContext_new_object(self, TextureCube);

    texture->data_type = data_type;
    texture->texture_target = texture_target;
    texture->size = size;
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
        const char * ptr[6] = {
            (const char *)buf + expected_size * 0 / 6,
            (const char *)buf + expected_size * 1 / 6,
            (const char *)buf + expected_size * 2 / 6,
            (const char *)buf + expected_size * 3 / 6,
            (const char *)buf + expected_size * 4 / 6,
            (const char *)buf + expected_size * 5 / 6,
        };
        // if (gl.TexStorage3D) {
        //     gl.TexStorage3D(texture_target, levels, internal_format, width, height, array_size);
        //     gl.TexSubImage3D(texture_target, 0, 0, 0, 0, width, height, array_size, base_format, pixel_type, buf);
        // } else {
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[0]);
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[1]);
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[2]);
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[3]);
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[4]);
            gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internal_format, size, size, 0, base_format, pixel_type, ptr[5]);
        // }
    } else {
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
        gl.TexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, internal_format, size, size, 0, base_format, pixel_type, 0);
    }

    return NEW_REF(texture->wrapper);
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLTextureCube_methods[] = {
    {0},
};

#else

PyMethodDef MGLTextureCube_methods[] = {
    {0},
};

#endif

PyGetSetDef MGLTextureCube_getset[] = {
    {0},
};

PyType_Slot MGLTextureCube_slots[] = {
    {Py_tp_methods, MGLTextureCube_methods},
    {Py_tp_getset, MGLTextureCube_getset},
    {0},
};

PyType_Spec MGLTextureCube_spec = {
    mgl_ext ".Texture",
    sizeof(MGLTextureCube),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLTextureCube_slots,
};
