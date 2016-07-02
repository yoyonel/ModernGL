#pragma once

#include "Global.hpp"

#include "Python.h"
#include "structmember.h"

struct Framebuffer {
	PyObject_HEAD
	int fbo;
};

struct VertexArray {
	PyObject_HEAD
	int vao;
};

struct VertexBuffer {
	PyObject_HEAD
	int vbo;
};

struct IndexBuffer {
	PyObject_HEAD
	int ibo;
};

struct UniformBuffer {
	PyObject_HEAD
	int ubo;
};

struct StorageBuffer {
	PyObject_HEAD
	int ssbo;
};

struct Texture {
	PyObject_HEAD
	int texture;
};

struct Shader {
	PyObject_HEAD
	int shader;
};

struct Program {
	PyObject_HEAD
	int program;
};

struct AttributeLocation {
	PyObject_HEAD
	int location;
};

struct UniformLocation {
	PyObject_HEAD
	int location;
};

struct UniformBlockLocation {
	PyObject_HEAD
	int location;
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
extern PyTypeObject AttributeLocationType;
extern PyTypeObject UniformLocationType;
extern PyTypeObject UniformBlockLocationType;

PyObject * CreateFramebufferType(int fbo);
PyObject * CreateVertexArrayType(int vao);
PyObject * CreateVertexBufferType(int vbo);
PyObject * CreateIndexBufferType(int ibo);
PyObject * CreateUniformBufferType(int ubo);
PyObject * CreateStorageBufferType(int ssbo);
PyObject * CreateTextureType(int texture);
PyObject * CreateShaderType(int shader);
PyObject * CreateProgramType(int program);
PyObject * CreateAttributeLocationType(int location);
PyObject * CreateUniformLocationType(int location);
PyObject * CreateUniformBlockLocationType(int location);
