#include "sampler.hpp"
#include "context.hpp"
#include "texture.hpp"

#include "internal/wrapper.hpp"

#include "internal/compare_func.hpp"
#include "internal/tools.hpp"
#include "internal/glsl.hpp"

int MGLSampler_set_filter(MGLSampler * self, PyObject * value);
int MGLSampler_set_wrap(MGLSampler * self, PyObject * value);
int MGLSampler_set_anisotropy(MGLSampler * self, PyObject * value);
int MGLSampler_set_compare_func(MGLSampler * self, PyObject * value);
int MGLSampler_set_lod_range(MGLSampler * self, PyObject * value);
int MGLSampler_set_lod_bias(MGLSampler * self, PyObject * value);
int MGLSampler_set_border(MGLSampler * self, PyObject * value);
int MGLSampler_set_texture(MGLSampler * self, PyObject * value);

/* MGLContext.sampler(texture)
 */
PyObject * MGLContext_meth_sampler(MGLContext * self, PyObject * const * args, Py_ssize_t nargs) {
    ensure_num_args(8);

    MGLSampler * sampler = MGLContext_new_object(self, Sampler);

    const GLMethods & gl = self->gl;
    gl.GenSamplers(1, (GLuint *)&sampler->sampler_obj);

    if (!sampler->sampler_obj) {
        PyErr_Format(moderngl_error, "cannot create sampler");
        Py_DECREF(sampler);
        return 0;
    }

    SLOT(sampler->wrapper, PyObject, Sampler_class_filter) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_wrap) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_anisotropy) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_compare_func) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_lod_range) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_lod_bias) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_border) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_texture) = 0;
    SLOT(sampler->wrapper, PyObject, Sampler_class_extra) = 0;

    if (MGLSampler_set_texture(sampler, args[0])) {
        Py_DECREF(sampler);
        return 0;
    }

    if (MGLSampler_set_filter(sampler, args[1])) {
        Py_DECREF(sampler);
        return 0;
    }

    if (MGLSampler_set_wrap(sampler, args[2])) {
        Py_DECREF(sampler);
        return 0;
    }

    if (MGLSampler_set_compare_func(sampler, args[3])) {
        Py_DECREF(sampler);
        return 0;
    }

    if (args[4] != Py_None) {
        if (MGLSampler_set_anisotropy(sampler, args[4])) {
            Py_DECREF(sampler);
            return 0;
        }
    } else {
        Py_XSETREF(SLOT(sampler->wrapper, PyObject, Sampler_class_anisotropy), PyFloat_FromDouble(1.0));
    }

    if (args[5] != Py_None) {
        if (MGLSampler_set_lod_range(sampler, args[5])) {
            Py_DECREF(sampler);
            return 0;
        }
    } else {
        Py_XSETREF(SLOT(sampler->wrapper, PyObject, Sampler_class_lod_range), int_tuple(-1000, 1000));
    }

    if (args[6] != Py_None) {
        if (MGLSampler_set_lod_bias(sampler, args[6])) {
            Py_DECREF(sampler);
            return 0;
        }
    } else {
        Py_XSETREF(SLOT(sampler->wrapper, PyObject, Sampler_class_lod_bias), PyFloat_FromDouble(0.0));
    }

    if (args[7] != Py_None) {
        if (MGLSampler_set_border(sampler, args[7])) {
            Py_DECREF(sampler);
            return 0;
        }
    } else {
        Py_XSETREF(SLOT(sampler->wrapper, PyObject, Sampler_class_border), float_tuple(0.0, 0.0, 0.0, 0.0));
    }

    return NEW_REF(sampler->wrapper);
}

/* MGLSampler.use(location)
 */
PyObject * MGLSampler_meth_use(MGLSampler * self, PyObject * arg) {
    int location = PyLong_AsLong(arg);
    self->context->bind_sampler(location, self->texture->texture_target, self->texture->texture_obj, self->sampler_obj);

    if (PyErr_Occurred()) {
        return 0;
    }

    Py_RETURN_NONE;
}

