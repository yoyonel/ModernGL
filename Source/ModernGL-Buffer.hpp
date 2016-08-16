#pragma once

PyObject * NewVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * DeleteVertexBuffer(PyObject * self, PyObject * args);
PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args);
PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args);
PyObject * DeleteStorageBuffer(PyObject * self, PyObject * args);

PyObject * UpdateVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UseUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_NewVertexBuffer(PyObject * self);
PyObject * Dummy_NewIndexBuffer(PyObject * self);
PyObject * Dummy_NewUniformBuffer(PyObject * self);
PyObject * Dummy_NewStorageBuffer(PyObject * self);

PyObject * Dummy_DeleteVertexBuffer(PyObject * self);
PyObject * Dummy_DeleteIndexBuffer(PyObject * self);
PyObject * Dummy_DeleteUniformBuffer(PyObject * self);
PyObject * Dummy_DeleteStorageBuffer(PyObject * self);

PyObject * Dummy_UpdateVertexBuffer(PyObject * self);
PyObject * Dummy_UpdateUniformBuffer(PyObject * self);
PyObject * Dummy_UpdateIndexBuffer(PyObject * self);
PyObject * Dummy_UpdateStorageBuffer(PyObject * self);

PyObject * Dummy_UseStorageBuffer(PyObject * self);
PyObject * Dummy_UseUniformBuffer(PyObject * self);

PyObject * Dummy_ReadStorageBuffer(PyObject * self);
