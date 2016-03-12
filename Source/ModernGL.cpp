#include "ModernGL.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <malloc.h>

namespace GL {
	#include <OpenGL.h>
}

namespace Font {
	unsigned vertShader;
	unsigned fragShader;
	unsigned prog;
	unsigned vao;
	unsigned vbo;

	unsigned glyph;
	unsigned texture;
	unsigned position;
	unsigned viewport;
	unsigned color;
	unsigned size;
	unsigned vert;
	unsigned tex;

	float align_x;
	float align_y;

	#include <DroidSansMono.h>

	bool InitializeFont() {
		vertShader = NewVertexShader(R"(
			#version 400

			const int unit = 16;
			const float piece = 1.0 / unit;

			in vec2 vert;

			uniform int glyph;
			uniform vec2 glyph_position;
			uniform vec2 glyph_size;
			uniform vec2 viewport_size;

			out vec2 text;

			void main() {
				gl_Position = vec4((glyph_position + vert * glyph_size) * 2 / viewport_size - vec2(1.0, 1.0), 0.0, 1.0);
				text = vec2(float(glyph % unit) / unit, float(glyph / unit) / unit) + vert / unit;
			}
		)");

		fragShader = NewFragmentShader(R"(
			#version 400

			in vec2 text;

			uniform sampler2D glyph_texture;
			uniform vec4 glyph_color;

			out vec4 color;

			void main() {
				color = glyph_color;
				color.a *= texture(glyph_texture, text).r;
			}
		)");

		unsigned shaders[] = {vertShader, fragShader};
		prog = NewProgram(shaders, 2);

		float verts[] = {
			0, 0,
			0, 1,
			1, 0,
			1, 1,
		};

		vao = NewVertexArray();
		vbo = NewVertexBuffer(verts, sizeof(verts));
		vert = AttribLocation(prog, "vert");
		glyph = UniformLocation(prog, "glyph");
		texture = UniformLocation(prog, "glyph_texture");
		position = UniformLocation(prog, "glyph_position");
		color = UniformLocation(prog, "glyph_color");
		size = UniformLocation(prog, "glyph_size");
		viewport = UniformLocation(prog, "viewport_size");

		Attribute2f(vbo, vert);
		Uniform1i(texture, 0);
		Uniform4f(color, 0.0, 0.0, 0.0, 1.0);
	
		float sw = (float)DroidSansMono.glyph_width;
		float sh = -(float)DroidSansMono.glyph_height;
		Uniform2f(size, sw, sh);

		tex = NewTexture(DroidSansMono.texture_width, DroidSansMono.texture_height, DroidSansMono.texture_pixels, 1);
		SetTextureFilter(tex, TEXTURE_PIXELATED);

		return true;
	}
}

Info GetInfo() {
	GL::GLint major = 0;
	GL::GLint minor = 0;
	GL::GLint samples = 0;

	GL::glGetIntegerv(GL::GL_MAJOR_VERSION, &major);
	GL::glGetIntegerv(GL::GL_MINOR_VERSION, &minor);
	GL::glGetIntegerv(GL::GL_MAX_SAMPLES, &samples);
	const char * vendor = (const char *)GL::glGetString(GL::GL_VENDOR);
	const char * renderer = (const char *)GL::glGetString(GL::GL_RENDERER);

	if (!vendor) {
		vendor = "";
	}
	
	if (!renderer) {
		renderer = "";
	}

	Info result = {
		major,
		minor,
		samples,
		vendor,
		renderer,
	};

	return result;
}

const char * GetError() {
	switch (GL::glGetError()) {
		case GL::GL_NO_ERROR: return "GL_NO_ERROR";
		case GL::GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL::GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL::GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL::GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
		case GL::GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
		case GL::GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
		case GL::GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
		default: return "Unknown Error";
	}
}

void Viewport(int x, int y, int w, int h) {
	GL::glViewport(x, y, w, h);
}

void Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	const float c = 1.0 / 255.0;
	GL::glClearColor(r * c, g * c, b * c, a * c);
	unsigned GL_ALL_BUFFER_BIT = 0;
	GL_ALL_BUFFER_BIT |= GL::GL_DEPTH_BUFFER_BIT;
	GL_ALL_BUFFER_BIT |= GL::GL_COLOR_BUFFER_BIT;
	GL::glClear(GL_ALL_BUFFER_BIT);
}

void PointSize(float size) {
	GL::glPointSize(size);
}

void LineWidth(float size) {
	GL::glLineWidth(size);
}

