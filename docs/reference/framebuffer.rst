Framebuffer
===========

.. py:module:: moderngl
.. py:currentmodule:: moderngl

Methods
-------

.. automethod:: Framebuffer.clear(red=0.0, green=0.0, blue=0.0, alpha=0.0, depth=1.0, viewport=None)
.. automethod:: Framebuffer.use()
.. automethod:: Framebuffer.read(viewport=None, components=3, attachment=0, alignment=1, floats=False) -> bytes
.. automethod:: Framebuffer.read_into(buffer, viewport=None, components=3, attachment=0, alignment=1, floats=False, write_offset=0)

Attributes
----------

.. autoattribute:: Framebuffer.viewport
.. autoattribute:: Framebuffer.color_mask
.. autoattribute:: Framebuffer.depth_mask
.. autoattribute:: Framebuffer.width
.. autoattribute:: Framebuffer.height
.. autoattribute:: Framebuffer.size
.. autoattribute:: Framebuffer.samples
.. autoattribute:: Framebuffer.bits
.. autoattribute:: Framebuffer.color_attachments
.. autoattribute:: Framebuffer.depth_attachment
.. autoattribute:: Framebuffer.glo

.. toctree::
    :maxdepth: 2
