#pragma once

#include "Common.hpp"

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
	bool floats;
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
	int type;
};

struct UniformBufferLocation {
	PyObject_HEAD
	int location;
	int program;
	int size;
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
PyObject * CreateTextureType(int texture, int width, int height, int components, bool floats);
PyObject * CreateShaderType(int shader, ShaderCategory category);
PyObject * CreateProgramType(int program);
PyObject * CreateUniformLocationType(int location, int program, int type);
PyObject * CreateUniformBufferLocationType(int location, int program, int size);
PyObject * CreateComputeShaderType(int shader, int program);
PyObject * CreateEnableFlagType(unsigned value);
