Shaders and Programs
********************

.. currentmodule:: ModernGL

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

.. automethod:: Context.program(shaders, varyings=()) -> Program
	:noindex:

.. autoclass:: Shader
	:members: source

.. autoclass:: Program
	:members: vertex_shader, fragment_shader, geometry_shader, tess_evaluation_shader, tess_control_shader, geometry_input, geometry_output, geometry_vertices

	.. automethod:: uniforms() -> Dict[str, Uniform]
	.. automethod:: uniform_blocks() -> Dict[str, UniformBlock]
	.. automethod:: attributes() -> Dict[str, Attribute]
	.. automethod:: varyings() -> Dict[str, Varying]

.. toctree::
	:maxdepth: 4
	:caption: Classes:

	Uniforms <Uniforms.rst>
	Attributes <Attributes.rst>
	UniformBlocks <UniformBlocks.rst>
	Varyings <Varyings.rst>
