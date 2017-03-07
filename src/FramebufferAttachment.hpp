#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct FramebufferAttachment : public MGLContextMember {
	int obj;

	int width;
	int height;
	int components;

	bool floats;
	bool depth;

	int samples;
};

// extern PyTypeObject FramebufferAttachment_Type;
