Shader
=======

.. py:module:: moderngl
.. py:currentmodule:: moderngl

.. autoclass:: moderngl.Shader

Create
------

.. automethod:: Context.vertex_shader(source) -> Shader
    :noindex:

.. automethod:: Context.fragment_shader(source) -> Shader
    :noindex:

.. automethod:: Context.geometry_shader(source) -> Shader
    :noindex:

.. automethod:: Context.tess_evaluation_shader(source) -> Shader
    :noindex:

.. automethod:: Context.tess_control_shader(source) -> Shader
    :noindex:

Attributes
----------

.. autoattribute:: Shader.source
.. autoattribute:: Shader.typename
.. autoattribute:: Shader.glo

Examples
--------

.. rubric:: vertex_shader

.. code-block:: python
    :linenos:

    my_vertex_shader = ctx.vertex_shader('''
        #version 330

        in vec2 vert;

        void main() {
            gl_Position = vec4(vert, 0.0, 1.0);
        }
    ''')

.. rubric:: fragment_shader

.. code-block:: python
    :linenos:

    my_fragment_shader = ctx.fragment_shader('''
        #version 330

        out vec4 color;

        void main() {
            color = vec4(0.3, 0.5, 1.0, 1.0);
        }
    ''')

.. toctree::
    :maxdepth: 2
