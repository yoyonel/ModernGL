#pragma once

PyObject * NewVertexShader(PyObject * self, PyObject * args);
PyObject * NewFragmentShader(PyObject * self, PyObject * args);
PyObject * NewGeometryShader(PyObject * self, PyObject * args);
PyObject * NewTessControlShader(PyObject * self, PyObject * args);
PyObject * NewTessEvaluationShader(PyObject * self, PyObject * args);
PyObject * DeleteShader(PyObject * self, PyObject * args);

// Dummy

PyObject * Dummy_NewVertexShader(PyObject * self);
PyObject * Dummy_NewFragmentShader(PyObject * self);
PyObject * Dummy_NewGeometryShader(PyObject * self);
PyObject * Dummy_NewTessControlShader(PyObject * self);
PyObject * Dummy_NewTessEvaluationShader(PyObject * self);
PyObject * Dummy_DeleteShader(PyObject * self);
