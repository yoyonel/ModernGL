#pragma once

#include "OpenGL.hpp"

#include <cstdio>

#define GLMethods GLMethodsDebugImpl
#define MGL_GLMETHOD_DBG_UNIFORM_READER GLMethodsDebug_uniform_reader
#define MGL_GLMETHOD_DBG_UNIFORM_WRITER GLMethodsDebug_uniform_writer
#define MGL_GLMETHOD_DBG_ATTRIB_PTR GLMethodsDebug_attrib_ptr

#if defined(__x86_64__) || defined(_WIN64)
#define LL "ll"
#else
#define LL ""
#endif

// static FILE * GLMethodsDebugFile = stdout;
static FILE * GLMethodsDebugFile = fopen("ModernGL.log", "at");

struct MGLAttribute;
struct MGLUniform;

void GLMethodsDebug_attrib_ptr(MGLAttribute * attribute, GLuint index, GLsizei stride, const GLvoid * pointer);
void GLMethodsDebug_uniform_reader(MGLUniform * uniform, GLint location, GLvoid * params);
void GLMethodsDebug_uniform_writer(MGLUniform * uniform, GLint location, GLsizei count, const GLvoid * values);

struct GLMethodsDebugImpl {
	GLMethodsImpl gl;

	GLvoid CullFace(GLenum mode) const {
		gl.CullFace(mode);
		fprintf(GLMethodsDebugFile, "[%4d] CullFace(0x%x)\n", gl.GetError(), mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FrontFace(GLenum mode) const {
		gl.FrontFace(mode);
		fprintf(GLMethodsDebugFile, "[%4d] FrontFace(0x%x)\n", gl.GetError(), mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Hint(GLenum target, GLenum mode) const {
		gl.Hint(target, mode);
		fprintf(GLMethodsDebugFile, "[%4d] Hint(0x%x, 0x%x)\n", gl.GetError(), target, mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid LineWidth(GLfloat width) const {
		gl.LineWidth(width);
		fprintf(GLMethodsDebugFile, "[%4d] LineWidth(%f)\n", gl.GetError(), width);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PointSize(GLfloat size) const {
		gl.PointSize(size);
		fprintf(GLMethodsDebugFile, "[%4d] PointSize(%f)\n", gl.GetError(), size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PolygonMode(GLenum face, GLenum mode) const {
		gl.PolygonMode(face, mode);
		fprintf(GLMethodsDebugFile, "[%4d] PolygonMode(0x%x, 0x%x)\n", gl.GetError(), face, mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Scissor(GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.Scissor(x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] Scissor(%d, %d, %d, %d)\n", gl.GetError(), x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameterf(GLenum target, GLenum pname, GLfloat param) const {
		gl.TexParameterf(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterf(0x%x, 0x%x, %f)\n", gl.GetError(), target, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameterfv(GLenum target, GLenum pname, const GLfloat * params) const {
		gl.TexParameterfv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterfv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameteri(GLenum target, GLenum pname, GLint param) const {
		gl.TexParameteri(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameteri(0x%x, 0x%x, %d)\n", gl.GetError(), target, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameteriv(GLenum target, GLenum pname, const GLint * params) const {
		gl.TexParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage1D(target, level, internalformat, width, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage1D(0x%x, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, border, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, border, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawBuffer(GLenum buf) const {
		gl.DrawBuffer(buf);
		fprintf(GLMethodsDebugFile, "[%4d] DrawBuffer(0x%x)\n", gl.GetError(), buf);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Clear(GLbitfield mask) const {
		gl.Clear(mask);
		fprintf(GLMethodsDebugFile, "[%4d] Clear(0x%x)\n", gl.GetError(), mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const {
		gl.ClearColor(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] ClearColor(%f, %f, %f, %f)\n", gl.GetError(), red, green, blue, alpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearStencil(GLint s) const {
		gl.ClearStencil(s);
		fprintf(GLMethodsDebugFile, "[%4d] ClearStencil(%d)\n", gl.GetError(), s);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearDepth(GLdouble depth) const {
		gl.ClearDepth(depth);
		fprintf(GLMethodsDebugFile, "[%4d] ClearDepth(%lf)\n", gl.GetError(), depth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilMask(GLuint mask) const {
		gl.StencilMask(mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilMask(%u)\n", gl.GetError(), mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) const {
		gl.ColorMask(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] ColorMask(%d, %d, %d, %d)\n", gl.GetError(), red, green, blue, alpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DepthMask(GLboolean flag) const {
		gl.DepthMask(flag);
		fprintf(GLMethodsDebugFile, "[%4d] DepthMask(%d)\n", gl.GetError(), flag);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Disable(GLenum cap) const {
		gl.Disable(cap);
		fprintf(GLMethodsDebugFile, "[%4d] Disable(0x%x)\n", gl.GetError(), cap);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Enable(GLenum cap) const {
		gl.Enable(cap);
		fprintf(GLMethodsDebugFile, "[%4d] Enable(0x%x)\n", gl.GetError(), cap);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Finish() const {
		gl.Finish();
		fprintf(GLMethodsDebugFile, "[%4d] Finish()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid Flush() const {
		gl.Flush();
		fprintf(GLMethodsDebugFile, "[%4d] Flush()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendFunc(GLenum sfactor, GLenum dfactor) const {
		gl.BlendFunc(sfactor, dfactor);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFunc(0x%x, 0x%x)\n", gl.GetError(), sfactor, dfactor);
		fflush(GLMethodsDebugFile);
	}

	GLvoid LogicOp(GLenum opcode) const {
		gl.LogicOp(opcode);
		fprintf(GLMethodsDebugFile, "[%4d] LogicOp(0x%x)\n", gl.GetError(), opcode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilFunc(GLenum func, GLint ref, GLuint mask) const {
		gl.StencilFunc(func, ref, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilFunc(0x%x, %d, %u)\n", gl.GetError(), func, ref, mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilOp(GLenum fail, GLenum zfail, GLenum zpass) const {
		gl.StencilOp(fail, zfail, zpass);
		fprintf(GLMethodsDebugFile, "[%4d] StencilOp(0x%x, 0x%x, 0x%x)\n", gl.GetError(), fail, zfail, zpass);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DepthFunc(GLenum func) const {
		gl.DepthFunc(func);
		fprintf(GLMethodsDebugFile, "[%4d] DepthFunc(0x%x)\n", gl.GetError(), func);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PixelStoref(GLenum pname, GLfloat param) const {
		gl.PixelStoref(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PixelStoref(0x%x, %f)\n", gl.GetError(), pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PixelStorei(GLenum pname, GLint param) const {
		gl.PixelStorei(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PixelStorei(0x%x, %d)\n", gl.GetError(), pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ReadBuffer(GLenum src) const {
		gl.ReadBuffer(src);
		fprintf(GLMethodsDebugFile, "[%4d] ReadBuffer(0x%x)\n", gl.GetError(), src);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * pixels) const {
		gl.ReadPixels(x, y, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] ReadPixels(%d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), x, y, width, height, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetBooleanv(GLenum pname, GLboolean * data) const {
		gl.GetBooleanv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBooleanv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetDoublev(GLenum pname, GLdouble * data) const {
		gl.GetDoublev(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetDoublev(0x%x, 0x%p)\n", gl.GetError(), pname, data);
		fflush(GLMethodsDebugFile);
	}

	GLenum GetError() const {
		GLenum res = gl.GetError();
		fprintf(GLMethodsDebugFile, "[%4d] GetError() -> 0x%x\n", gl.GetError(), res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetFloatv(GLenum pname, GLfloat * data) const {
		gl.GetFloatv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetFloatv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetIntegerv(GLenum pname, GLint * data) const {
		gl.GetIntegerv(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetIntegerv(0x%x, 0x%p)\n", gl.GetError(), pname, data);
		fflush(GLMethodsDebugFile);
	}

	const GLubyte * GetString(GLenum name) const {
		const GLubyte * res = gl.GetString(name);
		fprintf(GLMethodsDebugFile, "[%4d] GetString(0x%x) -> 0x%p\n", gl.GetError(), name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid * pixels) const {
		gl.GetTexImage(target, level, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexImage(0x%x, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) const {
		gl.GetTexParameterfv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterfv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetTexParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat * params) const {
		gl.GetTexLevelParameterfv(target, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexLevelParameterfv(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), target, level, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint * params) const {
		gl.GetTexLevelParameteriv(target, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexLevelParameteriv(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), target, level, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsEnabled(GLenum cap) const {
		GLboolean res = gl.IsEnabled(cap);
		fprintf(GLMethodsDebugFile, "[%4d] IsEnabled(0x%x) -> %d\n", gl.GetError(), cap, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid DepthRange(GLdouble near, GLdouble far) const {
		gl.DepthRange(near, far);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRange(%lf, %lf)\n", gl.GetError(), near, far);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Viewport(GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.Viewport(x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] Viewport(%d, %d, %d, %d)\n", gl.GetError(), x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawArrays(GLenum mode, GLint first, GLsizei count) const {
		gl.DrawArrays(mode, first, count);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArrays(0x%x, %d, %d)\n", gl.GetError(), mode, first, count);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices) const {
		gl.DrawElements(mode, count, type, indices);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElements(0x%x, %d, 0x%x, 0x%p)\n", gl.GetError(), mode, count, type, indices);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetPointerv(GLenum pname, GLvoid ** params) const {
		gl.GetPointerv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetPointerv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PolygonOffset(GLfloat factor, GLfloat units) const {
		gl.PolygonOffset(factor, units);
		fprintf(GLMethodsDebugFile, "[%4d] PolygonOffset(%f, %f)\n", gl.GetError(), factor, units);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border) const {
		gl.CopyTexImage1D(target, level, internalformat, x, y, width, border);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexImage1D(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, level, internalformat, x, y, width, border);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) const {
		gl.CopyTexImage2D(target, level, internalformat, x, y, width, height, border);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, internalformat, x, y, width, height, border);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) const {
		gl.CopyTexSubImage1D(target, level, xoffset, x, y, width);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage1D(0x%x, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, x, y, width);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage2D(0x%x, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, yoffset, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage1D(target, level, xoffset, width, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage1D(0x%x, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, width, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, width, height, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindTexture(GLenum target, GLuint texture) const {
		gl.BindTexture(target, texture);
		fprintf(GLMethodsDebugFile, "[%4d] BindTexture(0x%x, %u)\n", gl.GetError(), target, texture);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteTextures(GLsizei n, const GLuint * textures) const {
		gl.DeleteTextures(n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteTextures(%d, 0x%p)\n", gl.GetError(), n, textures);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenTextures(GLsizei n, GLuint * textures) const {
		gl.GenTextures(n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] GenTextures(%d, 0x%p)\n", gl.GetError(), n, textures);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsTexture(GLuint texture) const {
		GLboolean res = gl.IsTexture(texture);
		fprintf(GLMethodsDebugFile, "[%4d] IsTexture(%u) -> %d\n", gl.GetError(), texture, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid DrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices) const {
		gl.DrawRangeElements(mode, start, end, count, type, indices);
		fprintf(GLMethodsDebugFile, "[%4d] DrawRangeElements(0x%x, %u, %u, %d, 0x%x, 0x%p)\n", gl.GetError(), mode, start, end, count, type, indices);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage3D(0x%x, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, depth, border, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ActiveTexture(GLenum texture) const {
		gl.ActiveTexture(texture);
		fprintf(GLMethodsDebugFile, "[%4d] ActiveTexture(0x%x)\n", gl.GetError(), texture);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SampleCoverage(GLfloat value, GLboolean invert) const {
		gl.SampleCoverage(value, invert);
		fprintf(GLMethodsDebugFile, "[%4d] SampleCoverage(%f, %d)\n", gl.GetError(), value, invert);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage3D(0x%x, %d, 0x%x, %d, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, depth, border, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage2D(0x%x, %d, 0x%x, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, height, border, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexImage1D(target, level, internalformat, width, border, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexImage1D(0x%x, %d, 0x%x, %d, %d, %d, 0x%p)\n", gl.GetError(), target, level, internalformat, width, border, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage3D(0x%x, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage2D(0x%x, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, yoffset, width, height, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTexSubImage1D(0x%x, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, xoffset, width, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetCompressedTexImage(GLenum target, GLint level, GLvoid * img) const {
		gl.GetCompressedTexImage(target, level, img);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTexImage(0x%x, %d, 0x%p)\n", gl.GetError(), target, level, img);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) const {
		gl.BlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFuncSeparate(0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MultiDrawArrays(GLenum mode, const GLint * first, const GLsizei * count, GLsizei drawcount) const {
		gl.MultiDrawArrays(mode, first, count, drawcount);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawArrays(0x%x, 0x%p, 0x%p, %d)\n", gl.GetError(), mode, first, count, drawcount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MultiDrawElements(GLenum mode, const GLsizei * count, GLenum type, const GLvoid * const* indices, GLsizei drawcount) const {
		gl.MultiDrawElements(mode, count, type, indices, drawcount);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElements(0x%x, 0x%p, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, drawcount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PointParameterf(GLenum pname, GLfloat param) const {
		gl.PointParameterf(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameterf(0x%x, %f)\n", gl.GetError(), pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PointParameterfv(GLenum pname, const GLfloat * params) const {
		gl.PointParameterfv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameterfv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PointParameteri(GLenum pname, GLint param) const {
		gl.PointParameteri(pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameteri(0x%x, %d)\n", gl.GetError(), pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PointParameteriv(GLenum pname, const GLint * params) const {
		gl.PointParameteriv(pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] PointParameteriv(0x%x, 0x%p)\n", gl.GetError(), pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) const {
		gl.BlendColor(red, green, blue, alpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendColor(%f, %f, %f, %f)\n", gl.GetError(), red, green, blue, alpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendEquation(GLenum mode) const {
		gl.BlendEquation(mode);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquation(0x%x)\n", gl.GetError(), mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenQueries(GLsizei n, GLuint * ids) const {
		gl.GenQueries(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] GenQueries(%d, 0x%p)\n", gl.GetError(), n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteQueries(GLsizei n, const GLuint * ids) const {
		gl.DeleteQueries(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteQueries(%d, 0x%p)\n", gl.GetError(), n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsQuery(GLuint id) const {
		GLboolean res = gl.IsQuery(id);
		fprintf(GLMethodsDebugFile, "[%4d] IsQuery(%u) -> %d\n", gl.GetError(), id, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BeginQuery(GLenum target, GLuint id) const {
		gl.BeginQuery(target, id);
		fprintf(GLMethodsDebugFile, "[%4d] BeginQuery(0x%x, %u)\n", gl.GetError(), target, id);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EndQuery(GLenum target) const {
		gl.EndQuery(target);
		fprintf(GLMethodsDebugFile, "[%4d] EndQuery(0x%x)\n", gl.GetError(), target);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryiv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetQueryiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryObjectiv(GLuint id, GLenum pname, GLint * params) const {
		gl.GetQueryObjectiv(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectiv(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryObjectuiv(GLuint id, GLenum pname, GLuint * params) const {
		gl.GetQueryObjectuiv(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindBuffer(GLenum target, GLuint buffer) const {
		gl.BindBuffer(target, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffer(0x%x, %u)\n", gl.GetError(), target, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteBuffers(GLsizei n, const GLuint * buffers) const {
		gl.DeleteBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenBuffers(GLsizei n, GLuint * buffers) const {
		gl.GenBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsBuffer(GLuint buffer) const {
		GLboolean res = gl.IsBuffer(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsBuffer(%u) -> %d\n", gl.GetError(), buffer, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BufferData(GLenum target, GLsizeiptr size, const GLvoid * data, GLenum usage) const {
		gl.BufferData(target, size, data, usage);
		fprintf(GLMethodsDebugFile, "[%4d] BufferData(0x%x, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), target, size, data, usage);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid * data) const {
		gl.BufferSubData(target, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] BufferSubData(0x%x, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), target, offset, size, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, GLvoid * data) const {
		gl.GetBufferSubData(target, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferSubData(0x%x, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), target, offset, size, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid * MapBuffer(GLenum target, GLenum access) const {
		GLvoid * res = gl.MapBuffer(target, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapBuffer(0x%x, 0x%x) -> 0x%p\n", gl.GetError(), target, access, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLboolean UnmapBuffer(GLenum target) const {
		GLboolean res = gl.UnmapBuffer(target);
		fprintf(GLMethodsDebugFile, "[%4d] UnmapBuffer(0x%x) -> %d\n", gl.GetError(), target, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetBufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetBufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetBufferPointerv(GLenum target, GLenum pname, GLvoid ** params) const {
		gl.GetBufferPointerv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferPointerv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) const {
		gl.BlendEquationSeparate(modeRGB, modeAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationSeparate(0x%x, 0x%x)\n", gl.GetError(), modeRGB, modeAlpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawBuffers(GLsizei n, const GLenum * bufs) const {
		gl.DrawBuffers(n, bufs);
		fprintf(GLMethodsDebugFile, "[%4d] DrawBuffers(%d, 0x%p)\n", gl.GetError(), n, bufs);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) const {
		gl.StencilOpSeparate(face, sfail, dpfail, dppass);
		fprintf(GLMethodsDebugFile, "[%4d] StencilOpSeparate(0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), face, sfail, dpfail, dppass);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) const {
		gl.StencilFuncSeparate(face, func, ref, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilFuncSeparate(0x%x, 0x%x, %d, %u)\n", gl.GetError(), face, func, ref, mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid StencilMaskSeparate(GLenum face, GLuint mask) const {
		gl.StencilMaskSeparate(face, mask);
		fprintf(GLMethodsDebugFile, "[%4d] StencilMaskSeparate(0x%x, %u)\n", gl.GetError(), face, mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid AttachShader(GLuint program, GLuint shader) const {
		gl.AttachShader(program, shader);
		fprintf(GLMethodsDebugFile, "[%4d] AttachShader(%u, %u)\n", gl.GetError(), program, shader);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindAttribLocation(GLuint program, GLuint index, const GLchar * name) const {
		gl.BindAttribLocation(program, index, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindAttribLocation(%u, %u, 0x%p)\n", gl.GetError(), program, index, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompileShader(GLuint shader) const {
		gl.CompileShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] CompileShader(%u)\n", gl.GetError(), shader);
		fflush(GLMethodsDebugFile);
	}

	GLuint CreateProgram() const {
		GLuint res = gl.CreateProgram();
		fprintf(GLMethodsDebugFile, "[%4d] CreateProgram() -> %u\n", gl.GetError(), res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLuint CreateShader(GLenum type) const {
		GLuint res = gl.CreateShader(type);
		fprintf(GLMethodsDebugFile, "[%4d] CreateShader(0x%x) -> %u\n", gl.GetError(), type, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid DeleteProgram(GLuint program) const {
		gl.DeleteProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteProgram(%u)\n", gl.GetError(), program);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteShader(GLuint shader) const {
		gl.DeleteShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteShader(%u)\n", gl.GetError(), shader);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DetachShader(GLuint program, GLuint shader) const {
		gl.DetachShader(program, shader);
		fprintf(GLMethodsDebugFile, "[%4d] DetachShader(%u, %u)\n", gl.GetError(), program, shader);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DisableVertexAttribArray(GLuint index) const {
		gl.DisableVertexAttribArray(index);
		fprintf(GLMethodsDebugFile, "[%4d] DisableVertexAttribArray(%u)\n", gl.GetError(), index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EnableVertexAttribArray(GLuint index) const {
		gl.EnableVertexAttribArray(index);
		fprintf(GLMethodsDebugFile, "[%4d] EnableVertexAttribArray(%u)\n", gl.GetError(), index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) const {
		gl.GetActiveAttrib(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveAttrib(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) const {
		gl.GetActiveUniform(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniform(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) const {
		gl.GetAttachedShaders(program, maxCount, count, shaders);
		fprintf(GLMethodsDebugFile, "[%4d] GetAttachedShaders(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, maxCount, count, shaders);
		fflush(GLMethodsDebugFile);
	}

	GLint GetAttribLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetAttribLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetAttribLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetProgramiv(GLuint program, GLenum pname, GLint * params) const {
		gl.GetProgramiv(program, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramiv(%u, 0x%x, 0x%p)\n", gl.GetError(), program, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetProgramInfoLog(program, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, bufSize, length, infoLog);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetShaderiv(GLuint shader, GLenum pname, GLint * params) const {
		gl.GetShaderiv(shader, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderiv(%u, 0x%x, 0x%p)\n", gl.GetError(), shader, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetShaderInfoLog(shader, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, bufSize, length, infoLog);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) const {
		gl.GetShaderSource(shader, bufSize, length, source);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderSource(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, bufSize, length, source);
		fflush(GLMethodsDebugFile);
	}

	GLint GetUniformLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetUniformLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	// GLvoid GetUniformfv(GLuint program, GLint location, GLfloat * params) const {
	// 	gl.GetUniformfv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformfv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid GetUniformiv(GLuint program, GLint location, GLint * params) const {
	// 	gl.GetUniformiv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformiv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// 	fflush(GLMethodsDebugFile);
	// }

	GLvoid GetVertexAttribdv(GLuint index, GLenum pname, GLdouble * params) const {
		gl.GetVertexAttribdv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribdv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) const {
		gl.GetVertexAttribfv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribfv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribiv(GLuint index, GLenum pname, GLint * params) const {
		gl.GetVertexAttribiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid ** pointer) const {
		gl.GetVertexAttribPointerv(index, pname, pointer);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribPointerv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, pointer);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsProgram(GLuint program) const {
		GLboolean res = gl.IsProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] IsProgram(%u) -> %d\n", gl.GetError(), program, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLboolean IsShader(GLuint shader) const {
		GLboolean res = gl.IsShader(shader);
		fprintf(GLMethodsDebugFile, "[%4d] IsShader(%u) -> %d\n", gl.GetError(), shader, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid LinkProgram(GLuint program) const {
		gl.LinkProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] LinkProgram(%u)\n", gl.GetError(), program);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ShaderSource(GLuint shader, GLsizei count, const GLchar * const* string, const GLint * length) const {
		gl.ShaderSource(shader, count, string, length);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderSource(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), shader, count, string, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UseProgram(GLuint program) const {
		gl.UseProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] UseProgram(%u)\n", gl.GetError(), program);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1f(GLint location, GLfloat v0) const {
		gl.Uniform1f(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1f(%d, %f)\n", gl.GetError(), location, v0);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2f(GLint location, GLfloat v0, GLfloat v1) const {
		gl.Uniform2f(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2f(%d, %f, %f)\n", gl.GetError(), location, v0, v1);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const {
		gl.Uniform3f(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3f(%d, %f, %f, %f)\n", gl.GetError(), location, v0, v1, v2);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
		gl.Uniform4f(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4f(%d, %f, %f, %f, %f)\n", gl.GetError(), location, v0, v1, v2, v3);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1i(GLint location, GLint v0) const {
		gl.Uniform1i(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1i(%d, %d)\n", gl.GetError(), location, v0);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2i(GLint location, GLint v0, GLint v1) const {
		gl.Uniform2i(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2i(%d, %d, %d)\n", gl.GetError(), location, v0, v1);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3i(GLint location, GLint v0, GLint v1, GLint v2) const {
		gl.Uniform3i(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3i(%d, %d, %d, %d)\n", gl.GetError(), location, v0, v1, v2);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const {
		gl.Uniform4i(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4i(%d, %d, %d, %d, %d)\n", gl.GetError(), location, v0, v1, v2, v3);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform1fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform2fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform3fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4fv(GLint location, GLsizei count, const GLfloat * value) const {
		gl.Uniform4fv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4fv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform1iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform2iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform3iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4iv(GLint location, GLsizei count, const GLint * value) const {
		gl.Uniform4iv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4iv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ValidateProgram(GLuint program) const {
		gl.ValidateProgram(program);
		fprintf(GLMethodsDebugFile, "[%4d] ValidateProgram(%u)\n", gl.GetError(), program);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1d(GLuint index, GLdouble x) const {
		gl.VertexAttrib1d(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1d(%u, %lf)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib1dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1f(GLuint index, GLfloat x) const {
		gl.VertexAttrib1f(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1f(%u, %f)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib1fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1fv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1s(GLuint index, GLshort x) const {
		gl.VertexAttrib1s(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1s(%u, %d)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib1sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib1sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib1sv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2d(GLuint index, GLdouble x, GLdouble y) const {
		gl.VertexAttrib2d(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2d(%u, %lf, %lf)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib2dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2f(GLuint index, GLfloat x, GLfloat y) const {
		gl.VertexAttrib2f(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2f(%u, %f, %f)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib2fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2fv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2s(GLuint index, GLshort x, GLshort y) const {
		gl.VertexAttrib2s(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2s(%u, %d, %d)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib2sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib2sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib2sv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) const {
		gl.VertexAttrib3d(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3d(%u, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib3dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) const {
		gl.VertexAttrib3f(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3f(%u, %f, %f, %f)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib3fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3fv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3s(GLuint index, GLshort x, GLshort y, GLshort z) const {
		gl.VertexAttrib3s(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3s(%u, %d, %d, %d)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib3sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib3sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib3sv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nbv(GLuint index, const GLbyte * v) const {
		gl.VertexAttrib4Nbv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nbv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Niv(GLuint index, const GLint * v) const {
		gl.VertexAttrib4Niv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Niv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nsv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib4Nsv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nsv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w) const {
		gl.VertexAttrib4Nub(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nub(%u, %u, %u, %u, %u)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttrib4Nubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nubv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nuiv(GLuint index, const GLuint * v) const {
		gl.VertexAttrib4Nuiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nuiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4Nusv(GLuint index, const GLushort * v) const {
		gl.VertexAttrib4Nusv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4Nusv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4bv(GLuint index, const GLbyte * v) const {
		gl.VertexAttrib4bv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4bv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.VertexAttrib4d(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4d(%u, %lf, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttrib4dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) const {
		gl.VertexAttrib4f(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4f(%u, %f, %f, %f, %f)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4fv(GLuint index, const GLfloat * v) const {
		gl.VertexAttrib4fv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4fv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4iv(GLuint index, const GLint * v) const {
		gl.VertexAttrib4iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4iv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4s(GLuint index, GLshort x, GLshort y, GLshort z, GLshort w) const {
		gl.VertexAttrib4s(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4s(%u, %d, %d, %d, %d)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4sv(GLuint index, const GLshort * v) const {
		gl.VertexAttrib4sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4sv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4ubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttrib4ubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4ubv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttrib4uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4uiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttrib4usv(GLuint index, const GLushort * v) const {
		gl.VertexAttrib4usv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttrib4usv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2x3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3x2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix2x4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4x2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4x2fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x2fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3x4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix3x4fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x4fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4x3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
		gl.UniformMatrix4x3fv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x3fv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ColorMaski(GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a) const {
		gl.ColorMaski(index, r, g, b, a);
		fprintf(GLMethodsDebugFile, "[%4d] ColorMaski(%u, %d, %d, %d, %d)\n", gl.GetError(), index, r, g, b, a);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetBooleani_v(GLenum target, GLuint index, GLboolean * data) const {
		gl.GetBooleani_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetBooleani_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetIntegeri_v(GLenum target, GLuint index, GLint * data) const {
		gl.GetIntegeri_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetIntegeri_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Enablei(GLenum target, GLuint index) const {
		gl.Enablei(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] Enablei(0x%x, %u)\n", gl.GetError(), target, index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Disablei(GLenum target, GLuint index) const {
		gl.Disablei(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] Disablei(0x%x, %u)\n", gl.GetError(), target, index);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsEnabledi(GLenum target, GLuint index) const {
		GLboolean res = gl.IsEnabledi(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] IsEnabledi(0x%x, %u) -> %d\n", gl.GetError(), target, index, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BeginTransformFeedback(GLenum primitiveMode) const {
		gl.BeginTransformFeedback(primitiveMode);
		fprintf(GLMethodsDebugFile, "[%4d] BeginTransformFeedback(0x%x)\n", gl.GetError(), primitiveMode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EndTransformFeedback() const {
		gl.EndTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] EndTransformFeedback()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.BindBufferRange(target, index, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] BindBufferRange(0x%x, %u, %u, %" LL "d, %" LL "d)\n", gl.GetError(), target, index, buffer, offset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindBufferBase(GLenum target, GLuint index, GLuint buffer) const {
		gl.BindBufferBase(target, index, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindBufferBase(0x%x, %u, %u)\n", gl.GetError(), target, index, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TransformFeedbackVaryings(GLuint program, GLsizei count, const GLchar * const* varyings, GLenum bufferMode) const {
		gl.TransformFeedbackVaryings(program, count, varyings, bufferMode);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackVaryings(%u, %d, 0x%p, 0x%x)\n", gl.GetError(), program, count, varyings, bufferMode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTransformFeedbackVarying(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLsizei * size, GLenum * type, GLchar * name) const {
		gl.GetTransformFeedbackVarying(program, index, bufSize, length, size, type, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbackVarying(%u, %u, %d, 0x%p, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, index, bufSize, length, size, type, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClampColor(GLenum target, GLenum clamp) const {
		gl.ClampColor(target, clamp);
		fprintf(GLMethodsDebugFile, "[%4d] ClampColor(0x%x, 0x%x)\n", gl.GetError(), target, clamp);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BeginConditionalRender(GLuint id, GLenum mode) const {
		gl.BeginConditionalRender(id, mode);
		fprintf(GLMethodsDebugFile, "[%4d] BeginConditionalRender(%u, 0x%x)\n", gl.GetError(), id, mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EndConditionalRender() const {
		gl.EndConditionalRender();
		fprintf(GLMethodsDebugFile, "[%4d] EndConditionalRender()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribIiv(GLuint index, GLenum pname, GLint * params) const {
		gl.GetVertexAttribIiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribIuiv(GLuint index, GLenum pname, GLuint * params) const {
		gl.GetVertexAttribIuiv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI1i(GLuint index, GLint x) const {
		gl.VertexAttribI1i(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1i(%u, %d)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI2i(GLuint index, GLint x, GLint y) const {
		gl.VertexAttribI2i(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2i(%u, %d, %d)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI3i(GLuint index, GLint x, GLint y, GLint z) const {
		gl.VertexAttribI3i(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3i(%u, %d, %d, %d)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4i(GLuint index, GLint x, GLint y, GLint z, GLint w) const {
		gl.VertexAttribI4i(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4i(%u, %d, %d, %d, %d)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI1ui(GLuint index, GLuint x) const {
		gl.VertexAttribI1ui(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1ui(%u, %u)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI2ui(GLuint index, GLuint x, GLuint y) const {
		gl.VertexAttribI2ui(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2ui(%u, %u, %u)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI3ui(GLuint index, GLuint x, GLuint y, GLuint z) const {
		gl.VertexAttribI3ui(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3ui(%u, %u, %u, %u)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4ui(GLuint index, GLuint x, GLuint y, GLuint z, GLuint w) const {
		gl.VertexAttribI4ui(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4ui(%u, %u, %u, %u, %u)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI1iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI1iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1iv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI2iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI2iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2iv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI3iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI3iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3iv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4iv(GLuint index, const GLint * v) const {
		gl.VertexAttribI4iv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4iv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI1uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI1uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI1uiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI2uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI2uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI2uiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI3uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI3uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI3uiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4uiv(GLuint index, const GLuint * v) const {
		gl.VertexAttribI4uiv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4uiv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4bv(GLuint index, const GLbyte * v) const {
		gl.VertexAttribI4bv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4bv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4sv(GLuint index, const GLshort * v) const {
		gl.VertexAttribI4sv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4sv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4ubv(GLuint index, const GLubyte * v) const {
		gl.VertexAttribI4ubv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4ubv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribI4usv(GLuint index, const GLushort * v) const {
		gl.VertexAttribI4usv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribI4usv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	// GLvoid GetUniformuiv(GLuint program, GLint location, GLuint * params) const {
	// 	gl.GetUniformuiv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformuiv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// 	fflush(GLMethodsDebugFile);
	// }

	GLvoid BindFragDataLocation(GLuint program, GLuint color, const GLchar * name) const {
		gl.BindFragDataLocation(program, color, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindFragDataLocation(%u, %u, 0x%p)\n", gl.GetError(), program, color, name);
		fflush(GLMethodsDebugFile);
	}

	GLint GetFragDataLocation(GLuint program, const GLchar * name) const {
		GLint res = gl.GetFragDataLocation(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetFragDataLocation(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid Uniform1ui(GLint location, GLuint v0) const {
		gl.Uniform1ui(location, v0);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1ui(%d, %u)\n", gl.GetError(), location, v0);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2ui(GLint location, GLuint v0, GLuint v1) const {
		gl.Uniform2ui(location, v0, v1);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2ui(%d, %u, %u)\n", gl.GetError(), location, v0, v1);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3ui(GLint location, GLuint v0, GLuint v1, GLuint v2) const {
		gl.Uniform3ui(location, v0, v1, v2);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3ui(%d, %u, %u, %u)\n", gl.GetError(), location, v0, v1, v2);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4ui(GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
		gl.Uniform4ui(location, v0, v1, v2, v3);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4ui(%d, %u, %u, %u, %u)\n", gl.GetError(), location, v0, v1, v2, v3);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform1uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform2uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform3uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4uiv(GLint location, GLsizei count, const GLuint * value) const {
		gl.Uniform4uiv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4uiv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameterIiv(GLenum target, GLenum pname, const GLint * params) const {
		gl.TexParameterIiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterIiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexParameterIuiv(GLenum target, GLenum pname, const GLuint * params) const {
		gl.TexParameterIuiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TexParameterIuiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexParameterIiv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetTexParameterIiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterIiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTexParameterIuiv(GLenum target, GLenum pname, GLuint * params) const {
		gl.GetTexParameterIuiv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTexParameterIuiv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferiv(GLenum buffer, GLint drawbuffer, const GLint * value) const {
		gl.ClearBufferiv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferiv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferuiv(GLenum buffer, GLint drawbuffer, const GLuint * value) const {
		gl.ClearBufferuiv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferuiv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferfv(GLenum buffer, GLint drawbuffer, const GLfloat * value) const {
		gl.ClearBufferfv(buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferfv(0x%x, %d, 0x%p)\n", gl.GetError(), buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferfi(GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) const {
		gl.ClearBufferfi(buffer, drawbuffer, depth, stencil);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferfi(0x%x, %d, %f, %d)\n", gl.GetError(), buffer, drawbuffer, depth, stencil);
		fflush(GLMethodsDebugFile);
	}

	const GLubyte * GetStringi(GLenum name, GLuint index) const {
		const GLubyte * res = gl.GetStringi(name, index);
		fprintf(GLMethodsDebugFile, "[%4d] GetStringi(0x%x, %u) -> 0x%p\n", gl.GetError(), name, index, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLboolean IsRenderbuffer(GLuint renderbuffer) const {
		GLboolean res = gl.IsRenderbuffer(renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsRenderbuffer(%u) -> %d\n", gl.GetError(), renderbuffer, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BindRenderbuffer(GLenum target, GLuint renderbuffer) const {
		gl.BindRenderbuffer(target, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindRenderbuffer(0x%x, %u)\n", gl.GetError(), target, renderbuffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) const {
		gl.DeleteRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenRenderbuffers(GLsizei n, GLuint * renderbuffers) const {
		gl.GenRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.RenderbufferStorage(target, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] RenderbufferStorage(0x%x, 0x%x, %d, %d)\n", gl.GetError(), target, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetRenderbufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetRenderbufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsFramebuffer(GLuint framebuffer) const {
		GLboolean res = gl.IsFramebuffer(framebuffer);
		fprintf(GLMethodsDebugFile, "[%4d] IsFramebuffer(%u) -> %d\n", gl.GetError(), framebuffer, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BindFramebuffer(GLenum target, GLuint framebuffer) const {
		gl.BindFramebuffer(target, framebuffer);
		fprintf(GLMethodsDebugFile, "[%4d] BindFramebuffer(0x%x, %u)\n", gl.GetError(), target, framebuffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteFramebuffers(GLsizei n, const GLuint * framebuffers) const {
		gl.DeleteFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenFramebuffers(GLsizei n, GLuint * framebuffers) const {
		gl.GenFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] GenFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
		fflush(GLMethodsDebugFile);
	}

	GLenum CheckFramebufferStatus(GLenum target) const {
		GLenum res = gl.CheckFramebufferStatus(target);
		fprintf(GLMethodsDebugFile, "[%4d] CheckFramebufferStatus(0x%x) -> 0x%x\n", gl.GetError(), target, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid FramebufferTexture1D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) const {
		gl.FramebufferTexture1D(target, attachment, textarget, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture1D(0x%x, 0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, textarget, texture, level);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) const {
		gl.FramebufferTexture2D(target, attachment, textarget, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture2D(0x%x, 0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, textarget, texture, level);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferTexture3D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level, GLint zoffset) const {
		gl.FramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture3D(0x%x, 0x%x, 0x%x, %u, %d, %d)\n", gl.GetError(), target, attachment, textarget, texture, level, zoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) const {
		gl.FramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferRenderbuffer(0x%x, 0x%x, 0x%x, %u)\n", gl.GetError(), target, attachment, renderbuffertarget, renderbuffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) const {
		gl.GetFramebufferAttachmentParameteriv(target, attachment, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetFramebufferAttachmentParameteriv(0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, attachment, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenerateMipmap(GLenum target) const {
		gl.GenerateMipmap(target);
		fprintf(GLMethodsDebugFile, "[%4d] GenerateMipmap(0x%x)\n", gl.GetError(), target);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlitFramebuffer(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
		gl.BlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fprintf(GLMethodsDebugFile, "[%4d] BlitFramebuffer(%d, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fflush(GLMethodsDebugFile);
	}

	GLvoid RenderbufferStorageMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.RenderbufferStorageMultisample(target, samples, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] RenderbufferStorageMultisample(0x%x, %d, 0x%x, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferTextureLayer(GLenum target, GLenum attachment, GLuint texture, GLint level, GLint layer) const {
		gl.FramebufferTextureLayer(target, attachment, texture, level, layer);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTextureLayer(0x%x, 0x%x, %u, %d, %d)\n", gl.GetError(), target, attachment, texture, level, layer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid * MapBufferRange(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access) const {
		GLvoid * res = gl.MapBufferRange(target, offset, length, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapBufferRange(0x%x, %" LL "d, %" LL "d, 0x%x) -> 0x%p\n", gl.GetError(), target, offset, length, access, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid FlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length) const {
		gl.FlushMappedBufferRange(target, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] FlushMappedBufferRange(0x%x, %" LL "d, %" LL "d)\n", gl.GetError(), target, offset, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindVertexArray(GLuint array) const {
		gl.BindVertexArray(array);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexArray(%u)\n", gl.GetError(), array);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteVertexArrays(GLsizei n, const GLuint * arrays) const {
		gl.DeleteVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenVertexArrays(GLsizei n, GLuint * arrays) const {
		gl.GenVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] GenVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsVertexArray(GLuint array) const {
		GLboolean res = gl.IsVertexArray(array);
		fprintf(GLMethodsDebugFile, "[%4d] IsVertexArray(%u) -> %d\n", gl.GetError(), array, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid DrawArraysInstanced(GLenum mode, GLint first, GLsizei count, GLsizei instancecount) const {
		gl.DrawArraysInstanced(mode, first, count, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysInstanced(0x%x, %d, %d, %d)\n", gl.GetError(), mode, first, count, instancecount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsInstanced(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount) const {
		gl.DrawElementsInstanced(mode, count, type, indices, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstanced(0x%x, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, instancecount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexBuffer(GLenum target, GLenum internalformat, GLuint buffer) const {
		gl.TexBuffer(target, internalformat, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TexBuffer(0x%x, 0x%x, %u)\n", gl.GetError(), target, internalformat, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PrimitiveRestartIndex(GLuint index) const {
		gl.PrimitiveRestartIndex(index);
		fprintf(GLMethodsDebugFile, "[%4d] PrimitiveRestartIndex(%u)\n", gl.GetError(), index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyBufferSubData(GLenum readTarget, GLenum writeTarget, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) const {
		gl.CopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
		fprintf(GLMethodsDebugFile, "[%4d] CopyBufferSubData(0x%x, 0x%x, %" LL "d, %" LL "d, %" LL "d)\n", gl.GetError(), readTarget, writeTarget, readOffset, writeOffset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetUniformIndices(GLuint program, GLsizei uniformCount, const GLchar * const* uniformNames, GLuint * uniformIndices) const {
		gl.GetUniformIndices(program, uniformCount, uniformNames, uniformIndices);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformIndices(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformCount, uniformNames, uniformIndices);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveUniformsiv(GLuint program, GLsizei uniformCount, const GLuint * uniformIndices, GLenum pname, GLint * params) const {
		gl.GetActiveUniformsiv(program, uniformCount, uniformIndices, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformsiv(%u, %d, 0x%p, 0x%x, 0x%p)\n", gl.GetError(), program, uniformCount, uniformIndices, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveUniformName(GLuint program, GLuint uniformIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformName) const {
		gl.GetActiveUniformName(program, uniformIndex, bufSize, length, uniformName);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformName(%u, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformIndex, bufSize, length, uniformName);
		fflush(GLMethodsDebugFile);
	}

	GLuint GetUniformBlockIndex(GLuint program, const GLchar * uniformBlockName) const {
		GLuint res = gl.GetUniformBlockIndex(program, uniformBlockName);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformBlockIndex(%u, 0x%p) -> %u\n", gl.GetError(), program, uniformBlockName, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetActiveUniformBlockiv(GLuint program, GLuint uniformBlockIndex, GLenum pname, GLint * params) const {
		gl.GetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformBlockiv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), program, uniformBlockIndex, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveUniformBlockName(GLuint program, GLuint uniformBlockIndex, GLsizei bufSize, GLsizei * length, GLchar * uniformBlockName) const {
		gl.GetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, uniformBlockName);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveUniformBlockName(%u, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, uniformBlockIndex, bufSize, length, uniformBlockName);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding) const {
		gl.UniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
		fprintf(GLMethodsDebugFile, "[%4d] UniformBlockBinding(%u, %u, %u)\n", gl.GetError(), program, uniformBlockIndex, uniformBlockBinding);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex) const {
		gl.DrawElementsBaseVertex(mode, count, type, indices, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsBaseVertex(0x%x, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, count, type, indices, basevertex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawRangeElementsBaseVertex(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid * indices, GLint basevertex) const {
		gl.DrawRangeElementsBaseVertex(mode, start, end, count, type, indices, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawRangeElementsBaseVertex(0x%x, %u, %u, %d, 0x%x, 0x%p, %d)\n", gl.GetError(), mode, start, end, count, type, indices, basevertex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsInstancedBaseVertex(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex) const {
		gl.DrawElementsInstancedBaseVertex(mode, count, type, indices, instancecount, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseVertex(0x%x, %d, 0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, count, type, indices, instancecount, basevertex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MultiDrawElementsBaseVertex(GLenum mode, const GLsizei * count, GLenum type, const GLvoid * const* indices, GLsizei drawcount, const GLint * basevertex) const {
		gl.MultiDrawElementsBaseVertex(mode, count, type, indices, drawcount, basevertex);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElementsBaseVertex(0x%x, 0x%p, 0x%x, 0x%p, %d, 0x%p)\n", gl.GetError(), mode, count, type, indices, drawcount, basevertex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ProvokingVertex(GLenum mode) const {
		gl.ProvokingVertex(mode);
		fprintf(GLMethodsDebugFile, "[%4d] ProvokingVertex(0x%x)\n", gl.GetError(), mode);
		fflush(GLMethodsDebugFile);
	}

	GLsync FenceSync(GLenum condition, GLbitfield flags) const {
		GLsync res = gl.FenceSync(condition, flags);
		fprintf(GLMethodsDebugFile, "[%4d] FenceSync(0x%x, 0x%x) -> 0x%p\n", gl.GetError(), condition, flags, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLboolean IsSync(GLsync sync) const {
		GLboolean res = gl.IsSync(sync);
		fprintf(GLMethodsDebugFile, "[%4d] IsSync(0x%p) -> %d\n", gl.GetError(), sync, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid DeleteSync(GLsync sync) const {
		gl.DeleteSync(sync);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteSync(0x%p)\n", gl.GetError(), sync);
		fflush(GLMethodsDebugFile);
	}

	GLenum ClientWaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) const {
		GLenum res = gl.ClientWaitSync(sync, flags, timeout);
		fprintf(GLMethodsDebugFile, "[%4d] ClientWaitSync(0x%p, 0x%x, %llu) -> 0x%x\n", gl.GetError(), sync, flags, timeout, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid WaitSync(GLsync sync, GLbitfield flags, GLuint64 timeout) const {
		gl.WaitSync(sync, flags, timeout);
		fprintf(GLMethodsDebugFile, "[%4d] WaitSync(0x%p, 0x%x, %llu)\n", gl.GetError(), sync, flags, timeout);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetInteger64v(GLenum pname, GLint64 * data) const {
		gl.GetInteger64v(pname, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetInteger64v(0x%x, 0x%p)\n", gl.GetError(), pname, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetSynciv(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei * length, GLint * values) const {
		gl.GetSynciv(sync, pname, bufSize, length, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetSynciv(0x%p, 0x%x, %d, 0x%p, 0x%p)\n", gl.GetError(), sync, pname, bufSize, length, values);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetInteger64i_v(GLenum target, GLuint index, GLint64 * data) const {
		gl.GetInteger64i_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetInteger64i_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetBufferParameteri64v(GLenum target, GLenum pname, GLint64 * params) const {
		gl.GetBufferParameteri64v(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetBufferParameteri64v(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level) const {
		gl.FramebufferTexture(target, attachment, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferTexture(0x%x, 0x%x, %u, %d)\n", gl.GetError(), target, attachment, texture, level);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexImage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage2DMultisample(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexImage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexImage3DMultisample(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetMultisamplefv(GLenum pname, GLuint index, GLfloat * val) const {
		gl.GetMultisamplefv(pname, index, val);
		fprintf(GLMethodsDebugFile, "[%4d] GetMultisamplefv(0x%x, %u, 0x%p)\n", gl.GetError(), pname, index, val);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SampleMaski(GLuint maskNumber, GLbitfield mask) const {
		gl.SampleMaski(maskNumber, mask);
		fprintf(GLMethodsDebugFile, "[%4d] SampleMaski(%u, 0x%x)\n", gl.GetError(), maskNumber, mask);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindFragDataLocationIndexed(GLuint program, GLuint colorNumber, GLuint index, const GLchar * name) const {
		gl.BindFragDataLocationIndexed(program, colorNumber, index, name);
		fprintf(GLMethodsDebugFile, "[%4d] BindFragDataLocationIndexed(%u, %u, %u, 0x%p)\n", gl.GetError(), program, colorNumber, index, name);
		fflush(GLMethodsDebugFile);
	}

	GLint GetFragDataIndex(GLuint program, const GLchar * name) const {
		GLint res = gl.GetFragDataIndex(program, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetFragDataIndex(%u, 0x%p) -> %d\n", gl.GetError(), program, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GenSamplers(GLsizei count, GLuint * samplers) const {
		gl.GenSamplers(count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] GenSamplers(%d, 0x%p)\n", gl.GetError(), count, samplers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteSamplers(GLsizei count, const GLuint * samplers) const {
		gl.DeleteSamplers(count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteSamplers(%d, 0x%p)\n", gl.GetError(), count, samplers);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsSampler(GLuint sampler) const {
		GLboolean res = gl.IsSampler(sampler);
		fprintf(GLMethodsDebugFile, "[%4d] IsSampler(%u) -> %d\n", gl.GetError(), sampler, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BindSampler(GLuint unit, GLuint sampler) const {
		gl.BindSampler(unit, sampler);
		fprintf(GLMethodsDebugFile, "[%4d] BindSampler(%u, %u)\n", gl.GetError(), unit, sampler);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameteri(GLuint sampler, GLenum pname, GLint param) const {
		gl.SamplerParameteri(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameteri(%u, 0x%x, %d)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameteriv(GLuint sampler, GLenum pname, const GLint * param) const {
		gl.SamplerParameteriv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameterf(GLuint sampler, GLenum pname, GLfloat param) const {
		gl.SamplerParameterf(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterf(%u, 0x%x, %f)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameterfv(GLuint sampler, GLenum pname, const GLfloat * param) const {
		gl.SamplerParameterfv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameterIiv(GLuint sampler, GLenum pname, const GLint * param) const {
		gl.SamplerParameterIiv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid SamplerParameterIuiv(GLuint sampler, GLenum pname, const GLuint * param) const {
		gl.SamplerParameterIuiv(sampler, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] SamplerParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetSamplerParameteriv(GLuint sampler, GLenum pname, GLint * params) const {
		gl.GetSamplerParameteriv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetSamplerParameterIiv(GLuint sampler, GLenum pname, GLint * params) const {
		gl.GetSamplerParameterIiv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetSamplerParameterfv(GLuint sampler, GLenum pname, GLfloat * params) const {
		gl.GetSamplerParameterfv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetSamplerParameterIuiv(GLuint sampler, GLenum pname, GLuint * params) const {
		gl.GetSamplerParameterIuiv(sampler, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetSamplerParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), sampler, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid QueryCounter(GLuint id, GLenum target) const {
		gl.QueryCounter(id, target);
		fprintf(GLMethodsDebugFile, "[%4d] QueryCounter(%u, 0x%x)\n", gl.GetError(), id, target);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryObjecti64v(GLuint id, GLenum pname, GLint64 * params) const {
		gl.GetQueryObjecti64v(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjecti64v(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryObjectui64v(GLuint id, GLenum pname, GLuint64 * params) const {
		gl.GetQueryObjectui64v(id, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryObjectui64v(%u, 0x%x, 0x%p)\n", gl.GetError(), id, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribDivisor(GLuint index, GLuint divisor) const {
		gl.VertexAttribDivisor(index, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribDivisor(%u, %u)\n", gl.GetError(), index, divisor);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP1ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP1ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP1ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP1uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP1uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP1uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP2ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP2ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP2ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP2uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP2uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP2uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP3ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP3ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP3ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP3uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP3uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP3uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP4ui(GLuint index, GLenum type, GLboolean normalized, GLuint value) const {
		gl.VertexAttribP4ui(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP4ui(%u, 0x%x, %d, %u)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribP4uiv(GLuint index, GLenum type, GLboolean normalized, const GLuint * value) const {
		gl.VertexAttribP4uiv(index, type, normalized, value);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribP4uiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), index, type, normalized, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MinSampleShading(GLfloat value) const {
		gl.MinSampleShading(value);
		fprintf(GLMethodsDebugFile, "[%4d] MinSampleShading(%f)\n", gl.GetError(), value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendEquationi(GLuint buf, GLenum mode) const {
		gl.BlendEquationi(buf, mode);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationi(%u, 0x%x)\n", gl.GetError(), buf, mode);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendEquationSeparatei(GLuint buf, GLenum modeRGB, GLenum modeAlpha) const {
		gl.BlendEquationSeparatei(buf, modeRGB, modeAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendEquationSeparatei(%u, 0x%x, 0x%x)\n", gl.GetError(), buf, modeRGB, modeAlpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendFunci(GLuint buf, GLenum src, GLenum dst) const {
		gl.BlendFunci(buf, src, dst);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFunci(%u, 0x%x, 0x%x)\n", gl.GetError(), buf, src, dst);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlendFuncSeparatei(GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) const {
		gl.BlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
		fprintf(GLMethodsDebugFile, "[%4d] BlendFuncSeparatei(%u, 0x%x, 0x%x, 0x%x, 0x%x)\n", gl.GetError(), buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawArraysIndirect(GLenum mode, const GLvoid * indirect) const {
		gl.DrawArraysIndirect(mode, indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysIndirect(0x%x, 0x%p)\n", gl.GetError(), mode, indirect);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect) const {
		gl.DrawElementsIndirect(mode, type, indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsIndirect(0x%x, 0x%x, 0x%p)\n", gl.GetError(), mode, type, indirect);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1d(GLint location, GLdouble x) const {
		gl.Uniform1d(location, x);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1d(%d, %lf)\n", gl.GetError(), location, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2d(GLint location, GLdouble x, GLdouble y) const {
		gl.Uniform2d(location, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2d(%d, %lf, %lf)\n", gl.GetError(), location, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3d(GLint location, GLdouble x, GLdouble y, GLdouble z) const {
		gl.Uniform3d(location, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3d(%d, %lf, %lf, %lf)\n", gl.GetError(), location, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4d(GLint location, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.Uniform4d(location, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4d(%d, %lf, %lf, %lf, %lf)\n", gl.GetError(), location, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform1dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform1dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform1dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform2dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform2dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform2dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform3dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform3dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform3dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid Uniform4dv(GLint location, GLsizei count, const GLdouble * value) const {
		gl.Uniform4dv(location, count, value);
		fprintf(GLMethodsDebugFile, "[%4d] Uniform4dv(%d, %d, 0x%p)\n", gl.GetError(), location, count, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2x3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix2x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix2x4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix2x4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3x2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix3x4dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix3x4dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix3x4dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4x2dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4x2dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x2dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformMatrix4x3dv(GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
		gl.UniformMatrix4x3dv(location, count, transpose, value);
		fprintf(GLMethodsDebugFile, "[%4d] UniformMatrix4x3dv(%d, %d, %d, 0x%p)\n", gl.GetError(), location, count, transpose, value);
		fflush(GLMethodsDebugFile);
	}

	// GLvoid GetUniformdv(GLuint program, GLint location, GLdouble * params) const {
	// 	gl.GetUniformdv(program, location, params);
	// 	fprintf(GLMethodsDebugFile, "[%4d] GetUniformdv(%u, %d, 0x%p)\n", gl.GetError(), program, location, params);
	// 	fflush(GLMethodsDebugFile);
	// }

	GLint GetSubroutineUniformLocation(GLuint program, GLenum shadertype, const GLchar * name) const {
		GLint res = gl.GetSubroutineUniformLocation(program, shadertype, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetSubroutineUniformLocation(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, shadertype, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLuint GetSubroutineIndex(GLuint program, GLenum shadertype, const GLchar * name) const {
		GLuint res = gl.GetSubroutineIndex(program, shadertype, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetSubroutineIndex(%u, 0x%x, 0x%p) -> %u\n", gl.GetError(), program, shadertype, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetActiveSubroutineUniformiv(GLuint program, GLenum shadertype, GLuint index, GLenum pname, GLint * values) const {
		gl.GetActiveSubroutineUniformiv(program, shadertype, index, pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineUniformiv(%u, 0x%x, %u, 0x%x, 0x%p)\n", gl.GetError(), program, shadertype, index, pname, values);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveSubroutineUniformName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) const {
		gl.GetActiveSubroutineUniformName(program, shadertype, index, bufsize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineUniformName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, shadertype, index, bufsize, length, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveSubroutineName(GLuint program, GLenum shadertype, GLuint index, GLsizei bufsize, GLsizei * length, GLchar * name) const {
		gl.GetActiveSubroutineName(program, shadertype, index, bufsize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveSubroutineName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, shadertype, index, bufsize, length, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UniformSubroutinesuiv(GLenum shadertype, GLsizei count, const GLuint * indices) const {
		gl.UniformSubroutinesuiv(shadertype, count, indices);
		fprintf(GLMethodsDebugFile, "[%4d] UniformSubroutinesuiv(0x%x, %d, 0x%p)\n", gl.GetError(), shadertype, count, indices);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetUniformSubroutineuiv(GLenum shadertype, GLint location, GLuint * params) const {
		gl.GetUniformSubroutineuiv(shadertype, location, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetUniformSubroutineuiv(0x%x, %d, 0x%p)\n", gl.GetError(), shadertype, location, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramStageiv(GLuint program, GLenum shadertype, GLenum pname, GLint * values) const {
		gl.GetProgramStageiv(program, shadertype, pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramStageiv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), program, shadertype, pname, values);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PatchParameteri(GLenum pname, GLint value) const {
		gl.PatchParameteri(pname, value);
		fprintf(GLMethodsDebugFile, "[%4d] PatchParameteri(0x%x, %d)\n", gl.GetError(), pname, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PatchParameterfv(GLenum pname, const GLfloat * values) const {
		gl.PatchParameterfv(pname, values);
		fprintf(GLMethodsDebugFile, "[%4d] PatchParameterfv(0x%x, 0x%p)\n", gl.GetError(), pname, values);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindTransformFeedback(GLenum target, GLuint id) const {
		gl.BindTransformFeedback(target, id);
		fprintf(GLMethodsDebugFile, "[%4d] BindTransformFeedback(0x%x, %u)\n", gl.GetError(), target, id);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteTransformFeedbacks(GLsizei n, const GLuint * ids) const {
		gl.DeleteTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenTransformFeedbacks(GLsizei n, GLuint * ids) const {
		gl.GenTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] GenTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsTransformFeedback(GLuint id) const {
		GLboolean res = gl.IsTransformFeedback(id);
		fprintf(GLMethodsDebugFile, "[%4d] IsTransformFeedback(%u) -> %d\n", gl.GetError(), id, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid PauseTransformFeedback() const {
		gl.PauseTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] PauseTransformFeedback()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid ResumeTransformFeedback() const {
		gl.ResumeTransformFeedback();
		fprintf(GLMethodsDebugFile, "[%4d] ResumeTransformFeedback()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawTransformFeedback(GLenum mode, GLuint id) const {
		gl.DrawTransformFeedback(mode, id);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedback(0x%x, %u)\n", gl.GetError(), mode, id);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawTransformFeedbackStream(GLenum mode, GLuint id, GLuint stream) const {
		gl.DrawTransformFeedbackStream(mode, id, stream);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackStream(0x%x, %u, %u)\n", gl.GetError(), mode, id, stream);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BeginQueryIndexed(GLenum target, GLuint index, GLuint id) const {
		gl.BeginQueryIndexed(target, index, id);
		fprintf(GLMethodsDebugFile, "[%4d] BeginQueryIndexed(0x%x, %u, %u)\n", gl.GetError(), target, index, id);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EndQueryIndexed(GLenum target, GLuint index) const {
		gl.EndQueryIndexed(target, index);
		fprintf(GLMethodsDebugFile, "[%4d] EndQueryIndexed(0x%x, %u)\n", gl.GetError(), target, index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryIndexediv(GLenum target, GLuint index, GLenum pname, GLint * params) const {
		gl.GetQueryIndexediv(target, index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryIndexediv(0x%x, %u, 0x%x, 0x%p)\n", gl.GetError(), target, index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ReleaseShaderCompiler() const {
		gl.ReleaseShaderCompiler();
		fprintf(GLMethodsDebugFile, "[%4d] ReleaseShaderCompiler()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid ShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const GLvoid * binary, GLsizei length) const {
		gl.ShaderBinary(count, shaders, binaryformat, binary, length);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderBinary(%d, 0x%p, 0x%x, 0x%p, %d)\n", gl.GetError(), count, shaders, binaryformat, binary, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision) const {
		gl.GetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
		fprintf(GLMethodsDebugFile, "[%4d] GetShaderPrecisionFormat(0x%x, 0x%x, 0x%p, 0x%p)\n", gl.GetError(), shadertype, precisiontype, range, precision);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DepthRangef(GLfloat n, GLfloat f) const {
		gl.DepthRangef(n, f);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangef(%f, %f)\n", gl.GetError(), n, f);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearDepthf(GLfloat d) const {
		gl.ClearDepthf(d);
		fprintf(GLMethodsDebugFile, "[%4d] ClearDepthf(%f)\n", gl.GetError(), d);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramBinary(GLuint program, GLsizei bufSize, GLsizei * length, GLenum * binaryFormat, GLvoid * binary) const {
		gl.GetProgramBinary(program, bufSize, length, binaryFormat, binary);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramBinary(%u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), program, bufSize, length, binaryFormat, binary);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ProgramBinary(GLuint program, GLenum binaryFormat, const GLvoid * binary, GLsizei length) const {
		gl.ProgramBinary(program, binaryFormat, binary, length);
		fprintf(GLMethodsDebugFile, "[%4d] ProgramBinary(%u, 0x%x, 0x%p, %d)\n", gl.GetError(), program, binaryFormat, binary, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ProgramParameteri(GLuint program, GLenum pname, GLint value) const {
		gl.ProgramParameteri(program, pname, value);
		fprintf(GLMethodsDebugFile, "[%4d] ProgramParameteri(%u, 0x%x, %d)\n", gl.GetError(), program, pname, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid UseProgramStages(GLuint pipeline, GLbitfield stages, GLuint program) const {
		gl.UseProgramStages(pipeline, stages, program);
		fprintf(GLMethodsDebugFile, "[%4d] UseProgramStages(%u, 0x%x, %u)\n", gl.GetError(), pipeline, stages, program);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ActiveShaderProgram(GLuint pipeline, GLuint program) const {
		gl.ActiveShaderProgram(pipeline, program);
		fprintf(GLMethodsDebugFile, "[%4d] ActiveShaderProgram(%u, %u)\n", gl.GetError(), pipeline, program);
		fflush(GLMethodsDebugFile);
	}

	GLuint CreateShaderProgramv(GLenum type, GLsizei count, const GLchar * const* strings) const {
		GLuint res = gl.CreateShaderProgramv(type, count, strings);
		fprintf(GLMethodsDebugFile, "[%4d] CreateShaderProgramv(0x%x, %d, 0x%p) -> %u\n", gl.GetError(), type, count, strings, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid BindProgramPipeline(GLuint pipeline) const {
		gl.BindProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] BindProgramPipeline(%u)\n", gl.GetError(), pipeline);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DeleteProgramPipelines(GLsizei n, const GLuint * pipelines) const {
		gl.DeleteProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] DeleteProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenProgramPipelines(GLsizei n, GLuint * pipelines) const {
		gl.GenProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] GenProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
		fflush(GLMethodsDebugFile);
	}

	GLboolean IsProgramPipeline(GLuint pipeline) const {
		GLboolean res = gl.IsProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] IsProgramPipeline(%u) -> %d\n", gl.GetError(), pipeline, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetProgramPipelineiv(GLuint pipeline, GLenum pname, GLint * params) const {
		gl.GetProgramPipelineiv(pipeline, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramPipelineiv(%u, 0x%x, 0x%p)\n", gl.GetError(), pipeline, pname, params);
		fflush(GLMethodsDebugFile);
	}

	// GLvoid ProgramUniform1i(GLuint program, GLint location, GLint v0) const {
	// 	gl.ProgramUniform1i(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1i(%u, %d, %d)\n", gl.GetError(), program, location, v0);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform1iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1f(GLuint program, GLint location, GLfloat v0) const {
	// 	gl.ProgramUniform1f(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1f(%u, %d, %f)\n", gl.GetError(), program, location, v0);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform1fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1d(GLuint program, GLint location, GLdouble v0) const {
	// 	gl.ProgramUniform1d(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1d(%u, %d, %lf)\n", gl.GetError(), program, location, v0);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform1dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1ui(GLuint program, GLint location, GLuint v0) const {
	// 	gl.ProgramUniform1ui(program, location, v0);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1ui(%u, %d, %u)\n", gl.GetError(), program, location, v0);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform1uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform1uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform1uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2i(GLuint program, GLint location, GLint v0, GLint v1) const {
	// 	gl.ProgramUniform2i(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2i(%u, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform2iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2f(GLuint program, GLint location, GLfloat v0, GLfloat v1) const {
	// 	gl.ProgramUniform2f(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2f(%u, %d, %f, %f)\n", gl.GetError(), program, location, v0, v1);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform2fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2d(GLuint program, GLint location, GLdouble v0, GLdouble v1) const {
	// 	gl.ProgramUniform2d(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2d(%u, %d, %lf, %lf)\n", gl.GetError(), program, location, v0, v1);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform2dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2ui(GLuint program, GLint location, GLuint v0, GLuint v1) const {
	// 	gl.ProgramUniform2ui(program, location, v0, v1);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2ui(%u, %d, %u, %u)\n", gl.GetError(), program, location, v0, v1);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform2uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform2uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform2uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2) const {
	// 	gl.ProgramUniform3i(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3i(%u, %d, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1, v2);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform3iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) const {
	// 	gl.ProgramUniform3f(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3f(%u, %d, %f, %f, %f)\n", gl.GetError(), program, location, v0, v1, v2);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform3fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2) const {
	// 	gl.ProgramUniform3d(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3d(%u, %d, %lf, %lf, %lf)\n", gl.GetError(), program, location, v0, v1, v2);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform3dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2) const {
	// 	gl.ProgramUniform3ui(program, location, v0, v1, v2);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3ui(%u, %d, %u, %u, %u)\n", gl.GetError(), program, location, v0, v1, v2);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform3uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform3uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform3uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4i(GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3) const {
	// 	gl.ProgramUniform4i(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4i(%u, %d, %d, %d, %d, %d)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4iv(GLuint program, GLint location, GLsizei count, const GLint * value) const {
	// 	gl.ProgramUniform4iv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4iv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4f(GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
	// 	gl.ProgramUniform4f(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4f(%u, %d, %f, %f, %f, %f)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4fv(GLuint program, GLint location, GLsizei count, const GLfloat * value) const {
	// 	gl.ProgramUniform4fv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4fv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4d(GLuint program, GLint location, GLdouble v0, GLdouble v1, GLdouble v2, GLdouble v3) const {
	// 	gl.ProgramUniform4d(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4d(%u, %d, %lf, %lf, %lf, %lf)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4dv(GLuint program, GLint location, GLsizei count, const GLdouble * value) const {
	// 	gl.ProgramUniform4dv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4dv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4ui(GLuint program, GLint location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
	// 	gl.ProgramUniform4ui(program, location, v0, v1, v2, v3);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4ui(%u, %d, %u, %u, %u, %u)\n", gl.GetError(), program, location, v0, v1, v2, v3);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniform4uiv(GLuint program, GLint location, GLsizei count, const GLuint * value) const {
	// 	gl.ProgramUniform4uiv(program, location, count, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniform4uiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2x3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3x2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix2x4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4x2fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4x2fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3x4fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix3x4fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4x3fv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) const {
	// 	gl.ProgramUniformMatrix4x3fv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3fv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2x3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3x2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix2x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix2x4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix2x4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4x2dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4x2dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x2dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix3x4dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix3x4dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix3x4dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	// GLvoid ProgramUniformMatrix4x3dv(GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLdouble * value) const {
	// 	gl.ProgramUniformMatrix4x3dv(program, location, count, transpose, value);
	// 	fprintf(GLMethodsDebugFile, "[%4d] ProgramUniformMatrix4x3dv(%u, %d, %d, %d, 0x%p)\n", gl.GetError(), program, location, count, transpose, value);
	// 	fflush(GLMethodsDebugFile);
	// }

	GLvoid ValidateProgramPipeline(GLuint pipeline) const {
		gl.ValidateProgramPipeline(pipeline);
		fprintf(GLMethodsDebugFile, "[%4d] ValidateProgramPipeline(%u)\n", gl.GetError(), pipeline);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramPipelineInfoLog(GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog) const {
		gl.GetProgramPipelineInfoLog(pipeline, bufSize, length, infoLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramPipelineInfoLog(%u, %d, 0x%p, 0x%p)\n", gl.GetError(), pipeline, bufSize, length, infoLog);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL1d(GLuint index, GLdouble x) const {
		gl.VertexAttribL1d(index, x);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL1d(%u, %lf)\n", gl.GetError(), index, x);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL2d(GLuint index, GLdouble x, GLdouble y) const {
		gl.VertexAttribL2d(index, x, y);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL2d(%u, %lf, %lf)\n", gl.GetError(), index, x, y);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL3d(GLuint index, GLdouble x, GLdouble y, GLdouble z) const {
		gl.VertexAttribL3d(index, x, y, z);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL3d(%u, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL4d(GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w) const {
		gl.VertexAttribL4d(index, x, y, z, w);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL4d(%u, %lf, %lf, %lf, %lf)\n", gl.GetError(), index, x, y, z, w);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL1dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL1dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL1dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL2dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL2dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL2dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL3dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL3dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL3dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribL4dv(GLuint index, const GLdouble * v) const {
		gl.VertexAttribL4dv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribL4dv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexAttribLdv(GLuint index, GLenum pname, GLdouble * params) const {
		gl.GetVertexAttribLdv(index, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexAttribLdv(%u, 0x%x, 0x%p)\n", gl.GetError(), index, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ViewportArrayv(GLuint first, GLsizei count, const GLfloat * v) const {
		gl.ViewportArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ViewportIndexedf(GLuint index, GLfloat x, GLfloat y, GLfloat w, GLfloat h) const {
		gl.ViewportIndexedf(index, x, y, w, h);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportIndexedf(%u, %f, %f, %f, %f)\n", gl.GetError(), index, x, y, w, h);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ViewportIndexedfv(GLuint index, const GLfloat * v) const {
		gl.ViewportIndexedfv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] ViewportIndexedfv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ScissorArrayv(GLuint first, GLsizei count, const GLint * v) const {
		gl.ScissorArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ScissorIndexed(GLuint index, GLint left, GLint bottom, GLsizei width, GLsizei height) const {
		gl.ScissorIndexed(index, left, bottom, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorIndexed(%u, %d, %d, %d, %d)\n", gl.GetError(), index, left, bottom, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ScissorIndexedv(GLuint index, const GLint * v) const {
		gl.ScissorIndexedv(index, v);
		fprintf(GLMethodsDebugFile, "[%4d] ScissorIndexedv(%u, 0x%p)\n", gl.GetError(), index, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DepthRangeArrayv(GLuint first, GLsizei count, const GLdouble * v) const {
		gl.DepthRangeArrayv(first, count, v);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangeArrayv(%u, %d, 0x%p)\n", gl.GetError(), first, count, v);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DepthRangeIndexed(GLuint index, GLdouble n, GLdouble f) const {
		gl.DepthRangeIndexed(index, n, f);
		fprintf(GLMethodsDebugFile, "[%4d] DepthRangeIndexed(%u, %lf, %lf)\n", gl.GetError(), index, n, f);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetFloati_v(GLenum target, GLuint index, GLfloat * data) const {
		gl.GetFloati_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetFloati_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetDoublei_v(GLenum target, GLuint index, GLdouble * data) const {
		gl.GetDoublei_v(target, index, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetDoublei_v(0x%x, %u, 0x%p)\n", gl.GetError(), target, index, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawArraysInstancedBaseInstance(GLenum mode, GLint first, GLsizei count, GLsizei instancecount, GLuint baseinstance) const {
		gl.DrawArraysInstancedBaseInstance(mode, first, count, instancecount, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawArraysInstancedBaseInstance(0x%x, %d, %d, %d, %u)\n", gl.GetError(), mode, first, count, instancecount, baseinstance);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsInstancedBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLuint baseinstance) const {
		gl.DrawElementsInstancedBaseInstance(mode, count, type, indices, instancecount, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseInstance(0x%x, %d, 0x%x, 0x%p, %d, %u)\n", gl.GetError(), mode, count, type, indices, instancecount, baseinstance);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawElementsInstancedBaseVertexBaseInstance(GLenum mode, GLsizei count, GLenum type, const GLvoid * indices, GLsizei instancecount, GLint basevertex, GLuint baseinstance) const {
		gl.DrawElementsInstancedBaseVertexBaseInstance(mode, count, type, indices, instancecount, basevertex, baseinstance);
		fprintf(GLMethodsDebugFile, "[%4d] DrawElementsInstancedBaseVertexBaseInstance(0x%x, %d, 0x%x, 0x%p, %d, %d, %u)\n", gl.GetError(), mode, count, type, indices, instancecount, basevertex, baseinstance);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetInternalformativ(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint * params) const {
		gl.GetInternalformativ(target, internalformat, pname, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetInternalformativ(0x%x, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, internalformat, pname, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetActiveAtomicCounterBufferiv(GLuint program, GLuint bufferIndex, GLenum pname, GLint * params) const {
		gl.GetActiveAtomicCounterBufferiv(program, bufferIndex, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetActiveAtomicCounterBufferiv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), program, bufferIndex, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindImageTexture(GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format) const {
		gl.BindImageTexture(unit, texture, level, layered, layer, access, format);
		fprintf(GLMethodsDebugFile, "[%4d] BindImageTexture(%u, %u, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), unit, texture, level, layered, layer, access, format);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MemoryBarrier(GLbitfield barriers) const {
		gl.MemoryBarrier(barriers);
		fprintf(GLMethodsDebugFile, "[%4d] MemoryBarrier(0x%x)\n", gl.GetError(), barriers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexStorage1D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width) const {
		gl.TexStorage1D(target, levels, internalformat, width);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage1D(0x%x, %d, 0x%x, %d)\n", gl.GetError(), target, levels, internalformat, width);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexStorage2D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.TexStorage2D(target, levels, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage2D(0x%x, %d, 0x%x, %d, %d)\n", gl.GetError(), target, levels, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexStorage3D(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.TexStorage3D(target, levels, internalformat, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage3D(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, levels, internalformat, width, height, depth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawTransformFeedbackInstanced(GLenum mode, GLuint id, GLsizei instancecount) const {
		gl.DrawTransformFeedbackInstanced(mode, id, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackInstanced(0x%x, %u, %d)\n", gl.GetError(), mode, id, instancecount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DrawTransformFeedbackStreamInstanced(GLenum mode, GLuint id, GLuint stream, GLsizei instancecount) const {
		gl.DrawTransformFeedbackStreamInstanced(mode, id, stream, instancecount);
		fprintf(GLMethodsDebugFile, "[%4d] DrawTransformFeedbackStreamInstanced(0x%x, %u, %u, %d)\n", gl.GetError(), mode, id, stream, instancecount);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferData(GLenum target, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearBufferData(target, internalformat, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferData(0x%x, 0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, internalformat, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearBufferSubData(GLenum target, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearBufferSubData(target, internalformat, offset, size, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearBufferSubData(0x%x, 0x%x, %" LL "d, %" LL "d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, internalformat, offset, size, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DispatchCompute(GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z) const {
		gl.DispatchCompute(num_groups_x, num_groups_y, num_groups_z);
		fprintf(GLMethodsDebugFile, "[%4d] DispatchCompute(%u, %u, %u)\n", gl.GetError(), num_groups_x, num_groups_y, num_groups_z);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DispatchComputeIndirect(GLintptr indirect) const {
		gl.DispatchComputeIndirect(indirect);
		fprintf(GLMethodsDebugFile, "[%4d] DispatchComputeIndirect(%" LL "d)\n", gl.GetError(), indirect);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyImageSubData(GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth) const {
		gl.CopyImageSubData(srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
		fprintf(GLMethodsDebugFile, "[%4d] CopyImageSubData(%u, 0x%x, %d, %d, %d, %d, %u, 0x%x, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), srcName, srcTarget, srcLevel, srcX, srcY, srcZ, dstName, dstTarget, dstLevel, dstX, dstY, dstZ, srcWidth, srcHeight, srcDepth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid FramebufferParameteri(GLenum target, GLenum pname, GLint param) const {
		gl.FramebufferParameteri(target, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] FramebufferParameteri(0x%x, 0x%x, %d)\n", gl.GetError(), target, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetFramebufferParameteriv(GLenum target, GLenum pname, GLint * params) const {
		gl.GetFramebufferParameteriv(target, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetFramebufferParameteriv(0x%x, 0x%x, 0x%p)\n", gl.GetError(), target, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetInternalformati64v(GLenum target, GLenum internalformat, GLenum pname, GLsizei bufSize, GLint64 * params) const {
		gl.GetInternalformati64v(target, internalformat, pname, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetInternalformati64v(0x%x, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, internalformat, pname, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.InvalidateTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateTexSubImage(%u, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateTexImage(GLuint texture, GLint level) const {
		gl.InvalidateTexImage(texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateTexImage(%u, %d)\n", gl.GetError(), texture, level);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr length) const {
		gl.InvalidateBufferSubData(buffer, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateBufferSubData(%u, %" LL "d, %" LL "d)\n", gl.GetError(), buffer, offset, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateBufferData(GLuint buffer) const {
		gl.InvalidateBufferData(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateBufferData(%u)\n", gl.GetError(), buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments) const {
		gl.InvalidateFramebuffer(target, numAttachments, attachments);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateFramebuffer(0x%x, %d, 0x%p)\n", gl.GetError(), target, numAttachments, attachments);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateSubFramebuffer(GLenum target, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.InvalidateSubFramebuffer(target, numAttachments, attachments, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateSubFramebuffer(0x%x, %d, 0x%p, %d, %d, %d, %d)\n", gl.GetError(), target, numAttachments, attachments, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MultiDrawArraysIndirect(GLenum mode, const GLvoid * indirect, GLsizei drawcount, GLsizei stride) const {
		gl.MultiDrawArraysIndirect(mode, indirect, drawcount, stride);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawArraysIndirect(0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, indirect, drawcount, stride);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MultiDrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect, GLsizei drawcount, GLsizei stride) const {
		gl.MultiDrawElementsIndirect(mode, type, indirect, drawcount, stride);
		fprintf(GLMethodsDebugFile, "[%4d] MultiDrawElementsIndirect(0x%x, 0x%x, 0x%p, %d, %d)\n", gl.GetError(), mode, type, indirect, drawcount, stride);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramInterfaceiv(GLuint program, GLenum programInterface, GLenum pname, GLint * params) const {
		gl.GetProgramInterfaceiv(program, programInterface, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramInterfaceiv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), program, programInterface, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLuint GetProgramResourceIndex(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLuint res = gl.GetProgramResourceIndex(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceIndex(%u, 0x%x, 0x%p) -> %u\n", gl.GetError(), program, programInterface, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetProgramResourceName(GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, GLchar * name) const {
		gl.GetProgramResourceName(program, programInterface, index, bufSize, length, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceName(%u, 0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), program, programInterface, index, bufSize, length, name);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetProgramResourceiv(GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params) const {
		gl.GetProgramResourceiv(program, programInterface, index, propCount, props, bufSize, length, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceiv(%u, 0x%x, %u, %d, 0x%p, %d, 0x%p, 0x%p)\n", gl.GetError(), program, programInterface, index, propCount, props, bufSize, length, params);
		fflush(GLMethodsDebugFile);
	}

	GLint GetProgramResourceLocation(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLint res = gl.GetProgramResourceLocation(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceLocation(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, programInterface, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLint GetProgramResourceLocationIndex(GLuint program, GLenum programInterface, const GLchar * name) const {
		GLint res = gl.GetProgramResourceLocationIndex(program, programInterface, name);
		fprintf(GLMethodsDebugFile, "[%4d] GetProgramResourceLocationIndex(%u, 0x%x, 0x%p) -> %d\n", gl.GetError(), program, programInterface, name, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid ShaderStorageBlockBinding(GLuint program, GLuint storageBlockIndex, GLuint storageBlockBinding) const {
		gl.ShaderStorageBlockBinding(program, storageBlockIndex, storageBlockBinding);
		fprintf(GLMethodsDebugFile, "[%4d] ShaderStorageBlockBinding(%u, %u, %u)\n", gl.GetError(), program, storageBlockIndex, storageBlockBinding);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexBufferRange(GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TexBufferRange(target, internalformat, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TexBufferRange(0x%x, 0x%x, %u, %" LL "d, %" LL "d)\n", gl.GetError(), target, internalformat, buffer, offset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexStorage2DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage2DMultisample(0x%x, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TexStorage3DMultisample(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TexStorage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TexStorage3DMultisample(0x%x, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), target, samples, internalformat, width, height, depth, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureView(GLuint texture, GLenum target, GLuint origtexture, GLenum internalformat, GLuint minlevel, GLuint numlevels, GLuint minlayer, GLuint numlayers) const {
		gl.TextureView(texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
		fprintf(GLMethodsDebugFile, "[%4d] TextureView(%u, 0x%x, %u, 0x%x, %u, %u, %u, %u)\n", gl.GetError(), texture, target, origtexture, internalformat, minlevel, numlevels, minlayer, numlayers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindVertexBuffer(GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) const {
		gl.BindVertexBuffer(bindingindex, buffer, offset, stride);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexBuffer(%u, %u, %" LL "d, %d)\n", gl.GetError(), bindingindex, buffer, offset, stride);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribFormat(GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const {
		gl.VertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribFormat(%u, %d, 0x%x, %d, %u)\n", gl.GetError(), attribindex, size, type, normalized, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribIFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexAttribIFormat(attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribIFormat(%u, %d, 0x%x, %u)\n", gl.GetError(), attribindex, size, type, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribLFormat(GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexAttribLFormat(attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribLFormat(%u, %d, 0x%x, %u)\n", gl.GetError(), attribindex, size, type, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexAttribBinding(GLuint attribindex, GLuint bindingindex) const {
		gl.VertexAttribBinding(attribindex, bindingindex);
		fprintf(GLMethodsDebugFile, "[%4d] VertexAttribBinding(%u, %u)\n", gl.GetError(), attribindex, bindingindex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexBindingDivisor(GLuint bindingindex, GLuint divisor) const {
		gl.VertexBindingDivisor(bindingindex, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexBindingDivisor(%u, %u)\n", gl.GetError(), bindingindex, divisor);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DebugMessageControl(GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint * ids, GLboolean enabled) const {
		gl.DebugMessageControl(source, type, severity, count, ids, enabled);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageControl(0x%x, 0x%x, 0x%x, %d, 0x%p, %d)\n", gl.GetError(), source, type, severity, count, ids, enabled);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DebugMessageInsert(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * buf) const {
		gl.DebugMessageInsert(source, type, id, severity, length, buf);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageInsert(0x%x, 0x%x, %u, 0x%x, %d, 0x%p)\n", gl.GetError(), source, type, id, severity, length, buf);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DebugMessageCallback(GLDEBUGPROC callback, const GLvoid * userParam) const {
		gl.DebugMessageCallback(callback, userParam);
		fprintf(GLMethodsDebugFile, "[%4d] DebugMessageCallback(0x%p, 0x%p)\n", gl.GetError(), callback, userParam);
		fflush(GLMethodsDebugFile);
	}

	GLuint GetDebugMessageLog(GLuint count, GLsizei bufSize, GLenum * sources, GLenum * types, GLuint * ids, GLenum * severities, GLsizei * lengths, GLchar * messageLog) const {
		GLuint res = gl.GetDebugMessageLog(count, bufSize, sources, types, ids, severities, lengths, messageLog);
		fprintf(GLMethodsDebugFile, "[%4d] GetDebugMessageLog(%u, %d, 0x%p, 0x%p, 0x%p, 0x%p, 0x%p, 0x%p) -> %u\n", gl.GetError(), count, bufSize, sources, types, ids, severities, lengths, messageLog, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid PushDebugGroup(GLenum source, GLuint id, GLsizei length, const GLchar * message) const {
		gl.PushDebugGroup(source, id, length, message);
		fprintf(GLMethodsDebugFile, "[%4d] PushDebugGroup(0x%x, %u, %d, 0x%p)\n", gl.GetError(), source, id, length, message);
		fflush(GLMethodsDebugFile);
	}

	GLvoid PopDebugGroup() const {
		gl.PopDebugGroup();
		fprintf(GLMethodsDebugFile, "[%4d] PopDebugGroup()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	GLvoid ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const GLchar * label) const {
		gl.ObjectLabel(identifier, name, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] ObjectLabel(0x%x, %u, %d, 0x%p)\n", gl.GetError(), identifier, name, length, label);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei * length, GLchar * label) const {
		gl.GetObjectLabel(identifier, name, bufSize, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] GetObjectLabel(0x%x, %u, %d, 0x%p, 0x%p)\n", gl.GetError(), identifier, name, bufSize, length, label);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ObjectPtrLabel(const GLvoid * ptr, GLsizei length, const GLchar * label) const {
		gl.ObjectPtrLabel(ptr, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] ObjectPtrLabel( 0x%p, %d, 0x%p)\n", gl.GetError(), ptr, length, label);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetObjectPtrLabel(const GLvoid * ptr, GLsizei bufSize, GLsizei * length, GLchar * label) const {
		gl.GetObjectPtrLabel(ptr, bufSize, length, label);
		fprintf(GLMethodsDebugFile, "[%4d] GetObjectPtrLabel( 0x%p, %d, 0x%p, 0x%p)\n", gl.GetError(), ptr, bufSize, length, label);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BufferStorage(GLenum target, GLsizeiptr size, const GLvoid * data, GLbitfield flags) const {
		gl.BufferStorage(target, size, data, flags);
		fprintf(GLMethodsDebugFile, "[%4d] BufferStorage(0x%x, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), target, size, data, flags);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearTexImage(GLuint texture, GLint level, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearTexImage(texture, level, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearTexImage(%u, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearTexSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearTexSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearTexSubImage(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindBuffersBase(GLenum target, GLuint first, GLsizei count, const GLuint * buffers) const {
		gl.BindBuffersBase(target, first, count, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffersBase(0x%x, %u, %d, 0x%p)\n", gl.GetError(), target, first, count, buffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindBuffersRange(GLenum target, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizeiptr * sizes) const {
		gl.BindBuffersRange(target, first, count, buffers, offsets, sizes);
		fprintf(GLMethodsDebugFile, "[%4d] BindBuffersRange(0x%x, %u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), target, first, count, buffers, offsets, sizes);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindTextures(GLuint first, GLsizei count, const GLuint * textures) const {
		gl.BindTextures(first, count, textures);
		fprintf(GLMethodsDebugFile, "[%4d] BindTextures(%u, %d, 0x%p)\n", gl.GetError(), first, count, textures);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindSamplers(GLuint first, GLsizei count, const GLuint * samplers) const {
		gl.BindSamplers(first, count, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] BindSamplers(%u, %d, 0x%p)\n", gl.GetError(), first, count, samplers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindImageTextures(GLuint first, GLsizei count, const GLuint * textures) const {
		gl.BindImageTextures(first, count, textures);
		fprintf(GLMethodsDebugFile, "[%4d] BindImageTextures(%u, %d, 0x%p)\n", gl.GetError(), first, count, textures);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindVertexBuffers(GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) const {
		gl.BindVertexBuffers(first, count, buffers, offsets, strides);
		fprintf(GLMethodsDebugFile, "[%4d] BindVertexBuffers(%u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), first, count, buffers, offsets, strides);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClipControl(GLenum origin, GLenum depth) const {
		gl.ClipControl(origin, depth);
		fprintf(GLMethodsDebugFile, "[%4d] ClipControl(0x%x, 0x%x)\n", gl.GetError(), origin, depth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateTransformFeedbacks(GLsizei n, GLuint * ids) const {
		gl.CreateTransformFeedbacks(n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] CreateTransformFeedbacks(%d, 0x%p)\n", gl.GetError(), n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TransformFeedbackBufferBase(GLuint xfb, GLuint index, GLuint buffer) const {
		gl.TransformFeedbackBufferBase(xfb, index, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackBufferBase(%u, %u, %u)\n", gl.GetError(), xfb, index, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TransformFeedbackBufferRange(GLuint xfb, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TransformFeedbackBufferRange(xfb, index, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TransformFeedbackBufferRange(%u, %u, %u, %" LL "d, %" LL "d)\n", gl.GetError(), xfb, index, buffer, offset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTransformFeedbackiv(GLuint xfb, GLenum pname, GLint * param) const {
		gl.GetTransformFeedbackiv(xfb, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbackiv(%u, 0x%x, 0x%p)\n", gl.GetError(), xfb, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTransformFeedbacki_v(GLuint xfb, GLenum pname, GLuint index, GLint * param) const {
		gl.GetTransformFeedbacki_v(xfb, pname, index, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbacki_v(%u, 0x%x, %u, 0x%p)\n", gl.GetError(), xfb, pname, index, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTransformFeedbacki64_v(GLuint xfb, GLenum pname, GLuint index, GLint64 * param) const {
		gl.GetTransformFeedbacki64_v(xfb, pname, index, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetTransformFeedbacki64_v(%u, 0x%x, %u, 0x%p)\n", gl.GetError(), xfb, pname, index, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateBuffers(GLsizei n, GLuint * buffers) const {
		gl.CreateBuffers(n, buffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateBuffers(%d, 0x%p)\n", gl.GetError(), n, buffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedBufferStorage(GLuint buffer, GLsizeiptr size, const GLvoid * data, GLbitfield flags) const {
		gl.NamedBufferStorage(buffer, size, data, flags);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferStorage(%u, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), buffer, size, data, flags);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedBufferData(GLuint buffer, GLsizeiptr size, const GLvoid * data, GLenum usage) const {
		gl.NamedBufferData(buffer, size, data, usage);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferData(%u, %" LL "d, 0x%p, 0x%x)\n", gl.GetError(), buffer, size, data, usage);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const GLvoid * data) const {
		gl.NamedBufferSubData(buffer, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] NamedBufferSubData(%u, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), buffer, offset, size, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyNamedBufferSubData(GLuint readBuffer, GLuint writeBuffer, GLintptr readOffset, GLintptr writeOffset, GLsizeiptr size) const {
		gl.CopyNamedBufferSubData(readBuffer, writeBuffer, readOffset, writeOffset, size);
		fprintf(GLMethodsDebugFile, "[%4d] CopyNamedBufferSubData(%u, %u, %" LL "d, %" LL "d, %" LL "d)\n", gl.GetError(), readBuffer, writeBuffer, readOffset, writeOffset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedBufferData(GLuint buffer, GLenum internalformat, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearNamedBufferData(buffer, internalformat, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedBufferData(%u, 0x%x, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), buffer, internalformat, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedBufferSubData(GLuint buffer, GLenum internalformat, GLintptr offset, GLsizeiptr size, GLenum format, GLenum type, const GLvoid * data) const {
		gl.ClearNamedBufferSubData(buffer, internalformat, offset, size, format, type, data);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedBufferSubData(%u, 0x%x, %" LL "d, %" LL "d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), buffer, internalformat, offset, size, format, type, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid * MapNamedBuffer(GLuint buffer, GLenum access) const {
		GLvoid * res = gl.MapNamedBuffer(buffer, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapNamedBuffer(%u, 0x%x) -> 0x%p\n", gl.GetError(), buffer, access, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid * MapNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access) const {
		GLvoid * res = gl.MapNamedBufferRange(buffer, offset, length, access);
		fprintf(GLMethodsDebugFile, "[%4d] MapNamedBufferRange(%u, %" LL "d, %" LL "d, 0x%x) -> 0x%p\n", gl.GetError(), buffer, offset, length, access, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLboolean UnmapNamedBuffer(GLuint buffer) const {
		GLboolean res = gl.UnmapNamedBuffer(buffer);
		fprintf(GLMethodsDebugFile, "[%4d] UnmapNamedBuffer(%u) -> %d\n", gl.GetError(), buffer, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid FlushMappedNamedBufferRange(GLuint buffer, GLintptr offset, GLsizeiptr length) const {
		gl.FlushMappedNamedBufferRange(buffer, offset, length);
		fprintf(GLMethodsDebugFile, "[%4d] FlushMappedNamedBufferRange(%u, %" LL "d, %" LL "d)\n", gl.GetError(), buffer, offset, length);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedBufferParameteriv(GLuint buffer, GLenum pname, GLint * params) const {
		gl.GetNamedBufferParameteriv(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedBufferParameteri64v(GLuint buffer, GLenum pname, GLint64 * params) const {
		gl.GetNamedBufferParameteri64v(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferParameteri64v(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedBufferPointerv(GLuint buffer, GLenum pname, GLvoid ** params) const {
		gl.GetNamedBufferPointerv(buffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferPointerv(%u, 0x%x, 0x%p)\n", gl.GetError(), buffer, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, GLvoid * data) const {
		gl.GetNamedBufferSubData(buffer, offset, size, data);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedBufferSubData(%u, %" LL "d, %" LL "d, 0x%p)\n", gl.GetError(), buffer, offset, size, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateFramebuffers(GLsizei n, GLuint * framebuffers) const {
		gl.CreateFramebuffers(n, framebuffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateFramebuffers(%d, 0x%p)\n", gl.GetError(), n, framebuffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferRenderbuffer(GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) const {
		gl.NamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferRenderbuffer(%u, 0x%x, 0x%x, %u)\n", gl.GetError(), framebuffer, attachment, renderbuffertarget, renderbuffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferParameteri(GLuint framebuffer, GLenum pname, GLint param) const {
		gl.NamedFramebufferParameteri(framebuffer, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferParameteri(%u, 0x%x, %d)\n", gl.GetError(), framebuffer, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferTexture(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level) const {
		gl.NamedFramebufferTexture(framebuffer, attachment, texture, level);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferTexture(%u, 0x%x, %u, %d)\n", gl.GetError(), framebuffer, attachment, texture, level);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferTextureLayer(GLuint framebuffer, GLenum attachment, GLuint texture, GLint level, GLint layer) const {
		gl.NamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferTextureLayer(%u, 0x%x, %u, %d, %d)\n", gl.GetError(), framebuffer, attachment, texture, level, layer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferDrawBuffer(GLuint framebuffer, GLenum buf) const {
		gl.NamedFramebufferDrawBuffer(framebuffer, buf);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferDrawBuffer(%u, 0x%x)\n", gl.GetError(), framebuffer, buf);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferDrawBuffers(GLuint framebuffer, GLsizei n, const GLenum * bufs) const {
		gl.NamedFramebufferDrawBuffers(framebuffer, n, bufs);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferDrawBuffers(%u, %d, 0x%p)\n", gl.GetError(), framebuffer, n, bufs);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedFramebufferReadBuffer(GLuint framebuffer, GLenum src) const {
		gl.NamedFramebufferReadBuffer(framebuffer, src);
		fprintf(GLMethodsDebugFile, "[%4d] NamedFramebufferReadBuffer(%u, 0x%x)\n", gl.GetError(), framebuffer, src);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateNamedFramebufferData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments) const {
		gl.InvalidateNamedFramebufferData(framebuffer, numAttachments, attachments);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateNamedFramebufferData(%u, %d, 0x%p)\n", gl.GetError(), framebuffer, numAttachments, attachments);
		fflush(GLMethodsDebugFile);
	}

	GLvoid InvalidateNamedFramebufferSubData(GLuint framebuffer, GLsizei numAttachments, const GLenum * attachments, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.InvalidateNamedFramebufferSubData(framebuffer, numAttachments, attachments, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] InvalidateNamedFramebufferSubData(%u, %d, 0x%p, %d, %d, %d, %d)\n", gl.GetError(), framebuffer, numAttachments, attachments, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLint * value) const {
		gl.ClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLuint * value) const {
		gl.ClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferuiv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer, GLint drawbuffer, const GLfloat * value) const {
		gl.ClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferfv(%u, 0x%x, %d, 0x%p)\n", gl.GetError(), framebuffer, buffer, drawbuffer, value);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer, GLint drawbuffer, GLfloat depth, GLint stencil) const {
		gl.ClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil);
		fprintf(GLMethodsDebugFile, "[%4d] ClearNamedFramebufferfi(%u, 0x%x, %d, %f, %d)\n", gl.GetError(), framebuffer, buffer, drawbuffer, depth, stencil);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BlitNamedFramebuffer(GLuint readFramebuffer, GLuint drawFramebuffer, GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter) const {
		gl.BlitNamedFramebuffer(readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fprintf(GLMethodsDebugFile, "[%4d] BlitNamedFramebuffer(%u, %u, %d, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x)\n", gl.GetError(), readFramebuffer, drawFramebuffer, srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
		fflush(GLMethodsDebugFile);
	}

	GLenum CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target) const {
		GLenum res = gl.CheckNamedFramebufferStatus(framebuffer, target);
		fprintf(GLMethodsDebugFile, "[%4d] CheckNamedFramebufferStatus(%u, 0x%x) -> 0x%x\n", gl.GetError(), framebuffer, target, res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetNamedFramebufferParameteriv(GLuint framebuffer, GLenum pname, GLint * param) const {
		gl.GetNamedFramebufferParameteriv(framebuffer, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedFramebufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), framebuffer, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedFramebufferAttachmentParameteriv(GLuint framebuffer, GLenum attachment, GLenum pname, GLint * params) const {
		gl.GetNamedFramebufferAttachmentParameteriv(framebuffer, attachment, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedFramebufferAttachmentParameteriv(%u, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), framebuffer, attachment, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateRenderbuffers(GLsizei n, GLuint * renderbuffers) const {
		gl.CreateRenderbuffers(n, renderbuffers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateRenderbuffers(%d, 0x%p)\n", gl.GetError(), n, renderbuffers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedRenderbufferStorage(GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.NamedRenderbufferStorage(renderbuffer, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] NamedRenderbufferStorage(%u, 0x%x, %d, %d)\n", gl.GetError(), renderbuffer, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid NamedRenderbufferStorageMultisample(GLuint renderbuffer, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.NamedRenderbufferStorageMultisample(renderbuffer, samples, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] NamedRenderbufferStorageMultisample(%u, %d, 0x%x, %d, %d)\n", gl.GetError(), renderbuffer, samples, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetNamedRenderbufferParameteriv(GLuint renderbuffer, GLenum pname, GLint * params) const {
		gl.GetNamedRenderbufferParameteriv(renderbuffer, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetNamedRenderbufferParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), renderbuffer, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateTextures(GLenum target, GLsizei n, GLuint * textures) const {
		gl.CreateTextures(target, n, textures);
		fprintf(GLMethodsDebugFile, "[%4d] CreateTextures(0x%x, %d, 0x%p)\n", gl.GetError(), target, n, textures);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureBuffer(GLuint texture, GLenum internalformat, GLuint buffer) const {
		gl.TextureBuffer(texture, internalformat, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] TextureBuffer(%u, 0x%x, %u)\n", gl.GetError(), texture, internalformat, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureBufferRange(GLuint texture, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size) const {
		gl.TextureBufferRange(texture, internalformat, buffer, offset, size);
		fprintf(GLMethodsDebugFile, "[%4d] TextureBufferRange(%u, 0x%x, %u, %" LL "d, %" LL "d)\n", gl.GetError(), texture, internalformat, buffer, offset, size);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureStorage1D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width) const {
		gl.TextureStorage1D(texture, levels, internalformat, width);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage1D(%u, %d, 0x%x, %d)\n", gl.GetError(), texture, levels, internalformat, width);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureStorage2D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height) const {
		gl.TextureStorage2D(texture, levels, internalformat, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage2D(%u, %d, 0x%x, %d, %d)\n", gl.GetError(), texture, levels, internalformat, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureStorage3D(GLuint texture, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth) const {
		gl.TextureStorage3D(texture, levels, internalformat, width, height, depth);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage3D(%u, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), texture, levels, internalformat, width, height, depth);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureStorage2DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations) const {
		gl.TextureStorage2DMultisample(texture, samples, internalformat, width, height, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage2DMultisample(%u, %d, 0x%x, %d, %d, %d)\n", gl.GetError(), texture, samples, internalformat, width, height, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureStorage3DMultisample(GLuint texture, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations) const {
		gl.TextureStorage3DMultisample(texture, samples, internalformat, width, height, depth, fixedsamplelocations);
		fprintf(GLMethodsDebugFile, "[%4d] TextureStorage3DMultisample(%u, %d, 0x%x, %d, %d, %d, %d)\n", gl.GetError(), texture, samples, internalformat, width, height, depth, fixedsamplelocations);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage1D(texture, level, xoffset, width, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage1D(%u, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, width, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage2D(%u, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, width, height, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid * pixels) const {
		gl.TextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] TextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage1D(texture, level, xoffset, width, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage1D(%u, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, width, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage2D(%u, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, width, height, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CompressedTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid * data) const {
		gl.CompressedTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] CompressedTextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTextureSubImage1D(GLuint texture, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width) const {
		gl.CopyTextureSubImage1D(texture, level, xoffset, x, y, width);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage1D(%u, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, x, y, width);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTextureSubImage2D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTextureSubImage2D(texture, level, xoffset, yoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage2D(%u, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CopyTextureSubImage3D(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height) const {
		gl.CopyTextureSubImage3D(texture, level, xoffset, yoffset, zoffset, x, y, width, height);
		fprintf(GLMethodsDebugFile, "[%4d] CopyTextureSubImage3D(%u, %d, %d, %d, %d, %d, %d, %d, %d)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, x, y, width, height);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameterf(GLuint texture, GLenum pname, GLfloat param) const {
		gl.TextureParameterf(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterf(%u, 0x%x, %f)\n", gl.GetError(), texture, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameterfv(GLuint texture, GLenum pname, const GLfloat * param) const {
		gl.TextureParameterfv(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameteri(GLuint texture, GLenum pname, GLint param) const {
		gl.TextureParameteri(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameteri(%u, 0x%x, %d)\n", gl.GetError(), texture, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameterIiv(GLuint texture, GLenum pname, const GLint * params) const {
		gl.TextureParameterIiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameterIuiv(GLuint texture, GLenum pname, const GLuint * params) const {
		gl.TextureParameterIuiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureParameteriv(GLuint texture, GLenum pname, const GLint * param) const {
		gl.TextureParameteriv(texture, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] TextureParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GenerateTextureMipmap(GLuint texture) const {
		gl.GenerateTextureMipmap(texture);
		fprintf(GLMethodsDebugFile, "[%4d] GenerateTextureMipmap(%u)\n", gl.GetError(), texture);
		fflush(GLMethodsDebugFile);
	}

	GLvoid BindTextureUnit(GLuint unit, GLuint texture) const {
		gl.BindTextureUnit(unit, texture);
		fprintf(GLMethodsDebugFile, "[%4d] BindTextureUnit(%u, %u)\n", gl.GetError(), unit, texture);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureImage(GLuint texture, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetTextureImage(texture, level, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureImage(%u, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, format, type, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetCompressedTextureImage(GLuint texture, GLint level, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetCompressedTextureImage(texture, level, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTextureImage(%u, %d, %d, 0x%p)\n", gl.GetError(), texture, level, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureLevelParameterfv(GLuint texture, GLint level, GLenum pname, GLfloat * params) const {
		gl.GetTextureLevelParameterfv(texture, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureLevelParameterfv(%u, %d, 0x%x, 0x%p)\n", gl.GetError(), texture, level, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureLevelParameteriv(GLuint texture, GLint level, GLenum pname, GLint * params) const {
		gl.GetTextureLevelParameteriv(texture, level, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureLevelParameteriv(%u, %d, 0x%x, 0x%p)\n", gl.GetError(), texture, level, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureParameterfv(GLuint texture, GLenum pname, GLfloat * params) const {
		gl.GetTextureParameterfv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterfv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureParameterIiv(GLuint texture, GLenum pname, GLint * params) const {
		gl.GetTextureParameterIiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterIiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureParameterIuiv(GLuint texture, GLenum pname, GLuint * params) const {
		gl.GetTextureParameterIuiv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameterIuiv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureParameteriv(GLuint texture, GLenum pname, GLint * params) const {
		gl.GetTextureParameteriv(texture, pname, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureParameteriv(%u, 0x%x, 0x%p)\n", gl.GetError(), texture, pname, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateVertexArrays(GLsizei n, GLuint * arrays) const {
		gl.CreateVertexArrays(n, arrays);
		fprintf(GLMethodsDebugFile, "[%4d] CreateVertexArrays(%d, 0x%p)\n", gl.GetError(), n, arrays);
		fflush(GLMethodsDebugFile);
	}

	GLvoid DisableVertexArrayAttrib(GLuint vaobj, GLuint index) const {
		gl.DisableVertexArrayAttrib(vaobj, index);
		fprintf(GLMethodsDebugFile, "[%4d] DisableVertexArrayAttrib(%u, %u)\n", gl.GetError(), vaobj, index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid EnableVertexArrayAttrib(GLuint vaobj, GLuint index) const {
		gl.EnableVertexArrayAttrib(vaobj, index);
		fprintf(GLMethodsDebugFile, "[%4d] EnableVertexArrayAttrib(%u, %u)\n", gl.GetError(), vaobj, index);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayElementBuffer(GLuint vaobj, GLuint buffer) const {
		gl.VertexArrayElementBuffer(vaobj, buffer);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayElementBuffer(%u, %u)\n", gl.GetError(), vaobj, buffer);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayVertexBuffer(GLuint vaobj, GLuint bindingindex, GLuint buffer, GLintptr offset, GLsizei stride) const {
		gl.VertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayVertexBuffer(%u, %u, %u, %" LL "d, %d)\n", gl.GetError(), vaobj, bindingindex, buffer, offset, stride);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayVertexBuffers(GLuint vaobj, GLuint first, GLsizei count, const GLuint * buffers, const GLintptr * offsets, const GLsizei * strides) const {
		gl.VertexArrayVertexBuffers(vaobj, first, count, buffers, offsets, strides);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayVertexBuffers(%u, %u, %d, 0x%p, 0x%p, 0x%p)\n", gl.GetError(), vaobj, first, count, buffers, offsets, strides);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayAttribBinding(GLuint vaobj, GLuint attribindex, GLuint bindingindex) const {
		gl.VertexArrayAttribBinding(vaobj, attribindex, bindingindex);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribBinding(%u, %u, %u)\n", gl.GetError(), vaobj, attribindex, bindingindex);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayAttribFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset) const {
		gl.VertexArrayAttribFormat(vaobj, attribindex, size, type, normalized, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribFormat(%u, %u, %d, 0x%x, %d, %u)\n", gl.GetError(), vaobj, attribindex, size, type, normalized, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayAttribIFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexArrayAttribIFormat(vaobj, attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribIFormat(%u, %u, %d, 0x%x, %u)\n", gl.GetError(), vaobj, attribindex, size, type, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayAttribLFormat(GLuint vaobj, GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset) const {
		gl.VertexArrayAttribLFormat(vaobj, attribindex, size, type, relativeoffset);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayAttribLFormat(%u, %u, %d, 0x%x, %u)\n", gl.GetError(), vaobj, attribindex, size, type, relativeoffset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid VertexArrayBindingDivisor(GLuint vaobj, GLuint bindingindex, GLuint divisor) const {
		gl.VertexArrayBindingDivisor(vaobj, bindingindex, divisor);
		fprintf(GLMethodsDebugFile, "[%4d] VertexArrayBindingDivisor(%u, %u, %u)\n", gl.GetError(), vaobj, bindingindex, divisor);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexArrayiv(GLuint vaobj, GLenum pname, GLint * param) const {
		gl.GetVertexArrayiv(vaobj, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayiv(%u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexArrayIndexediv(GLuint vaobj, GLuint index, GLenum pname, GLint * param) const {
		gl.GetVertexArrayIndexediv(vaobj, index, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayIndexediv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, index, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetVertexArrayIndexed64iv(GLuint vaobj, GLuint index, GLenum pname, GLint64 * param) const {
		gl.GetVertexArrayIndexed64iv(vaobj, index, pname, param);
		fprintf(GLMethodsDebugFile, "[%4d] GetVertexArrayIndexed64iv(%u, %u, 0x%x, 0x%p)\n", gl.GetError(), vaobj, index, pname, param);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateSamplers(GLsizei n, GLuint * samplers) const {
		gl.CreateSamplers(n, samplers);
		fprintf(GLMethodsDebugFile, "[%4d] CreateSamplers(%d, 0x%p)\n", gl.GetError(), n, samplers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateProgramPipelines(GLsizei n, GLuint * pipelines) const {
		gl.CreateProgramPipelines(n, pipelines);
		fprintf(GLMethodsDebugFile, "[%4d] CreateProgramPipelines(%d, 0x%p)\n", gl.GetError(), n, pipelines);
		fflush(GLMethodsDebugFile);
	}

	GLvoid CreateQueries(GLenum target, GLsizei n, GLuint * ids) const {
		gl.CreateQueries(target, n, ids);
		fprintf(GLMethodsDebugFile, "[%4d] CreateQueries(0x%x, %d, 0x%p)\n", gl.GetError(), target, n, ids);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryBufferObjecti64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjecti64v(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjecti64v(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryBufferObjectiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectiv(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectiv(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryBufferObjectui64v(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectui64v(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectui64v(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetQueryBufferObjectuiv(GLuint id, GLuint buffer, GLenum pname, GLintptr offset) const {
		gl.GetQueryBufferObjectuiv(id, buffer, pname, offset);
		fprintf(GLMethodsDebugFile, "[%4d] GetQueryBufferObjectuiv(%u, %u, 0x%x, %" LL "d)\n", gl.GetError(), id, buffer, pname, offset);
		fflush(GLMethodsDebugFile);
	}

	GLvoid MemoryBarrierByRegion(GLbitfield barriers) const {
		gl.MemoryBarrierByRegion(barriers);
		fprintf(GLMethodsDebugFile, "[%4d] MemoryBarrierByRegion(0x%x)\n", gl.GetError(), barriers);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetTextureSubImage(%u, %d, %d, %d, %d, %d, %d, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, format, type, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetCompressedTextureSubImage(GLuint texture, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetCompressedTextureSubImage(texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetCompressedTextureSubImage(%u, %d, %d, %d, %d, %d, %d, %d, %d, 0x%p)\n", gl.GetError(), texture, level, xoffset, yoffset, zoffset, width, height, depth, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLenum GetGraphicsResetStatus() const {
		GLenum res = gl.GetGraphicsResetStatus();
		fprintf(GLMethodsDebugFile, "[%4d] GetGraphicsResetStatus() -> 0x%x\n", gl.GetError(), res);
		fflush(GLMethodsDebugFile);
		return res;
	}

	GLvoid GetnCompressedTexImage(GLenum target, GLint lod, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetnCompressedTexImage(target, lod, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetnCompressedTexImage(0x%x, %d, %d, 0x%p)\n", gl.GetError(), target, lod, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetnTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLsizei bufSize, GLvoid * pixels) const {
		gl.GetnTexImage(target, level, format, type, bufSize, pixels);
		fprintf(GLMethodsDebugFile, "[%4d] GetnTexImage(0x%x, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), target, level, format, type, bufSize, pixels);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetnUniformdv(GLuint program, GLint location, GLsizei bufSize, GLdouble * params) const {
		gl.GetnUniformdv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformdv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetnUniformfv(GLuint program, GLint location, GLsizei bufSize, GLfloat * params) const {
		gl.GetnUniformfv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformfv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetnUniformiv(GLuint program, GLint location, GLsizei bufSize, GLint * params) const {
		gl.GetnUniformiv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid GetnUniformuiv(GLuint program, GLint location, GLsizei bufSize, GLuint * params) const {
		gl.GetnUniformuiv(program, location, bufSize, params);
		fprintf(GLMethodsDebugFile, "[%4d] GetnUniformuiv(%u, %d, %d, 0x%p)\n", gl.GetError(), program, location, bufSize, params);
		fflush(GLMethodsDebugFile);
	}

	GLvoid ReadnPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, GLvoid * data) const {
		gl.ReadnPixels(x, y, width, height, format, type, bufSize, data);
		fprintf(GLMethodsDebugFile, "[%4d] ReadnPixels(%d, %d, %d, %d, 0x%x, 0x%x, %d, 0x%p)\n", gl.GetError(), x, y, width, height, format, type, bufSize, data);
		fflush(GLMethodsDebugFile);
	}

	GLvoid TextureBarrier() const {
		gl.TextureBarrier();
		fprintf(GLMethodsDebugFile, "[%4d] TextureBarrier()\n", gl.GetError());
		fflush(GLMethodsDebugFile);
	}

	PROC_glVertexAttribIPointer VertexAttribIPointer;
	PROC_glVertexAttribLPointer VertexAttribLPointer;
	PROC_glVertexAttribPointer VertexAttribPointer;

	PROC_glGetUniformdv GetUniformdv;
	PROC_glGetUniformfv GetUniformfv;
	PROC_glGetUniformiv GetUniformiv;
	PROC_glGetUniformuiv GetUniformuiv;

	PROC_glProgramUniform1d ProgramUniform1d;
	PROC_glProgramUniform1dv ProgramUniform1dv;
	PROC_glProgramUniform1f ProgramUniform1f;
	PROC_glProgramUniform1fv ProgramUniform1fv;
	PROC_glProgramUniform1i ProgramUniform1i;
	PROC_glProgramUniform1iv ProgramUniform1iv;
	PROC_glProgramUniform1ui ProgramUniform1ui;
	PROC_glProgramUniform1uiv ProgramUniform1uiv;
	PROC_glProgramUniform2d ProgramUniform2d;
	PROC_glProgramUniform2dv ProgramUniform2dv;
	PROC_glProgramUniform2f ProgramUniform2f;
	PROC_glProgramUniform2fv ProgramUniform2fv;
	PROC_glProgramUniform2i ProgramUniform2i;
	PROC_glProgramUniform2iv ProgramUniform2iv;
	PROC_glProgramUniform2ui ProgramUniform2ui;
	PROC_glProgramUniform2uiv ProgramUniform2uiv;
	PROC_glProgramUniform3d ProgramUniform3d;
	PROC_glProgramUniform3dv ProgramUniform3dv;
	PROC_glProgramUniform3f ProgramUniform3f;
	PROC_glProgramUniform3fv ProgramUniform3fv;
	PROC_glProgramUniform3i ProgramUniform3i;
	PROC_glProgramUniform3iv ProgramUniform3iv;
	PROC_glProgramUniform3ui ProgramUniform3ui;
	PROC_glProgramUniform3uiv ProgramUniform3uiv;
	PROC_glProgramUniform4d ProgramUniform4d;
	PROC_glProgramUniform4dv ProgramUniform4dv;
	PROC_glProgramUniform4f ProgramUniform4f;
	PROC_glProgramUniform4fv ProgramUniform4fv;
	PROC_glProgramUniform4i ProgramUniform4i;
	PROC_glProgramUniform4iv ProgramUniform4iv;
	PROC_glProgramUniform4ui ProgramUniform4ui;
	PROC_glProgramUniform4uiv ProgramUniform4uiv;
	PROC_glProgramUniformMatrix2dv ProgramUniformMatrix2dv;
	PROC_glProgramUniformMatrix2fv ProgramUniformMatrix2fv;
	PROC_glProgramUniformMatrix2x3dv ProgramUniformMatrix2x3dv;
	PROC_glProgramUniformMatrix2x3fv ProgramUniformMatrix2x3fv;
	PROC_glProgramUniformMatrix2x4dv ProgramUniformMatrix2x4dv;
	PROC_glProgramUniformMatrix2x4fv ProgramUniformMatrix2x4fv;
	PROC_glProgramUniformMatrix3dv ProgramUniformMatrix3dv;
	PROC_glProgramUniformMatrix3fv ProgramUniformMatrix3fv;
	PROC_glProgramUniformMatrix3x2dv ProgramUniformMatrix3x2dv;
	PROC_glProgramUniformMatrix3x2fv ProgramUniformMatrix3x2fv;
	PROC_glProgramUniformMatrix3x4dv ProgramUniformMatrix3x4dv;
	PROC_glProgramUniformMatrix3x4fv ProgramUniformMatrix3x4fv;
	PROC_glProgramUniformMatrix4dv ProgramUniformMatrix4dv;
	PROC_glProgramUniformMatrix4fv ProgramUniformMatrix4fv;
	PROC_glProgramUniformMatrix4x2dv ProgramUniformMatrix4x2dv;
	PROC_glProgramUniformMatrix4x2fv ProgramUniformMatrix4x2fv;
	PROC_glProgramUniformMatrix4x3dv ProgramUniformMatrix4x3dv;
	PROC_glProgramUniformMatrix4x3fv ProgramUniformMatrix4x3fv;

	bool load() {
		bool success = gl.load();

		VertexAttribIPointer = gl.VertexAttribIPointer;
		VertexAttribLPointer = gl.VertexAttribLPointer;
		VertexAttribPointer = gl.VertexAttribPointer;

		GetUniformdv = gl.GetUniformdv;
		GetUniformfv = gl.GetUniformfv;
		GetUniformiv = gl.GetUniformiv;
		GetUniformuiv = gl.GetUniformuiv;

		ProgramUniform1d = gl.ProgramUniform1d;
		ProgramUniform1dv = gl.ProgramUniform1dv;
		ProgramUniform1f = gl.ProgramUniform1f;
		ProgramUniform1fv = gl.ProgramUniform1fv;
		ProgramUniform1i = gl.ProgramUniform1i;
		ProgramUniform1iv = gl.ProgramUniform1iv;
		ProgramUniform1ui = gl.ProgramUniform1ui;
		ProgramUniform1uiv = gl.ProgramUniform1uiv;
		ProgramUniform2d = gl.ProgramUniform2d;
		ProgramUniform2dv = gl.ProgramUniform2dv;
		ProgramUniform2f = gl.ProgramUniform2f;
		ProgramUniform2fv = gl.ProgramUniform2fv;
		ProgramUniform2i = gl.ProgramUniform2i;
		ProgramUniform2iv = gl.ProgramUniform2iv;
		ProgramUniform2ui = gl.ProgramUniform2ui;
		ProgramUniform2uiv = gl.ProgramUniform2uiv;
		ProgramUniform3d = gl.ProgramUniform3d;
		ProgramUniform3dv = gl.ProgramUniform3dv;
		ProgramUniform3f = gl.ProgramUniform3f;
		ProgramUniform3fv = gl.ProgramUniform3fv;
		ProgramUniform3i = gl.ProgramUniform3i;
		ProgramUniform3iv = gl.ProgramUniform3iv;
		ProgramUniform3ui = gl.ProgramUniform3ui;
		ProgramUniform3uiv = gl.ProgramUniform3uiv;
		ProgramUniform4d = gl.ProgramUniform4d;
		ProgramUniform4dv = gl.ProgramUniform4dv;
		ProgramUniform4f = gl.ProgramUniform4f;
		ProgramUniform4fv = gl.ProgramUniform4fv;
		ProgramUniform4i = gl.ProgramUniform4i;
		ProgramUniform4iv = gl.ProgramUniform4iv;
		ProgramUniform4ui = gl.ProgramUniform4ui;
		ProgramUniform4uiv = gl.ProgramUniform4uiv;
		ProgramUniformMatrix2dv = gl.ProgramUniformMatrix2dv;
		ProgramUniformMatrix2fv = gl.ProgramUniformMatrix2fv;
		ProgramUniformMatrix2x3dv = gl.ProgramUniformMatrix2x3dv;
		ProgramUniformMatrix2x3fv = gl.ProgramUniformMatrix2x3fv;
		ProgramUniformMatrix2x4dv = gl.ProgramUniformMatrix2x4dv;
		ProgramUniformMatrix2x4fv = gl.ProgramUniformMatrix2x4fv;
		ProgramUniformMatrix3dv = gl.ProgramUniformMatrix3dv;
		ProgramUniformMatrix3fv = gl.ProgramUniformMatrix3fv;
		ProgramUniformMatrix3x2dv = gl.ProgramUniformMatrix3x2dv;
		ProgramUniformMatrix3x2fv = gl.ProgramUniformMatrix3x2fv;
		ProgramUniformMatrix3x4dv = gl.ProgramUniformMatrix3x4dv;
		ProgramUniformMatrix3x4fv = gl.ProgramUniformMatrix3x4fv;
		ProgramUniformMatrix4dv = gl.ProgramUniformMatrix4dv;
		ProgramUniformMatrix4fv = gl.ProgramUniformMatrix4fv;
		ProgramUniformMatrix4x2dv = gl.ProgramUniformMatrix4x2dv;
		ProgramUniformMatrix4x2fv = gl.ProgramUniformMatrix4x2fv;
		ProgramUniformMatrix4x3dv = gl.ProgramUniformMatrix4x3dv;
		ProgramUniformMatrix4x3fv = gl.ProgramUniformMatrix4x3fv;

		return success;
	}

private:
	GLMethodsDebugImpl(const GLMethodsDebugImpl & copy);
	void operator = (const GLMethodsDebugImpl & rhs);
};
