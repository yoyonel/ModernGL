#pragma once

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DeleteFramebuffer(PyObject * self, PyObject * args);
PyObject * UseFramebuffer(PyObject * self, PyObject * args);

PyObject * SetDefaultFramebuffer(PyObject * self, PyObject * args);
PyObject * UseDefaultFramebuffer(PyObject * self);

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadPixels(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadDepthPixels(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_NewFramebuffer(PyObject * self);
PyObject * Dummy_DeleteFramebuffer(PyObject * self);
PyObject * Dummy_UseFramebuffer(PyObject * self);

PyObject * Dummy_SetDefaultFramebuffer(PyObject * self);
PyObject * Dummy_UseDefaultFramebuffer(PyObject * self);

PyObject * Dummy_ReadPixel(PyObject * self);
PyObject * Dummy_ReadPixels(PyObject * self);
PyObject * Dummy_ReadDepthPixel(PyObject * self);
PyObject * Dummy_ReadDepthPixels(PyObject * self);
