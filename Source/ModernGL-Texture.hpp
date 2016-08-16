#pragma once

PyObject * NewTexture(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateTexture(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DeleteTexture(PyObject * self, PyObject * args);

PyObject * BuildMipmaps(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * UseTexture(PyObject * self, PyObject * args);
PyObject * UseTextureAsImage(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * SetTextureFiltered(PyObject * self, PyObject * args);
PyObject * SetTextureMipmapped(PyObject * self, PyObject * args);
PyObject * SetTexturePixelated(PyObject * self, PyObject * args);

// Dummy

PyObject * Dummy_NewTexture(PyObject * self);
PyObject * Dummy_UpdateTexture(PyObject * self);
PyObject * Dummy_DeleteTexture(PyObject * self);

PyObject * Dummy_BuildMipmaps(PyObject * self);

PyObject * Dummy_UseTexture(PyObject * self);
PyObject * Dummy_UseTextureAsImage(PyObject * self);

PyObject * Dummy_SetTextureFiltered(PyObject * self);
PyObject * Dummy_SetTextureMipmapped(PyObject * self);
PyObject * Dummy_SetTexturePixelated(PyObject * self);
