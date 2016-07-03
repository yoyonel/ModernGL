#include "Python-Types.hpp"

#include "Python-ModernGL.hpp"

PyObject * Framebuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int Framebuffer_init(Framebuffer * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Framebuffer. Call NewFramebuffer(...) to get a Framebuffer object.");
	return -1;
}

void Framebuffer_dealloc(Framebuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * Framebuffer_str(Framebuffer * self) {
	return PyUnicode_FromFormat("<Framebuffer = %d>", self->fbo);
}

PyTypeObject FramebufferType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Framebuffer",
	sizeof(Framebuffer),
	0,
	(destructor)Framebuffer_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Framebuffer_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Framebuffer",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Framebuffer_init,
	0,
	Framebuffer_new,
};

PyObject * VertexArray_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int VertexArray_init(VertexArray * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate VertexArray. Call NewVertexArray(...) to get a VertexArray object.");
	return -1;
}

void VertexArray_dealloc(VertexArray * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * VertexArray_str(VertexArray * self) {
	return PyUnicode_FromFormat("<VertexArray = %d>", self->vao);
}

PyTypeObject VertexArrayType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexArray",
	sizeof(VertexArray),
	0,
	(destructor)VertexArray_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)VertexArray_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"VertexArray",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)VertexArray_init,
	0,
	VertexArray_new,
};

PyObject * VertexBuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int VertexBuffer_init(VertexBuffer * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate VertexBuffer. Call NewVertexBuffer(...) to get a VertexBuffer object.");
	return -1;
}

void VertexBuffer_dealloc(VertexBuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * VertexBuffer_str(VertexBuffer * self) {
	return PyUnicode_FromFormat("<VertexBuffer = %d>", self->vbo);
}

PyTypeObject VertexBufferType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.VertexBuffer",
	sizeof(VertexBuffer),
	0,
	(destructor)VertexBuffer_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)VertexBuffer_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"VertexBuffer",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)VertexBuffer_init,
	0,
	VertexBuffer_new,
};

PyObject * IndexBuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int IndexBuffer_init(IndexBuffer * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate IndexBuffer. Call NewIndexBuffer(...) to get a IndexBuffer object.");
	return -1;
}

void IndexBuffer_dealloc(IndexBuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * IndexBuffer_str(IndexBuffer * self) {
	return PyUnicode_FromFormat("<IndexBuffer = %d>", self->ibo);
}

PyTypeObject IndexBufferType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.IndexBuffer",
	sizeof(IndexBuffer),
	0,
	(destructor)IndexBuffer_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)IndexBuffer_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"IndexBuffer",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)IndexBuffer_init,
	0,
	IndexBuffer_new,
};

PyObject * UniformBuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int UniformBuffer_init(UniformBuffer * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate UniformBuffer. Call NewUniformBuffer(...) to get a UniformBuffer object.");
	return -1;
}

void UniformBuffer_dealloc(UniformBuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * UniformBuffer_str(UniformBuffer * self) {
	return PyUnicode_FromFormat("<UniformBuffer = %d>", self->ubo);
}

PyTypeObject UniformBufferType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.UniformBuffer",
	sizeof(UniformBuffer),
	0,
	(destructor)UniformBuffer_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)UniformBuffer_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"UniformBuffer",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)UniformBuffer_init,
	0,
	UniformBuffer_new,
};

PyObject * StorageBuffer_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int StorageBuffer_init(StorageBuffer * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate StorageBuffer. Call NewStorageBuffer(...) to get a StorageBuffer object.");
	return -1;
}

void StorageBuffer_dealloc(StorageBuffer * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * StorageBuffer_str(StorageBuffer * self) {
	return PyUnicode_FromFormat("<StorageBuffer = %d>", self->ssbo);
}

PyTypeObject StorageBufferType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.StorageBuffer",
	sizeof(StorageBuffer),
	0,
	(destructor)StorageBuffer_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)StorageBuffer_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"StorageBuffer",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)StorageBuffer_init,
	0,
	StorageBuffer_new,
};

PyObject * Texture_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int Texture_init(Texture * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Texture. Call NewTexture(...) to get a Texture object.");
	return -1;
}

void Texture_dealloc(Texture * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * Texture_str(Texture * self) {
	return PyUnicode_FromFormat("<Texture = %d>", self->texture);
}

PyTypeObject TextureType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Texture",
	sizeof(Texture),
	0,
	(destructor)Texture_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Texture_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Texture",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Texture_init,
	0,
	Texture_new,
};

PyObject * Shader_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int Shader_init(Shader * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Shader. Call New...Shader(...) to get a Shader object.");
	return -1;
}

