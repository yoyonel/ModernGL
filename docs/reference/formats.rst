Buffer Formats
==============

.. py:module:: moderngl
.. py:currentmodule:: moderngl

TODO
----

* ~~initial commit with basic content from https://github.com/moderngl/moderngl/issues/306~~
* convert to rst / fix doc build warnings
* splice in Szabolcs' description of trailing ``\i``, etc. Ditch mention of
  divisors.
* Describe dtypes?
* study the issue carefully for suggestions I missed
* migrate to docs/next/reference?

---

Description
-----------

A buffer format is a short string describing the layout of data in a vertex
buffer array (VBO).

These are used in the :py:meth:`Context.vertex_array()` constructor,
as the 2nd component of the `content` arg.
For example::

    # a 2D triangle (ie. three (x, y) vertices)
    verts = [
         0.0, 0.9,
        -0.5, 0.0,
         0.5, 0.0,
    ]

    # pack all six values into a binary array of C floats
    verts_buffer = struct.pack("6f", *verts)

    # put the array into a VBO
    vbo = ctx.buffer(verts_buffer)

    # use the VBO in a VAO
    vao = ctx.vertex_array(
        shader_program,
        [
            (vbo, "2f", "in_vert"),
        ]
        index_buffer_object
    )

The line ``(vbo, "2f", "in_vert")`` indicates that the ``vbo`` buffer contains
an array of values to be passed to the shader's ``in_vert`` variable, and each
value in the array consists of two floats (``"2f"``).

The ``"6f"`` parameter used by ``struct.pack`` looks similar to the ``"2f"``
format used by :py:meth:`Context.vertex_array()`. But they are not the same.
The latter uses a syntax unique to ``moderngl``, as documented on this page.

By default, each float occupies 4 bytes, but the type of this data can be
modified with an optional trailing size, such as ``"2f8"``, indicating two
doubles (ie eight byte floats.)

A final optional slash and character, for example `/i`, indicates the divisor
size. **TODO:** explain this better.

Single values
-------------

The resulting overall form of a format is:

    ``[count] type [size] [/usage]``

For example: ``"3f2/i"``

Where:
* count is an optional integer, defaulting to `1`.
* type is a single character indicating data type (`f` float, `i` int, `u` unsigned int, `x` padding)
* size is an optional number of bytes used to store the type, defaulting to 4 for numeric types, or to 1 for padding bytes.
* usage is a single character indicating the divisor (`i`=1, `r`=0x7fffffff, `v`=0)

This results in the following possibilities:

| Type |             size 1            |            size 2 | size 4                    | size 8    |
|:----:|------------------------------:|------------------:|--------------------------:|----------:|
| f    | GL_UNSIGNED_BYTE (normalized) | GL_HALF_FLOAT     | GL_FLOAT | GL_DOUBLE |
| i    | GL_BYTE | GL_SHORT | GL_INT         |     -     |
| u    | GL_UNSIGNED_BYTE | GL_UNSIGNED_SHORT | GL_UNSIGNED_INT |     -     |
| x    | 1 byte              | 2 bytes  | 4 bytes                   | 8 bytes   |

There is no size 8 variant for `i` and `u`.

The entry for `f1` is _normalized_, ie. passing in unsigned bytes from 0 to 255 appear in the vertex shader as float values from 0.0 to 1.0. This is intended for passing in colors as unsigned bytes.

Multiple values
---------------

A buffer could contain multiple items of data. This is described by a format string containing multiple space-separated formats. For example, "`3f 3f1 x`" indicates a buffer that contains an array of:
* three floats (each on occupying the default four bytes)
* three unsigned bytes, which will be normalized before being passed to the shader
* one padding byte, for alignment.

.. toctree::
    :maxdepth: 2
