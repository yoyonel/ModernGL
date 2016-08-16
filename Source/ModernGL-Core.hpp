#pragma once

PyObject * Viewport(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * Clear(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * GetInfo(PyObject * self);

PyObject * PointSize(PyObject * self, PyObject * args);
PyObject * LineSize(PyObject * self, PyObject * args);

PyObject * EnableOnly(PyObject * self, PyObject * args);

PyObject * EnableBlend(PyObject * self);
PyObject * EnableCullFace(PyObject * self);
PyObject * EnableDepthTest(PyObject * self);
PyObject * EnableMultisample(PyObject * self);

PyObject * DisableBlend(PyObject * self);
PyObject * DisableCullFace(PyObject * self);
PyObject * DisableDepthTest(PyObject * self);
PyObject * DisableMultisample(PyObject * self);

// Dummy

PyObject * Dummy_Viewport(PyObject * self);
PyObject * Dummy_Clear(PyObject * self);
PyObject * Dummy_GetInfo(PyObject * self);

PyObject * Dummy_PointSize(PyObject * self);
PyObject * Dummy_LineSize(PyObject * self);

PyObject * Dummy_EnableOnly(PyObject * self);

PyObject * Dummy_EnableBlend(PyObject * self);
PyObject * Dummy_EnableCullFace(PyObject * self);
PyObject * Dummy_EnableDepthTest(PyObject * self);
PyObject * Dummy_EnableMultisample(PyObject * self);

PyObject * Dummy_DisableBlend(PyObject * self);
PyObject * Dummy_DisableCullFace(PyObject * self);
PyObject * Dummy_DisableDepthTest(PyObject * self);
PyObject * Dummy_DisableMultisample(PyObject * self);
