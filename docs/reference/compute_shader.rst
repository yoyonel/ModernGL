ComputeShader
=============

.. py:module:: moderngl
.. py:currentmodule:: moderngl

.. autoclass:: moderngl.ComputeShader

Create
------

.. automethod:: Context.compute_shader(source) -> ComputeShader
    :noindex:

Methods
-------

.. automethod:: ComputeShader.run(group_x=1, group_y=1, group_z=1)
.. automethod:: ComputeShader.get(key, default) -> Union[Uniform, UniformBlock, Subroutine, Attribute, Varying]
.. automethod:: ComputeShader.release()

Attributes
----------

.. autoattribute:: ComputeShader.source
.. autoattribute:: ComputeShader.glo
.. autoattribute:: ComputeShader.mglo
.. autoattribute:: ComputeShader.extra
.. autoattribute:: ComputeShader.ctx

.. toctree::
    :maxdepth: 2
