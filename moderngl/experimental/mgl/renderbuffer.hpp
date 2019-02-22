#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLDataType;

struct MGLRenderbuffer {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLDataType * data_type;
    int renderbuffer_obj;
    int width;
    int height;
    int depth;
    int components;
    int levels;
    int samples;
};

extern PyType_Spec MGLRenderbuffer_spec;
PyObject * MGLContext_meth_renderbuffer(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
PyObject * MGLContext_meth_depth_renderbuffer(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
