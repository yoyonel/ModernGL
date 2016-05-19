#include "ModernGL.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>
#include <malloc.h>

namespace {
	unsigned defaultVertexArray;
	unsigned defaultFramebuffer;
	unsigned defaultProgram;

	unsigned defaultTextureUnit;

	const int maxCompilerLog = 16 * 1024;
	char compilerLog[maxCompilerLog + 1];
}

namespace GL {
	#include <OpenGL.h>
}

// namespace Font {
// 	unsigned vertShader;
// 	unsigned fragShader;
// 	unsigned prog;
// 	unsigned vao;
// 	unsigned vbo;

// 	unsigned glyph;
// 	unsigned texture;
// 	unsigned position;
// 	unsigned viewport;
// 	unsigned color;
// 	unsigned size;
// 	unsigned vert;
// 	unsigned tex;

// 	float align_x;
// 	float align_y;

// 	#include <DroidSansMono.h>

// 	bool InitializeFont() {
// 		vertShader = NewVertexShader(R"(
// 			#version 400

// 			const int unit = 16;
// 			const float piece = 1.0 / unit;

// 			in vec2 vert;

// 			uniform int glyph;
// 			uniform vec2 glyph_position;
// 			uniform vec2 glyph_size;
// 			uniform vec2 viewport_size;

// 			out vec2 text;

// 			void main() {
// 				gl_Position = vec4((glyph_position + vert * glyph_size) * 2 / viewport_size - vec2(1.0, 1.0), 0.0, 1.0);
// 				text = vec2(float(glyph % unit) / unit, float(glyph / unit) / unit) + vert / unit;
// 			}
// 		)");

// 		fragShader = NewFragmentShader(R"(
// 			#version 400

// 			in vec2 text;

// 			uniform sampler2D glyph_texture;
// 			uniform vec4 glyph_color;

// 			out vec4 color;

// 			void main() {
// 				color = glyph_color;
// 				color.a *= texture(glyph_texture, text).r;
// 			}
// 		)");

// 		unsigned shaders[] = {vertShader, fragShader};
// 		prog = NewProgram(shaders, 2);

// 		float verts[] = {
// 			0, 0,
// 			0, 1,
// 			1, 0,
// 			1, 1,
// 		};

// 		vao = NewVertexArray();
// 		vbo = NewVertexBuffer(verts, sizeof(verts));
// 		vert = AttribLocation(prog, "vert");
// 		glyph = UniformLocation(prog, "glyph");
// 		texture = UniformLocation(prog, "glyph_texture");
// 		position = UniformLocation(prog, "glyph_position");
// 		color = UniformLocation(prog, "glyph_color");
// 		size = UniformLocation(prog, "glyph_size");
// 		viewport = UniformLocation(prog, "viewport_size");

// 		Attribute2f(vbo, vert);
// 		Uniform1i(texture, 0);
// 		Uniform4f(color, 0.0, 0.0, 0.0, 1.0);
	
// 		float sw = (float)DroidSansMono.glyph_width;
// 		float sh = -(float)DroidSansMono.glyph_height;
// 		Uniform2f(size, sw, sh);

// 		tex = NewTexture(DroidSansMono.texture_width, DroidSansMono.texture_height, DroidSansMono.texture_pixels, 1);
// 		SetTextureFilter(tex, TEXTURE_PIXELATED);

// 		return true;
// 	}
// }

