Buffer Format
=============

.. py:module:: moderngl
.. py:currentmodule:: moderngl

Description
-----------

A buffer format is a short string describing the layout of data in a vertex
buffer array (VBO).

A VBO often contains a homogeneous array of C-like structures. The buffer
format describes what each element of the array looks like. For example,
a buffer containing an array of 2D vertex positions might have the format
string ``"2f8"`` - each element of the array consists of two floats, each
float being 8 bytes wide, ie a double.

Buffer formats are used in the :py:meth:`Context.vertex_array()` constructor,
as the 2nd component of the `content` arg. See the examples below.

Syntax
------

A buffer format looks like:

    ``[count]type[size] [[count]type[size]...] [/usage]``

Where:

- ``count`` is an optional integer. If omitted, it defaults to ``1``.
- ``type`` is a single character indicating the data type:

   - ``f`` float
   - ``i`` int
   - ``u`` unsigned int
   - ``x`` padding
- ``size`` is an optional number of bytes used to store the type.
  If omitted, it defaults to 4 for numeric types, or to 1 for padding bytes.
- ``usage`` is optional. It may be preceded by a space, and then consists of
  a slash followed by a single character, indicating how successive values in
  the buffer should be passed to the shader:

   - ``/v`` per vertex.
     Successive values from the buffer are passed to each vertex.
     This is the default behavior if usage is omitted.
   - ``/i`` per instance.
     Successive values from the buffer are passed to each instance.
   - ``/r`` per render.
     the first buffer value is passed to every vertex of every instance.
     ie. behaves like a uniform.

Some example buffer formats:

``"2f"`` has a count of ``2`` and a type of ``f`` (float). Hence it describes
two floats. The size of the floats is unspecified, so it defaults to ``4``. The
usage of the buffer is unspecified, so defaults to ``/v`` (vertex), meaning
each successive pair of floats in the array are passed to successive vertices
during the render call.

``"3i2/i"`` means three ``i`` (integers). The size of each integer is ``2``
bytes, ie. they are shorts. The trailing ``/i`` means that consecutive values
in the buffer are passed to successive _instances_ during an instanced render
call. So the same value is passed to every vertex within a particular instance.

Buffers contining interleaved values are represented by multiple space
separated count-type-size triples. Hence:

``"2f 3u x /v"`` means two floats, followed by three ``u`` (unsigned bytes),
and then ``x`` - a single byte of padding, for alignment. The ``/v`` indicates
successive elements in the buffer are passed to successive vertices during the
render. This is the default, so the ``/v`` could be omitted.

Valid combinations of type and size are:

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

There is no size 8 variant for types ``i`` and ``u``.

Usage Examples
--------------

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
            (vbo, "2f", "in_vert"), # the buffer format is the "2f" here
        ]
        index_buffer_object
    )

The line ``(vbo, "2f", "in_vert")``, known as the VAO content, indicates that
``vbo`` contains an array of values, each of which consists of two floats.
These values are passed to the shader's ``in_vert`` variable, which must
therefore be a vec2.

The ``"2f"`` format omits a ``size`` component, so the floats default to
4-bytes each. The format also omits the trailing ``/usage`` component, which
defaults to ``/v``, so successive (x, y) rows from the buffer are passed to
successive vertices during the render call.

Buffer formats use a syntax that is unique to ModernGL. As in the example
above, they sometimes look similar to the format strings passed to
``struct.pack``, but that is a different syntax (documented here_.)

.. _here: https://docs.python.org/3.7/library/struct.html

Multiple value example
......................

A buffer array might contain elements consisting of multiple interleaved
values.

For example, consider a buffer array, each element of which contains a 2D
vertex position as floats, an RGB color as unsigned ints, and a single byte of
padding for alignment:

+-------+-------+----------+----------+----------+---------+
| position      | color                          | padding |
+-------+-------+----------+----------+----------+---------+
| x     | y     | r        | g        | b        | \-      |
+-------+-------+----------+----------+----------+---------+
| float | float | unsigned | unsigned | unsigned | byte    |
|       |       | byte     | byte     | byte     |         |
+-------+-------+----------+----------+----------+---------+

This is passed as VAO content using::

    (vbo, "2f 3f1 x", "in_vert", "in_color")

The format starts with ``2f``, for the two position floats, which will
be passed to the shader's ``in_vert`` attribute, which must therfore be a
``vec2``.

Next, after a space, is ``3f1``, for the three color unsigned bytes, which
get normalized to floats by ``f1``. These floats will be passed to the shader's
``in_color`` attribute, which must therefore be a ``vec3``.

Finally, the format ends with ``x``, a single byte of padding, which needs
no shader attribute name.

.. toctree::
    :maxdepth: 2
