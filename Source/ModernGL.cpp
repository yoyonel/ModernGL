#include "ModernGL.hpp"

#include "OpenGL.hpp"

bool initialized = false;
bool extensionActive = false;
PyObject * ModuleError;

int defaultTextureUnit;
int defaultVertexArray;
int defaultFramebuffer;
int defaultProgram;

int activeFramebuffer;
int activeProgram;

int activeViewportWidth;
int activeViewportHeight;

PyObject * ExtensionActive(PyObject * self) {
	if (extensionActive) {
		Py_RETURN_TRUE;
	} else {
		Py_RETURN_FALSE;
	}
}

PyObject * Dummy(PyObject * self, PyObject * args) {
	PyErr_SetString(ModuleError, "Module not initialized.\n\nCall InitializeModernGL() first.\n\n");
	return 0;
}

PyObject * DummyExtension(PyObject * self, PyObject * args) {
	if (initialized) {
		PyErr_SetString(ModuleError, "Extension not initialized.\n\nCall ExtensionActive() to test the full extension support.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Module not initialized.\n\nCall InitializeModernGL() first.\n\n");
	}
	return 0;
}

PyObject * Testing(PyObject * self, PyObject * args) {
	Py_RETURN_NONE;
}

static PyMethodDef methods[] = {
	{
		"InitializeModernGL",
		(PyCFunction)InitializeModernGL,
		METH_VARARGS,
		"Initialize the ModernGL module inside a valid OpenGL context.\n"
		"A valid OpenGL context must exists before the function call.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tokey (bool) True on success, False on failure.\n"
		"\n"
	},
	{
		"ExtensionActive",
		(PyCFunction)ExtensionActive,
		METH_NOARGS,
		"Check for full ModernGL support.\n"
		"The initialization of the extensions are not affected by this method.\n"

		"\n"
		"Parameters:\n"
		"\tNone\n"

		"\n"
		"Returns:\n"
		"\tactive (bool) True on supported extensions, False otherwise.\n"
		"\n"
	},
	{
		"GetInfo",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"Viewport",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"Clear",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"PointSize",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"LineSize",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"EnableOnly",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"EnableBlend",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"DisableBlend",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"EnableCullFace",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"DisableCullFace",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"EnableDepthTest",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"DisableDepthTest",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"EnableMultisample",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"DisableMultisample",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"NewVertexShader",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"NewFragmentShader",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"NewGeometryShader",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteShader",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"NewProgram",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteProgram",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"Uniform1f",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"Uniform2f",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec2` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform3f",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec3` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"
		"\tv2 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform4f",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `vec4` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (float) Value to set.\n"
		"\tv1 (float) Value to set.\n"
		"\tv2 (float) Value to set.\n"
		"\tv3 (float) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform1i",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `int` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"


		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform2i",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec2` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform3i",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec3` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"
		"\tv2 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"Uniform4i",
		(PyCFunction)Dummy,
		METH_VARARGS,
		"Set the value of the uniform.\n"
		"The value must have the type of `ivec4` in the shader.\n"
		"The location of the uniform can be queried by the UniformLocation method.\n"


		"\n"
		"Parameters:\n"
		"\tlocation (int) Location of the uniform returned by the UniformLocation.\n"
		"\tv0 (int) Value to set.\n"
		"\tv1 (int) Value to set.\n"
		"\tv2 (int) Value to set.\n"
		"\tv3 (int) Value to set.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UniformMatrix",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"UniformTransposeMatrix",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"UseUniformBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewTexture",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"DeleteTexture",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"UpdateTexture",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"UseTexture",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"SetTexturePixelated",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"SetTextureFiltered",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"SetTextureMipmapped",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"BuildMipmap",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewVertexArray",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"NewAdvancedVertexArray",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteVertexArray",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"EnableAttributes",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"DisableAttributes",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewVertexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewIndexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewUniformBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"DeleteVertexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteIndexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteUniformBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"DeleteStorageBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"UpdateVertexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"UpdateIndexBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"UpdateUniformBuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"RenderTriangles",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderTriangleStrip",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderTriangleFan",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderLines",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderLineStrip",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderLineLoop",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderPoints",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderLineStripAdjacency",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderLinesAdjacency",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderTriangleStripAdjacency",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"RenderTrianglesAdjacency",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,

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
		"NewFramebuffer",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"DeleteFramebuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,

		"\n"
		"Parameters:\n"
		"\tframebuffer (int) Index of the framebuffer returned by the NewFramebuffer.\n"

		"\n"
		"Returns:\n"
		"\tNone\n"
		"\n"
	},
	{
		"UseFramebuffer",
		(PyCFunction)Dummy,
		METH_VARARGS,
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
		"GetDefaultFramebuffer",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"UseDefaultFramebuffer",
		(PyCFunction)Dummy,
		METH_NOARGS,
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
		"ReadPixels",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"ReadDepthPixels",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"ReadPixel",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"ReadDepthPixel",
		(PyCFunction)Dummy,
		METH_VARARGS | METH_KEYWORDS,
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
		"UseTextureAsImage",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewTessEvaluationShader",
		(PyCFunction)DummyExtension,
		METH_VARARGS,
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
		"NewTessControlShader",
		(PyCFunction)DummyExtension,
		METH_VARARGS,
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
		"NewComputeShader",
		(PyCFunction)DummyExtension,
		METH_VARARGS,
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
		"DeleteComputeShader",
		(PyCFunction)DummyExtension,
		METH_VARARGS,
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
		"RunComputeShader",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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
		"NewStorageBuffer",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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
		"UseStorageBuffer",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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
		"UpdateStorageBuffer",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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
		"ReadStorageBuffer",
		(PyCFunction)DummyExtension,
		METH_VARARGS | METH_KEYWORDS,
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

	{"Testing", (PyCFunction)Testing, METH_VARARGS, 0},
	// Better than nothing font

	// {"DebugFontColor", DebugFontColor, METH_VARARGS, 0},
	// {"DebugFontAlight", DebugFontAlight, METH_VARARGS, 0},
	// {"DebugFontPrint", DebugFontPrint, METH_VARARGS, 0},
	{0, 0, 0, 0},
};

void LoadImplementation() {
	PyCFunction implementation[] = {
		(PyCFunction)InitializeModernGL,
		(PyCFunction)ExtensionActive,
		(PyCFunction)GetInfo,
		(PyCFunction)Viewport,
		(PyCFunction)Clear,
		(PyCFunction)PointSize,
		(PyCFunction)LineSize,
		(PyCFunction)EnableOnly,
		(PyCFunction)EnableBlend,
		(PyCFunction)DisableBlend,
		(PyCFunction)EnableCullFace,
		(PyCFunction)DisableCullFace,
		(PyCFunction)EnableDepthTest,
		(PyCFunction)DisableDepthTest,
		(PyCFunction)EnableMultisample,
		(PyCFunction)DisableMultisample,
		(PyCFunction)NewVertexShader,
		(PyCFunction)NewFragmentShader,
		(PyCFunction)NewGeometryShader,
		(PyCFunction)DeleteShader,
		(PyCFunction)NewProgram,
		(PyCFunction)DeleteProgram,
		(PyCFunction)Uniform1f,
		(PyCFunction)Uniform2f,
		(PyCFunction)Uniform3f,
		(PyCFunction)Uniform4f,
		(PyCFunction)Uniform1i,
		(PyCFunction)Uniform2i,
		(PyCFunction)Uniform3i,
		(PyCFunction)Uniform4i,
		(PyCFunction)UniformMatrix,
		(PyCFunction)UniformTransposeMatrix,
		(PyCFunction)UseUniformBuffer,
		(PyCFunction)NewTexture,
		(PyCFunction)DeleteTexture,
		(PyCFunction)UpdateTexture,
		(PyCFunction)UseTexture,
		(PyCFunction)SetTexturePixelated,
		(PyCFunction)SetTextureFiltered,
		(PyCFunction)SetTextureMipmapped,
		(PyCFunction)BuildMipmap,
		(PyCFunction)NewVertexArray,
		(PyCFunction)NewAdvancedVertexArray,
		(PyCFunction)DeleteVertexArray,
		(PyCFunction)EnableAttributes,
		(PyCFunction)DisableAttributes,
		(PyCFunction)NewVertexBuffer,
		(PyCFunction)NewIndexBuffer,
		(PyCFunction)NewUniformBuffer,
		(PyCFunction)DeleteVertexBuffer,
		(PyCFunction)DeleteIndexBuffer,
		(PyCFunction)DeleteUniformBuffer,
		(PyCFunction)DeleteStorageBuffer,
		(PyCFunction)UpdateVertexBuffer,
		(PyCFunction)UpdateIndexBuffer,
		(PyCFunction)UpdateUniformBuffer,
		(PyCFunction)RenderTriangles,
		(PyCFunction)RenderTriangleStrip,
		(PyCFunction)RenderTriangleFan,
		(PyCFunction)RenderLines,
		(PyCFunction)RenderLineStrip,
		(PyCFunction)RenderLineLoop,
		(PyCFunction)RenderPoints,
		(PyCFunction)RenderLineStripAdjacency,
		(PyCFunction)RenderLinesAdjacency,
		(PyCFunction)RenderTriangleStripAdjacency,
		(PyCFunction)RenderTrianglesAdjacency,
		(PyCFunction)NewFramebuffer,
		(PyCFunction)DeleteFramebuffer,
		(PyCFunction)UseFramebuffer,
		(PyCFunction)GetDefaultFramebuffer,
		(PyCFunction)UseDefaultFramebuffer,
		(PyCFunction)ReadPixels,
		(PyCFunction)ReadDepthPixels,
		(PyCFunction)ReadPixel,
		(PyCFunction)ReadDepthPixel,
		(PyCFunction)UseTextureAsImage,
		(PyCFunction)NewTessEvaluationShader,
		(PyCFunction)NewTessControlShader,
		(PyCFunction)NewComputeShader,
		(PyCFunction)DeleteComputeShader,
		(PyCFunction)RunComputeShader,
		(PyCFunction)NewStorageBuffer,
		(PyCFunction)UseStorageBuffer,
		(PyCFunction)UpdateStorageBuffer,
		(PyCFunction)ReadStorageBuffer,
		(PyCFunction)Testing,
	};

	bool extensionSupport = extensionActive;
	int count = sizeof(implementation) / sizeof(implementation[0]);
	for (int i = 0; i < count; ++i) {
		if (methods[i].ml_meth == Dummy || extensionSupport) {
			methods[i].ml_meth = implementation[i];
		}
	}
}

const char * TestFunctions() {
	if (!OpenGL::isglActiveTexture()) {
		return "glActiveTexture not loaded.";
	}
	if (!OpenGL::isglAttachShader()) {
		return "glAttachShader not loaded.";
	}
	if (!OpenGL::isglBindBuffer()) {
		return "glBindBuffer not loaded.";
	}
	if (!OpenGL::isglBindBufferBase()) {
		return "glBindBufferBase not loaded.";
	}
	if (!OpenGL::isglBindFramebuffer()) {
		return "glBindFramebuffer not loaded.";
	}
	if (!OpenGL::isglBindTexture()) {
		return "glBindTexture not loaded.";
	}
	if (!OpenGL::isglBindVertexArray()) {
		return "glBindVertexArray not loaded.";
	}
	if (!OpenGL::isglBlendFunc()) {
		return "glBlendFunc not loaded.";
	}
	if (!OpenGL::isglBufferData()) {
		return "glBufferData not loaded.";
	}
	if (!OpenGL::isglBufferSubData()) {
		return "glBufferSubData not loaded.";
	}
	if (!OpenGL::isglClear()) {
		return "glClear not loaded.";
	}
	if (!OpenGL::isglClearColor()) {
		return "glClearColor not loaded.";
	}
	if (!OpenGL::isglCompileShader()) {
		return "glCompileShader not loaded.";
	}
	if (!OpenGL::isglCreateProgram()) {
		return "glCreateProgram not loaded.";
	}
	if (!OpenGL::isglCreateShader()) {
		return "glCreateShader not loaded.";
	}
	if (!OpenGL::isglDeleteBuffers()) {
		return "glDeleteBuffers not loaded.";
	}
	if (!OpenGL::isglDeleteFramebuffers()) {
		return "glDeleteFramebuffers not loaded.";
	}
	if (!OpenGL::isglDeleteProgram()) {
		return "glDeleteProgram not loaded.";
	}
	if (!OpenGL::isglDeleteShader()) {
		return "glDeleteShader not loaded.";
	}
	if (!OpenGL::isglDeleteTextures()) {
		return "glDeleteTextures not loaded.";
	}
	if (!OpenGL::isglDeleteVertexArrays()) {
		return "glDeleteVertexArrays not loaded.";
	}
	if (!OpenGL::isglDisable()) {
		return "glDisable not loaded.";
	}
	if (!OpenGL::isglDisableVertexAttribArray()) {
		return "glDisableVertexAttribArray not loaded.";
	}
	if (!OpenGL::isglDrawArraysInstanced()) {
		return "glDrawArraysInstanced not loaded.";
	}
	if (!OpenGL::isglDrawElementsInstanced()) {
		return "glDrawElementsInstanced not loaded.";
	}
	if (!OpenGL::isglEnable()) {
		return "glEnable not loaded.";
	}
	if (!OpenGL::isglEnableVertexAttribArray()) {
		return "glEnableVertexAttribArray not loaded.";
	}
	if (!OpenGL::isglFramebufferTexture2D()) {
		return "glFramebufferTexture2D not loaded.";
	}
	if (!OpenGL::isglGenBuffers()) {
		return "glGenBuffers not loaded.";
	}
	if (!OpenGL::isglGenerateMipmap()) {
		return "glGenerateMipmap not loaded.";
	}
	if (!OpenGL::isglGenFramebuffers()) {
		return "glGenFramebuffers not loaded.";
	}
	if (!OpenGL::isglGenTextures()) {
		return "glGenTextures not loaded.";
	}
	if (!OpenGL::isglGenVertexArrays()) {
		return "glGenVertexArrays not loaded.";
	}
	if (!OpenGL::isglGetAttachedShaders()) {
		return "glGetAttachedShaders not loaded.";
	}
	if (!OpenGL::isglGetAttribLocation()) {
		return "glGetAttribLocation not loaded.";
	}
	if (!OpenGL::isglGetError()) {
		return "glGetError not loaded.";
	}
	if (!OpenGL::isglGetFramebufferAttachmentParameteriv()) {
		return "glGetFramebufferAttachmentParameteriv not loaded.";
	}
	if (!OpenGL::isglGetIntegerv()) {
		return "glGetIntegerv not loaded.";
	}
	if (!OpenGL::isglGetProgramInfoLog()) {
		return "glGetProgramInfoLog not loaded.";
	}
	if (!OpenGL::isglGetProgramiv()) {
		return "glGetProgramiv not loaded.";
	}
	if (!OpenGL::isglGetShaderInfoLog()) {
		return "glGetShaderInfoLog not loaded.";
	}
	if (!OpenGL::isglGetShaderiv()) {
		return "glGetShaderiv not loaded.";
	}
	if (!OpenGL::isglGetString()) {
		return "glGetString not loaded.";
	}
	if (!OpenGL::isglGetStringi()) {
		return "glGetStringi not loaded.";
	}
	if (!OpenGL::isglGetUniformBlockIndex()) {
		return "glGetUniformBlockIndex not loaded.";
	}
	if (!OpenGL::isglGetUniformLocation()) {
		return "glGetUniformLocation not loaded.";
	}
	if (!OpenGL::isglLineWidth()) {
		return "glLineWidth not loaded.";
	}
	if (!OpenGL::isglLinkProgram()) {
		return "glLinkProgram not loaded.";
	}
	if (!OpenGL::isglMapBufferRange()) {
		return "glMapBufferRange not loaded.";
	}
	if (!OpenGL::isglPointSize()) {
		return "glPointSize not loaded.";
	}
	if (!OpenGL::isglPrimitiveRestartIndex()) {
		return "glPrimitiveRestartIndex not loaded.";
	}
	if (!OpenGL::isglReadPixels()) {
		return "glReadPixels not loaded.";
	}
	if (!OpenGL::isglShaderSource()) {
		return "glShaderSource not loaded.";
	}
	if (!OpenGL::isglTexImage2D()) {
		return "glTexImage2D not loaded.";
	}
	if (!OpenGL::isglTexParameteri()) {
		return "glTexParameteri not loaded.";
	}
	if (!OpenGL::isglUniform1f()) {
		return "glUniform1f not loaded.";
	}
	if (!OpenGL::isglUniform1i()) {
		return "glUniform1i not loaded.";
	}
	if (!OpenGL::isglUniform2f()) {
		return "glUniform2f not loaded.";
	}
	if (!OpenGL::isglUniform2i()) {
		return "glUniform2i not loaded.";
	}
	if (!OpenGL::isglUniform3f()) {
		return "glUniform3f not loaded.";
	}
	if (!OpenGL::isglUniform3i()) {
		return "glUniform3i not loaded.";
	}
	if (!OpenGL::isglUniform4f()) {
		return "glUniform4f not loaded.";
	}
	if (!OpenGL::isglUniform4i()) {
		return "glUniform4i not loaded.";
	}
	if (!OpenGL::isglUniformMatrix4fv()) {
		return "glUniformMatrix4fv not loaded.";
	}
	if (!OpenGL::isglUnmapBuffer()) {
		return "glUnmapBuffer not loaded.";
	}
	if (!OpenGL::isglUseProgram()) {
		return "glUseProgram not loaded.";
	}
	if (!OpenGL::isglVertexAttribPointer()) {
		return "glVertexAttribPointer not loaded.";
	}
	if (!OpenGL::isglViewport()) {
		return "glViewport not loaded.";
	}
	if (!OpenGL::isglGetBufferParameteriv()) {
		return "glGetBufferParameteriv not loaded.";
	}
	if (!OpenGL::isglGetActiveAttrib()) {
		return "glGetActiveAttrib not loaded.";
	}
	if (!OpenGL::isglGetActiveUniform()) {
		return "glGetActiveUniform not loaded.";
	}

	return 0;
}

bool TestExtensions() {
	int extensions = 0;
	OpenGL::glGetIntegerv(OpenGL::GL_NUM_EXTENSIONS, &extensions);

	bool shader_storage_buffer_object = false;
	bool tessellation_shader = false;
	bool compute_shader = false;

	for (int i = 0; i < extensions; ++i) {
		const char * ext = (const char *)OpenGL::glGetStringi(OpenGL::GL_EXTENSIONS, i);
		if (!ext) {
			continue;
		}

		if (!shader_storage_buffer_object && !strcmp("GL_ARB_shader_storage_buffer_object", ext)) {
			shader_storage_buffer_object = true;
		}

		if (!tessellation_shader && !strcmp("GL_ARB_tessellation_shader", ext)) {
			tessellation_shader = true;
		}

		if (!compute_shader && !strcmp("GL_ARB_compute_shader", ext)) {
			compute_shader = true;
		}
	}

	if (!shader_storage_buffer_object) {
		return false;
	}

	if (!tessellation_shader) {
		return false;
	}
	
	if (!compute_shader) {
		return false;
	}

	if (!OpenGL::isglBindImageTexture()) {
		return false;
	}

	if (!OpenGL::isglDispatchCompute()) {
		return false;
	}

	return true;
}

PyObject * InitializeModernGL(PyObject * self, PyObject * args) {
	if (initialized) {
		Py_RETURN_NONE;
	}

	if (!PyArg_ParseTuple(args, ":InitializeModernGL")) {
		return 0;
	}

	// Initialize OpenGL
	if (!OpenGL::InitializeOpenGL()) {
		PyErr_SetString(ModuleError, "InitializeOpenGL failed.");
		return 0;
	}

	// Test all the gl functions
	const char * error = TestFunctions();
	if (error) {
		PyErr_SetString(ModuleError, error);
		return 0;
	}

	// Test for better support
	extensionActive = TestExtensions();
	
	// Default blending
	OpenGL::glBlendFunc(OpenGL::GL_SRC_ALPHA, OpenGL::GL_ONE_MINUS_SRC_ALPHA);

	// Default primitive restart index
	OpenGL::glEnable(OpenGL::GL_PRIMITIVE_RESTART);
	OpenGL::glPrimitiveRestartIndex(-1);

	// Default VAO for GL_ELEMENT_ARRAY operations
	OpenGL::glGenVertexArrays(1, (OpenGL::GLuint *)&defaultVertexArray);
	OpenGL::glBindVertexArray(defaultVertexArray);

	// Default FBO and program
	OpenGL::glGetIntegerv(OpenGL::GL_DRAW_FRAMEBUFFER_BINDING, (OpenGL::GLint *)&defaultFramebuffer);
	OpenGL::glGetIntegerv(OpenGL::GL_CURRENT_PROGRAM, (OpenGL::GLint *)&defaultProgram);

	// Default texture unit for texture operations
	int maxTextureUnits = 1;
	OpenGL::glGetIntegerv(OpenGL::GL_MAX_TEXTURE_IMAGE_UNITS, (OpenGL::GLint *)&maxTextureUnits);
	defaultTextureUnit = maxTextureUnits - 1;

	activeFramebuffer = defaultFramebuffer;
	activeProgram = defaultProgram;

	int viewport[4] = {};
	OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewport);
	activeViewportWidth = viewport[2];
	activeViewportHeight = viewport[3];

	LoadImplementation();
	initialized = true;
	Py_RETURN_NONE;
}

bool ModuleReady() {
	if (PyType_Ready(&FramebufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexArrayType) < 0) {
		return false;
	}

	if (PyType_Ready(&VertexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&IndexBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&StorageBufferType) < 0) {
		return false;
	}

	if (PyType_Ready(&TextureType) < 0) {
		return false;
	}

	if (PyType_Ready(&ShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&ProgramType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&UniformBufferLocationType) < 0) {
		return false;
	}

	if (PyType_Ready(&ComputeShaderType) < 0) {
		return false;
	}

	if (PyType_Ready(&EnableFlagType) < 0) {
		return false;
	}

	return true;
}

PyObject * InitModule(PyObject * module) {
	if (!module) {
		return module;
	}
	
	Py_INCREF(&FramebufferType);
	Py_INCREF(&VertexArrayType);
	Py_INCREF(&VertexBufferType);
	Py_INCREF(&IndexBufferType);
	Py_INCREF(&UniformBufferType);
	Py_INCREF(&StorageBufferType);
	Py_INCREF(&TextureType);
	Py_INCREF(&ShaderType);
	Py_INCREF(&ProgramType);
	Py_INCREF(&UniformLocationType);
	Py_INCREF(&UniformBufferLocationType);
	Py_INCREF(&ComputeShaderType);
	Py_INCREF(&EnableFlagType);

	PyModule_AddObject(module, "Framebuffer", (PyObject *)&FramebufferType);
	PyModule_AddObject(module, "VertexArray", (PyObject *)&VertexArrayType);
	PyModule_AddObject(module, "VertexBuffer", (PyObject *)&VertexBufferType);
	PyModule_AddObject(module, "IndexBuffer", (PyObject *)&IndexBufferType);
	PyModule_AddObject(module, "UniformBuffer", (PyObject *)&UniformBufferType);
	PyModule_AddObject(module, "StorageBuffer", (PyObject *)&StorageBufferType);
	PyModule_AddObject(module, "Texture", (PyObject *)&TextureType);
	PyModule_AddObject(module, "Shader", (PyObject *)&ShaderType);
	PyModule_AddObject(module, "Program", (PyObject *)&ProgramType);
	PyModule_AddObject(module, "UniformLocation", (PyObject *)&UniformLocationType);
	PyModule_AddObject(module, "UniformBufferLocation", (PyObject *)&UniformBufferLocationType);
	PyModule_AddObject(module, "ComputeShader", (PyObject *)&ComputeShaderType);
	PyModule_AddObject(module, "EnableFlag", (PyObject *)&EnableFlagType);

	ModuleError = PyErr_NewException((char *)"ModernGL.Error", 0, 0);
	Py_INCREF(ModuleError);

	PyModule_AddObject(module, "Error", ModuleError);

	PyModule_AddObject(module, "ENABLE_NOTHING", CreateEnableFlagType(ENABLE_NOTHING));
	PyModule_AddObject(module, "ENABLE_BLEND", CreateEnableFlagType(ENABLE_BLEND));
	PyModule_AddObject(module, "ENABLE_CULL_FACE", CreateEnableFlagType(ENABLE_CULL_FACE));
	PyModule_AddObject(module, "ENABLE_DEPTH_TEST", CreateEnableFlagType(ENABLE_DEPTH_TEST));
	PyModule_AddObject(module, "ENABLE_MULTISAMPLE", CreateEnableFlagType(ENABLE_MULTISAMPLE));
	PyModule_AddObject(module, "ENABLE_ALL", CreateEnableFlagType(ENABLE_ALL));

	PyModule_AddStringConstant(module, "VERSION", "2.2.0");
	
	PyModule_AddStringConstant(module, "__AUTHOR_NAME__", "Szabolcs Dombi");
	PyModule_AddStringConstant(module, "__AUTHOR_EMAIL__", "cprogrammer1994@gmail.com");

	return module;
}

#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {PyModuleDef_HEAD_INIT, "ModernGL", 0, -1, methods, 0, 0, 0, 0};

extern "C" {
	PyObject * PyInit_ModernGL();
}

PyObject * PyInit_ModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}
	PyObject * module = PyModule_Create(&moduledef);
	return InitModule(module);
}

#else

extern "C" {
	PyObject * initModernGL();
}

PyObject * initModernGL() {
	if (!ModuleReady()) {
		PyErr_SetString(PyExc_ImportError, "cannot import module");
		return 0;
	}
	PyObject * module = Py_InitModule("ModernGL", methods);
	return InitModule(module);
}

#endif
