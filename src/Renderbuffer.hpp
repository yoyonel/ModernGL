#pragma once

#include <Python.h>

#include "FramebufferAttachment.hpp"

struct MGLRenderbuffer : public FramebufferAttachment {
};

extern PyTypeObject MGLRenderbuffer_Type;

MGLRenderbuffer * MGLRenderbuffer_New();
void MGLRenderbuffer_Invalidate(MGLRenderbuffer * renderbuffer);