bool InitializeModernGL() {
	if (!GL::Initialize()) {
		return false;
	}

	// if (!Font::InitializeFont()) {
	// 	return false;
	// }

	GL::glBlendFunc(GL::GL_SRC_ALPHA, GL::GL_ONE_MINUS_SRC_ALPHA);
	GL::glEnable(GL::GL_PRIMITIVE_RESTART_FIXED_INDEX);

	GL::glGenVertexArrays(1, &defaultVertexArray);
	GL::glBindVertexArray(defaultVertexArray);

	GL::glGetIntegerv(GL::GL_DRAW_FRAMEBUFFER_BINDING, (GL::GLint *)&defaultFramebuffer);
	GL::glGetIntegerv(GL::GL_CURRENT_PROGRAM, (GL::GLint *)&defaultProgram);

	unsigned maxTextureUnits = 1;
	GL::glGetIntegerv(GL::GL_MAX_TEXTURE_IMAGE_UNITS, (GL::GLint *)&maxTextureUnits);
	defaultTextureUnit = maxTextureUnits - 1;
	return true;
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

unsigned NewProgram(unsigned * shader, int count) {
	GL::GLuint program = GL::glCreateProgram();

	for (int i = 0; i < count; ++i) {
		GL::glAttachShader(program, shader[i]);
	}

	GL::glLinkProgram(program);

	GL::GLint linked = GL::GL_FALSE;
	GL::glGetProgramiv(program, GL::GL_LINK_STATUS, &linked);
	if (!linked) {
		int logSize = 0;
		GL::glGetProgramInfoLog(program, maxCompilerLog, &logSize, compilerLog);
		compilerLog[logSize] = 0;
		GL::glDeleteProgram(program);
		program = 0;
	} else {
		compilerLog[0] = 0;
		GL::glUseProgram(program);
	} 

	return program;
}

void DeleteProgram(unsigned program) {
	unsigned shaders[8] = {};
	int numShaders = 0;

	GL::glGetAttachedShaders(program, 8, &numShaders, shaders);
	for (int i = 0; i < numShaders; ++i) {
		GL::glDeleteShader(shaders[i]);
	}
	GL::glDeleteProgram(program);
}

void UseProgram(unsigned program) {
	GL::glUseProgram(program);
}

void UseDefaultProgram() {
	GL::glUseProgram(defaultProgram);
}

template <unsigned Type>
inline unsigned NewShader(const char * source) {
	GL::GLuint shader = GL::glCreateShader(Type);
	GL::glShaderSource(shader, 1, &source, 0);
	GL::glCompileShader(shader);

	GL::GLint compiled = GL::GL_FALSE;
	GL::glGetShaderiv(shader, GL::GL_COMPILE_STATUS, &compiled);
	if (!compiled) {
		int logSize = 0;
		GL::glGetShaderInfoLog(shader, maxCompilerLog, &logSize, compilerLog);
		compilerLog[logSize] = 0;
		GL::glDeleteShader(shader);
		shader = 0;
	} else {
		compilerLog[0] = 0;
	}

	return shader;
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

void DeleteShader(unsigned shader) {
	GL::glDeleteShader(shader);
}

const char * CompilerLog() {
	return compilerLog;
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

void UniformTransposeMatrix(unsigned location, const float * matrix) {
	GL::glUniformMatrix4fv(location, 1, GL::GL_TRUE, matrix);
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

	GL::glActiveTexture(GL::GL_TEXTURE0 + defaultTextureUnit);

	GL::GLuint texture = 0;
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

void UseTexture(unsigned texture, unsigned location) {
	GL::glActiveTexture(GL::GL_TEXTURE0 + location);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
}

void SetTextureFilter(unsigned texture, unsigned mode) {
	GL::glActiveTexture(GL::GL_TEXTURE0 + defaultTextureUnit);
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

void BuildMipmap(unsigned texture, int base, int max) {
	GL::glActiveTexture(GL::GL_TEXTURE0);
	GL::glBindTexture(GL::GL_TEXTURE_2D, texture);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_BASE_LEVEL, base);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAX_LEVEL, max);
	GL::glGenerateMipmap(GL::GL_TEXTURE_2D);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MIN_FILTER, GL::GL_LINEAR_MIPMAP_LINEAR);
	GL::glTexParameteri(GL::GL_TEXTURE_2D, GL::GL_TEXTURE_MAG_FILTER, GL::GL_LINEAR);
}

unsigned NewVertexArray(const char * format, int * attribs, unsigned vertexBuffer, unsigned indexBuffer) {
	// format regex: '([1-4][if])+'

	GL::GLuint vertexArray = 0;
	GL::glGenVertexArrays(1, &vertexArray);

	int stride = 0;
	for (int i = 0; format[i]; i += 2) {
		stride += (format[i] - '0') * 4;
	}

	GL::glBindVertexArray(vertexArray);
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, vertexBuffer);
	char * ptr = 0;
	for (int i = 0; format[i]; i += 2) {
		int dimension = format[i] - '0';
		int index = attribs[i / 2];
		if (format[i + 1] == 'f') {
			GL::glVertexAttribPointer(index, dimension, GL::GL_FLOAT, false, stride, ptr);
		}
		else
		if (format[i + 1] == 'i') {
			GL::glVertexAttribPointer(index, dimension, GL::GL_INT, false, stride, ptr);
		}
		GL::glEnableVertexAttribArray(index);
		ptr += dimension * 4;
	}
	GL::glBindBuffer(GL::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	GL::glBindVertexArray(defaultVertexArray);
	return vertexArray;
}

void DeleteVertexArray(unsigned array) {
	GL::glDeleteVertexArrays(1, &array);
}

void EnableAttribute(unsigned vao, unsigned target) {
	GL::glBindVertexArray(vao);
	GL::glEnableVertexAttribArray(target);
	GL::glBindVertexArray(defaultVertexArray);
}

void DisableAttribute(unsigned vao, unsigned target) {
	GL::glBindVertexArray(vao);
	GL::glDisableVertexAttribArray(target);
	GL::glBindVertexArray(defaultVertexArray);
}

void EnableAttributes(unsigned vao, unsigned * target, int count) {
	GL::glBindVertexArray(vao);
	for (int i = 0; i < count; ++i) {
		GL::glEnableVertexAttribArray(target[i]);
	}
	GL::glBindVertexArray(defaultVertexArray);
}

void DisableAttributes(unsigned vao, unsigned * target, int count) {
	GL::glBindVertexArray(vao);
	for (int i = 0; i < count; ++i) {
		GL::glDisableVertexAttribArray(target[i]);
	}
	GL::glBindVertexArray(defaultVertexArray);
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

unsigned NewStorageBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_SHADER_STORAGE_BUFFER, buffer);
	GL::glBufferData(GL::GL_SHADER_STORAGE_BUFFER, size, data, GL::GL_STATIC_DRAW);
	return buffer;
}

unsigned NewUniformBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	GL::glBufferData(GL::GL_UNIFORM_BUFFER, size, data, GL::GL_STATIC_DRAW);
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

unsigned NewDynamicStorageBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_SHADER_STORAGE_BUFFER, buffer);
	GL::glBufferData(GL::GL_SHADER_STORAGE_BUFFER, size, data, GL::GL_DYNAMIC_DRAW);
	return buffer;
}

