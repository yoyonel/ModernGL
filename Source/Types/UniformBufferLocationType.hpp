#pragma once

struct UniformBufferLocation {
	PyObject_HEAD
	int location;
	int program;
	int size;
};

extern PyTypeObject UniformBufferLocationType;

PyObject * CreateUniformBufferLocationType(int location, int program, int size);
