Program
=======

.. py:module:: moderngl
.. py:currentmodule:: moderngl

.. autoclass:: moderngl.Program

Create
------

.. automethod:: Context.program(shaders, varyings=()) -> Program
    :noindex:

Attributes
----------

.. autoattribute:: Program.geometry_input
.. autoattribute:: Program.geometry_output
.. autoattribute:: Program.geometry_vertices
.. autoattribute:: Program.subroutines
.. autoattribute:: Program.glo

Examples
--------

.. rubric:: A simple program designed for rendering

.. code-block:: python
    :linenos:

    my_render_program = ctx.program([
        ctx.vertex_shader('''
            #version 330

            in vec2 vert;

            void main() {
                gl_Position = vec4(vert, 0.0, 1.0);
            }
        '''),
        ctx.fragment_shader('''
            #version 330

            out vec4 color;

            void main() {
                color = vec4(0.3, 0.5, 1.0, 1.0);
            }
        '''),
    ])

.. rubric:: A simple program designed for transforming

.. code-block:: python
    :linenos:

    my_vertex_shader = ctx.vertex_shader('''
        #version 330

        in vec4 vert;
        out float vert_length;

        void main() {
            vert_length = length(vert);
        }
    ''')

    my_transform_program = ctx.program(my_vertex_shader, varyings=['vert_length'])

.. toctree::
    :maxdepth: 2

    program_members.rst
