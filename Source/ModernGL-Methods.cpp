#include "ModernGL.hpp"

struct Implementation {
	int version;
	PyCFunction method;
	PyCFunction dummy;
	int flags;

	const char * name;
	const char * doc;
};

Implementation implementation[] = {
	{
		0,
		(PyCFunction)InitializeModernGL,
		(PyCFunction)InitializeModernGL,
		METH_VARARGS,
		"InitializeModernGL",
		"Initialize the ModernGL module inside a valid OpenGL context.\n"
		"A valid OpenGL context must exists before the function call.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) There is no valid OpenGL context or OpenGL version is below 3.1\n"
		"\n"
	},
	{
		301,
		(PyCFunction)GetInfo,
		(PyCFunction)Dummy_GetInfo,
		METH_NOARGS,
		"GetInfo",
		"Get information about the OpenGL context.\n"
		"The module must be initialized first.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tinfo (dict) Dictionary with the results of the most popular queries using glGet.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)Viewport,
		(PyCFunction)Dummy_Viewport,
		METH_VARARGS | METH_KEYWORDS,
		"Viewport",
		"Set the viewport for rendering.\n"
		"\n"

		"Parameters:\n"
		"\tx (int) Position of the viewport.\n"
		"\ty (int) Position of the viewport.\n"
		"\twidth (int) Width of the viewport.\n"
		"\theight (int) Height of the viewport.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)Clear,
		(PyCFunction)Dummy_Clear,
		METH_VARARGS | METH_KEYWORDS,
		"Clear",
		"Clear the viewport with the specified colors.\n"
		"Also clears the depth attachments.\n"
		"\n"

		"Parameters:\n"
		"\tr (int) Clear value for the red channel. By default is 0\n"
		"\tg (int) Clear value for the green channel. By default is 0\n"
		"\tb (int) Clear value for the blue channel. By default is 0\n"
		"\ta (int) Clear value for the alpha channel. By default is 255\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)PointSize,
		(PyCFunction)Dummy_PointSize,
		METH_VARARGS,
		"PointSize",
		"Set the size of the point primitive.\n"
		"\n"

		"Parameters:\n"
		"\tsize (float) Size of the point.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)LineSize,
		(PyCFunction)Dummy_LineSize,
		METH_VARARGS,
		"LineSize",
		"Set the with of the line primitive.\n"
		"\n"

		"Parameters:\n"
		"\tsize (float) Width of the line.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableOnly,
		(PyCFunction)Dummy_EnableOnly,
		METH_VARARGS,
		"EnableOnly",
		"Enables only the specified flags.\n"
		"The enable flags are:\n"
		"- ModernGL.ENABLE_NOTHING\n"
		"- ModernGL.ENABLE_BLEND\n"
		"- ModernGL.ENABLE_CULL_FACE\n"
		"- ModernGL.ENABLE_DEPTH_TEST\n"
		"- ModernGL.ENABLE_MULTISAMPLE\n"
		"- ModernGL.ENABLE_ALL\n"
		"\n"

		"Parameters:\n"
		"\tflags (ModernGL.EnableFlag) A combination of the enable flags using + and - operators.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableBlend,
		(PyCFunction)Dummy_EnableBlend,
		METH_NOARGS,
		"EnableBlend",
		"Enable blending.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DisableBlend,
		(PyCFunction)Dummy_DisableBlend,
		METH_NOARGS,
		"DisableBlend",
		"Disable blending.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableCullFace,
		(PyCFunction)Dummy_EnableCullFace,
		METH_NOARGS,
		"EnableCullFace",
		"Enable face culling.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DisableCullFace,
		(PyCFunction)Dummy_DisableCullFace,
		METH_NOARGS,
		"DisableCullFace",
		"Disable face culling.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableDepthTest,
		(PyCFunction)Dummy_EnableDepthTest,
		METH_NOARGS,
		"EnableDepthTest",
		"Enable depth testing.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DisableDepthTest,
		(PyCFunction)Dummy_DisableDepthTest,
		METH_NOARGS,
		"DisableDepthTest",
		"Disable depth testing.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableMultisample,
		(PyCFunction)Dummy_EnableMultisample,
		METH_NOARGS,
		"EnableMultisample",
		"Enable multisampling.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DisableMultisample,
		(PyCFunction)Dummy_DisableMultisample,
		METH_NOARGS,
		"DisableMultisample",
		"Disable multisampling.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewVertexShader,
		(PyCFunction)Dummy_NewVertexShader,
		METH_VARARGS,
		"NewVertexShader",
		"Create a vertex shader from GLSL source.\n"
		"A shader can be attached only once and will be deleted with the program object.\n"
		"If the shader was not attached, it must be deleted using the ModernGL.DeleteShader method.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tshader (ModernGL.Shader) The shader object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.CompileError) The source cannot be compiled.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewFragmentShader,
		(PyCFunction)Dummy_NewFragmentShader,
		METH_VARARGS,
		"NewFragmentShader",
		"Create a fragment shader from GLSL source.\n"
		"A shader can be attached only once and will be deleted with the program object.\n"
		"If the shader was not attached, it must be deleted using the ModernGL.DeleteShader method.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.CompileError) The source cannot be compiled.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)NewGeometryShader,
		(PyCFunction)Dummy_NewGeometryShader,
		METH_VARARGS,
		"NewGeometryShader",
		"Create a geometry shader from GLSL source.\n"
		"A shader can be attached only once and will be deleted with the program object.\n"
		"If the shader was not attached, it must be deleted using the ModernGL.DeleteShader method.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.CompileError) The source cannot be compiled.\n"
		"\n"
	},
	{
		400,
		(PyCFunction)NewTessEvaluationShader,
		(PyCFunction)Dummy_NewTessEvaluationShader,
		METH_VARARGS,
		"NewTessEvaluationShader",
		"Create a tesselation evaluation shader from GLSL source.\n"
		"A shader can be attached only once and will be deleted with the program object.\n"
		"If the shader was not attached, it must be deleted using the ModernGL.DeleteShader method.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\t(ModernGL.CompileError) The source cannot be compiled.\n"
		"\n"
	},
	{
		400,
		(PyCFunction)NewTessControlShader,
		(PyCFunction)Dummy_NewTessControlShader,
		METH_VARARGS,
		"NewTessControlShader",
		"Create a tesselation control shader from GLSL source.\n"
		"A shader can be attached only once and will be deleted with the program object.\n"
		"If the shader was not attached, it must be deleted using the ModernGL.DeleteShader method.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\t(ModernGL.CompileError) The source cannot be compiled.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteShader,
		(PyCFunction)Dummy_DeleteShader,
		METH_VARARGS,
		"DeleteShader",
		"Delete shader object created by:\n"
		"- ModernGL.NewVertexShader\n"
		"- ModernGL.NewFragmentShader\n"
		"- ModernGL.NewGeometryShader\n"
		"- ModernGL.NewTessControlShader\n"
		"- ModernGL.NewTessEvaluationShader\n"
		"A shader object must be deleted if it was not attached to any program objects.\n"
		"\n"

		"Parameters:\n"
		"\tshader (ModernGL.Shader) Shader object that was not attached to any program object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewProgram,
		(PyCFunction)Dummy_NewProgram,
		METH_VARARGS,
		"NewProgram",
		"Create a program object from a list of ModernGL.Shader objects.\n"
		"There must be only one shader for each shader types.\n"
		"\n"

		"Parameters:\n"
		"\tshaders (list) List containing shader objects.\n"
		"\n"

		"Returns:\n"
		"\tprogram (ModernGL.Program) The new program object.\n"
		"\tinterface (dict) The active uniforms and uniform buffers.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.CompileError) Linking error or duplicate shaders of the same type.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteProgram,
		(PyCFunction)Dummy_DeleteProgram,
		METH_VARARGS,
		"DeleteProgram",
		"Delete a program objects and all the attached shaders.\n"
		"A shader must be attached only to a single program object.\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.Program) A program object returned by the ModernGL.NewProgram function.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniform,
		(PyCFunction)Dummy_SetUniform,
		METH_VARARGS,
		"SetUniform",
		"Set the value of the uniform (except for matrices).\n"
		"The number of parameters depends on the uniform type.\n"
		"The location of active uniforms is always accessable from the program interface.\n"
		"The program interface is the second value returned by the ModernGL.NewProgram.\n"
		"\n"

		"Parameters:\n"
		"\tlocation (ModernGL.UniformLocation) Location of the uniform.\n"
		"\tv0 (float or int) Value to set.\n"
		"\tv1 (float or int) Value to set.\n"
		"\tv2 (float or int) Value to set.\n"
		"\tv3 (float or int) Value to set.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(TypeError) The dimension or the type of the uniform is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniformMatrix,
		(PyCFunction)Dummy_SetUniformMatrix,
		METH_VARARGS,
		"SetUniformMatrix",
		"Set the value of the uniform matrix.\n"
		"The matrix type must be either mat2, mat3 or mat4.\n"
		"\n"

		"Parameters:\n"
		"\tlocation (ModernGL.UniformLocation) Location of the uniform.\n"
		"\tmatrix (list) List containing 4x4=16 float values.\n"
		"\ttranspose (bool) Transpose matrix.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(TypeError) The dimension or the type of the matrix is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseUniformBuffer,
		(PyCFunction)Dummy_UseUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UseUniformBuffer",
		"Bind a unirom buffer to a location in the program.\n"
		"\n"

		"Parameters:\n"
		"\tubo (ModernGL.UniformBuffer) Index of a uniform buffer.\n"
		"\tlocation (ModernGL.UniformBufferLocation) Location of the uniform buffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewTexture,
		(PyCFunction)Dummy_NewTexture,
		METH_VARARGS | METH_KEYWORDS,
		"NewTexture",
		"Create a new texture.\n"
		"\n"

		"Parameters:\n"
		"\twidth (int) Width of the texture.\n"
		"\theight (int) Height of the texture.\n"
		"\tpixels (bytes) Pixels stored in bytes.\n"
		"\tcomponents (int) By default is 3\n"
		"\n"

		"Returns:\n"
		"\ttexture (ModernGL.Texture) The index of the new texture object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.RangeError) The size of pixels is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteTexture,
		(PyCFunction)Dummy_DeleteTexture,
		METH_VARARGS,
		"DeleteTexture",
		"Delete a texture created by the ModernGL.NewTexture method.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateTexture,
		(PyCFunction)Dummy_UpdateTexture,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateTexture",
		"Update the content of a texture.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture.\n"
		"\tx (int) Offset of the new texture part.\n"
		"\ty (int) Offset of the new texture part.\n"
		"\twidth (int) Width of the texture.\n"
		"\theight (int) Height of the texture.\n"
		"\tpixels (bytes) Pixels stored in bytes.\n"
		"\tcomponents (int) By default is 3\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.RangeError) The size of pixels is different.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseTexture,
		(PyCFunction)Dummy_UseTexture,
		METH_VARARGS,
		"UseTexture",
		"Bind a texture to a location.\n"
		"The default location is 0.\n"
		"Initialize sampler2D uniforms with ModernGL.SetUniform\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture function.\n"
		"\tlocation (int) Location of the texture. By default is 0\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetTexturePixelated,
		(PyCFunction)Dummy_SetTexturePixelated,
		METH_VARARGS,
		"SetTexturePixelated",
		"Set texture filter to nearest.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture function.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetTextureFiltered,
		(PyCFunction)Dummy_SetTextureFiltered,
		METH_VARARGS,
		"SetTextureFiltered",
		"Set texture filter to linear.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture function.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetTextureMipmapped,
		(PyCFunction)Dummy_SetTextureMipmapped,
		METH_VARARGS,
		"SetTextureMipmapped",
		"Set texture filter to mipmap linear.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the ModernGL.NewTexture function.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)BuildMipmap,
		(PyCFunction)Dummy_BuildMipmap,
		METH_VARARGS | METH_KEYWORDS,
		"BuildMipmap",
		"Generate the mipmaps for the texture.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Index of a texture returned by the NewTexture function.\n"
		"\tbase (int) Base mipmap level to build.\n"
		"\tmax (int) Maximum mipmap level to build.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewVertexArray,
		(PyCFunction)Dummy_NewVertexArray,
		METH_VARARGS,
		"NewVertexArray",
		"Create a vertex array object.\n"
		"Prepare vertex and index buffers for rendering. enable or disable attributes.\n"
		"To use more than one vertex buffer call the ModernGL.NewAdvancedVertexArray method.\n"
		"The format regex is: ([1-4][if])+\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.Program) A program object that will be used for rendering.\n"
		"\tvbo (ModernGL.VertexBuffer) A buffer containing data for the vertex attributes.\n"
		"\tformat (str) Format of the vertex array attrubites. ([1-4][if])+\n"
		"\tattributes (list) List of vertex attribute names.\n"
		"\tibo (ModernGL.IndexBuffer) Index of an index buffer object. By default is None\n"
		"\tstrict (bool) Enable AttributeNotFound error. By default is True\n"
		"\n"

		"Returns:\n"
		"\tvao (ModernGL.VertexArray) The index of the new vertex array object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.InvalidFormat) The format is invalid or the size of attributes is different.\n"
		"\t(ModernGL.AttributeNotFound) The attribute is missing (only strict enabled).\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewAdvancedVertexArray,
		(PyCFunction)Dummy_NewAdvancedVertexArray,
		METH_VARARGS,
		"NewAdvancedVertexArray",
		"Advanced version of NewVertexArray that can handle multiple VertexBuffer objects.\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.Program) A program object that will be used for rendering.\n"
		"\tcontent (list) List of tuples similar to the ModernGL.NewVertexArray parameters.\n"
		"\tibo (ModernGL.IndexBuffer) Index of an index buffer object. By default is None\n"
		"\tstrict (bool) Enable AttributeNotFound error. By default is True\n"
		"\n"

		"Returns:\n"
		"\tvao (ModernGL.VertexArray) The index of the new vertex array object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteVertexArray,
		(PyCFunction)Dummy_DeleteVertexArray,
		METH_VARARGS,
		"DeleteVertexArray",
		"\n"
		""
		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of the new vertex array object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)EnableAttributes,
		(PyCFunction)Dummy_EnableAttributes,
		METH_VARARGS | METH_KEYWORDS,
		"EnableAttributes",
		"Enable attributes in the vertex array object.\n"
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object.\n"
		"\tattribs (list) The names of the vertex attributes.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DisableAttributes,
		(PyCFunction)Dummy_DisableAttributes,
		METH_VARARGS | METH_KEYWORDS,
		"DisableAttributes",
		"Disable attributes in the vertex array object.\n"
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object.\n"
		"\tattribs (list) The names of the vertex attributes.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewVertexBuffer,
		(PyCFunction)Dummy_NewVertexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewVertexBuffer",
		"Create a vertex buffer.\n"
		"\n"

		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"
		"\n"

		"Returns:\n"
		"\tvbo (ModernGL.VertexBuffer) The index of the new vertex buffer object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewIndexBuffer,
		(PyCFunction)Dummy_NewIndexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewIndexBuffer",
		"Create an index buffer.\n"
		"\n"

		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"
		"\n"

		"Returns:\n"
		"\tibo (ModernGL.IndexBuffer) The index of the new index buffer object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewUniformBuffer,
		(PyCFunction)Dummy_NewUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewUniformBuffer",
		"Create a uniform buffer.\n"
		"\n"

		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"
		"\n"

		"Returns:\n"
		"\tubo (int) The index of the new uniform buffer object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)NewStorageBuffer,
		(PyCFunction)Dummy_NewStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewStorageBuffer",
		"Create a shader storage buffer.\n"
		"\n"

		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"
		"\n"

		"Returns:\n"
		"\tsbo (ModernGL.StorageBuffer) The index of the new shader storage buffer object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteVertexBuffer,
		(PyCFunction)Dummy_DeleteVertexBuffer,
		METH_VARARGS,
		"DeleteVertexBuffer",
		"Delete a vertex buffer created by the ModernGL.NewVertexBuffer.\n"
		"\n"

		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteIndexBuffer,
		(PyCFunction)Dummy_DeleteIndexBuffer,
		METH_VARARGS,
		"DeleteIndexBuffer",
		"Delete an index buffer created by the ModernGL.NewIndexBuffer.\n"
		"\n"

		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteUniformBuffer,
		(PyCFunction)Dummy_DeleteUniformBuffer,
		METH_VARARGS,
		"DeleteUniformBuffer",
		"Delete a uniform buffer created by the ModernGL.NewUniformBuffer.\n"
		"\n"

		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteStorageBuffer,
		(PyCFunction)Dummy_DeleteStorageBuffer,
		METH_VARARGS,
		"DeleteStorageBuffer",
		"Delete a shader storage buffer created by the ModernGL.NewStorageBuffer.\n"
		"\n"

		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateVertexBuffer,
		(PyCFunction)Dummy_UpdateVertexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateVertexBuffer",
		"Update the content of the buffer.\n"
		"\n"

		"Parameters:\n"
		"\tbuffer (int) The index of a vertex buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.RangeError) The offset or size of data is out of the buffer bounds.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateIndexBuffer,
		(PyCFunction)Dummy_UpdateIndexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateIndexBuffer",
		"Update the content of the buffer.\n"
		"\n"

		"Parameters:\n"
		"\tibo (ModernGL.IndexBuffer) The index of an index buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.RangeError) The offset or size of data is out of the buffer bounds.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateUniformBuffer,
		(PyCFunction)Dummy_UpdateUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateUniformBuffer",
		"Update the content of the buffer.\n"
		"\n"

		"Parameters:\n"
		"\tubo (ModernGL.UniformBuffer) The index of a uniform buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.RangeError) The offset or size of data is out of the buffer bounds.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)UpdateStorageBuffer,
		(PyCFunction)Dummy_UpdateStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateStorageBuffer",
		"Update the content of a shader storage buffer.\n"
		"\n"

		"Parameters:\n"
		"\tsbo (ModernGL.StorageBuffer) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to update.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\t(ModernGL.RangeError) The offset or size of data is out of the buffer bounds.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderTriangles,
		(PyCFunction)Dummy_RenderTriangles,
		METH_VARARGS | METH_KEYWORDS,
		"RenderTriangles",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderTriangleStrip,
		(PyCFunction)Dummy_RenderTriangleStrip,
		METH_VARARGS | METH_KEYWORDS,
		"RenderTriangleStrip",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderTriangleFan,
		(PyCFunction)Dummy_RenderTriangleFan,
		METH_VARARGS | METH_KEYWORDS,
		"RenderTriangleFan",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderLines,
		(PyCFunction)Dummy_RenderLines,
		METH_VARARGS | METH_KEYWORDS,
		"RenderLines",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderLineStrip,
		(PyCFunction)Dummy_RenderLineStrip,
		METH_VARARGS | METH_KEYWORDS,
		"RenderLineStrip",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderLineLoop,
		(PyCFunction)Dummy_RenderLineLoop,
		METH_VARARGS | METH_KEYWORDS,
		"RenderLineLoop",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)RenderPoints,
		(PyCFunction)Dummy_RenderPoints,
		METH_VARARGS | METH_KEYWORDS,
		"RenderPoints",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)RenderLineStripAdjacency,
		(PyCFunction)Dummy_RenderLineStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"RenderLineStripAdjacency",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)RenderLinesAdjacency,
		(PyCFunction)Dummy_RenderLinesAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"RenderLinesAdjacency",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)RenderTriangleStripAdjacency,
		(PyCFunction)Dummy_RenderTriangleStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"RenderTriangleStripAdjacency",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)RenderTrianglesAdjacency,
		(PyCFunction)Dummy_RenderTrianglesAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"RenderTrianglesAdjacency",
		"\n"

		"Parameters:\n"
		"\tvao (ModernGL.VertexArray) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewFramebuffer,
		(PyCFunction)Dummy_NewFramebuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewFramebuffer",
		"Creates a framebuffer with two texture attachments. (color and depth)\n"
		"The color attachment have RGBA format, 8bit for each channel.\n"
		"The depth texture contains float values.\n"
		"\n"

		"Parameters:\n"
		"\twidth (int) Width of the framebuffer. By default is 0\n"
		"\theight (int) Height of the framebuffer. By default is 0\n"
		"\n"

		"Returns:\n"
		"\tfbo (int) The index of the new framebuffer object.\n"
		"\tcolor (int) The index of the color attachment texture object.\n"
		"\tdepth (int) The index of the depth attachment texture object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteFramebuffer,
		(PyCFunction)Dummy_DeleteFramebuffer,
		METH_VARARGS,
		"DeleteFramebuffer",
		"\n"

		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseFramebuffer,
		(PyCFunction)Dummy_UseFramebuffer,
		METH_VARARGS,
		"UseFramebuffer",
		"Bind a framebuffer.\n"
		"\n"

		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetDefaultFramebuffer,
		(PyCFunction)Dummy_SetDefaultFramebuffer,
		METH_VARARGS,
		"SetDefaultFramebuffer",
		"Some application provide a default framebuffer.\n"
		"Otherwise the default framebuffer is 0.\n"
		"\n"

		"Parameters:\n"
		"\tfbo_index (int) The value provided by the application.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseDefaultFramebuffer,
		(PyCFunction)Dummy_UseDefaultFramebuffer,
		METH_NOARGS,
		"UseDefaultFramebuffer",
		"Use the default framebuffer.\n"
		"The default framebuffer is 0.\n"
		"It can be set with the ModernGL.SetDefaultFramebuffer method.\n"
		"\n"

		"Parameters:\n"
		"\tNone\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	
	{
		301,
		(PyCFunction)ReadPixels,
		(PyCFunction)Dummy_ReadPixels,
		METH_VARARGS | METH_KEYWORDS,
		"ReadPixels",
		"Read the pixels from the active framebuffer.\n"
		"\n"

		"Parameters:\n"
		"\tx (int) Offset of the image to read.\n"
		"\ty (int) Offset of the image to read.\n"
		"\twidth (int) Width of the image to read.\n"
		"\theight (int) Height of the image to read.\n"
		"\tcomponents (int) By default is 3\n"
		"\n"

		"Returns:\n"
		"\tpixels (bytes) The color channels selected by components from the active framebuffer.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)ReadDepthPixels,
		(PyCFunction)Dummy_ReadDepthPixels,
		METH_VARARGS | METH_KEYWORDS,
		"ReadDepthPixels",
		"Read the depth pixels from the active framebuffer.\n"
		"\n"

		"Parameters:\n"
		"\tx (int) Offset of the image to read.\n"
		"\ty (int) Offset of the image to read.\n"
		"\twidth (int) Width of the image to read.\n"
		"\theight (int) Height of the image to read.\n"
		"\n"

		"Returns:\n"
		"\tpixels (bytes) The depth channel from the active framebuffer.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)ReadPixel,
		(PyCFunction)Dummy_ReadPixel,
		METH_VARARGS | METH_KEYWORDS,
		"ReadPixel",
		"Read a single pixel from the active framebuffer.\n"
		"\n"

		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"
		"\n"

		"Returns:\n"
		"\tpixel (int) The rgba value at (x, y) from the active framebuffer.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)ReadDepthPixel,
		(PyCFunction)Dummy_ReadDepthPixel,
		METH_VARARGS | METH_KEYWORDS,
		"ReadDepthPixel",
		"Read a single depth value from the active framebuffer.\n"
		"\n"

		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"
		"\n"

		"Returns:\n"
		"\tpixel (float) The depth value at (x, y) from the active framebuffer.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\n"
	},
	{
		402,
		(PyCFunction)UseTextureAsImage,
		(PyCFunction)Dummy_UseTextureAsImage,
		METH_VARARGS | METH_KEYWORDS,
		"UseTextureAsImage",
		"To use image2D instead of sampler2D.\n"
		"\n"

		"Parameters:\n"
		"\ttexture (ModernGL.Texture) Texture.\n"
		"\tbinding (int) Image binding specified by the layout in GLSL. By default is 0\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)NewComputeShader,
		(PyCFunction)Dummy_NewComputeShader,
		METH_VARARGS,
		"NewComputeShader",
		"Compiles and links a compute shader from GLSL source.\n"
		"\n"

		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"
		"\n"

		"Returns:\n"
		"\tprogram (ModernGL.ComputeShader) The index of the new program object.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteComputeShader,
		(PyCFunction)Dummy_DeleteComputeShader,
		METH_VARARGS,
		"DeleteComputeShader",
		"Compute shader is a standalone shader program.\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.ComputeShader) The index of a program object returned by the ModernGL.NewComputeShader.\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)RunComputeShader,
		(PyCFunction)Dummy_RunComputeShader,
		METH_VARARGS | METH_KEYWORDS,
		"RunComputeShader",
		"Run the compute shader.\n"
		"\n"

		"Parameters:\n"
		"\tprogram (ModernGL.ComputeShader) The index of a program object returned by the ModernGL.NewComputeShader.\n"
		"\tx (int) The x group size of the workers. By default is 1\n"
		"\ty (int) The y group size of the workers. By default is 1\n"
		"\tz (int) The z group size of the workers. By default is 1\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)UseStorageBuffer,
		(PyCFunction)Dummy_UseStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UseStorageBuffer",
		"Bind a shader storage buffer to a location specified in the GLSL layout.\n"
		"\n"

		"Parameters:\n"
		"\tsbo (ModernGL.StorageBuffer) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\tbinding (int) Buffer binding specified by the layout in GLSL. By default is 0\n"
		"\n"

		"Returns:\n"
		"\tNone\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)ReadStorageBuffer,
		(PyCFunction)Dummy_ReadStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"ReadStorageBuffer",
		"Read the content of a shader storage buffer.\n"
		"If the size parameter is 0 the remaining size will be used.\n"
		"\n"

		"Parameters:\n"
		"\tsbo (ModernGL.StorageBuffer) The index of a shader storage buffer object returned by the ModernGL.NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to read. By default is 0\n"
		"\tsize (int) The size of the data to read from the buffer. By default is 0\n"
		"\n"

		"Returns:\n"
		"\tdata (bytes) The content of the shader storage buffer.\n"
		"\n"

		"Errors:\n"
		"\t(ModernGL.NotInitialized) The module must be initialized first.\n"
		"\t(ModernGL.NotSupported) The OpenGL version is below the required.\n"
		"\t(ModernGL.RangeError) The offset or size is out of the buffer bounds.\n"
		"\n"
	},
	{
		0,
		(PyCFunction)NewTransformProgram,
		(PyCFunction)Dummy_NewTransformProgram,
		METH_VARARGS | METH_KEYWORDS,
		"NewTransformProgram",
		""
	},
	{
		0,
		(PyCFunction)TransformTriangles,
		(PyCFunction)Dummy_TransformTriangles,
		METH_VARARGS | METH_KEYWORDS,
		"TransformTriangles",
		""
	},
	{
		0,
		(PyCFunction)TransformTriangleStrip,
		(PyCFunction)Dummy_TransformTriangleStrip,
		METH_VARARGS | METH_KEYWORDS,
		"TransformTriangleStrip",
		""
	},
	{
		0,
		(PyCFunction)TransformTriangleFan,
		(PyCFunction)Dummy_TransformTriangleFan,
		METH_VARARGS | METH_KEYWORDS,
		"TransformTriangleFan",
		""
	},
	{
		0,
		(PyCFunction)TransformLines,
		(PyCFunction)Dummy_TransformLines,
		METH_VARARGS | METH_KEYWORDS,
		"TransformLines",
		""
	},
	{
		0,
		(PyCFunction)TransformLineStrip,
		(PyCFunction)Dummy_TransformLineStrip,
		METH_VARARGS | METH_KEYWORDS,
		"TransformLineStrip",
		""
	},
	{
		0,
		(PyCFunction)TransformLineLoop,
		(PyCFunction)Dummy_TransformLineLoop,
		METH_VARARGS | METH_KEYWORDS,
		"TransformLineLoop",
		""
	},
	{
		0,
		(PyCFunction)TransformPoints,
		(PyCFunction)Dummy_TransformPoints,
		METH_VARARGS | METH_KEYWORDS,
		"TransformPoints",
		""
	},
	{
		0,
		(PyCFunction)TransformLineStripAdjacency,
		(PyCFunction)Dummy_TransformLineStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"TransformLineStripAdjacency",
		""
	},
	{
		0,
		(PyCFunction)TransformLinesAdjacency,
		(PyCFunction)Dummy_TransformLinesAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"TransformLinesAdjacency",
		""
	},
	{
		0,
		(PyCFunction)TransformTriangleStripAdjacency,
		(PyCFunction)Dummy_TransformTriangleStripAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"TransformTriangleStripAdjacency",
		""
	},
	{
		0,
		(PyCFunction)TransformTrianglesAdjacency,
		(PyCFunction)Dummy_TransformTrianglesAdjacency,
		METH_VARARGS | METH_KEYWORDS,
		"TransformTrianglesAdjacency",
		""
	},
	{
		301,
		(PyCFunction)DebugInfo,
		(PyCFunction)Dummy_DebugInfo,
		METH_NOARGS,
		"DebugInfo",
		""
	},
	{
		301,
		(PyCFunction)DebugVar,
		(PyCFunction)Dummy_DebugVar,
		METH_VARARGS,
		"DebugVar",
		""
	},
};

const int implementations = sizeof(implementation) / sizeof(Implementation);

PyMethodDef methods[implementations + 1];

void InitMethods() {
	for (int i = 0; i < implementations; ++i) {
		methods[i].ml_name = (char *)implementation[i].name;
		methods[i].ml_doc = (char *)implementation[i].doc;
		methods[i].ml_flags = implementation[i].flags;
		methods[i].ml_meth = implementation[i].dummy;
	}
}

void LoadMethods() {
	for (int i = 0; i < implementations; ++i) {
		if (versionNumber >= implementation[i].version) {
			methods[i].ml_meth = implementation[i].method;
		}
	}
}
