#pragma once

PyObject * NewProgram(PyObject * self, PyObject * args);
PyObject * NewTransformProgram(PyObject * self, PyObject * args);

PyObject * DeleteProgram(PyObject * self, PyObject * args);

PyObject * SetUniform(PyObject * self, PyObject * args);
PyObject * SetUniformMatrix(PyObject * self, PyObject * args);

// Dummy

PyObject * Dummy_NewProgram(PyObject * self);
PyObject * Dummy_NewTransformProgram(PyObject * self);

PyObject * Dummy_DeleteProgram(PyObject * self);

PyObject * Dummy_SetUniform(PyObject * self);
PyObject * Dummy_SetUniformMatrix(PyObject * self);
