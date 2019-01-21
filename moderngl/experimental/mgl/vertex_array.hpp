#pragma once
#include "mgl.hpp"

struct MGLContext;

struct MGLVertexArray {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    int vertex_array_obj;
    int max_vertices;
};

extern PyType_Spec MGLVertexArray_spec;
PyObject * MGLContext_meth_vertex_array(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
void MGLVertexArray_render_core(MGLVertexArray * self, int mode, int vertices, int first, int instances, unsigned long long color_mask, bool depth_mask);
