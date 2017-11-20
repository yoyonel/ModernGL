# Structure of ModernGL

The module has two layers:

- [Python layer](#python-layer)
- [C++ layer](#c-layer)

## Python layer

The documentation, type hints and the high level api is implemented in the python layer.

## C++ layer

> Same as the `ModernGL.mgl` module

The OpenGL calls are made in the C++ layer.
Types and methods implemented in this layer **should** be used in the Python layer only.

## Example

For example the [write] method of the [Buffer] class is implemented in the Buffer.cpp:

[write]: https://moderngl.readthedocs.io/en/stable/Buffers.html#ModernGL.Buffer.write
[Buffer]: https://moderngl.readthedocs.io/en/stable/Buffers.html#ModernGL.Buffer

```c++
PyObject * MGLBuffer_write(MGLBuffer * self, PyObject * args) {

  ...

  const GLMethods & gl = self->context->gl;
  gl.BindBuffer(GL_ARRAY_BUFFER, self->buffer_obj);
  gl.BufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, size, data);
  Py_RETURN_NONE;
}
```

This method is interfaced in the Python layer as follows:

```python
def write(self, data, *, offset=0) -> None:
  '''
    google style docstring
  '''
  self.mglo.write(data, offset)
```

The C++ implementation does not take any keyword arguments and no default values are specified.
The python layer is documented and type hinted properly.

Most of the objects have a `self.mglo` member.
For example the Buffer object's `mglo` member is an `MGLBuffer` object from the C++ layer.
The user **should not** access directly the C++ implementation.

And finally a feature implemented entirely in the Python layer:

```python
def detect_format(program, attributes) -> str:

    def fmt(attr):
        return attr.array_length * attr.dimension, attr.shape

    return ''.join('%d%s' % fmt(program.attributes[a]) for a in attributes)
```

## The Purpose of the Python layer

- Provides documentation
- Provides type hinting
- Provides linting support
- Provides an error when the module is not properly compiled
- Mocks linters and parsers when the C++ implementation is not compiled
- Wraps similar objects with the same class
- Converts the arguments passed to the C++ layer

## Files and folders

```s
[ModernGL]                # the python implementation of ModernGL (the Python layer)
  |-- [ext]               # external modules are allowed to add files here
  |-- [tk]                # tkinter connector
  |-- __init__.py         # this file exposes the constants and the classes
  |-- __main__.py         # the purpose of this file is to provide version info quickly
  |-- buffers.py          # Buffer and BufferAccess
  |-- common.py           # constants and their types
  |-- context.py          # The Context class and context creation
  |-- framebuffer.py      # Framebuffer class
  |-- members.py          # Program members and VertexArray members
  |-- mock.py             # Mock pylint and sphinx
  |-- programs.py         # Program, Shander and ComputeShader classes
  |-- renderbuffer.py     # Renderbuffer class
  |-- textures.py         # Texture class
  |-- vertex_arrays.py    # VertexArray class

[src]                     # The c++ implementation of ModernGL (the C++ layer)
  |-- ModernGL.cpp        # ...

[docs]                    # The documentation
  |-- ...

[tests]                   # The tests
  |-- ...

[extras]                  # Useful files for easy development
  |-- ...
```

> This document is not yet finished