void Shader_dealloc(Shader * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * Shader_str(Shader * self) {
	return PyUnicode_FromFormat("<Shader = %d>", self->shader);
}

PyTypeObject ShaderType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Shader",
	sizeof(Shader),
	0,
	(destructor)Shader_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Shader_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Shader",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Shader_init,
	0,
	Shader_new,
};

PyObject * Program_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int Program_init(Program * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate Program. Call NewProgram(...) to get a Program object.");
	return -1;
}

void Program_dealloc(Program * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * Program_str(Program * self) {
	return PyUnicode_FromFormat("<Program = %d>", self->program);
}

PyTypeObject ProgramType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.Program",
	sizeof(Program),
	0,
	(destructor)Program_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)Program_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"Program",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)Program_init,
	0,
	Program_new,
};

PyObject * AttributeLocation_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int AttributeLocation_init(AttributeLocation * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate AttributeLocation. Call GetAttributeLocation(...) to get a AttributeLocation object.");
	return -1;
}

void AttributeLocation_dealloc(AttributeLocation * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * AttributeLocation_str(AttributeLocation * self) {
	return PyUnicode_FromFormat("<AttributeLocation = %d>", self->location);
}

PyTypeObject AttributeLocationType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.AttributeLocation",
	sizeof(AttributeLocation),
	0,
	(destructor)AttributeLocation_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)AttributeLocation_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"AttributeLocation",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)AttributeLocation_init,
	0,
	AttributeLocation_new,
};

PyObject * UniformLocation_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int UniformLocation_init(UniformLocation * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate UniformLocation. Call GetUniformLocation(...) to get a UniformLocation object.");
	return -1;
}

void UniformLocation_dealloc(UniformLocation * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * UniformLocation_str(UniformLocation * self) {
	return PyUnicode_FromFormat("<UniformLocation = %d>", self->location);
}

PyTypeObject UniformLocationType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.UniformLocation",
	sizeof(UniformLocation),
	0,
	(destructor)UniformLocation_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)UniformLocation_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"UniformLocation",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)UniformLocation_init,
	0,
	UniformLocation_new,
};

PyObject * UniformBlockLocation_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int UniformBlockLocation_init(UniformBlockLocation * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate UniformBlockLocation. Call GetUniformBlockLocation(...) to get a UniformBlockLocation object.");
	return -1;
}

void UniformBlockLocation_dealloc(UniformBlockLocation * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * UniformBlockLocation_str(UniformBlockLocation * self) {
	return PyUnicode_FromFormat("<UniformBlockLocation = %d>", self->location);
}

PyTypeObject UniformBlockLocationType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.UniformBlockLocation",
	sizeof(UniformBlockLocation),
	0,
	(destructor)UniformBlockLocation_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)UniformBlockLocation_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"UniformBlockLocation",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)UniformBlockLocation_init,
	0,
	UniformBlockLocation_new,
};

PyObject * ComputeShader_new(PyTypeObject * type, PyObject * args, PyObject * kwargs) {
	return type->tp_alloc(type, 0);
}

int ComputeShader_init(ComputeShader * self, PyObject * args, PyObject * kwargs) {
	PyErr_SetString(ModuleError, "Cannot instantiate ComputeShader. Call NewComputeShader(...) to get a ComputeShader object.");
	return -1;
}

void ComputeShader_dealloc(ComputeShader * self) {
	Py_TYPE(self)->tp_free((PyObject*)self);
}

PyObject * ComputeShader_str(ComputeShader * self) {
	return PyUnicode_FromFormat("<ComputeShader = %d>", self->shader);
}

PyTypeObject ComputeShaderType = {
	PyVarObject_HEAD_INIT(0, 0)
	"ModernGL.ComputeShader",
	sizeof(ComputeShader),
	0,
	(destructor)ComputeShader_dealloc,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(unaryfunc)ComputeShader_str,
	0,
	0,
	0,
	Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
	"ComputeShader",
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(initproc)ComputeShader_init,
	0,
	ComputeShader_new,
};

PyObject * CreateFramebufferType(int fbo) {
	Framebuffer * obj = (Framebuffer *)FramebufferType.tp_alloc(&FramebufferType, 0);

	if (obj != 0) {
		obj->fbo = fbo;
	}

	return (PyObject *)obj;
}

PyObject * CreateVertexArrayType(int vao) {
	VertexArray * obj = (VertexArray *)VertexArrayType.tp_alloc(&VertexArrayType, 0);

	if (obj != 0) {
		obj->vao = vao;
	}

	return (PyObject *)obj;
}

PyObject * CreateVertexBufferType(int vbo) {
	VertexBuffer * obj = (VertexBuffer *)VertexBufferType.tp_alloc(&VertexBufferType, 0);

	if (obj != 0) {
		obj->vbo = vbo;
	}

	return (PyObject *)obj;
}

