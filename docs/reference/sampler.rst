Sampler
=======

.. py:module:: moderngl
.. py:currentmodule:: moderngl

.. autoclass:: moderngl.Sampler

Create
------

.. automethod:: Context.sampler(repeat_x=True, repeat_y=True, repeat_z=True, filter=None, anisotropy=1.0, compare_func='', border_color=None) -> Sampler

Methods
-------

.. automethod:: Sampler.use(location=0)
.. automethod:: Sampler.clear(location=0)
.. automethod:: Sampler.release()

Attributes
----------

.. autoattribute:: Sampler.repeat_x
.. autoattribute:: Sampler.repeat_y
.. autoattribute:: Sampler.repeat_z
.. autoattribute:: Sampler.filter
.. autoattribute:: Sampler.compare_func
.. autoattribute:: Sampler.anisotropy
.. autoattribute:: Sampler.border_color
