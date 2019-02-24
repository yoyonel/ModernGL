#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLDataType;

struct MGLTexture {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLDataType * data_type;
    int texture_obj;
    int texture_target;
    int width;
    int height;
    int depth;
    int components;
    int levels;
    int samples;
};

extern PyType_Spec MGLTexture_spec;
PyObject * MGLContext_meth_texture(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
