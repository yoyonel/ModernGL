#pragma once

#include "Global.hpp"

const int ENABLE_NOTHING = 0x00;
const int ENABLE_BLEND = 0x01;
const int ENABLE_CULL_FACE = 0x02;
const int ENABLE_DEPTH_TEST = 0x04;
const int ENABLE_MULTISAMPLE = 0x08;
const int ENABLE_ALL = 0x0F;

extern PyObject * ModuleError;

extern int defaultTextureUnit;
extern int defaultVertexArray;
extern int defaultFramebuffer;
extern int defaultProgram;

extern int activeProgram;
extern int activeFramebuffer;

extern int activeViewportWidth;
extern int activeViewportHeight;

enum ShaderCategory {
	VERTEX_SHADER,
	FRAGMENT_SHADER,
	GEOMETRY_SHADER,
	TESS_EVALUATION_SHADER,
	TESS_CONTROL_SHADER,
	NUM_SHADER_CATEGORIES,
};

struct Framebuffer {
	PyObject_HEAD
	int fbo;
	int color;
	int depth;
};

struct VertexArray {
	PyObject_HEAD
	int vao;
	bool indexed;
	int program;
};

struct VertexBuffer {
	PyObject_HEAD
	int vbo;
	int size;
};

struct IndexBuffer {
	PyObject_HEAD
	int ibo;
	int size;
};

struct UniformBuffer {
	PyObject_HEAD
	int ubo;
	int size;
};

struct StorageBuffer {
	PyObject_HEAD
	int sbo;
	int size;
};

struct Texture {
	PyObject_HEAD
	int texture;
	int width;
	int height;
	int components;
};

struct Shader {
	PyObject_HEAD
	int shader;
	ShaderCategory category;
	bool attached;
};

struct Program {
	PyObject_HEAD
	int program;
};

struct UniformLocation {
	PyObject_HEAD
	int location;
	int program;
};

struct UniformBufferLocation {
	PyObject_HEAD
	int location;
	int program;
};

struct ComputeShader {
	PyObject_HEAD
	int shader;
	int program;
};

struct EnableFlag {
	PyObject_HEAD
	unsigned value;
};

extern PyTypeObject FramebufferType;
extern PyTypeObject VertexArrayType;
extern PyTypeObject VertexBufferType;
extern PyTypeObject IndexBufferType;
extern PyTypeObject UniformBufferType;
extern PyTypeObject StorageBufferType;
extern PyTypeObject TextureType;
extern PyTypeObject ShaderType;
extern PyTypeObject ProgramType;
extern PyTypeObject UniformLocationType;
extern PyTypeObject UniformBufferLocationType;
extern PyTypeObject ComputeShaderType;
extern PyTypeObject EnableFlagType;

PyObject * CreateFramebufferType(int fbo, int color, int depth);
PyObject * CreateVertexArrayType(int vao, int program, bool indexed);
PyObject * CreateVertexBufferType(int vbo, int size);
PyObject * CreateIndexBufferType(int ibo, int size);
PyObject * CreateUniformBufferType(int ubo, int size);
PyObject * CreateStorageBufferType(int sbo, int size);
PyObject * CreateTextureType(int texture, int width, int height, int components);
PyObject * CreateShaderType(int shader, ShaderCategory category);
PyObject * CreateProgramType(int program);
PyObject * CreateUniformLocationType(int location, int program);
PyObject * CreateUniformBufferLocationType(int location, int program);
PyObject * CreateComputeShaderType(int shader, int program);
PyObject * CreateEnableFlagType(unsigned value);

PyObject * InitializeModernGL(PyObject * self, PyObject * args);
PyObject * ExtensionActive(PyObject * self);

PyObject * Viewport(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * Clear(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * GetInfo(PyObject * self);

PyObject * PointSize(PyObject * self, PyObject * args);
PyObject * LineSize(PyObject * self, PyObject * args);

PyObject * EnableOnly(PyObject * self, PyObject * args);

PyObject * EnableBlend(PyObject * self);
PyObject * EnableCullFace(PyObject * self);
PyObject * EnableDepthTest(PyObject * self);
PyObject * EnableMultisample(PyObject * self);

PyObject * DisableBlend(PyObject * self);
PyObject * DisableCullFace(PyObject * self);
PyObject * DisableDepthTest(PyObject * self);
PyObject * DisableMultisample(PyObject * self);

PyObject * NewComputeShader(PyObject * self, PyObject * args);
PyObject * DeleteComputeShader(PyObject * self, PyObject * args);
PyObject * RunComputeShader(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * NewVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * NewStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * UseStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * DeleteVertexBuffer(PyObject * self, PyObject * args);
PyObject * DeleteIndexBuffer(PyObject * self, PyObject * args);
PyObject * DeleteUniformBuffer(PyObject * self, PyObject * args);
PyObject * DeleteStorageBuffer(PyObject * self, PyObject * args);

PyObject * NewVertexArray(PyObject * self, PyObject * args);
PyObject * NewAdvancedVertexArray(PyObject * self, PyObject * args);
PyObject * DeleteVertexArray(PyObject * self, PyObject * args);

PyObject * EnableAttributes(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DisableAttributes(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * NewVertexShader(PyObject * self, PyObject * args);
PyObject * NewFragmentShader(PyObject * self, PyObject * args);
PyObject * NewGeometryShader(PyObject * self, PyObject * args);
PyObject * NewTessControlShader(PyObject * self, PyObject * args);
PyObject * NewTessEvaluationShader(PyObject * self, PyObject * args);
PyObject * DeleteShader(PyObject * self, PyObject * args);

PyObject * NewProgram(PyObject * self, PyObject * args);
PyObject * DeleteProgram(PyObject * self, PyObject * args);

PyObject * RenderPoints(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLines(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineLoop(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangles(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleStrip(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleFan(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLinesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderLineStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTrianglesAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * RenderTriangleStripAdjacency(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * Uniform1f(PyObject * self, PyObject * args);
PyObject * Uniform1i(PyObject * self, PyObject * args);
PyObject * Uniform2f(PyObject * self, PyObject * args);
PyObject * Uniform2i(PyObject * self, PyObject * args);
PyObject * Uniform3f(PyObject * self, PyObject * args);
PyObject * Uniform3i(PyObject * self, PyObject * args);
PyObject * Uniform4f(PyObject * self, PyObject * args);
PyObject * Uniform4i(PyObject * self, PyObject * args);
PyObject * UniformMatrix(PyObject * self, PyObject * args);
PyObject * UniformTransposeMatrix(PyObject * self, PyObject * args);
PyObject * UseUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * UpdateVertexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateUniformBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateIndexBuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateStorageBuffer(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * NewFramebuffer(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DeleteFramebuffer(PyObject * self, PyObject * args);
PyObject * UseFramebuffer(PyObject * self, PyObject * args);

PyObject * GetDefaultFramebuffer(PyObject * self);
PyObject * UseDefaultFramebuffer(PyObject * self);

PyObject * ReadPixel(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadPixels(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadDepthPixel(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * ReadDepthPixels(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * NewTexture(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * UpdateTexture(PyObject * self, PyObject * args, PyObject * kwargs);
PyObject * DeleteTexture(PyObject * self, PyObject * args);

PyObject * BuildMipmap(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * UseTexture(PyObject * self, PyObject * args);
PyObject * UseTextureAsImage(PyObject * self, PyObject * args, PyObject * kwargs);

PyObject * SetTextureFiltered(PyObject * self, PyObject * args);
PyObject * SetTextureMipmapped(PyObject * self, PyObject * args);
PyObject * SetTexturePixelated(PyObject * self, PyObject * args);
