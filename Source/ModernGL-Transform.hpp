#pragma once

PyObject * TransformPoints(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformTriangles(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformLines(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformLineStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformLineLoop(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * TransformTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_TransformPoints(PyObject * self);
PyObject * Dummy_TransformTriangles(PyObject * self);
PyObject * Dummy_TransformTriangleStrip(PyObject * self);
PyObject * Dummy_TransformTriangleFan(PyObject * self);
PyObject * Dummy_TransformLines(PyObject * self);
PyObject * Dummy_TransformLineStrip(PyObject * self);
PyObject * Dummy_TransformLineLoop(PyObject * self);
PyObject * Dummy_TransformLineStripAdjacency(PyObject * self);
PyObject * Dummy_TransformLinesAdjacency(PyObject * self);
PyObject * Dummy_TransformTriangleStripAdjacency(PyObject * self);
PyObject * Dummy_TransformTrianglesAdjacency(PyObject * self);