void EnableOnly(unsigned mask) {
	(mask & ENABLE_BLEND ? GL::glEnable : GL::glDisable)(GL::GL_BLEND);
	(mask & ENABLE_CULL_FACE ? GL::glEnable : GL::glDisable)(GL::GL_CULL_FACE);
	(mask & ENABLE_DEPTH_TEST ? GL::glEnable : GL::glDisable)(GL::GL_DEPTH_TEST);
	(mask & ENABLE_MULTISAMPLE ? GL::glEnable : GL::glDisable)(GL::GL_MULTISAMPLE);
}

void EnableBlend() {
	GL::glEnable(GL::GL_BLEND);
}

void DisableBlend() {
	GL::glDisable(GL::GL_BLEND);
}

void EnableCullFace() {
	GL::glEnable(GL::GL_CULL_FACE);
}

void DisableCullFace() {
	GL::glDisable(GL::GL_CULL_FACE);
}

void EnableDepthTest() {
	GL::glEnable(GL::GL_DEPTH_TEST);
}

void DisableDepthTest() {
	GL::glDisable(GL::GL_DEPTH_TEST);
}

void EnableMultisample() {
	GL::glEnable(GL::GL_MULTISAMPLE);
}

void DisableMultisample() {
	GL::glDisable(GL::GL_MULTISAMPLE);
}

bool InitializeModernGL() {
	if (!GL::Initialize()) {
		return false;
	}

	if (!Font::InitializeFont()) {
		return false;
	}

	GL::glBlendFunc(GL::GL_SRC_ALPHA, GL::GL_ONE_MINUS_SRC_ALPHA);
	GL::glEnable(GL::GL_PRIMITIVE_RESTART_FIXED_INDEX);
	return true;
}

char compiler_log[16 * 1024 + 1];

template <unsigned Type>
inline unsigned NewShader(const char * source) {
	GL::GLuint shader = GL::glCreateShader(Type);
	GL::glShaderSource(shader, 1, &source, 0);
	GL::glCompileShader(shader);

	GL::GLint compiled = GL::GL_FALSE;
	GL::glGetShaderiv(shader, GL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int log_size = 0;
		GL::glGetShaderInfoLog(shader, 16 * 1024, &log_size, compiler_log);
		compiler_log[log_size] = 0;
		GL::glDeleteShader(shader);
		shader = 0;
	} else {
		compiler_log[0] = 0;
	}

	return shader;
}

unsigned DeleteShader(unsigned shader) {
	GL::glDeleteShader(shader);
}

unsigned NewProgram(unsigned * shader, int count) {
	int program = GL::glCreateProgram();

	for (int i = 0; i < count; ++i) {
		GL::glAttachShader(program, shader[i]);
	}

	GL::glLinkProgram(program);

	GL::GLint linked = GL::GL_FALSE;
	GL::glGetProgramiv(program, GL::GL_LINK_STATUS, &linked);
	if (!linked) {
		int log_size = 0;
		GL::glGetProgramInfoLog(program, 16 * 1024, &log_size, compiler_log);
		compiler_log[log_size] = 0;
		GL::glDeleteProgram(program);
		program = 0;
	} else {
		compiler_log[0] = 0;
		GL::glUseProgram(program);
	} 

	return program;
}

const char * CompilerLog() {
	return compiler_log;
}

void DispatchCompute(unsigned x, unsigned y, unsigned z) {
	// GL::glBindImageTexture(0, 2, 0, 0, GL::GL_FALSE, GL::GL_WRITE_ONLY, GL::GL_RGBA8);
	GL::glDispatchCompute(x, y, z);
}

unsigned DeleteProgram(unsigned program) {
	GL::glDeleteProgram(program);
}

unsigned NewFragmentShader(const char * source) {
	return NewShader<GL::GL_FRAGMENT_SHADER>(source);
}

unsigned NewGeometryShader(const char * source) {
	return NewShader<GL::GL_GEOMETRY_SHADER>(source);
}

unsigned NewVertexShader(const char * source) {
	return NewShader<GL::GL_VERTEX_SHADER>(source);
}

unsigned NewComputeShader(const char * source) {
	return NewShader<GL::GL_COMPUTE_SHADER>(source);
}

unsigned NewTessControlShader(const char * source) {
	return NewShader<GL::GL_TESS_CONTROL_SHADER>(source);
}

unsigned NewTessEvaluationShader(const char * source) {
	return NewShader<GL::GL_TESS_EVALUATION_SHADER>(source);
}

void UseProgram(unsigned program) {
	GL::glUseProgram(program);
}

unsigned AttribLocation(unsigned program, const char * name) {
	return GL::glGetAttribLocation(program, name);
}

