#pragma once

#include "Common.h"

struct Framebuffer {
	PyObject_HEAD
	int fbo;
	int color;
	int depth;
};

extern PyTypeObject FramebufferType;

PyObject * CreateFramebufferType(int fbo, int color, int depth);
