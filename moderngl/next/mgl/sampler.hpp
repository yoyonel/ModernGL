#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLTexture;

struct MGLSampler {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLTexture * texture;
    int sampler_obj;
};

extern PyType_Spec MGLSampler_spec;
PyObject * MGLContext_meth_sampler(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