unsigned UniformLocation(unsigned program, const char * name) {
	return GL::glGetUniformLocation(program, name);
}

unsigned UniformBlockLocation(unsigned program, const char * name) {
	return GL::glGetUniformBlockIndex(program, name);
}

void Uniform1f(unsigned location, float v0) {
	GL::glUniform1f(location, v0);
}

void Uniform2f(unsigned location, float v0, float v1) {
	GL::glUniform2f(location, v0, v1);
}

void Uniform3f(unsigned location, float v0, float v1, float v2) {
	GL::glUniform3f(location, v0, v1, v2);
}

void Uniform4f(unsigned location, float v0, float v1, float v2, float v3) {
	GL::glUniform4f(location, v0, v1, v2, v3);
}

void Uniform1i(unsigned location, int v0) {
	GL::glUniform1i(location, v0);
}

void Uniform2i(unsigned location, int v0, int v1) {
	GL::glUniform2i(location, v0, v1);
}

void Uniform3i(unsigned location, int v0, int v1, int v2) {
	GL::glUniform3i(location, v0, v1, v2);
}

void Uniform4i(unsigned location, int v0, int v1, int v2, int v3) {
	GL::glUniform4i(location, v0, v1, v2, v3);
}

void UniformMatrix(unsigned location, const float * matrix) {
	GL::glUniformMatrix4fv(location, 1, GL::GL_FALSE, matrix);
}

void UniformBlock(unsigned location, unsigned buffer) {
	GL::glBindBufferBase(GL::GL_UNIFORM_BUFFER, location, buffer);
}

unsigned NewTexture(int width, int height, const void * data, int components) {
	const int formats[] = {0, GL::GL_RED, GL::GL_RG, GL::GL_RGB, GL::GL_RGBA};
	int format = formats[components];

	if (!width && !height) {
		int viewportValue[4];
		GL::glGetIntegerv(GL::GL_VIEWPORT, viewportValue);
		width = viewportValue[2];
		height = viewportValue[3];
	}

	GL::GLuint texture = 0;
	GL::glActiveTexture(GL::GL_TEXTURE0);
	GL::glGenTextures(1, &texture);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
	GL::glTexImage2D(GL::GL_TEXTURE_2D, 0, format, width, height, 0, format, GL::GL_UNSIGNED_BYTE, data);
	return texture;
}

void DeleteTexture(unsigned texture) {
	GL::glDeleteTextures(1, &texture);
}

void SetTextureFilter(unsigned texture, unsigned mode) {
	GL::glActiveTexture(GL::GL_TEXTURE0);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
	switch (mode) {
		case TEXTURE_PIXELATED: {
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_NEAREST);
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_NEAREST);
			break;
		}
		case TEXTURE_FILTERED: {
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR);
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
			break;
		}
		case TEXTURE_MIPMAPPED: {
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR_MIPMAP_LINEAR);
			GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
			break;
		}
	}
}

void UseTexture(unsigned texture, unsigned location) {
	GL::glActiveTexture(GL::GL_TEXTURE0 + location);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
}

void BuildMipmap(unsigned texture, int base, int max) {
	GL::glActiveTexture(GL::GL_TEXTURE0);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BASE_LEVEL, base);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAX_LEVEL, max);
	GL::glGenerateMipmap(GL::GL_TEXTURE_2D);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR_MIPMAP_LINEAR);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
}

unsigned NewVertexArray() {
	GL::GLuint array = 0;
	GL::glGenVertexArrays(1, &array);
	GL::glBindVertexArray(array);
	return array;
}

void DeleteVertexArray(unsigned array) {
	GL::glDeleteVertexArrays(1, &array);
}

void UseVertexArray(unsigned array) {
	GL::glBindVertexArray(array);
}

unsigned NewVertexBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, buffer);
	GL::glBufferData(GL::GL_ARRAY_BUFFER, size, data, GL::GL_STATIC_DRAW);
	return buffer;
}

unsigned NewIndexBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_ELEMENT_ARRAY_BUFFER, buffer);
	GL::glBufferData(GL::GL_ELEMENT_ARRAY_BUFFER, size, data, GL::GL_STATIC_DRAW);
	return buffer;
}

unsigned NewDynamicVertexBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, buffer);
	GL::glBufferData(GL::GL_ARRAY_BUFFER, size, data, GL::GL_DYNAMIC_DRAW);
	return buffer;
}

unsigned NewDynamicIndexBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_ELEMENT_ARRAY_BUFFER, buffer);
	GL::glBufferData(GL::GL_ELEMENT_ARRAY_BUFFER, size, data, GL::GL_DYNAMIC_DRAW);
	return buffer;
}

