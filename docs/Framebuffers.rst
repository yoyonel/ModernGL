Framebuffers
************

.. currentmodule:: ModernGL

.. automethod:: Context.framebuffer(color_attachments, depth_attachment=None) -> Framebuffer
	:noindex:

.. autoclass:: Framebuffer

	.. autoattribute:: viewport
	.. autoattribute:: color_mask
	.. autoattribute:: depth_mask
	.. autoattribute:: width
	.. autoattribute:: height
	.. autoattribute:: size
	.. autoattribute:: samples
	.. autoattribute:: color_attachments
	.. autoattribute:: depth_attachment
	.. autoattribute:: bits

	.. automethod:: clear(red=0.0, green=0.0, blue=0.0, alpha=0.0, viewport=None)
	.. automethod:: use()

	.. automethod:: read(viewport=None, components=3, attachment=0, alignment=1, floats=False) -> bytes
	.. automethod:: read_into(buffer, viewport=None, components=3, attachment=0, alignment=1, floats=False, write_offset=0)

.. toctree::
	:maxdepth: 4
