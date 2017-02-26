#pragma once

#include <Python.h>

#include "ContextMember.hpp"

struct MGLFramebuffer : public MGLContextMember {
	int obj;

	PyObject * color_attachments;
	PyObject * depth_attachment;
};

extern PyTypeObject MGLFramebuffer_Type;

MGLFramebuffer * MGLFramebuffer_New();
