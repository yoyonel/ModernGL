#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLFramebufferAttachment : public MGLContextMember {
	union {
		int renderbuffer_obj;
		int texture_obj;
	};

	int width;
	int height;
	int components;

	bool floats;
	bool depth;

	int samples;
};

extern PyTypeObject MGLFramebufferAttachment_Type;
