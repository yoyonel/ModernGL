#pragma once

#include "Global.hpp"

#include "Python.h"
#include "structmember.h"

#include "ModernGL-Buffer.hpp"
#include "ModernGL-Compute.hpp"
#include "ModernGL-Core.hpp"
#include "ModernGL-Debug.hpp"
#include "ModernGL-Framebuffer.hpp"
#include "ModernGL-Methods.hpp"
#include "ModernGL-Program.hpp"
#include "ModernGL-Render.hpp"
#include "ModernGL-Shader.hpp"
#include "ModernGL-Texture.hpp"
#include "ModernGL-Transform.hpp"
#include "ModernGL-Types.hpp"
#include "ModernGL-VertexArray.hpp"

const int ENABLE_NOTHING = 0x00;
const int ENABLE_BLEND = 0x01;
const int ENABLE_CULL_FACE = 0x02;
const int ENABLE_DEPTH_TEST = 0x04;
const int ENABLE_MULTISAMPLE = 0x08;
const int ENABLE_ALL = 0x0F;

extern PyMethodDef methods[];
extern PyObject * ModuleError;
extern PyObject * ModuleRangeError;
extern PyObject * ModuleCompileError;
extern PyObject * ModuleInvalidFormat;
extern PyObject * ModuleAttributeNotFound;
extern PyObject * ModuleNotInitialized;
extern PyObject * ModuleNotSupported;

extern bool initialized;

extern int defaultTextureUnit;
extern int defaultVertexArray;
extern int defaultFramebuffer;

extern int activeProgram;
extern int activeFramebuffer;

extern int activeViewportWidth;
extern int activeViewportHeight;
extern int versionNumber;

extern int maxTextureUnits;

PyObject * InitializeModernGL(PyObject * self, PyObject * args);
