#pragma once

enum EnableEnum {
	ENABLE_BLEND = 0x01,
	ENABLE_CULL_FACE = 0x02,
	ENABLE_DEPTH_TEST = 0x04,
	ENABLE_MULTISAMPLE = 0x08,
};

enum TextureFilterEnum {
	TEXTURE_PIXELATED = 0x01,
	TEXTURE_FILTERED = 0x02,
	TEXTURE_MIPMAPPED = 0x03,
};

struct Info {
	int major;
	int minor;
	int samples;
	const char * vendor;
	const char * renderer;
};

struct Framebuffer {
	unsigned framebuffer;
	unsigned color;
	unsigned depth;
};

extern "C" {
	bool InitializeModernGL();
	Info GetInfo();

	const char * GetError();

	void Viewport(int x, int y, int w, int h);
	void Clear(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255);

	void PointSize(float size);
	void LineWidth(float size);

	void EnableBlend();
	void DisableBlend();
	void EnableCullFace();
	void DisableCullFace();
	void EnableDepthTest();
	void DisableDepthTest();
	void EnableMultisample();
	void DisableMultisample();

	void EnableOnly(unsigned mask);

	unsigned NewFragmentShader(const char * source);
	unsigned NewGeometryShader(const char * source);
	unsigned NewVertexShader(const char * source);
	unsigned NewComputeShader(const char * source);
	unsigned NewTessControlShader(const char * source);
	unsigned NewTessEvaluationShader(const char * source);
	unsigned DeleteShader(unsigned shader);
	
	unsigned NewProgram(unsigned * shader, int count);
	unsigned DeleteProgram(unsigned program);
	void UseProgram(unsigned program);

	const char * CompilerLog();

	void DispatchCompute(unsigned x = 1, unsigned y = 1, unsigned z = 1);

	unsigned AttribLocation(unsigned program, const char * name);
	unsigned UniformLocation(unsigned program, const char * name);
	unsigned UniformBlockLocation(unsigned program, const char * name);

	void Uniform1f(unsigned location, float v0);
	void Uniform2f(unsigned location, float v0, float v1);
	void Uniform3f(unsigned location, float v0, float v1, float v2);
	void Uniform4f(unsigned location, float v0, float v1, float v2, float v3);
	void Uniform1i(unsigned location, int v0);
	void Uniform2i(unsigned location, int v0, int v1);
	void Uniform3i(unsigned location, int v0, int v1, int v2);
	void Uniform4i(unsigned location, int v0, int v1, int v2, int v3);
	void UniformMatrix(unsigned location, const float * matrix);
	void UniformBlock(unsigned location, unsigned buffer);

	unsigned NewTexture(int width, int height, const void * data, int components = 3);
	void SetTextureFilter(unsigned texture, unsigned mode);
	void DeleteTexture(unsigned texture);
	void UseTexture(unsigned texture, unsigned location = 0);
	void BuildMipmap(unsigned texture, int base = 0, int max = 1000);

	unsigned NewVertexArray();
	void DeleteVertexArray(unsigned array);
	void UseVertexArray(unsigned array);

	unsigned NewVertexBuffer(const void * data, int size);
	unsigned NewIndexBuffer(const void * data, int size);
	unsigned NewStorageBuffer(const void * data, int size);
	unsigned NewDynamicVertexBuffer(const void * data, int size);
	unsigned NewDynamicIndexBuffer(const void * data, int size);
	unsigned NewDynamicStorageBuffer(const void * data, int size);
	unsigned NewUniformBuffer(const void * data, int size);

	void UpdateVertexBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateIndexBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateStorageBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateUniformBuffer(unsigned buffer, unsigned offset, const void * data, int size);

	void UseStorageBuffer(unsigned buffer, unsigned binding);
	void * ReadStorageBuffer(unsigned buffer, unsigned offset, int size);

	void DeleteBuffer(unsigned buffer);

	void RenderTriangles(int count, int first = 0);
	void RenderTriangleStrip(int count, int first = 0);
	void RenderTriangleFan(int count, int first = 0);
	void RenderLines(int count, int first = 0);
	void RenderLineStrip(int count, int first = 0);
	void RenderLineLoop(int count, int first = 0);
	void RenderPoints(int count, int first = 0);
	void RenderLineStripAdjacency(int count, int first = 0);
	void RenderLinesAdjacency(int count, int first = 0);
	void RenderTriangleStripAdjacency(int count, int first = 0);
	void RenderTrianglesAdjacency(int count, int first = 0);
	void RenderIndexedTriangles(int count, int first = 0);
	void RenderIndexedTriangleStrip(int count, int first = 0);
	void RenderIndexedTriangleFan(int count, int first = 0);
	void RenderIndexedLines(int count, int first = 0);
	void RenderIndexedLineStrip(int count, int first = 0);
	void RenderIndexedLineLoop(int count, int first = 0);
	void RenderIndexedPoints(int count, int first = 0);
	void RenderIndexedLineStripAdjacency(int count, int first = 0);
	void RenderIndexedLinesAdjacency(int count, int first = 0);
	void RenderIndexedTriangleStripAdjacency(int count, int first = 0);
	void RenderIndexedTrianglesAdjacency(int count, int first = 0);

	void EnableAttribute(unsigned target);
	void DisableAttribute(unsigned target);
	void EnableAttributes(unsigned * target, int count);
	void DisableAttributes(unsigned * target, int count);
	
	void Attribute1f(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute2f(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute3f(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute4f(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute1i(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute2i(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute3i(unsigned buffer, unsigned target, const void * ptr = 0);
	void Attribute4i(unsigned buffer, unsigned target, const void * ptr = 0);

	Framebuffer NewFramebuffer(int width = 0, int height = 0, bool mutisample = true);
	void DeleteFramebuffer(unsigned framebuffer);
	void UseFramebuffer(unsigned framebuffer);
	void UseDefaultFramebuffer();

	unsigned char * ReadPixels(int x, int y, int width, int height, int components = 3);
	float * ReadDepthPixels(int x, int y, int width, int height);

	void DebugFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	void DebugFontAlign(float px, float py);
	void DebugFontPrint(float x, float y, const char * fmt, ...);
}