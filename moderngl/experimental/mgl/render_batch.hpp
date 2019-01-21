#pragma once
#include "mgl.hpp"
#include "vertex_array.hpp"

struct MGLContext;

enum MGLRenderTask {
    MGL_RENDER_TASK,
};

struct MGLRenderBatchTask {
    int task;
    MGLVertexArray * vertex_array;
    union {
        struct {
            int mode;
            int vertices;
            int first;
            int instances;
            unsigned long long color_mask;
            bool depth_mask;
        } render_args;
    };
};

struct MGLRenderBatch {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLRenderBatchTask * tasks;
    int num_tasks;
};

extern PyType_Spec MGLRenderBatch_spec;
PyObject * MGLContext_meth_render_batch(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
