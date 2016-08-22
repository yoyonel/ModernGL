#include "ModernGL.hpp"

#include "ModernGL-Buffer.hpp"
#include "ModernGL-Compute.hpp"
#include "ModernGL-Core.hpp"
#include "ModernGL-Debug.hpp"
#include "ModernGL-Framebuffer.hpp"
#include "ModernGL-Program.hpp"
#include "ModernGL-Render.hpp"
#include "ModernGL-Shader.hpp"
#include "ModernGL-Texture.hpp"
#include "ModernGL-Transform.hpp"
#include "ModernGL-Types.hpp"
#include "ModernGL-VertexArray.hpp"

PyMethodDef methods[1024];

void InitMethods() {
	for (int i = 0; i < implementations; ++i) {
		methods[i].ml_name = (char *)implementation[i].name;
		methods[i].ml_doc = (char *)implementation[i].doc;
		methods[i].ml_flags = implementation[i].flags;
		methods[i].ml_meth = implementation[i].dummy;
	}
}

void LoadMethods() {
	for (int i = 0; i < implementations; ++i) {
		if (versionNumber >= implementation[i].version) {
			methods[i].ml_meth = implementation[i].method;
		}
	}
}