unsigned NewDynamicUniformBuffer(const void * data, int size) {
	GL::GLuint buffer = 0;
	GL::glGenBuffers(1, &buffer);
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	GL::glBufferData(GL::GL_UNIFORM_BUFFER, size, data, GL::GL_DYNAMIC_DRAW);
	return buffer;
}

void DeleteBuffer(unsigned buffer) {
	GL::glDeleteBuffers(1, &buffer);
}

void UpdateVertexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_ARRAY_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_ARRAY_BUFFER, (GL::GLintptr)offset, size, data);
}

void UpdateIndexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_ELEMENT_ARRAY_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_ELEMENT_ARRAY_BUFFER, (GL::GLintptr)offset, size, data);
}

void UpdateStorageBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_SHADER_STORAGE_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_SHADER_STORAGE_BUFFER, (GL::GLintptr)offset, size, data);
}

void UpdateUniformBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	GL::glBindBuffer(GL::GL_UNIFORM_BUFFER, buffer);
	GL::glBufferSubData(GL::GL_UNIFORM_BUFFER, (GL::GLintptr)offset, size, data);
}

void UseStorageBuffer(unsigned buffer, unsigned binding) {
	GL::glBindBufferBase(GL::GL_SHADER_STORAGE_BUFFER, binding, buffer);
}

void * ReadStorageBuffer(unsigned buffer, unsigned offset, int size) {
	GL::glBindBuffer(GL::GL_SHADER_STORAGE_BUFFER, buffer);
	void * map = GL::glMapBufferRange(GL::GL_SHADER_STORAGE_BUFFER, offset, size, GL::GL_READ_ONLY);
	void * content = malloc(size);
	memcpy(content, map, size);
	GL::glUnmapBuffer(GL::GL_SHADER_STORAGE_BUFFER);
	return content;
}

