#include "ModernGL-Methods.hpp"

#include "ModernGL-Buffer.hpp"
#include "ModernGL-Compute.hpp"
#include "ModernGL-Core.hpp"
#include "ModernGL-Debug.hpp"
#include "ModernGL-Framebuffer.hpp"
#include "ModernGL-Initialize.hpp"
#include "ModernGL-Program.hpp"
#include "ModernGL-Render.hpp"
#include "ModernGL-Shader.hpp"
#include "ModernGL-Texture.hpp"
#include "ModernGL-Transform.hpp"
#include "ModernGL-VertexArray.hpp"

#include "PythonMethod.hpp"
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
