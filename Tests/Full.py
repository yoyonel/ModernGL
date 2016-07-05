import ModernGL as GL
import GLContext
import os, struct

from PIL import Image

if not os.path.isdir('TestResults'):
	os.mkdir('TestResults')

GLContext.Context(True)
GL.InitializeModernGL()
ext = GL.ExtensionActive()

major, minor, samples, vendor, renderer = GL.GetInfo()

GL.GetDefaultFramebuffer()

fbo = []
color = []
depth = []
for i in range(10):
	f, c, d = GL.NewFramebuffer(100, 100)
	fbo.append(f)
	color.append(c)
	depth.append(d)

GL.UseDefaultFramebuffer()

GL.PointSize(5)
GL.LineSize(2)

GL.EnableOnly

GL.EnableBlend
GL.DisableBlend
GL.EnableCullFace
GL.DisableCullFace
GL.EnableDepthTest
GL.DisableDepthTest
GL.EnableMultisample
GL.DisableMultisample

vert_sdr = GL.NewVertexShader('''
	#version 430

	in vec2 vert;

	void main() {
		gl_Position = vec4(vert, 0.0, 1.0);
	}
''')

frag_sdr = GL.NewFragmentShader('''
	#version 430

	out vec4 color;

	void main() {
		color = vec4(0.0, 0.0, 1.0, 1.0);
	}
''')

geom_sdr = GL.NewGeometryShader('''
	#version 430

	layout(points) in;
	layout(line_strip, max_vertices = 2) out;

	void main() {
		gl_Position = gl_in[0].gl_Position + vec4(-0.1, 0.0, 0.0, 0.0);
		EmitVertex();

		gl_Position = gl_in[0].gl_Position + vec4(0.1, 0.0, 0.0, 0.0);
		EmitVertex();

		EndPrimitive();
	}
''')

tess_eval_sdr = GL.NewTessEvaluationShader('''
	#version 430

	void main() {
	}
''')

tess_cont_sdr = GL.NewTessControlShader('''
	#version 430

	void main() {
	}
''')

prog = [
	GL.NewProgram([vert_sdr, frag_sdr]),
	GL.NewProgram([vert_sdr, frag_sdr, geom_sdr]),
	GL.NewProgram([vert_sdr, frag_sdr, geom_sdr]), #, tess_eval_sdr, tess_cont_sdr]),
]

vert = GL.GetAttributeLocation(prog[0], 'vert')

vbo = GL.NewVertexBuffer(struct.pack('8f', 0.2, 0.2, 0.4, 0.2, 0.2, 0.4, 0.4, 0.4))
ibo = GL.NewIndexBuffer(struct.pack('3I', 1, 2, 3))

vao = [
	GL.NewVertexArray('2f', [(vbo, vert)]),
	GL.NewVertexArray('2f', [(vbo, vert)], ibo),
]

GL.UseFramebuffer(fbo[0])
GL.Viewport(0, 0, 100, 100)
GL.Clear(240, 240, 240)

GL.UseFramebuffer(fbo[1])
GL.Viewport(0, 0, 100, 100)
GL.Clear(240, 240, 240)

GL.UseProgram(prog[0])
GL.RenderLines(vao[0], 4)
GL.RenderTriangles(vao[0], 3)
GL.RenderPoints(vao[1], 3)

GL.UseFramebuffer(fbo[0])
Image.frombytes('RGB', (100, 100), GL.ReadPixels(0, 0, 100, 100)).save('TestResults/Image_00.png')

GL.UseFramebuffer(fbo[1])
Image.frombytes('RGB', (100, 100), GL.ReadPixels(0, 0, 100, 100)).save('TestResults/Image_01.png')

exit()
# uni_1f = GL.GetUniformLocation(prog, 'uni_1f')
# uni_2f = GL.GetUniformLocation(prog, 'uni_2f')
# uni_3f = GL.GetUniformLocation(prog, 'uni_3f')
# uni_4f = GL.GetUniformLocation(prog, 'uni_4f')
# uni_1i = GL.GetUniformLocation(prog, 'uni_1i')
# uni_2i = GL.GetUniformLocation(prog, 'uni_2i')
# uni_3i = GL.GetUniformLocation(prog, 'uni_3i')
# uni_4i = GL.GetUniformLocation(prog, 'uni_4i')
# uni_mat_A = GL.GetUniformLocation(prog, 'uni_mat_A')
# uni_mat_B = GL.GetUniformLocation(prog, 'uni_mat_B')
# buf = GL.GetUniformBufferLocation(prog, 'buf')

GL.UseProgram(prog)

GL.Uniform1f(uni_1f, 0.0)
GL.Uniform2f(uni_2f, 0.0, 0.0)
GL.Uniform3f(uni_3f, 0.0, 0.0, 0.0)
GL.Uniform4f(uni_4f, 0.0, 0.0, 0.0, 0.0)
GL.Uniform1i(uni_1i, 0)
GL.Uniform2i(uni_2i, 0, 0)
GL.Uniform3i(uni_3i, 0, 0, 0)
GL.Uniform4i(uni_4i, 0, 0, 0, 0)
GL.UniformMatrix(uni_mat_A, [0.0] * 16)
GL.UniformTransposeMatrix(uni_mat_B, [0.0] * 16)

UseUniformBuffer(ubo, buf)

NewTexture
UpdateTexture
UseTexture

SetTexturePixelated
SetTextureFiltered
SetTextureMipmapped

BuildMipmap

EnableAttribute
DisableAttribute

EnableAttributes
DisableAttributes

vbo = NewVertexBuffer(b'')
ibo = NewIndexBuffer(b'')
ubo = NewUniformBuffer(b'')

NewDynamicVertexBuffer(b'')
NewDynamicIndexBuffer(b'')
NewDynamicUniformBuffer(b'')

UpdateVertexBuffer
UpdateIndexBuffer
UpdateUniformBuffer

RenderTriangles(vao)
RenderTriangleStrip(vao)
RenderTriangleFan(vao)
RenderLines(vao)
RenderLineStrip(vao)
RenderLineLoop(vao)
RenderLineStripAdjacency(vao)
RenderLinesAdjacency(vao)
RenderTriangleStripAdjacency(vao)
RenderTrianglesAdjacency(vao)

RenderTriangles(ivao)
RenderTriangleStrip(ivao)
RenderTriangleFan(ivao)
RenderLines(ivao)
RenderLineStrip(ivao)
RenderLineLoop(ivao)
RenderPoints(ivao)
RenderLineStripAdjacency(ivao)
RenderLinesAdjacency(ivao)
RenderTriangleStripAdjacency(ivao)
RenderTrianglesAdjacency(ivao)

ReadDepthPixels
ReadPixel
ReadDepthPixel

UseTextureAsImage

NewComputeShader
RunComputeShader
NewStorageBuffer
NewDynamicStorageBuffer
UseStorageBuffer
UpdateStorageBuffer
ReadStorageBuffer

DeleteProgram
DeleteShader
DeleteTexture
DeleteVertexArray
DeleteVertexBuffer
DeleteIndexBuffer
DeleteUniformBuffer
DeleteFramebuffer
DeleteComputeShader