int MGLSampler_set_filter(MGLSampler * self, PyObject * value) {
    int min_filter;
    int mag_filter;
    if (PyLong_Check(value)) {
        min_filter = PyLong_AsLong(value);
        mag_filter = min_filter;
    } else {
        PyObject * filter = PySequence_Fast(value, "not iterable");
        if (!filter) {
            return -1;
        }

        if (PySequence_Fast_GET_SIZE(filter) != 2) {
            Py_DECREF(filter);
    		PyErr_Format(moderngl_error, "invalid filter");
            return -1;
        }

        min_filter = PyLong_AsLong(PySequence_Fast_GET_ITEM(filter, 0));
        mag_filter = PyLong_AsLong(PySequence_Fast_GET_ITEM(filter, 1));
        Py_DECREF(filter);
    }

 	const GLMethods & gl = self->context->gl;
	gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MIN_FILTER, min_filter);
	gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MAG_FILTER, mag_filter);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_filter), int_tuple(min_filter, mag_filter));

    if (PyErr_Occurred()) {
        return -1;
    }

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
    static const int pnames[] = {GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_T, GL_TEXTURE_WRAP_R};

    int wrap = PyLong_AsLong(value);

    if (wrap >> (8 * self->texture->dimensions)) {
        PyErr_Format(moderngl_error, "invalid wrap");
        return -1;
    }

 	const GLMethods & gl = self->context->gl;

    for (int i = 0; i < self->texture->dimensions; ++i) {
        switch (((unsigned char *)&wrap)[i]) {
            case 0:
            case MGL_CLAMP_TO_EDGE:
                gl.SamplerParameteri(self->sampler_obj, pnames[i], GL_CLAMP_TO_EDGE);
                break;
            case MGL_REPEAT:
                gl.SamplerParameteri(self->sampler_obj, pnames[i], GL_REPEAT);
                break;
            case MGL_MIRRORED_REPEAT:
                gl.SamplerParameteri(self->sampler_obj, pnames[i], GL_MIRRORED_REPEAT);
                break;
            case MGL_MIRROR_CLAMP_TO_EDGE:
                gl.SamplerParameteri(self->sampler_obj, pnames[i], GL_MIRROR_CLAMP_TO_EDGE);
                break;
            case MGL_CLAMP_TO_BORDER:
                gl.SamplerParameteri(self->sampler_obj, pnames[i], GL_CLAMP_TO_BORDER);
                break;
            default:
                PyErr_Format(moderngl_error, "invalid wrap");
                return -1;
        }
    }

    if (PyErr_Occurred()) {
        return -1;
    }

    return 0;
}

int MGLSampler_set_border(MGLSampler * self, PyObject * value) {
    float color[4] = {};

    if (PyNumber_Check(value)) {
        color[0] = (float)PyFloat_AsDouble(value);
        color[1] = color[0];
        color[2] = color[0];
        color[3] = color[0];
    } else {
        PyObject * border = PySequence_Fast(value, "not iterable");
        if (!border) {
            return -1;
        }

        switch (PySequence_Fast_GET_SIZE(border)) {
            case 4:
                color[3] = (float)PyFloat_AsDouble(PySequence_Fast_GET_ITEM(border, 3));
            case 3:
                color[2] = (float)PyFloat_AsDouble(PySequence_Fast_GET_ITEM(border, 2));
            case 2:
                color[1] = (float)PyFloat_AsDouble(PySequence_Fast_GET_ITEM(border, 1));
            case 1:
                color[0] = (float)PyFloat_AsDouble(PySequence_Fast_GET_ITEM(border, 0));
                break;
            default:
                Py_DECREF(border);
                PyErr_Format(moderngl_error, "invalid border");
                return -1;
        }

        Py_DECREF(border);
    }

	self->context->gl.SamplerParameterfv(self->sampler_obj, GL_TEXTURE_BORDER_COLOR, color);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_border), float_tuple(color[0], color[1], color[2], color[3]));

    if (PyErr_Occurred()) {
        return -1;
    }

    return 0;
}

