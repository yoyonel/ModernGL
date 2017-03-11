#pragma once

#include <Python.h>

#include "FramebufferAttachment.hpp"

struct MGLTexture : public MGLFramebufferAttachment {
};

extern PyTypeObject MGLTexture_Type;

MGLTexture * MGLTexture_New();
void MGLTexture_Invalidate(MGLTexture * texture);
