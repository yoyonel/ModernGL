VertexArray
===========

.. py:module:: moderngl
.. py:currentmodule:: moderngl

Create
------

.. automethod:: Context.simple_vertex_array(program, buffer, *attributes, index_buffer=None) -> VertexArray
    :noindex:

.. automethod:: Context.vertex_array(program, content, index_buffer=None) -> VertexArray
    :noindex:

Methods
-------

.. automethod:: VertexArray.render(mode=TRIANGLES, vertices=-1, first=0, instances=1)
.. automethod:: VertexArray.transform(buffer, mode=POINTS, vertices=-1, first=0, instances=1)
.. automethod:: VertexArray.bind(attribute, buffer, offset, stride, divisor)

Attributes
----------

.. autoattribute:: VertexArray.program
.. autoattribute:: VertexArray.index_buffer
.. autoattribute:: VertexArray.vertices
.. autoattribute:: VertexArray.subroutines
.. autoattribute:: VertexArray.glo

.. toctree::
    :maxdepth: 2
