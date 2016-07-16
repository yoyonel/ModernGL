#include "ModernGL.hpp"

PyObject * Dummy_Viewport(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Viewport() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Viewport() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Clear(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Clear() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Clear() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_GetInfo(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "GetInfo() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "GetInfo() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_PointSize(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "PointSize() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "PointSize() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_LineSize(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "LineSize() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "LineSize() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableOnly(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableOnly() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableOnly() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableBlend(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableBlend() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableBlend() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableCullFace(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableCullFace() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableCullFace() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableDepthTest(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableDepthTest() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableDepthTest() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableMultisample(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableMultisample() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableMultisample() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableBlend(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DisableBlend() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DisableBlend() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableCullFace(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DisableCullFace() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DisableCullFace() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableDepthTest(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DisableDepthTest() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DisableDepthTest() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableMultisample(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DisableMultisample() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DisableMultisample() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewComputeShader() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteComputeShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RunComputeShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RunComputeShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RunComputeShader() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_UseStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "ReadStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "ReadStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteStorageBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewAdvancedVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewAdvancedVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewAdvancedVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteVertexArray(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteVertexArray() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteVertexArray() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_EnableAttributes(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "EnableAttributes() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "EnableAttributes() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DisableAttributes(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DisableAttributes() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DisableAttributes() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewVertexShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewVertexShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewVertexShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewFragmentShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewFragmentShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewFragmentShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewGeometryShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewGeometryShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewGeometryShader() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessControlShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewTessControlShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewTessControlShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTessEvaluationShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewTessEvaluationShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewTessEvaluationShader() function not initialized. OpenGL 4.0 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteShader(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteShader() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteShader() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteProgram(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteProgram() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteProgram() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderPoints(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderPoints() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderPoints() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLines(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderLines() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderLines() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderLineStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderLineStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineLoop(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderLineLoop() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderLineLoop() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangles(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderTriangles() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderTriangles() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStrip(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderTriangleStrip() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderTriangleStrip() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleFan(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderTriangleFan() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderTriangleFan() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLinesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderLinesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderLinesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderLineStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderLineStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderLineStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTrianglesAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderTrianglesAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderTrianglesAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_RenderTriangleStripAdjacency(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "RenderTriangleStripAdjacency() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "RenderTriangleStripAdjacency() function not initialized. OpenGL 3.2 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform1f(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform1f() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform1f() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform1i(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform1i() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform1i() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform2f(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform2f() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform2f() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform2i(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform2i() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform2i() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform3f(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform3f() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform3f() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform3i(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform3i() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform3i() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform4f(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform4f() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform4f() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_Uniform4i(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "Uniform4i() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "Uniform4i() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UniformMatrix(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UniformMatrix() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UniformMatrix() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateVertexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UpdateVertexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UpdateVertexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateUniformBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UpdateUniformBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UpdateUniformBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateIndexBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UpdateIndexBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UpdateIndexBuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateStorageBuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UpdateStorageBuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UpdateStorageBuffer() function not initialized. OpenGL 4.3 is required.");
	}
	return 0;
}

PyObject * Dummy_NewFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_GetDefaultFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "GetDefaultFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "GetDefaultFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseDefaultFramebuffer(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseDefaultFramebuffer() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseDefaultFramebuffer() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadPixel(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "ReadPixel() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "ReadPixel() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadPixels(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "ReadPixels() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "ReadPixels() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadDepthPixel(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "ReadDepthPixel() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "ReadDepthPixel() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_ReadDepthPixels(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "ReadDepthPixels() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "ReadDepthPixels() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_NewTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "NewTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "NewTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UpdateTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UpdateTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UpdateTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_DeleteTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "DeleteTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "DeleteTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_BuildMipmap(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "BuildMipmap() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "BuildMipmap() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseTexture(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseTexture() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseTexture() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_UseTextureAsImage(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "UseTextureAsImage() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "UseTextureAsImage() function not initialized. OpenGL 4.2 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTextureFiltered(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "SetTextureFiltered() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "SetTextureFiltered() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTextureMipmapped(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "SetTextureMipmapped() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "SetTextureMipmapped() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

PyObject * Dummy_SetTexturePixelated(PyObject * self) {
	if (!initialized) {
		PyErr_SetString(ModuleError, "SetTexturePixelated() function not initialized.\n\nCall ModernGL.InitializeModernGL() first.\n\n");
	} else {
		PyErr_SetString(ModuleError, "SetTexturePixelated() function not initialized. OpenGL 3.1 is required.");
	}
	return 0;
}