int MGLSampler_set_anisotropy(MGLSampler * self, PyObject * value) {
	float anisotropy = (float)PyFloat_AsDouble(value);
    if (anisotropy < 1.0) {
        anisotropy = 1.0;
    }
    // TODO: clamp with max value
	self->context->gl.SamplerParameterf(self->sampler_obj, GL_TEXTURE_MAX_ANISOTROPY, anisotropy);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_anisotropy), PyFloat_FromDouble(anisotropy));
    return 0;
}

int MGLSampler_set_compare_func(MGLSampler * self, PyObject * value) {
	const GLMethods & gl = self->context->gl;
    if (value == Py_None) {
		gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_MODE, GL_NONE);
        Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_compare_func), NEW_REF(Py_None));
        return 0;
    }

    const char * compare_func_str = PyUnicode_AsUTF8(value);
	int compare_func = compare_func_from_str(compare_func_str);
	if (!compare_func) {
        PyErr_Format(moderngl_error, "invalid compare_func");
        return -1;
	}

    gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_COMPARE_FUNC, compare_func);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_compare_func), PyUnicode_FromString(compare_func_str));

    if (PyErr_Occurred()) {
        return -1;
    }

    return 0;
}

int MGLSampler_set_lod_range(MGLSampler * self, PyObject * value) {
    PyObject * lod_range = PySequence_Fast(value, "not iterable");
    if (!lod_range) {
        return -1;
    }

    if (PySequence_Fast_GET_SIZE(lod_range) != 2) {
        Py_DECREF(lod_range);
        PyErr_Format(moderngl_error, "invalid lod_range");
        return -1;
    }

    int min_lod = PyLong_AsLong(PySequence_Fast_GET_ITEM(lod_range, 0));
    int max_lod = PyLong_AsLong(PySequence_Fast_GET_ITEM(lod_range, 1));
    Py_DECREF(lod_range);

	self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MIN_LOD, min_lod);
	self->context->gl.SamplerParameteri(self->sampler_obj, GL_TEXTURE_MAX_LOD, max_lod);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_lod_range), int_tuple(min_lod, max_lod));

    if (PyErr_Occurred()) {
        return -1;
    }

    return 0;
}

int MGLSampler_set_lod_bias(MGLSampler * self, PyObject * value) {
	float lod_bias = (float)PyFloat_AsDouble(value);
	self->context->gl.SamplerParameterf(self->sampler_obj, GL_TEXTURE_LOD_BIAS, lod_bias);
    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_lod_bias), PyFloat_FromDouble(lod_bias));

    if (PyErr_Occurred()) {
        return -1;
    }

    return 0;
}

int MGLSampler_set_texture(MGLSampler * self, PyObject * value) {
    if (value->ob_type != Texture_class) {
        PyErr_Format(moderngl_error, "invalid texture");
        return -1;
    }

    self->texture = SLOT(value, MGLTexture, Texture_class_mglo);;

    Py_XSETREF(SLOT(self->wrapper, PyObject, Sampler_class_texture), NEW_REF(value));
    return 0;
}

void MGLSampler_dealloc(MGLSampler * self) {
    Py_TYPE(self)->tp_free(self);
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
    {"compare_func", 0, (setter)MGLSampler_set_compare_func, 0, 0},
    {"border", 0, (setter)MGLSampler_set_border, 0, 0},
    {"lod_range", 0, (setter)MGLSampler_set_lod_range, 0, 0},
    {"lod_bias", 0, (setter)MGLSampler_set_lod_bias, 0, 0},
    {"texture", 0, (setter)MGLSampler_set_texture, 0, 0},
    {0},
};

PyType_Slot MGLSampler_slots[] = {
    {Py_tp_methods, MGLSampler_methods},
    {Py_tp_getset, MGLSampler_getset},
    {Py_tp_dealloc, (void *)MGLSampler_dealloc},
    {0},
};

PyType_Spec MGLSampler_spec = {
    "moderngl.mgl.new.MGLSampler",
    sizeof(MGLSampler),
    0,
    Py_TPFLAGS_DEFAULT,
    MGLSampler_slots,
};
