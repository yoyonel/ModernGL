#pragma once
#include "mgl.hpp"

#include "internal/opengl/gl_methods.hpp"

struct MGLContext;

struct MGLRecorder {
    PyObject_HEAD
    MGLContext * context;
};

extern PyTypeObject * MGLRecorder_class;
PyObject * MGLContext_meth_replay(MGLContext * self, PyObject * bytecode);

void initialize_recording();