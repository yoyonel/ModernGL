#pragma once

#include "Python.hpp"

#include "FramebufferAttachment.hpp"

#include "TextureFilter.hpp"
#include "TextureWrap.hpp"

struct MGLTexture : public MGLFramebufferAttachment {
	MGLTextureFilter * filter;
	MGLTextureWrap * wrap_x;
	MGLTextureWrap * wrap_y;
};

extern PyTypeObject MGLTexture_Type;

MGLTexture * MGLTexture_New();
void MGLTexture_Invalidate(MGLTexture * texture);
