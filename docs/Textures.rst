Textures
********

.. currentmodule:: ModernGL

.. automethod:: Context.texture(size, components, data=None, samples=0, floats=False) -> Texture
	:noindex:

.. automethod:: Context.depth_texture(size, data=None, samples=0) -> Texture
	:noindex:

.. automethod:: Context.texture3d(size, components, data=None, floats=False) -> Texture3D
	:noindex:

.. autoclass:: Texture

	.. autoattribute:: width
	.. autoattribute:: height
	.. autoattribute:: size
	.. autoattribute:: components
	.. autoattribute:: samples
	.. autoattribute:: floats
	.. autoattribute:: depth
	.. autoattribute:: filter
	.. autoattribute:: repeat_x
	.. autoattribute:: repeat_y
	.. autoattribute:: swizzle

	.. automethod:: read(alignment=1) -> bytes
	.. automethod:: read_into(buffer, alignment=1, write_offset=0)
	.. automethod:: write(data, viewport=None, alignment=1)
	.. automethod:: build_mipmaps(base=0, max_level=1000)
	.. automethod:: use(location=0)

.. autoclass:: Texture3D

	.. autoattribute:: width
	.. autoattribute:: height
	.. autoattribute:: depth
	.. autoattribute:: size
	.. autoattribute:: components
	.. autoattribute:: floats
	.. autoattribute:: filter
	.. autoattribute:: repeat_x
	.. autoattribute:: repeat_y
	.. autoattribute:: repeat_z
	.. autoattribute:: swizzle

	.. automethod:: read(alignment=1) -> bytes
	.. automethod:: read_into(buffer, alignment=1, write_offset=0)
	.. automethod:: write(data, viewport=None, alignment=1)
	.. automethod:: build_mipmaps(base=0, max_level=1000)
	.. automethod:: use(location=0)

.. autoclass:: TextureCube
	.. automethod:: read(face, alignment=1) -> bytes
	.. automethod:: read_into(buffer, face, alignment=1, write_offset=0)
	.. automethod:: write(face, data, viewport=None, alignment=1)
	.. automethod:: use(location=0)

.. toctree::
	:maxdepth: 4
