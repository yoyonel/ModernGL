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
	},
	{
		301,
		(PyCFunction)GetInfo,
		(PyCFunction)Dummy_GetInfo,
		METH_NOARGS,
		"GetInfo",
		"Get information about the OpenGL context.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tmajor (int) The major OpenGL version.\n"
		"\tminor (int) The minor OpenGL version.\n"
		"\tsamples (int) The samples supported by the default framebuffer.\n"
		"\tvendor (int) The vendor.\n"
		"\trenderer (int) The renderer.\n"
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
	},
	{
		301,
		(PyCFunction)EnableOnly,
		(PyCFunction)Dummy_EnableOnly,
		METH_VARARGS,
		"EnableOnly",
		"Enables only the specified flags.\n"
		"The enable flags are: ENABLE_NOTHING, ENABLE_BLEND, ENABLE_DEPTH_TEST, ENABLE_CULL_FACE and ENABLE_MULTISAMPLE.\n"

		"\n"
		"Parameters:\n"
		"\tflags (int) A combination of the enable flags using bitwise OR operator.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
	},
	{
		301,
		(PyCFunction)NewVertexShader,
		(PyCFunction)Dummy_NewVertexShader,
		METH_VARARGS,
		"NewVertexShader",
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewFragmentShader,
		(PyCFunction)Dummy_NewFragmentShader,
		METH_VARARGS,
		"NewFragmentShader",
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		302,
		(PyCFunction)NewGeometryShader,
		(PyCFunction)Dummy_NewGeometryShader,
		METH_VARARGS,
		"NewGeometryShader",
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteShader,
		(PyCFunction)Dummy_DeleteShader,
		METH_VARARGS,
		"DeleteShader",
		"Delete shader object created by the NewFragmentShader, the NewGeometryShader, the NewTessControlShader, the NewTessEvaluationShader or the NewVertexShader.\n"

		"\n"
		"Parameters:\n"
		"\tshader (int) Index of a shader object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewProgram,
		(PyCFunction)Dummy_NewProgram,
		METH_VARARGS,
		"NewProgram",
		""

		"\n"
		"Parameters:\n"
		"\tshaders (list of ints) List containing shader indices.\n"

		"\n"
		"Returns:\n"
		"\tprogram (int) The index of the new program object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteProgram,
		(PyCFunction)Dummy_DeleteProgram,
		METH_VARARGS,
		"DeleteProgram",
		""

		"\n"
		"Parameters:\n"
		"\tprogram (int) Index of a program object returned by the NewProgram function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniform,
		(PyCFunction)Dummy_SetUniform,
		METH_VARARGS,
		"SetUniform",
		"Set the value of the uniform.\n"
		"The value must have the type of `float` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetUniformMatrix,
		(PyCFunction)Dummy_SetUniformMatrix,
		METH_VARARGS,
		"SetUniformMatrix",
		""

		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tmatrix (list of floats) List containing 4x4=16 float values.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseUniformBuffer,
		(PyCFunction)Dummy_UseUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UseUniformBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tubo (int) Index of a uniform buffer returned by a NewUniformBuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewTexture,
		(PyCFunction)Dummy_NewTexture,
		METH_VARARGS | METH_KEYWORDS,
		"NewTexture",
		""

		"\n"
		"Parameters:\n"
		"\twidth (int) Width of the texture.\n"
		"\theight (int) Height of the texture.\n"
		"\tpixels (bytes) Pixels stored in bytes.\n"
		"\tcomponents (int) By default is 3\n"

		"\n"
		"Returns:\n"
		"\ttexture (int) The index of the new texture object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteTexture,
		(PyCFunction)Dummy_DeleteTexture,
		METH_VARARGS,
		"DeleteTexture",
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateTexture,
		(PyCFunction)Dummy_UpdateTexture,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateTexture",
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
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
	},
	{
		301,
		(PyCFunction)UseTexture,
		(PyCFunction)Dummy_UseTexture,
		METH_VARARGS,
		"UseTexture",
		""

		"\n"
		"Parameters:\n"
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
		"\tlocation (int) Location of the texture. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\ttexture (int) Index of a texture returned by the NewTexture function.\n"
		"\tbase (int) Base mipmap level to build.\n"
		"\tmax (int) Maximum mipmap level to build.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewVertexArray,
		(PyCFunction)Dummy_NewVertexArray,
		METH_VARARGS,
		"NewVertexArray",
		"The foreach int or float attribute an index of a vertex buffer object and the location of a vertex attribute must be specified.\n"

		"\n"
		"Parameters:\n"
		"\tformat (str) Format of the vertex array attrubites. ([1-4][if])+\n"
		"\tattribs (list of int pairs) List of vertex buffer object and vertex location pairs.\n"
		"\tibo (int) Index of an index buffer object. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tvao (int) The index of the new vertex array object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewAdvancedVertexArray,
		(PyCFunction)Dummy_NewAdvancedVertexArray,
		METH_VARARGS,
		"NewAdvancedVertexArray",
		"The foreach int or float attribute an index of a vertex buffer object and the location of a vertex attribute must be specified.\n"

		"\n"
		"Parameters:\n"
		"\tformat (str) Format of the vertex array attrubites. ([1-4][if])+\n"
		"\tattribs (list of int pairs) List of vertex buffer object and vertex location pairs.\n"
		"\tibo (int) Index of an index buffer object. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tvao (int) The index of the new vertex array object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteVertexArray,
		(PyCFunction)Dummy_DeleteVertexArray,
		METH_VARARGS,
		"DeleteVertexArray",
		""
		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object.\n"
		"\tattribs (list of ints) The locations of the vertex attributes returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object.\n"
		"\tattribs (list of ints) The locations of the vertex attributes returned by the GetAttributeLocation function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewVertexBuffer,
		(PyCFunction)Dummy_NewVertexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewVertexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tvbo (int) The index of the new vertex buffer object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewIndexBuffer,
		(PyCFunction)Dummy_NewIndexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewIndexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tibo (int) The index of the new index buffer object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)NewUniformBuffer,
		(PyCFunction)Dummy_NewUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewUniformBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tubo (int) The index of the new uniform buffer object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteVertexBuffer,
		(PyCFunction)Dummy_DeleteVertexBuffer,
		METH_VARARGS,
		"DeleteVertexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteIndexBuffer,
		(PyCFunction)Dummy_DeleteIndexBuffer,
		METH_VARARGS,
		"DeleteIndexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteUniformBuffer,
		(PyCFunction)Dummy_DeleteUniformBuffer,
		METH_VARARGS,
		"DeleteUniformBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteStorageBuffer,
		(PyCFunction)Dummy_DeleteStorageBuffer,
		METH_VARARGS,
		"DeleteStorageBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of any buffer object except the framebuffer object.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateVertexBuffer,
		(PyCFunction)Dummy_UpdateVertexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateVertexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of a vertex buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateIndexBuffer,
		(PyCFunction)Dummy_UpdateIndexBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateIndexBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of an index buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UpdateUniformBuffer,
		(PyCFunction)Dummy_UpdateUniformBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateUniformBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tbuffer (int) The index of a uniform buffer object except the framebuffer object.\n"
		"\toffset (int) The offset of the data in the buffer to write.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tvao (int) The index of a vertex array object that will be used during the rendering.\n"
		"\tcount (int) Number of vertices to render.\n"
		"\tfirst (int) Index of the first vertex. By default is 0\n"
		"\tinstances (int) Number of instances. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		""

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
	},
	{
		301,
		(PyCFunction)UseFramebuffer,
		(PyCFunction)Dummy_UseFramebuffer,
		METH_VARARGS,
		"UseFramebuffer",
		""

		"\n"
		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)SetDefaultFramebuffer,
		(PyCFunction)Dummy_SetDefaultFramebuffer,
		METH_VARARGS,
		"SetDefaultFramebuffer",
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		301,
		(PyCFunction)UseDefaultFramebuffer,
		(PyCFunction)Dummy_UseDefaultFramebuffer,
		METH_NOARGS,
		"UseDefaultFramebuffer",
		""

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	
	{
		301,
		(PyCFunction)ReadPixels,
		(PyCFunction)Dummy_ReadPixels,
		METH_VARARGS | METH_KEYWORDS,
		"ReadPixels",
		""

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
	},
	{
		301,
		(PyCFunction)ReadDepthPixels,
		(PyCFunction)Dummy_ReadDepthPixels,
		METH_VARARGS | METH_KEYWORDS,
		"ReadDepthPixels",
		""

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
	},
	{
		301,
		(PyCFunction)ReadPixel,
		(PyCFunction)Dummy_ReadPixel,
		METH_VARARGS | METH_KEYWORDS,
		"ReadPixel",
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"

		"\n"
		"Returns:\n"
		"\tpixels (int) The rgba value at (x, y) from the active framebuffer.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)ReadDepthPixel,
		(PyCFunction)Dummy_ReadDepthPixel,
		METH_VARARGS | METH_KEYWORDS,
		"ReadDepthPixel",
		""

		"\n"
		"Parameters:\n"
		"\tx (int) Offset of the pixel to read.\n"
		"\ty (int) Offset of the pixel to read.\n"

		"\n"
		"Returns:\n"
		"\tpixels (float) The depth value at (x, y) from the active framebuffer.\n"
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
		"\ttexture (int) .\n"
		"\tbinding (int) Image binding specified by the layout in GLSL. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		400,
		(PyCFunction)NewTessEvaluationShader,
		(PyCFunction)Dummy_NewTessEvaluationShader,
		METH_VARARGS,
		"NewTessEvaluationShader",
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		400,
		(PyCFunction)NewTessControlShader,
		(PyCFunction)Dummy_NewTessControlShader,
		METH_VARARGS,
		"NewTessControlShader",
		""

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tshader (int) The index of the new shader object.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)NewComputeShader,
		(PyCFunction)Dummy_NewComputeShader,
		METH_VARARGS,
		"NewComputeShader",
		"Compiles and links a compute shader from source.\n"

		"\n"
		"Parameters:\n"
		"\tsource (str) Source code in GLSL.\n"

		"\n"
		"Returns:\n"
		"\tprogram (int) The index of the new program object.\n"
		"\n"
	},
	{
		301,
		(PyCFunction)DeleteComputeShader,
		(PyCFunction)Dummy_DeleteComputeShader,
		METH_VARARGS,
		"DeleteComputeShader",
		"Compute shader is a standalone shader program. NOT part of the rendering pipeline.\n"
		"Equivalent to the DeleteProgram.\n"

		"\n"
		"Parameters:\n"
		"\tprogram (int) The index of a program object returned by the NewComputeShader function.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
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
		"\tprogram (int) The index of a program object returned by the NewComputeShader function.\n"
		"\tx (int) The x group size of the workers. By default is 1\n"
		"\ty (int) The y group size of the workers. By default is 1\n"
		"\tz (int) The z group size of the workers. By default is 1\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		403,
		(PyCFunction)NewStorageBuffer,
		(PyCFunction)Dummy_NewStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"NewStorageBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tdata (bytes) The content of the buffer.\n"

		"\n"
		"Returns:\n"
		"\tsbo (int) The index of the new shader storage buffer object.\n"
		"\n"
	},
	{
		403,
		(PyCFunction)UseStorageBuffer,
		(PyCFunction)Dummy_UseStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UseStorageBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tsbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\tbinding (int) Buffer binding specified by the layout in GLSL. By default is 0\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		403,
		(PyCFunction)UpdateStorageBuffer,
		(PyCFunction)Dummy_UpdateStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"UpdateStorageBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tsbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to update.\n"
		"\tdata (bytes) The content of the data to write to the buffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		403,
		(PyCFunction)ReadStorageBuffer,
		(PyCFunction)Dummy_ReadStorageBuffer,
		METH_VARARGS | METH_KEYWORDS,
		"ReadStorageBuffer",
		""

		"\n"
		"Parameters:\n"
		"\tsbo (int) The index of a shader storage buffer object returned by the NewStorageBuffer.\n"
		"\toffset (int) The offset of the data in the buffer to read.\n"
		"\tsize (int) The size of the data to read from the buffer.\n"

		"\n"
		"Returns:\n"
		"\tdata (bytes) The Content of the buffer.\n"
		"\n"
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
