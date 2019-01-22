#pragma once
#include "mgl.hpp"

struct MGLContext;
struct MGLObject;
struct MGLFramebuffer;
struct MGLScope;
struct MGLVertexArray;

enum MGLBatchTaskCode {
    MGL_SCOPE_USE_TASK,
    MGL_VAO_SIMPLE_RENDER_TASK,
    MGL_FBO_SIMPLE_CLEAR_TASK,
};

struct MGLBatchTask {
    int task_code;
    union {
        MGLObject * object;
        MGLFramebuffer * framebuffer;
        MGLScope * scope;
        MGLVertexArray * vertex_array;
    };
    union {
        // struct {
        // } scope_use;
        struct {
            int mode;
            int vertices;
            unsigned long long color_mask;
            bool depth_mask;
        } vao_simple_render;
        struct {
            int attachment;
            int color_mask;
            unsigned char color[16];
        } fbo_simple_clear;
        char raw[32];
    };
};

struct MGLBatch {
    PyObject_HEAD
    PyObject * wrapper;
    MGLContext * context;
    MGLBatchTask * tasks;
    int num_tasks;
};

extern PyType_Spec MGLBatch_spec;
PyObject * MGLContext_meth_batch(MGLContext * self, PyObject * const * args, Py_ssize_t nargs);
