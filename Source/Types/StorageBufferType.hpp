#pragma once

struct StorageBuffer {
	PyObject_HEAD
	int sbo;
	int size;
};

extern PyTypeObject StorageBufferType;

PyObject * CreateStorageBufferType(int sbo, int size);
