#include "ModernGL.hpp"

PyObject * Dummy_Viewport(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "Viewport() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "Viewport() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Clear(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "Clear() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "Clear() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_GetInfo(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "GetInfo() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "GetInfo() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_PointSize(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "PointSize() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "PointSize() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_LineSize(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "LineSize() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "LineSize() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableOnly(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableOnly() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableOnly() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableBlend(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableBlend() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableBlend() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableCullFace(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableCullFace() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableCullFace() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableDepthTest(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableDepthTest() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableDepthTest() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableMultisample(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableMultisample() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableMultisample() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableBlend(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DisableBlend() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DisableBlend() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableCullFace(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DisableCullFace() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DisableCullFace() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableDepthTest(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DisableDepthTest() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DisableDepthTest() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableMultisample(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DisableMultisample() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DisableMultisample() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewComputeShader() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteComputeShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RunComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RunComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RunComputeShader() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_UseStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteStorageBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewAdvancedVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewAdvancedVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewAdvancedVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableAttributes(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "EnableAttributes() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "EnableAttributes() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableAttributes(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DisableAttributes() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DisableAttributes() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewVertexShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewVertexShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewFragmentShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewFragmentShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewFragmentShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewGeometryShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewGeometryShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewGeometryShader() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessControlShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTessControlShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTessControlShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessEvaluationShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTessEvaluationShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTessEvaluationShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderPoints(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderPoints() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderPoints() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLines(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLines() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLines() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineLoop(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineLoop() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineLoop() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangles(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangles() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangles() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleFan(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleFan() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleFan() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLinesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLinesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLinesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderLineStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderLineStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTrianglesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTrianglesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTrianglesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "RenderTriangleStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "RenderTriangleStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_SetUniform(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetUniform() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetUniform() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetUniformMatrix(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetUniformMatrix() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetUniformMatrix() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_NewFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetDefaultFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetDefaultFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetDefaultFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseDefaultFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseDefaultFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseDefaultFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadPixel(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadPixel() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadPixel() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadPixels(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadPixels() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadPixels() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadDepthPixel(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadDepthPixel() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadDepthPixel() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadDepthPixels(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "ReadDepthPixels() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "ReadDepthPixels() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UpdateTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UpdateTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DeleteTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DeleteTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_BuildMipmap(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "BuildMipmap() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "BuildMipmap() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseTextureAsImage(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "UseTextureAsImage() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "UseTextureAsImage() function not initialized. OpenGL 4.2 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTextureFiltered(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetTextureFiltered() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetTextureFiltered() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTextureMipmapped(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetTextureMipmapped() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetTextureMipmapped() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTexturePixelated(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "SetTexturePixelated() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "SetTexturePixelated() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTransformProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "NewTransformProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "NewTransformProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformTriangles(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformTriangles() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformTriangles() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformTriangleStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformTriangleStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformTriangleStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformTriangleFan(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformTriangleFan() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformTriangleFan() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformLines(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformLines() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformLines() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformLineStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformLineStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformLineStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformLineLoop(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformLineLoop() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformLineLoop() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformPoints(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformPoints() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformPoints() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformLineStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformLineStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformLineStripAdjacency() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformLinesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformLinesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformLinesAdjacency() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformTriangleStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformTriangleStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformTriangleStripAdjacency() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_TransformTrianglesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "TransformTrianglesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "TransformTrianglesAdjacency() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DebugInfo(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DebugInfo() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DebugInfo() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DebugVar(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleNotInitialized, "DebugVar() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleNotSupported, "DebugVar() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

