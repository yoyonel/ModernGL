Buffer Formats
==============

.. py:module:: moderngl
.. py:currentmodule:: moderngl

TODO
----

- splice in Szabolcs' description of trailing ``\i``, etc. Is 'usage' a bad name? Figure out how 'divisors' are relevant, and whether they need to be mentioned.
- Describe dtypes?
- study the issue carefully for suggestions I missed
- migrate to docs/next/reference?

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

    # pack all six values into a binary array of C-like floats
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

The line ``(vbo, "2f", "in_vert")`` indicates that ``vbo`` contains an array of
values to be passed to the shader's ``in_vert`` variable, and each value in the
array consists of two floats (``"2f"``).

The ``"6f"`` format parameter used by ``struct.pack`` is documented here_.
Although it looks similar to the ``"2f"`` format used by
:py:meth:`Context.vertex_array()`, they are not the same. The latter is unique
to ``moderngl``, and is documented on this page.

.. _here: https://docs.python.org/3.7/library/struct.html

By default, each float occupies 4 bytes, but the type of this data can be
modified with an optional trailing size, such as ``"2f8"``, indicating two
doubles (ie eight byte floats.)

A final optional component containing a single and usage character, for example `/i`, indicates the divisor
size. **TODO:** explain this better.

Single values
-------------

The resulting overall form of a format is:

    ``[count] type [size] [/usage]``

Where:

- ``count`` is an optional integer, defaulting to ``1``.
- ``type`` is a single character indicating data type (``f`` float, ``i`` int, ``u`` unsigned int, ``x`` padding)
- ``size`` is an optional number of bytes used to store the type, defaulting to 4 for numeric types, or to 1 for padding bytes.
- ``usage`` is a single character indicating the intended usage.

For example: ``"3f2/i"`` means three floats, each two bytes wide ("`half floats`"), intended for **TODO**.

This results in the following possibilities:

+-------+---------------+-------------------+-----------------+---------+
|       |                 size                                          |
+-------+---------------+-------------------+-----------------+---------+
| type  | 1             | 2                 | 4               | 8       |
+=======+===============+===================+=================+=========+
| f     | Unsigned byte | Half float        | Float           | Double  |
|       | (normalized)  |                   |                 |         |
+-------+---------------+-------------------+-----------------+---------+
| i     | Byte          | Short             | Int             | \-      |
+-------+---------------+-------------------+-----------------+---------+
| u     | Unsigned byte | Unsigned short    | Unsigned int    | \-      |
+-------+---------------+-------------------+-----------------+---------+
| x     | 1 byte        | 2 bytes           | 4 bytes         | 8 bytes |
+-------+---------------+-------------------+-----------------+---------+

The entry for ``f1`` looks unusual on first glance, in that its type is ``f``
(for float), but it defines a buffer value containing unsigned bytes. However,
for this combination only, the values are `normalized` as they are passed to
the vertex shader, ie. unsigned bytes from 0 to 255 in the buffer are converted
to float values from 0.0 to 1.0 in the vertex shader. This is intended for
passing in colors as unsigned bytes.

There is no size 8 variant for `i` and `u`.

Multiple values
---------------

A buffer could contain multiple items of data. This is described by a format
string containing multiple space-separated formats. For example, "`3f 3f1 x`"
indicates a buffer that contains an array of C-like structs, where each struct
consists of:

- three floats (each on occupying the default four bytes.)
- three unsigned bytes, which will be normalized before being passed to the shader.
- one padding byte, for alignment.

.. toctree::
    :maxdepth: 2
