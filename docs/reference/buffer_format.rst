.. _buffer-format-label:

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
a buffer containing an array of high-precision 2D vertex positions might have
the format ``"2f8"`` - each element of the array consists of two floats, each
float being 8 bytes wide, ie. a double.

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

  A format may contain multiple, space-separated ``[count]type[size]`` triples
  (See the :ref:`example-of-single-interleaved-array-label`), followed by:


- ``/usage`` is optional. It may be preceded by a space, and then consists of
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

  When passing multiple VBOs to a VAO, the first one must be of usage ``\v``,
  as shown in the :ref:`example-of-multiple-arrays-with-differing-usage-label`.

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

There are no size 8 variants for types ``i`` and ``u``.

This buffer format syntax is specific to ModernGL. As seen in the usage
examples below, the formats sometimes look similar to the format strings passed
to ``struct.pack``, but that is a different syntax (documented here_.)

.. _here: https://docs.python.org/3.7/library/struct.html

Buffer formats can represent a wide range of vertex attribute formats.
For rare cases of specialized attribute formats that are not expressible
using buffer formats, there is a :py:meth:`VertexArray.bind()` method, to
manually configure the underlying OpenGL binding calls. This is not generally
recommended.

Examples
--------

Example buffer formats
......................

``"2f"`` has a count of ``2`` and a type of ``f`` (float). Hence it describes
two floats. The size of the floats is unspecified, so it defaults to ``4``. The
usage of the buffer is unspecified, so defaults to ``/v`` (vertex), meaning
each successive pair of floats in the array are passed to successive vertices
during the render call.

``"3i2/i"`` means three ``i`` (integers). The size of each integer is ``2``
bytes, ie. they are shorts. The trailing ``/i`` means that consecutive values
in the buffer are passed to successive `instances` during an instanced render
call. So the same value is passed to every vertex within a particular instance.

Buffers contining interleaved values are represented by multiple space
separated count-type-size triples. Hence:

``"2f 3u x /v"`` means two floats, followed by three ``u`` (unsigned bytes),
and then ``x`` - a single byte of padding, for alignment. The ``/v`` indicates
successive elements in the buffer are passed to successive vertices during the
render. This is the default, so the ``/v`` could be omitted.

Example of simple usage
.......................

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
            (vbo, "2f", "in_vert"), # <---- the "2f" is the buffer format
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

.. _example-of-single-interleaved-array-label:

Example of single interleaved array
...................................

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

Such a buffer, however you choose to contruct it, would then be passed into
a VAO using::

    vao = ctx.vertex_array(
        shader_program,
        [
            (vbo, "2f 3f1 x", "in_vert", "in_color")
        ]
        index_buffer_object
    )

The format starts with ``2f``, for the two position floats, which will
be passed to the shader's ``in_vert`` attribute, which must therefore be a
``vec2``.

Next, after a space, is ``3f1``, for the three color unsigned bytes, which
get normalized to floats by ``f1``. These floats will be passed to the shader's
``in_color`` attribute, which must therefore be a ``vec3``.

Finally, the format ends with ``x``, a single byte of padding, which needs
no shader attribute name.

.. _example-of-multiple-arrays-with-differing-usage-label:

Example of multiple arrays with differing ``/usage``
....................................................

To illustrate the trailing ``/usage`` portion, imagine rendering a dozen cubes
with instanced rendering. We will use:

* ``vbo_verts_normals`` contains vertices (3 floats) and normals (3 floats)
  for the vertices within a single cube.
* ``vbo_offset_orientation`` contains offsets (3 floats) and orientations (9
  float matrices) that are used to position and orient each cube.
* ``vbo_colors`` contains one color (3 floats), that will be used for every
  cube.

Our shader will take all the above values as attributes, none of them are
uniforms.

We bind the above VBOs in a single VAO, to prepare for an instanced rendering
call::

    vao = ctx.vertex_array(
        shader_program,
        [
            (vbo_verts_normals,      "3f 3f /v", in_vert, in_norm),
            (vbo_offset_orientation, "3f 9f /i", in_offset, in_orientation),
            (vbo_colors,             "3f /r",    in_color),
        ]
        index_buffer_object
    )

So, the vertices and normals, using ``/v``, are passed to each vertex within
an instance. This fulfills the rule tha the first VBO in a VAO must have usage
``/v``.

The offsets and orientations pass the same value to each vertex within an
instance, but then pass the next value in the buffer to the vertices of the
next instance.

And the single color is passed to every vertex of every instance.
If we had stored the color with ``/v`` or ``/i``, it would have needed
needless duplication, once per vertex or once per instance. Using ``/r``,
only one color is passed to every vertex of every instance for the whole render
call.

We could have achieved the same with a uniform, but doing it as an attribute
allows us to reuse the same shader program, bound to a different buffer, to
pass in color data which varies per instance, or per vertex.

Another alternative would be to not specify the color in our render at all, and
rely on a default color set in the OpenGL state before the render call. But in
general these default values don't have perfect support across all devices.
Using attributes is more reliable.

.. toctree::
    :maxdepth: 2
