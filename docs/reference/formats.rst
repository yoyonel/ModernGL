Buffer Format Strings
=====================

.. py:module:: moderngl
.. py:currentmodule:: moderngl

TODO
----

- splice in Szabolcs' description of trailing ``\i``, etc. Is 'usage' a bad name?
  Figure out how 'divisors' are relevant, and whether they need to be mentioned.
- the intro description - should it actually be in a section of examples,
  lower down the page?
- Describe dtypes?
- study the parent issue carefully for suggestions I missed
- migrate to docs/next/reference?

---

Description
-----------

A buffer format is a short string describing the layout of data in a vertex
buffer array (VBO).

A VBO usually contains an homogeneous array of C-like structures. The buffer
format string describes what each element of the array looks like. For example,
a buffer containing an array of 2D vertex positions would have the format
string ``"2f"`` - each element of the array consists of two floats.

Buffer format strings use a syntax that is unique to ModernGL, although the
resulting formats sometimes look similar to related strings used elsewhere,
such as the format strings used by ``struct.pack`` (which are documented
here_.)

.. _here: https://docs.python.org/3.7/library/struct.html

Format strings are used in the :py:meth:`Context.vertex_array()` constructor,
as the 2nd component of the `content` arg. See the examples below.

Single values
-------------

The form of a single-value format string is:

    ``[count] type [size] [/usage]``

Where:

- ``count`` is an optional integer. If omitted, it defaults to ``1``.
- ``type`` is a single character indicating the data type (``f`` float, ``i`` int, ``u`` unsigned int, ``x`` padding)
- ``size`` is an optional number of bytes used to store the type. If omitted, it defaults to 4 for numeric types, or to 1 for padding bytes.
- ``usage`` is a single character indicating the intended usage.

For example: ``"3f2/i"`` means the buffer contains an array of three floats,
each two bytes wide ("`half floats`"), intended for **TODO**.

This results in the following possibilities:

+----------+---------------+-------------------+-----------------+---------+
|          |                 size                                          |
+==========+===============+===================+=================+=========+
| **type** | 1             | 2                 | 4               | 8       |
+----------+---------------+-------------------+-----------------+---------+
| f        | Unsigned byte | Half float        | Float           | Double  |
|          | (normalized)  |                   |                 |         |
+----------+---------------+-------------------+-----------------+---------+
| i        | Byte          | Short             | Int             | \-      |
+----------+---------------+-------------------+-----------------+---------+
| u        | Unsigned byte | Unsigned short    | Unsigned int    | \-      |
+----------+---------------+-------------------+-----------------+---------+
| x        | 1 byte        | 2 bytes           | 4 bytes         | 8 bytes |
+----------+---------------+-------------------+-----------------+---------+

The entry for ``f1`` looks unusual on first glance, in that its type is ``f``
(for float), but it defines a buffer value containing unsigned bytes. However,
for this combination only, the values are `normalized`, ie. unsigned bytes from
0 to 255 in the buffer are converted to float values from 0.0 to 1.0 by the
time they reach the vertex shader. This is intended for passing in colors as
unsigned bytes.

There is no size 8 variant for `i` and `u`.

Single value example
....................

Consider a VBO containing 2D vertex positions, forming a single triangle::

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
            (vbo, "2f", "in_vert"), # the buffer format string is the "2f" here
        ]
        index_buffer_object
    )

The line ``(vbo, "2f", "in_vert")`` indicates that ``vbo`` contains an array of
values to be passed to the shader's ``in_vert`` variable, and each element in
the array consists of two floats (``"2f"``).

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