unsigned NewUniformBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	GL::glBufferData(GL::GL_UNIFORM_BUFFER, size, data, GL::GL_STATIC_DRAW);
	return buffer;
}

void UpdateVertexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_ARRAY_BUFFER, (GL::GLintptr)offset, size, data);
}

void UpdateIndexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_ELEMENT_ARRAY_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_ELEMENT_ARRAY_BUFFER, (GL::GLintptr)offset, size, data);
}

void UpdateUniformBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_UNIFORM_BUFFER, (GL::GLintptr)offset, size, data);
}

void * ReadUniformBuffer(unsigned buffer, unsigned offset, int size) {
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	void * map = GL::glMapBufferRange(GL::GL_UNIFORM_BUFFER, offset, size, GL::GL_READ_ONLY);
	void * content = malloc(size);
	memcpy(content, map, size);
	GL::glUnmapBuffer(GL::GL_UNIFORM_BUFFER);
	return content;
}

void DeleteBuffer(unsigned buffer) {
	GL::glDeleteBuffers(1, &buffer);
}

void RenderTriangles(int count, int first) {
	GL::glDrawArrays(GL::GL_TRIANGLES, first, count);
}

void RenderTriangleStrip(int count, int first) {
	GL::glDrawArrays(GL::GL_TRIANGLE_STRIP, first, count);
}

void RenderTriangleFan(int count, int first) {
	GL::glDrawArrays(GL::GL_TRIANGLE_FAN, first, count);
}

void RenderLines(int count, int first) {
	GL::glDrawArrays(GL::GL_LINES, first, count);
}

void RenderLineStrip(int count, int first) {
	GL::glDrawArrays(GL::GL_LINE_STRIP, first, count);
}

void RenderLineLoop(int count, int first) {
	GL::glDrawArrays(GL::GL_LINE_LOOP, first, count);
}

void RenderPoints(int count, int first) {
	GL::glDrawArrays(GL::GL_POINTS, first, count);
}

void RenderLineStripAdjacency(int count, int first) {
	GL::glDrawArrays(GL::GL_LINE_STRIP_ADJACENCY, first, count);
}

void RenderLinesAdjacency(int count, int first) {
	GL::glDrawArrays(GL::GL_LINES_ADJACENCY, first, count);
}

void RenderTriangleStripAdjacency(int count, int first) {
	GL::glDrawArrays(GL::GL_TRIANGLE_STRIP_ADJACENCY, first, count);
}

void RenderTrianglesAdjacency(int count, int first) {
	GL::glDrawArrays(GL::GL_TRIANGLES_ADJACENCY, first, count);
}

