#include "ModernGL-Methods.hpp"

#include "Methods/ModernGL-Buffer.hpp"
#include "Methods/ModernGL-Compute.hpp"
#include "Methods/ModernGL-Core.hpp"
#include "Methods/ModernGL-Debug.hpp"
#include "Methods/ModernGL-Framebuffer.hpp"
#include "Methods/ModernGL-Initialize.hpp"
#include "Methods/ModernGL-Program.hpp"
#include "Methods/ModernGL-Render.hpp"
#include "Methods/ModernGL-Shader.hpp"
#include "Methods/ModernGL-Texture.hpp"
#include "Methods/ModernGL-Transform.hpp"
#include "Methods/ModernGL-VertexArray.hpp"

#include "Utils/PythonMethod.hpp"
#include "ModernGL.hpp"

PyMethodDef moduleMethod[1024];
PythonMethod implementation[1024];
int implementations;

void RegisterMethods(PythonMethod * method, int methods) {
	for (int i = 0; i < methods; ++i) {
		if (method[i].method) {
			implementation[implementations++] = method[i];
		}
	}
}

void InitMethods() {
	RegisterMethods(InitializeMethods, NumInitializeMethods);
	RegisterMethods(BufferMethods, NumBufferMethods);
	RegisterMethods(ComputeMethods, NumComputeMethods);
	RegisterMethods(CoreMethods, NumCoreMethods);
	RegisterMethods(DebugMethods, NumDebugMethods);
	RegisterMethods(FramebufferMethods, NumFramebufferMethods);
	RegisterMethods(ProgramMethods, NumProgramMethods);
	RegisterMethods(RenderMethods, NumRenderMethods);
	RegisterMethods(ShaderMethods, NumShaderMethods);
	RegisterMethods(TextureMethods, NumTextureMethods);
	RegisterMethods(TransformMethods, NumTransformMethods);
	RegisterMethods(VertexArrayMethods, NumVertexArrayMethods);

	#ifdef EXPERIMENTAL
	RegisterMethods(ExperimentalMethods, NumExperimentalMethods);
	#endif

	for (int i = 0; i < implementations; ++i) {
		moduleMethod[i].ml_name = (char *)implementation[i].name;
		moduleMethod[i].ml_doc = (char *)implementation[i].doc;
		moduleMethod[i].ml_flags = implementation[i].flags;
		moduleMethod[i].ml_meth = implementation[i].dummy;
	}
}

void LoadMethods() {
	for (int i = 0; i < implementations; ++i) {
		if (versionNumber >= implementation[i].version) {
			moduleMethod[i].ml_meth = implementation[i].method;
		}
	}
}
