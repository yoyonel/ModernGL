#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLDataType;

struct MGLTextureCube {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLDataType * data_type;
    int texture_obj;
    int texture_target;
    int size;
    int components;
    int levels;
};

extern PyType_Spec MGLTextureCube_spec;
PyObject * MGLContext_meth_texture_cube(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