void RenderTriangles(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_TRIANGLES, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderTriangleStrip(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_TRIANGLE_STRIP, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderTriangleFan(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_TRIANGLE_FAN, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderLines(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_LINES, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderLineStrip(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_LINE_STRIP, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderLineLoop(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_LINE_LOOP, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderPoints(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_POINTS, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderLineStripAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_LINE_STRIP_ADJACENCY, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderLinesAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_LINES_ADJACENCY, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderTriangleStripAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_TRIANGLE_STRIP_ADJACENCY, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderTrianglesAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	GL::glDrawArraysInstanced(GL::GL_TRIANGLES_ADJACENCY, first, count, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedTriangles(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_TRIANGLES, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedTriangleStrip(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_TRIANGLE_STRIP, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedTriangleFan(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_TRIANGLE_FAN, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedLines(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_LINES, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedLineStrip(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_LINE_STRIP, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedLineLoop(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_LINE_LOOP, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedPoints(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_POINTS, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedLineStripAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_LINE_STRIP_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedLinesAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_LINES_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedTriangleStripAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_TRIANGLE_STRIP_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
}

void RenderIndexedTrianglesAdjacency(unsigned vao, int count, int first, int instances) {
	GL::glBindVertexArray(vao);
	const void * ptr = (const void *)((GL::GLintptr)first * 4);
	GL::glDrawElementsInstanced(GL::GL_TRIANGLES_ADJACENCY, count, GL::GL_UNSIGNED_INT, ptr, instances);
	GL::glBindVertexArray(defaultVertexArray);
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

	GL::glBindFramebuffer(GL::GL_FRAMEBUFFER, defaultFramebuffer);
}

void DeleteFramebuffer(unsigned framebuffer) {
	unsigned color = 0;
	GL::glGetFramebufferAttachmentParameteriv(GL::GL_FRAMEBUFFER, GL::GL_COLOR_ATTACHMENT0, GL::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GL::GLint *)&color);

	if (color) {
		GL::glDeleteTextures(1, &color);
	}

	unsigned depth = 0;
	GL::glGetFramebufferAttachmentParameteriv(GL::GL_FRAMEBUFFER, GL::GL_DEPTH_ATTACHMENT, GL::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (GL::GLint *)&depth);

	if (depth) {
		GL::glDeleteTextures(1, &depth);
	}

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

unsigned ReadPixel(int x, int y) {
	unsigned rgba = 0;
	GL::glReadPixels(x, y, 1, 1, GL::GL_RGBA, GL::GL_UNSIGNED_BYTE, &rgba);
	return rgba;
}

float ReadDepthPixel(int x, int y) {
	float depth = 0.0;
	GL::glReadPixels(x, y, 1, 1, GL::GL_DEPTH_COMPONENT, GL::GL_FLOAT, &depth);
	return depth;
}

// void DebugFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
// 	const float c = 1.0 / 255.0;
// 	UseProgram(Font::prog);
// 	Uniform4f(Font::color, r * c, g * c, b * c, a * c);
// }

// void DebugFontAlign(float px, float py) {
// 	Font::align_x = px;
// 	Font::align_y = py;
// }

// void DebugFontPrint(float x, float y, const char * fmt, ...) {
// 	va_list ap;
// 	char str[2048];
// 	va_start(ap, fmt);
// 	vsprintf(str, fmt, ap);
// 	va_end(ap);

// 	EnableOnly(ENABLE_BLEND);
// 	UseProgram(Font::prog);
// 	UseTexture(Font::tex);
// 	UseVertexArray(Font::vao);

// 	int viewport[4] = {};
// 	GL::glGetIntegerv(GL::GL_VIEWPORT, viewport);
// 	Uniform2f(Font::viewport, viewport[2], viewport[3]);

// 	x -= strlen(str) * Font::DroidSansMono.char_width * Font::align_x;
// 	y -= Font::DroidSansMono.char_height * Font::align_y;
// 	y += Font::DroidSansMono.char_height;
// 	x = (int)x;
// 	y = (int)y;

// 	float step = (float)Font::DroidSansMono.char_width;
// 	const unsigned char * bytes = (const unsigned char *)str;
// 	for (int i = 0; i < bytes[i]; ++i) {
// 		Uniform2f(Font::position, x, y);
// 		Uniform1i(Font::glyph, bytes[i]);
// 		RenderTriangleStrip(4);
// 		x += step;
// 	}
// }
