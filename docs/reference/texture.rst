Texture
=======

.. py:module:: moderngl
.. py:currentmodule:: moderngl

Create
------

.. automethod:: Context.texture(size, components, data=None, samples=0, alignment=1, dtype='f1') -> Texture
    :noindex:

.. automethod:: Context.depth_texture(size, data=None, samples=0, alignment=4) -> Texture
    :noindex:

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
