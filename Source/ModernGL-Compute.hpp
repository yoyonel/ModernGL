#pragma once

PyObject * NewComputeShader(PyObject * self, PyObject * args);
PyObject * DeleteComputeShader(PyObject * self, PyObject * args);
PyObject * RunComputeShader(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_NewComputeShader(PyObject * self);
PyObject * Dummy_DeleteComputeShader(PyObject * self);
PyObject * Dummy_RunComputeShader(PyObject * self);
