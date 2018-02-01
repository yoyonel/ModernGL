Texture
=======

.. py:module:: moderngl
.. py:currentmodule:: moderngl

Methods
-------

.. automethod:: Texture.read(alignment=1) -> bytes
.. automethod:: Texture.read_into(buffer, alignment=1, write_offset=0)
.. automethod:: Texture.write(data, viewport=None, alignment=1)
.. automethod:: Texture.build_mipmaps(base=0, max_level=1000)
.. automethod:: Texture.use(location=0)

Attributes
----------

.. autoattribute:: Texture.repeat_x
.. autoattribute:: Texture.repeat_y
.. autoattribute:: Texture.filter
.. autoattribute:: Texture.swizzle
.. autoattribute:: Texture.width
.. autoattribute:: Texture.height
.. autoattribute:: Texture.size
.. autoattribute:: Texture.components
.. autoattribute:: Texture.samples
.. autoattribute:: Texture.depth
.. autoattribute:: Texture.glo

.. toctree::
    :maxdepth: 2
