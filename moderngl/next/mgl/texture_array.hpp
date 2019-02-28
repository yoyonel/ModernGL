#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLDataType;

struct MGLTextureArray {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLDataType * data_type;
    int texture_obj;
    int texture_target;
    int width;
    int height;
    int array_size;
    int components;
    int levels;
};

extern PyType_Spec MGLTextureArray_spec;
PyObject * MGLContext_meth_texture_array(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
