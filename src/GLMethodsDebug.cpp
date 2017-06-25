#ifdef MGL_DEBUG

#include "GLMethods.hpp"

#include "Attribute.hpp"

void GLMethodsDebug_attrib_ptr(MGLAttribute * attribute, GLuint index, GLsizei stride, const GLvoid * pointer) {
	const GLMethods & gl = attribute->context->gl;

	if (attribute->gl_attrib_ptr_proc == gl.VertexAttribPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribPointer(%u, %d, 0x%0x, %d, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, false, stride, pointer);
	} else if (attribute->gl_attrib_ptr_proc == gl.VertexAttribIPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribIPointer(%u, %d, 0x%0x, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, stride, pointer);
	} else if (attribute->gl_attrib_ptr_proc == gl.VertexAttribLPointer) {
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribLPointer(%u, %d, 0x%0x, %d, 0x%p)\n", gl.GetError(), index, attribute->row_length, attribute->scalar_type, stride, pointer);
	}
}

#endif
