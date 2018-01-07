Uniform
*******

.. currentmodule:: ModernGL

.. autoclass:: Uniform

	.. autoattribute:: name
	.. autoattribute:: location
	.. autoattribute:: dimension
	.. autoattribute:: array_length
	.. autoattribute:: value

	.. automethod:: read() -> bytes
	.. automethod:: write(value)

.. autoclass:: UniformMap

	.. automethod:: __getitem__(key) -> Uniform

.. toctree::
	:maxdepth: 4
