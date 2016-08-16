#pragma once

PyObject * NewVertexArray(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewAdvancedVertexArray(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DeleteVertexArray(PyObject * self, PyObject * args);

PyObject * EnableAttributes(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DisableAttributes(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_NewVertexArray(PyObject * self);
PyObject * Dummy_NewAdvancedVertexArray(PyObject * self);
PyObject * Dummy_DeleteVertexArray(PyObject * self);

PyObject * Dummy_EnableAttributes(PyObject * self);
PyObject * Dummy_DisableAttributes(PyObject * self);
