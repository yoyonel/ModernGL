#pragma once
#include "context.hpp"

struct MGLTexture;

struct MGLSampler : public MGLContextObject {
    MGLTexture * texture;
    int sampler_obj;
};

extern PyType_Spec MGLSampler_spec;
PyObject * MGLContext_meth_sampler(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
