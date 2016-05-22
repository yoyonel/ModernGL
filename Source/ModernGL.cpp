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

#include <OpenGL.h>

namespace ModernGL {
	bool InitializeModernGL(bool font) {
		if (!OpenGL::InitializeOpenGL()) {
			return false;
		}

		OpenGL::glBlendFunc(OpenGL::GL_SRC_ALPHA, OpenGL::GL_ONE_MINUS_SRC_ALPHA);
		// OpenGL::glEnable(OpenGL::GL_PRIMITIVE_RESTART_FIXED_INDEX);
		OpenGL::glEnable(OpenGL::GL_PRIMITIVE_RESTART_INDEX);
		OpenGL::glPrimitiveRestartIndex(-1);

		OpenGL::glGenVertexArrays(1, &defaultVertexArray);
		OpenGL::glBindVertexArray(defaultVertexArray);

		OpenGL::glGetIntegerv(OpenGL::GL_DRAW_FRAMEBUFFER_BINDING, (OpenGL::GLint *)&defaultFramebuffer);
		OpenGL::glGetIntegerv(OpenGL::GL_CURRENT_PROGRAM, (OpenGL::GLint *)&defaultProgram);

		unsigned maxTextureUnits = 1;
		OpenGL::glGetIntegerv(OpenGL::GL_MAX_TEXTURE_IMAGE_UNITS, (OpenGL::GLint *)&maxTextureUnits);
		defaultTextureUnit = maxTextureUnits - 1;
		return true;
	}

	Info GetInfo() {
		OpenGL::GLint major = 0;
		OpenGL::GLint minor = 0;
		OpenGL::GLint samples = 0;

		OpenGL::glGetIntegerv(OpenGL::GL_MAJOR_VERSION, &major);
		OpenGL::glGetIntegerv(OpenGL::GL_MINOR_VERSION, &minor);
		OpenGL::glGetIntegerv(OpenGL::GL_MAX_SAMPLES, &samples);
		const char * vendor = (const char *)OpenGL::glGetString(OpenGL::GL_VENDOR);
		const char * renderer = (const char *)OpenGL::glGetString(OpenGL::GL_RENDERER);

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
		switch (OpenGL::glGetError()) {
			case OpenGL::GL_NO_ERROR: return "GL_NO_ERROR";
			case OpenGL::GL_INVALID_ENUM: return "GL_INVALID_ENUM";
			case OpenGL::GL_INVALID_VALUE: return "GL_INVALID_VALUE";
			case OpenGL::GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
			case OpenGL::GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";
			case OpenGL::GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
			case OpenGL::GL_STACK_UNDERFLOW: return "GL_STACK_UNDERFLOW";
			case OpenGL::GL_STACK_OVERFLOW: return "GL_STACK_OVERFLOW";
			default: return "Unknown Error";
		}
	}

	void Viewport(int x, int y, int w, int h) {
		OpenGL::glViewport(x, y, w, h);
	}

