#pragma once

PyObject * DebugInfo(PyObject * self);
PyObject * DebugVar(PyObject * self, PyObject * args);

// Dummy

PyObject * Dummy_DebugInfo(PyObject * self);
PyObject * Dummy_DebugVar(PyObject * self);
