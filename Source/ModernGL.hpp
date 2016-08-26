#pragma once

#include "Common.hpp"
#include "Utils/PythonMethod.hpp"

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

extern int NumModuleMethods;
extern PythonMethod ModuleMethods[];
