#pragma once

PyObject * RenderPoints(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLines(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineLoop(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangles(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);

// Dummy

PyObject * Dummy_RenderPoints(PyObject * self);
PyObject * Dummy_RenderLines(PyObject * self);
PyObject * Dummy_RenderLineStrip(PyObject * self);
PyObject * Dummy_RenderLineLoop(PyObject * self);
PyObject * Dummy_RenderTriangles(PyObject * self);
PyObject * Dummy_RenderTriangleStrip(PyObject * self);
PyObject * Dummy_RenderTriangleFan(PyObject * self);
PyObject * Dummy_RenderLinesAdjacency(PyObject * self);
PyObject * Dummy_RenderLineStripAdjacency(PyObject * self);
PyObject * Dummy_RenderTrianglesAdjacency(PyObject * self);
PyObject * Dummy_RenderTriangleStripAdjacency(PyObject * self);
