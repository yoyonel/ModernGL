#pragma once
#include "mgl.hpp"

struct MGLContext;

struct MGLSampler {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    int sampler_obj;
    int texture_target;
    int texture_obj;
    int dimensions;
};

extern PyType_Spec MGLSampler_spec;
PyObject * MGLContext_meth_sampler(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