	void Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		const float c = 1.0 / 255.0;
		OpenGL::glClearColor(r * c, g * c, b * c, a * c);
		unsigned GL_ALL_BUFFER_BIT = 0;
		GL_ALL_BUFFER_BIT |= OpenGL::GL_DEPTH_BUFFER_BIT;
		GL_ALL_BUFFER_BIT |= OpenGL::GL_COLOR_BUFFER_BIT;
		OpenGL::glClear(GL_ALL_BUFFER_BIT);
	}

	void PointSize(float size) {
		OpenGL::glPointSize(size);
	}

	void LineWidth(float size) {
		OpenGL::glLineWidth(size);
	}

	void EnableOnly(unsigned mask) {
		(mask & ENABLE_BLEND ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_BLEND);
		(mask & ENABLE_CULL_FACE ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_CULL_FACE);
		(mask & ENABLE_DEPTH_TEST ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_DEPTH_TEST);
		(mask & ENABLE_MULTISAMPLE ? OpenGL::glEnable : OpenGL::glDisable)(OpenGL::GL_MULTISAMPLE);
	}

	void EnableBlend() {
		OpenGL::glEnable(OpenGL::GL_BLEND);
	}

	void DisableBlend() {
		OpenGL::glDisable(OpenGL::GL_BLEND);
	}

	void EnableCullFace() {
		OpenGL::glEnable(OpenGL::GL_CULL_FACE);
	}

	void DisableCullFace() {
		OpenGL::glDisable(OpenGL::GL_CULL_FACE);
	}

	void EnableDepthTest() {
		OpenGL::glEnable(OpenGL::GL_DEPTH_TEST);
	}

	void DisableDepthTest() {
		OpenGL::glDisable(OpenGL::GL_DEPTH_TEST);
	}

	void EnableMultisample() {
		OpenGL::glEnable(OpenGL::GL_MULTISAMPLE);
	}

	void DisableMultisample() {
		OpenGL::glDisable(OpenGL::GL_MULTISAMPLE);
	}

	unsigned NewProgram(unsigned * shader, int count) {
		OpenGL::GLuint program = OpenGL::glCreateProgram();

		for (int i = 0; i < count; ++i) {
			OpenGL::glAttachShader(program, shader[i]);
		}

		OpenGL::glLinkProgram(program);

		OpenGL::GLint linked = OpenGL::GL_FALSE;
		OpenGL::glGetProgramiv(program, OpenGL::GL_LINK_STATUS, &linked);
		if (!linked) {
			int logSize = 0;
			OpenGL::glGetProgramInfoLog(program, maxCompilerLog, &logSize, compilerLog);
			compilerLog[logSize] = 0;
			OpenGL::glDeleteProgram(program);
			program = 0;
		} else {
			compilerLog[0] = 0;
			OpenGL::glUseProgram(program);
		} 

		return program;
	}

	void DeleteProgram(unsigned program) {
		unsigned shaders[8] = {};
		int numShaders = 0;

		OpenGL::glGetAttachedShaders(program, 8, &numShaders, shaders);
		for (int i = 0; i < numShaders; ++i) {
			OpenGL::glDeleteShader(shaders[i]);
		}
		OpenGL::glDeleteProgram(program);
	}

	void UseProgram(unsigned program) {
		OpenGL::glUseProgram(program);
	}

	void UseDefaultProgram() {
		OpenGL::glUseProgram(defaultProgram);
	}

	template <unsigned Type>
	inline unsigned NewShader(const char * source) {
		OpenGL::GLuint shader = OpenGL::glCreateShader(Type);
		OpenGL::glShaderSource(shader, 1, &source, 0);
		OpenGL::glCompileShader(shader);

		OpenGL::GLint compiled = OpenGL::GL_FALSE;
		OpenGL::glGetShaderiv(shader, OpenGL::GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			int logSize = 0;
			OpenGL::glGetShaderInfoLog(shader, maxCompilerLog, &logSize, compilerLog);
			compilerLog[logSize] = 0;
			OpenGL::glDeleteShader(shader);
			shader = 0;
		} else {
			compilerLog[0] = 0;
		}

		return shader;
	}

	unsigned NewFragmentShader(const char * source) {
		return NewShader<OpenGL::GL_FRAGMENT_SHADER>(source);
	}

	unsigned NewGeometryShader(const char * source) {
		return NewShader<OpenGL::GL_GEOMETRY_SHADER>(source);
	}

	unsigned NewVertexShader(const char * source) {
		return NewShader<OpenGL::GL_VERTEX_SHADER>(source);
	}

	// unsigned NewComputeShader(const char * source) {
	// 	return NewShader<OpenGL::GL_COMPUTE_SHADER>(source);
	// }

	// unsigned NewTessControlShader(const char * source) {
	// 	return NewShader<OpenGL::GL_TESS_CONTROL_SHADER>(source);
	// }

	// unsigned NewTessEvaluationShader(const char * source) {
	// 	return NewShader<OpenGL::GL_TESS_EVALUATION_SHADER>(source);
	// }

	void DeleteShader(unsigned shader) {
		OpenGL::glDeleteShader(shader);
	}

	const char * CompilerLog() {
		return compilerLog;
	}

	unsigned AttribLocation(unsigned program, const char * name) {
		return OpenGL::glGetAttribLocation(program, name);
	}

	unsigned UniformLocation(unsigned program, const char * name) {
		return OpenGL::glGetUniformLocation(program, name);
	}

	unsigned UniformBlockLocation(unsigned program, const char * name) {
		return OpenGL::glGetUniformBlockIndex(program, name);
	}

	void Uniform1f(unsigned location, float v0) {
		OpenGL::glUniform1f(location, v0);
	}

	void Uniform2f(unsigned location, float v0, float v1) {
		OpenGL::glUniform2f(location, v0, v1);
	}

	void Uniform3f(unsigned location, float v0, float v1, float v2) {
		OpenGL::glUniform3f(location, v0, v1, v2);
	}

	void Uniform4f(unsigned location, float v0, float v1, float v2, float v3) {
		OpenGL::glUniform4f(location, v0, v1, v2, v3);
	}

	void Uniform1i(unsigned location, int v0) {
		OpenGL::glUniform1i(location, v0);
	}

	void Uniform2i(unsigned location, int v0, int v1) {
		OpenGL::glUniform2i(location, v0, v1);
	}

	void Uniform3i(unsigned location, int v0, int v1, int v2) {
		OpenGL::glUniform3i(location, v0, v1, v2);
	}

	void Uniform4i(unsigned location, int v0, int v1, int v2, int v3) {
		OpenGL::glUniform4i(location, v0, v1, v2, v3);
	}

	void UniformMatrix(unsigned location, const float * matrix) {
		OpenGL::glUniformMatrix4fv(location, 1, OpenGL::GL_FALSE, matrix);
	}

	void UniformTransposeMatrix(unsigned location, const float * matrix) {
		OpenGL::glUniformMatrix4fv(location, 1, OpenGL::GL_TRUE, matrix);
	}

	void UniformBlock(unsigned location, unsigned buffer) {
		OpenGL::glBindBufferBase(OpenGL::GL_UNIFORM_BUFFER, location, buffer);
	}

	unsigned NewTexture(int width, int height, const void * data, int components) {
		const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
		int format = formats[components];

		if (!width && !height) {
			int viewportValue[4];
			OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewportValue);
			width = viewportValue[2];
			height = viewportValue[3];
		}

		OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);

		OpenGL::GLuint texture = 0;
		OpenGL::glGenTextures(1, &texture);
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexImage2D(OpenGL::GL_TEXTURE_2D, 0, format, width, height, 0, format, OpenGL::GL_UNSIGNED_BYTE, data);
		return texture;
	}

	void DeleteTexture(unsigned texture) {
		OpenGL::glDeleteTextures(1, &texture);
	}

	void UseTexture(unsigned texture, unsigned location) {
		OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + location);
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture);
	}

	void SetTextureFilter(unsigned texture, unsigned mode) {
		OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0 + defaultTextureUnit);
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture);
		switch (mode) {
			case TEXTURE_PIXELATED: {
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_NEAREST);
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_NEAREST);
				break;
			}
			case TEXTURE_FILTERED: {
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
				break;
			}
			case TEXTURE_MIPMAPPED: {
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR_MIPMAP_LINEAR);
				OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
				break;
			}
		}
	}

	void BuildMipmap(unsigned texture, int base, int max) {
		OpenGL::glActiveTexture(OpenGL::GL_TEXTURE0);
		OpenGL::glBindTexture(OpenGL::GL_TEXTURE_2D, texture);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_BASE_LEVEL, base);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAX_LEVEL, max);
		OpenGL::glGenerateMipmap(OpenGL::GL_TEXTURE_2D);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR_MIPMAP_LINEAR);
		OpenGL::glTexParameteri(OpenGL::GL_TEXTURE_2D, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
	}

	unsigned NewVertexArray(const char * format, int * attribs, unsigned vertexBuffer, unsigned indexBuffer) {
		// format regex: '([1-4][if])+'

		OpenGL::GLuint vertexArray = 0;
		OpenGL::glGenVertexArrays(1, &vertexArray);

		int stride = 0;
		for (int i = 0; format[i]; i += 2) {
			stride += (format[i] - '0') * 4;
		}

		OpenGL::glBindVertexArray(vertexArray);
		OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, vertexBuffer);
		char * ptr = 0;
		for (int i = 0; format[i]; i += 2) {
			int dimension = format[i] - '0';
			int index = attribs[i / 2];
			if (format[i + 1] == 'f') {
				OpenGL::glVertexAttribPointer(index, dimension, OpenGL::GL_FLOAT, false, stride, ptr);
			}
			else
			if (format[i + 1] == 'i') {
				OpenGL::glVertexAttribPointer(index, dimension, OpenGL::GL_INT, false, stride, ptr);
			}
			OpenGL::glEnableVertexAttribArray(index);
			ptr += dimension * 4;
		}
		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		OpenGL::glBindVertexArray(defaultVertexArray);
		return vertexArray;
	}

	void DeleteVertexArray(unsigned array) {
		OpenGL::glDeleteVertexArrays(1, &array);
	}

	void EnableAttribute(unsigned vao, unsigned target) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glEnableVertexAttribArray(target);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void DisableAttribute(unsigned vao, unsigned target) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDisableVertexAttribArray(target);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void EnableAttributes(unsigned vao, unsigned * target, int count) {
		OpenGL::glBindVertexArray(vao);
		for (int i = 0; i < count; ++i) {
			OpenGL::glEnableVertexAttribArray(target[i]);
		}
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void DisableAttributes(unsigned vao, unsigned * target, int count) {
		OpenGL::glBindVertexArray(vao);
		for (int i = 0; i < count; ++i) {
			OpenGL::glDisableVertexAttribArray(target[i]);
		}
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	unsigned NewVertexBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_ARRAY_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
		return buffer;
	}

	unsigned NewIndexBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
		return buffer;
	}

	// unsigned NewStorageBuffer(const void * data, int size) {
	// 	OpenGL::GLuint buffer = 0;
	// 	OpenGL::glGenBuffers(1, &buffer);
	// 	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, buffer);
	// 	OpenGL::glBufferData(OpenGL::GL_SHADER_STORAGE_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
	// 	return buffer;
	// }

	unsigned NewUniformBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_UNIFORM_BUFFER, size, data, OpenGL::GL_STATIC_DRAW);
		return buffer;
	}

	unsigned NewDynamicVertexBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_ARRAY_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
		return buffer;
	}

	unsigned NewDynamicIndexBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
		return buffer;
	}

	// unsigned NewDynamicStorageBuffer(const void * data, int size) {
	// 	OpenGL::GLuint buffer = 0;
	// 	OpenGL::glGenBuffers(1, &buffer);
	// 	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, buffer);
	// 	OpenGL::glBufferData(OpenGL::GL_SHADER_STORAGE_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
	// 	return buffer;
	// }

	unsigned NewDynamicUniformBuffer(const void * data, int size) {
		OpenGL::GLuint buffer = 0;
		OpenGL::glGenBuffers(1, &buffer);
		OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, buffer);
		OpenGL::glBufferData(OpenGL::GL_UNIFORM_BUFFER, size, data, OpenGL::GL_DYNAMIC_DRAW);
		return buffer;
	}

	void DeleteBuffer(unsigned buffer) {
		OpenGL::glDeleteBuffers(1, &buffer);
	}

	void UpdateVertexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
		OpenGL::glBindBuffer(OpenGL::GL_ARRAY_BUFFER, buffer);
		OpenGL::glBufferSubData(OpenGL::GL_ARRAY_BUFFER, (OpenGL::GLintptr)offset, size, data);
	}

	void UpdateIndexBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
		OpenGL::glBindBuffer(OpenGL::GL_ELEMENT_ARRAY_BUFFER, buffer);
		OpenGL::glBufferSubData(OpenGL::GL_ELEMENT_ARRAY_BUFFER, (OpenGL::GLintptr)offset, size, data);
	}

	// void UpdateStorageBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
	// 	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, buffer);
	// 	OpenGL::glBufferSubData(OpenGL::GL_SHADER_STORAGE_BUFFER, (OpenGL::GLintptr)offset, size, data);
	// }

	void UpdateUniformBuffer(unsigned buffer, unsigned offset, const void * data, int size) {
		OpenGL::glBindBuffer(OpenGL::GL_UNIFORM_BUFFER, buffer);
		OpenGL::glBufferSubData(OpenGL::GL_UNIFORM_BUFFER, (OpenGL::GLintptr)offset, size, data);
	}

	// void UseStorageBuffer(unsigned buffer, unsigned binding) {
	// 	OpenGL::glBindBufferBase(OpenGL::GL_SHADER_STORAGE_BUFFER, binding, buffer);
	// }

	// void * ReadStorageBuffer(unsigned buffer, unsigned offset, int size) {
	// 	OpenGL::glBindBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER, buffer);
	// 	void * map = OpenGL::glMapBufferRange(OpenGL::GL_SHADER_STORAGE_BUFFER, offset, size, OpenGL::GL_READ_ONLY);
	// 	void * content = malloc(size);
	// 	memcpy(content, map, size);
	// 	OpenGL::glUnmapBuffer(OpenGL::GL_SHADER_STORAGE_BUFFER);
	// 	return content;
	// }

	void RenderTriangles(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderTriangleStrip(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderTriangleFan(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_FAN, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderLines(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderLineStrip(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderLineLoop(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_LOOP, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderPoints(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_POINTS, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderLineStripAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderLinesAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_LINES_ADJACENCY, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderTriangleStripAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderTrianglesAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		OpenGL::glDrawArraysInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, first, count, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedTriangles(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedTriangleStrip(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedTriangleFan(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_FAN, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedLines(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedLineStrip(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedLineLoop(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_LOOP, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedPoints(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_POINTS, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedLineStripAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedLinesAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_LINES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedTriangleStripAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLE_STRIP_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	void RenderIndexedTrianglesAdjacency(unsigned vao, int count, int first, int instances) {
		OpenGL::glBindVertexArray(vao);
		const void * ptr = (const void *)((OpenGL::GLintptr)first * 4);
		OpenGL::glDrawElementsInstanced(OpenGL::GL_TRIANGLES_ADJACENCY, count, OpenGL::GL_UNSIGNED_INT, ptr, instances);
		OpenGL::glBindVertexArray(defaultVertexArray);
	}

	Framebuffer NewFramebuffer(int width, int height, bool multisample) {
		OpenGL::GLuint framebuffer = 0;
		OpenGL::GLuint color = 0;
		OpenGL::GLuint depth = 0;

		OpenGL::glGenFramebuffers(1, &framebuffer);
		OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, framebuffer);

		OpenGL::GLuint target = OpenGL::GL_TEXTURE_2D;
		if (multisample) {
			target = OpenGL::GL_TEXTURE_2D_MULTISAMPLE;
		}

		if (!width && !height) {
			int viewport[4] = {};
			OpenGL::glGetIntegerv(OpenGL::GL_VIEWPORT, viewport);
			width = viewport[2];
			height = viewport[3];
		}

		OpenGL::glGenTextures(1, &color);
		OpenGL::glBindTexture(target, color);
		OpenGL::glTexParameteri(target, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexParameteri(target, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexImage2D(target, 0, OpenGL::GL_RGB, width, height, 0, OpenGL::GL_RGB, OpenGL::GL_FLOAT, 0);
		OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_COLOR_ATTACHMENT0, target, color, 0);

		OpenGL::glGenTextures(1, &depth);
		OpenGL::glBindTexture(target, depth);
		OpenGL::glTexParameteri(target, OpenGL::GL_TEXTURE_MIN_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexParameteri(target, OpenGL::GL_TEXTURE_MAG_FILTER, OpenGL::GL_LINEAR);
		OpenGL::glTexImage2D(target, 0, OpenGL::GL_DEPTH_COMPONENT, width, height, 0, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, 0);
		OpenGL::glFramebufferTexture2D(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_DEPTH_ATTACHMENT, target, depth, 0);

		return Framebuffer {
			framebuffer,
			color,
			depth,
		};

		OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, defaultFramebuffer);
	}

	void DeleteFramebuffer(unsigned framebuffer) {
		unsigned color = 0;
		OpenGL::glGetFramebufferAttachmentParameteriv(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_COLOR_ATTACHMENT0, OpenGL::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (OpenGL::GLint *)&color);

		if (color) {
			OpenGL::glDeleteTextures(1, &color);
		}

		unsigned depth = 0;
		OpenGL::glGetFramebufferAttachmentParameteriv(OpenGL::GL_FRAMEBUFFER, OpenGL::GL_DEPTH_ATTACHMENT, OpenGL::GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, (OpenGL::GLint *)&depth);

		if (depth) {
			OpenGL::glDeleteTextures(1, &depth);
		}

		OpenGL::glDeleteFramebuffers(1, &framebuffer);
	}

	void UseFramebuffer(unsigned framebuffer) {
		OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, framebuffer);
	}

	void UseDefaultFramebuffer() {
		OpenGL::glBindFramebuffer(OpenGL::GL_FRAMEBUFFER, 0);
	}

	unsigned char * ReadPixels(int x, int y, int width, int height, int components) {
		const int formats[] = {0, OpenGL::GL_RED, OpenGL::GL_RG, OpenGL::GL_RGB, OpenGL::GL_RGBA};
		int format = formats[components];

		unsigned char * data = (unsigned char *)malloc(width * height * components);
		OpenGL::glReadPixels(x, y, width, height, format, OpenGL::GL_UNSIGNED_BYTE, data);
		return data;
	}

	float * ReadDepthPixels(int x, int y, int width, int height) {
		float * data = (float *)malloc(width * height * sizeof(float));
		OpenGL::glReadPixels(x, y, width, height, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, data);
		return data;
	}

	unsigned ReadPixel(int x, int y) {
		unsigned rgba = 0;
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_RGBA, OpenGL::GL_UNSIGNED_BYTE, &rgba);
		return rgba;
	}

	float ReadDepthPixel(int x, int y) {
		float depth = 0.0;
		OpenGL::glReadPixels(x, y, 1, 1, OpenGL::GL_DEPTH_COMPONENT, OpenGL::GL_FLOAT, &depth);
		return depth;
	}

}