PyObject * CreateIndexBufferType(int ibo) {
	IndexBuffer * obj = (IndexBuffer *)IndexBufferType.tp_alloc(&IndexBufferType, 0);

	if (obj != 0) {
		obj->ibo = ibo;
	}

	return (PyObject *)obj;
}

PyObject * CreateUniformBufferType(int ubo) {
	UniformBuffer * obj = (UniformBuffer *)UniformBufferType.tp_alloc(&UniformBufferType, 0);

	if (obj != 0) {
		obj->ubo = ubo;
	}

	return (PyObject *)obj;
}

PyObject * CreateStorageBufferType(int ssbo) {
	StorageBuffer * obj = (StorageBuffer *)StorageBufferType.tp_alloc(&StorageBufferType, 0);

	if (obj != 0) {
		obj->ssbo = ssbo;
	}

	return (PyObject *)obj;
}

PyObject * CreateTextureType(int texture, int components) {
	Texture * obj = (Texture *)TextureType.tp_alloc(&TextureType, 0);

	if (obj != 0) {
		obj->texture = texture;
		obj->components = components;
	}

	return (PyObject *)obj;
}

PyObject * CreateShaderType(int shader) {
	Shader * obj = (Shader *)ShaderType.tp_alloc(&ShaderType, 0);

	if (obj != 0) {
		obj->shader = shader;
	}

	return (PyObject *)obj;
}

PyObject * CreateProgramType(int program) {
	Program * obj = (Program *)ProgramType.tp_alloc(&ProgramType, 0);

	if (obj != 0) {
		obj->program = program;
	}

	return (PyObject *)obj;
}

PyObject * CreateAttributeLocationType(int location) {
	AttributeLocation * obj = (AttributeLocation *)AttributeLocationType.tp_alloc(&AttributeLocationType, 0);

	if (obj != 0) {
		obj->location = location;
	}

	return (PyObject *)obj;
}

PyObject * CreateUniformLocationType(int location) {
	UniformLocation * obj = (UniformLocation *)UniformLocationType.tp_alloc(&UniformLocationType, 0);

	if (obj != 0) {
		obj->location = location;
	}

	return (PyObject *)obj;
}

PyObject * CreateUniformBlockLocationType(int location) {
	UniformBlockLocation * obj = (UniformBlockLocation *)UniformBlockLocationType.tp_alloc(&UniformBlockLocationType, 0);

	if (obj != 0) {
		obj->location = location;
	}

	return (PyObject *)obj;
}

PyObject * CreateComputeShaderType(int shader) {
	ComputeShader * obj = (ComputeShader *)ComputeShaderType.tp_alloc(&ComputeShaderType, 0);

	if (obj != 0) {
		obj->shader = shader;
	}

	return (PyObject *)obj;
}

bool ValidFramebufferType(Framebuffer * framebuffer) {
	return PyObject_TypeCheck((PyObject *)framebuffer, &FramebufferType);
}

bool ValidVertexArrayType(VertexArray * vertexArray) {
	return PyObject_TypeCheck((PyObject *)vertexArray, &VertexArrayType);
}

bool ValidVertexBufferType(VertexBuffer * vertexBuffer) {
	return PyObject_TypeCheck((PyObject *)vertexBuffer, &VertexBufferType);
}

bool ValidIndexBufferType(IndexBuffer * indexBuffer) {
	return PyObject_TypeCheck((PyObject *)indexBuffer, &IndexBufferType);
}

bool ValidUniformBufferType(UniformBuffer * uniformBuffer) {
	return PyObject_TypeCheck((PyObject *)uniformBuffer, &UniformBufferType);
}

bool ValidStorageBufferType(StorageBuffer * storageBuffer) {
	return PyObject_TypeCheck((PyObject *)storageBuffer, &StorageBufferType);
}

bool ValidTextureType(Texture * texture) {
	return PyObject_TypeCheck((PyObject *)texture, &TextureType);
}

bool ValidShaderType(Shader * shader) {
	return PyObject_TypeCheck((PyObject *)shader, &ShaderType);
}

bool ValidProgramType(Program * program) {
	return PyObject_TypeCheck((PyObject *)program, &ProgramType);
}

bool ValidAttributeLocationType(AttributeLocation * attributeLocation) {
	return PyObject_TypeCheck((PyObject *)attributeLocation, &AttributeLocationType);
}

bool ValidUniformLocationType(UniformLocation * uniformLocation) {
	return PyObject_TypeCheck((PyObject *)uniformLocation, &UniformLocationType);
}

bool ValidUniformBlockLocationType(UniformBlockLocation * uniformBlockLocation) {
	return PyObject_TypeCheck((PyObject *)uniformBlockLocation, &UniformBlockLocationType);
}

bool ValidComputeShaderType(ComputeShader * computeShader) {
	return PyObject_TypeCheck((PyObject *)computeShader, &ComputeShaderType);
}
