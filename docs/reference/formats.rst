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
a buffer containing an array of 2D vertex positions would have the format
string ``"2f"`` - each element of the array consists of two floats.

Buffer formats use a syntax that is unique to ModernGL, although the
resulting formats sometimes look similar to related strings used elsewhere,
such as the format strings used by ``struct.pack`` (which are documented
here_.)

.. _here: https://docs.python.org/3.7/library/struct.html

Buffer formats are used in the :py:meth:`Context.vertex_array()` constructor,
as the 2nd component of the `content` arg. See the examples below.

Syntax
------

The form of a single-value format is:

    ``[count] type [size] [/usage]``

Where:

- ``count`` is an optional integer. If omitted, it defaults to ``1``.
- ``type`` is a single character indicating the data type:

   - ``f`` float
   - ``i`` int
   - ``u`` unsigned int
   - ``x`` padding
- ``size`` is an optional number of bytes used to store the type.
  If omitted, it defaults to 4 for numeric types, or to 1 for padding bytes.
- ``usage`` is optional, consisting of a slash followed by a single character,
  indicating how successive values in the buffer should be passed to the
  shader:

   - ``/v`` per vertex.
     Successive values from the buffer are passed to each vertex.
     This is the default behavior if usage is omitted.
   - ``/i`` per instance.
     Successive values from the buffer are passed to each instance.
   - ``/r`` per render.
     the first buffer value is passed to every vertex of every instance.
     ie. behaves like a uniform.

For example: ``"3f2/i"`` means each element in the buffer array is a struct of
three floats. Each float is two bytes wide (ie. a "`half float`".) Consecutive
values in the buffer are passed to each successive instance during an
instanced render call.

Multiple formats may be concatenated together, separated by spaces.
See the multiple value example below.

The valid combinations of type and size are:

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

Single value example
--------------------

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
4-bytes each. The format also omits the trailing ``"/usage"`` component, which
defaults to ``/v``, so successive (x, y) rows from the buffer are passed to
successive vertices during the render.

Multiple value example
----------------------

A buffer array might contain elements consisting of multiple interleaved
values.

This is described by a format containing multiple space separated
formats. Each format (other than padding) requires the name of a shader ``in``
attribute, to which it will be passed.

For example, consider a buffer array, each element of which contains 2D vertex
positions as floats, RGB colors as unsigned ints, and a single byte of padding
for alignment:

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

This specifies that the initial two floats be passed to the vertex shader's
``in_vert`` attribute, which hence must be a ``vec2``. The three color unsigned
bytes (normalized to floats by ``f1``) are passed to the shader's ``vec3
in_color``. The final byte of padding (``x``) is ignored, and needs no shader
variable name.

.. toctree::
    :maxdepth: 2
