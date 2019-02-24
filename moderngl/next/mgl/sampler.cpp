#include "sampler.hpp"
#include "context.hpp"
#include "texture.hpp"

#include "internal/wrapper.hpp"

#include "internal/modules.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"

/* MGLContext.sampler(texture)
 */
PyObject * MGLContext_meth_sampler(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    if (nargs != 1) {
        // TODO: error
        return 0;
    }

    PyObject * texture = args[0];

    MGLSampler * sampler = MGLContext_new_object(self, Sampler);

    const GLMethods & gl = self->gl;
    gl.GenSamplers(1, (GLuint *)&sampler->sampler_obj);

    if (!sampler->sampler_obj) {
        PyErr_Format(moderngl_error, "cannot create sampler");
        Py_DECREF(sampler);
        return 0;
    }

    gl.SamplerParameteri(sampler->sampler_obj, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl.SamplerParameteri(sampler->sampler_obj, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    SLOT(sampler->wrapper, PyObject, Sampler_class_texture) = texture;
    return NEW_REF(sampler->wrapper);
}

/* MGLSampler.use(location)
 */
PyObject * MGLSampler_meth_use(MGLSampler * self, PyObject * arg) {
    PyObject * wrapper = SLOT(self->wrapper, PyObject, Sampler_class_texture);
    MGLTexture * texture = SLOT(wrapper, MGLTexture, Texture_class_mglo);

    int location = PyLong_AsLong(arg);
    self->context->bind_sampler(location, texture->texture_target, texture->texture_obj, self->sampler_obj);
    Py_RETURN_NONE;
}

int MGLSampler_set_filter(MGLSampler * self, PyObject * value) {
    return 0;
}

enum MGLSamplerWrapModes {
    MGL_CLAMP_TO_EDGE = 0x01,
    MGL_REPEAT = 0x02,
    MGL_MIRRORED_REPEAT = 0x04,
    MGL_MIRROR_CLAMP_TO_EDGE = 0x08,
    MGL_CLAMP_TO_BORDER = 0x10,
};

int MGLSampler_set_wrap(MGLSampler * self, PyObject * value) {
    int wrap = PyLong_AsLong(value);
    SLOT(self->wrapper, PyObject, Sampler_class_wrap) = PyLong_FromLong(wrap);
    switch (((unsigned char *)&wrap)[0]) {
        case 0:
        case MGL_CLAMP_TO_EDGE:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            break;
        case MGL_REPEAT:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_REPEAT);
            break;
        case MGL_MIRRORED_REPEAT:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            break;
        case MGL_MIRROR_CLAMP_TO_EDGE:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
            break;
        case MGL_CLAMP_TO_BORDER:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            break;
        default:
            // TODO: error
            return -1;
    }
    switch (((unsigned char *)&wrap)[1]) {
        case 0:
        case MGL_CLAMP_TO_EDGE:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case MGL_REPEAT:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case MGL_MIRRORED_REPEAT:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
        case MGL_MIRROR_CLAMP_TO_EDGE:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
            break;
        case MGL_CLAMP_TO_BORDER:
    		self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            break;
        default:
            // TODO: error
            return -1;
    }
    PyObject * wrapper = SLOT(self->wrapper, PyObject, Sampler_class_texture);
    MGLTexture * texture = SLOT(wrapper, MGLTexture, Texture_class_mglo);
    if (texture->texture_target == GL_TEXTURE_3D) {
        switch (((unsigned char *)&wrap)[2]) {
            case 0:
            case MGL_CLAMP_TO_EDGE:
                self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                break;
            case MGL_REPEAT:
                self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_R, GL_REPEAT);
                break;
            case MGL_MIRRORED_REPEAT:
                self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
                break;
            case MGL_MIRROR_CLAMP_TO_EDGE:
                self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_R, GL_MIRROR_CLAMP_TO_EDGE);
                break;
            case MGL_CLAMP_TO_BORDER:
                self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
                break;
            default:
                // TODO: error
                return -1;
        }
    } else if (((unsigned char *)&wrap)[2]) {
        return -1;
    }
    return 0;
}

int MGLSampler_set_anisotropy(MGLSampler * self, PyObject * value) {
    return 0;
}

int MGLSampler_set_min_lod(MGLSampler * self, PyObject * value) {
    int min_lod = PyLong_AsLong(value);
    SLOT(self->wrapper, PyObject, Sampler_class_min_lod) = NEW_REF(value);
	self->context->gl.SamplerParameterf(self->sampler_obj, GL_TEXTURE_MIN_LOD, min_lod);
    return 0;
}

int MGLSampler_set_max_lod(MGLSampler * self, PyObject * value) {
    int max_lod = PyLong_AsLong(value);
    SLOT(self->wrapper, PyObject, Sampler_class_max_lod) = NEW_REF(value);
	self->context->gl.SamplerParameterf(self->sampler_obj, GL_TEXTURE_MAX_LOD, max_lod);
    return 0;
}

#if PY_VERSION_HEX >= 0x03070000

PyMethodDef MGLSampler_methods[] = {
    {"use", (PyCFunction)MGLSampler_meth_use, METH_O, 0},
    {0},
};

#else

PyMethodDef MGLSampler_methods[] = {
    {"use", (PyCFunction)MGLSampler_meth_use, METH_O, 0},
    {0},
};

#endif

PyGetSetDef MGLSampler_getset[] = {
    {"filter", 0, (setter)MGLSampler_set_filter, 0, 0},
    {"wrap", 0, (setter)MGLSampler_set_wrap, 0, 0},
    {"anisotropy", 0, (setter)MGLSampler_set_anisotropy, 0, 0},
    {"min_lod", 0, (setter)MGLSampler_set_min_lod, 0, 0},
    {"max_lod", 0, (setter)MGLSampler_set_max_lod, 0, 0},
    {0},
};

PyType_Slot MGLSampler_slots[] = {
    {Py_tp_methods, MGLSampler_methods},
    {Py_tp_getset, MGLSampler_getset},
    {0},
};

PyType_Spec MGLSampler_spec = {
    mgl_ext ".Sampler",
    sizeof(MGLSampler),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLSampler_slots,
};
