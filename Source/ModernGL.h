#pragma once

enum EnableEnum {
	ENABLE_NOTHING = 0x00,
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
	void Clear(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void PointSize(float size);
	void LineWidth(float size);

	void EnableOnly(unsigned mask);
	void EnableBlend();
	void DisableBlend();
	void EnableCullFace();
	void DisableCullFace();
	void EnableDepthTest();
	void DisableDepthTest();
	void EnableMultisample();
	void DisableMultisample();

	unsigned NewProgram(unsigned * shader, int count);
	void DeleteProgram(unsigned program);
	void UseProgram(unsigned program);
	void UseDefaultProgram();

	unsigned NewFragmentShader(const char * source);
	unsigned NewGeometryShader(const char * source);
	unsigned NewVertexShader(const char * source);
	unsigned NewComputeShader(const char * source);
	unsigned NewTessControlShader(const char * source);
	unsigned NewTessEvaluationShader(const char * source);
	void DeleteShader(unsigned shader);

	const char * CompilerLog();

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
	void UniformTransposeMatrix(unsigned location, const float * matrix);
	void UniformBlock(unsigned location, unsigned buffer);

	unsigned NewTexture(int width, int height, const void * data, int components = 3);
	void DeleteTexture(unsigned texture);
	void UseTexture(unsigned texture, unsigned location = 0);

	void SetTextureFilter(unsigned texture, unsigned mode);
	void BuildMipmap(unsigned texture, int base, int max);

	unsigned NewVertexArray(const char * format, int * attribs, unsigned vertexBuffer, unsigned indexBuffer = 0);
	void DeleteVertexArray(unsigned array);

	void EnableAttribute(unsigned vao, unsigned target);
	void DisableAttribute(unsigned vao, unsigned target);
	void EnableAttributes(unsigned vao, unsigned * target, int count);
	void DisableAttributes(unsigned vao, unsigned * target, int count);

	unsigned NewVertexBuffer(const void * data, int size);
	unsigned NewIndexBuffer(const void * data, int size);
	unsigned NewStorageBuffer(const void * data, int size);
	unsigned NewUniformBuffer(const void * data, int size);
	unsigned NewDynamicVertexBuffer(const void * data, int size);
	unsigned NewDynamicIndexBuffer(const void * data, int size);
	unsigned NewDynamicStorageBuffer(const void * data, int size);
	unsigned NewDynamicUniformBuffer(const void * data, int size);
	void DeleteBuffer(unsigned buffer);

	void UpdateVertexBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateIndexBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateStorageBuffer(unsigned buffer, unsigned offset, const void * data, int size);
	void UpdateUniformBuffer(unsigned buffer, unsigned offset, const void * data, int size);

	void UseStorageBuffer(unsigned buffer, unsigned binding);
	void * ReadStorageBuffer(unsigned buffer, unsigned offset, int size);

	void RenderTriangles(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderTriangleStrip(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderTriangleFan(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderLines(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderLineStrip(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderLineLoop(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderPoints(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderLineStripAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderLinesAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderTriangleStripAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderTrianglesAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedTriangles(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedTriangleStrip(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedTriangleFan(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedLines(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedLineStrip(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedLineLoop(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedPoints(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedLineStripAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedLinesAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedTriangleStripAdjacency(unsigned vao, int count, int first = 0, int instances = 1);
	void RenderIndexedTrianglesAdjacency(unsigned vao, int count, int first = 0, int instances = 1);

	Framebuffer NewFramebuffer(int width, int height, bool multisample = true);
	void DeleteFramebuffer(unsigned framebuffer);
	void UseFramebuffer(unsigned framebuffer);
	void UseDefaultFramebuffer();

	unsigned char * ReadPixels(int x, int y, int width, int height, int components = 3);
	float * ReadDepthPixels(int x, int y, int width, int height);

	unsigned ReadPixel(int x, int y);
	float ReadDepthPixel(int x, int y);

	// void DebugFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255);
	// void DebugFontAlign(float px, float py);
	// void DebugFontPrint(float x, float y, const char * fmt, ...);
}