void RenderIndexedTriangles(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_TRIANGLES, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedTriangleStrip(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_TRIANGLE_STRIP, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedTriangleFan(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_TRIANGLE_FAN, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedLines(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_LINES, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedLineStrip(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_LINE_STRIP, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedLineLoop(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_LINE_LOOP, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedPoints(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_POINTS, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedLineStripAdjacency(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_LINE_STRIP_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedLinesAdjacency(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_LINES_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedTriangleStripAdjacency(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_TRIANGLE_STRIP_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr);
}

void RenderIndexedTrianglesAdjacency(int count, int first) {
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElements(GL::GL_TRIANGLES_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr);
}

template <unsigned Type, unsigned Dimension>
inline void SetAttribute(unsigned buffer, unsigned target, const void * ptr = 0) {
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, buffer);
	GL::glVertexAttribPointer(target, Dimension, Type, false, 0, ptr);
	GL::glEnableVertexAttribArray(target);
}

void EnableAttribute(unsigned target) {
	GL::glEnableVertexAttribArray(target);
}

void DisableAttribute(unsigned target) {
	GL::glDisableVertexAttribArray(target);
}

void EnableAttributes(unsigned * target, int count) {
	for (int i = 0; i < count; ++i) {
		GL::glEnableVertexAttribArray(target[i]);
	}
}

void DisableAttributes(unsigned * target, int count) {
	for (int i = 0; i < count; ++i) {
		GL::glDisableVertexAttribArray(target[i]);
	}
}

void Attribute1f(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_FLOAT, 1>(buffer, target, ptr);
}

void Attribute2f(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_FLOAT, 2>(buffer, target, ptr);
}

void Attribute3f(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_FLOAT, 3>(buffer, target, ptr);
}

void Attribute4f(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_FLOAT, 4>(buffer, target, ptr);
}

void Attribute1i(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_INT, 1>(buffer, target, ptr);
}

void Attribute2i(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_INT, 2>(buffer, target, ptr);
}

void Attribute3i(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_INT, 3>(buffer, target, ptr);
}

void Attribute4i(unsigned buffer, unsigned target, const void * ptr) {
	SetAttribute<GL::GL_INT, 4>(buffer, target, ptr);
}

Framebuffer NewFramebuffer(int width, int height, bool multisample) {
	GL::GLuint framebuffer = 0;
	GL::GLuint color = 0;
	GL::GLuint depth = 0;

	GL::glGenFramebuffers(1, &framebuffer);
	GL::glBindFramebuffer(GL::GL_FRAMEBUFFER, framebuffer);

	GL::GLuint target = GL::GL_TEXTURE_2D;
	if (multisample) {
		target = GL::GL_TEXTURE_2D_MULTISAMPLE;
	}

	if (!width && !height) {
		int viewport[4] = {};
		GL::glGetIntegerv(GL::GL_VIEWPORT, viewport);
		width = viewport[2];
		height = viewport[3];
	}

	GL::glGenTextures(1, &color);
	GL::glBindTexture(target, color);
	GL::glTexParameteri(target, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR);
	GL::glTexParameteri(target, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
	GL::glTexImage2D(target, 0, GL::GL_RGB, width, height, 0, GL::GL_RGB, GL::GL_FLOAT, 0);
	GL::glFramebufferTexture2D(GL::GL_FRAMEBUFFER, GL::GL_COLOR_ATTACHMENT0, target, color, 0);

	GL::glGenTextures(1, &depth);
	GL::glBindTexture(target, depth);
	GL::glTexParameteri(target, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR);
	GL::glTexParameteri(target, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
	GL::glTexImage2D(target, 0, GL::GL_DEPTH_COMPONENT, width, height, 0, GL::GL_DEPTH_COMPONENT, GL::GL_FLOAT, 0);
	GL::glFramebufferTexture2D(GL::GL_FRAMEBUFFER, GL::GL_DEPTH_ATTACHMENT, target, depth, 0);

	return Framebuffer {
		framebuffer,
		color,
		depth,
	};
}

void DeleteFramebuffer(unsigned framebuffer) {
	GL::glDeleteFramebuffers(1, &framebuffer);
}

void UseFramebuffer(unsigned framebuffer) {
	GL::glBindFramebuffer(GL::GL_FRAMEBUFFER, framebuffer);
}

void UseDefaultFramebuffer() {
	GL::glBindFramebuffer(GL::GL_FRAMEBUFFER, 0);
}

unsigned char * ReadPixels(int x, int y, int width, int height, int components) {
	const int formats[] = {0, GL::GL_RED, GL::GL_RG, GL::GL_RGB, GL::GL_RGBA};
	int format = formats[components];

	unsigned char * data = (unsigned char *)malloc(width * height * components);
	GL::glReadPixels(x, y, width, height, format, GL::GL_UNSIGNED_BYTE, data);
	return data;
}

float * ReadDepthPixels(int x, int y, int width, int height) {
	float * data = (float *)malloc(width * height * sizeof(float));
	GL::glReadPixels(x, y, width, height, GL::GL_DEPTH_COMPONENT, GL::GL_FLOAT, data);
	return data;
}

void DebugFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	const float c = 1.0 / 255.0;
	UseProgram(Font::prog);
	Uniform4f(Font::color, r * c, g * c, b * c, a * c);
}

void DebugFontAlign(float px, float py) {
	Font::align_x = px;
	Font::align_y = py;
}

void DebugFontPrint(float x, float y, const char * fmt, ...) {
	va_list ap;
	char str[2048];
	va_start(ap, fmt);
	vsprintf(str, fmt, ap);
	va_end(ap);

	EnableOnly(ENABLE_BLEND);
	UseProgram(Font::prog);
	UseTexture(Font::tex);
	UseVertexArray(Font::vao);

	int viewport[4] = {};
	GL::glGetIntegerv(GL::GL_VIEWPORT, viewport);
	Uniform2f(Font::viewport, viewport[2], viewport[3]);

	x -= strlen(str) * Font::DroidSansMono.char_width * Font::align_x;
	y -= Font::DroidSansMono.char_height * Font::align_y;
	y += Font::DroidSansMono.char_height;
	x = (int)x;
	y = (int)y;

	float step = (float)Font::DroidSansMono.char_width;
	const unsigned char * bytes = (const unsigned char *)str;
	for (int i = 0; i < bytes[i]; ++i) {
		Uniform2f(Font::position, x, y);
		Uniform1i(Font::glyph, bytes[i]);
		RenderTriangleStrip(4);
		x += step;
	}
}
