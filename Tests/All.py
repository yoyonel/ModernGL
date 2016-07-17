import GLContext as CTX
import ModernGL as GL
import math, struct, os
import GLWindow

from PIL import Image

bg = [
	(255, 0, 0),
	(0, 255, 0),
	(0, 0, 255),
	(0, 255, 255),
	(255, 0, 255),
	(255, 255, 0),
]

verts = [
	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 6 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 6 / 6), -0.6, 0.9,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 6 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 6 / 6), -0.6, 0.9,
	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 6 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 6 / 6), -0.6, 0.9,

	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 5 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 5 / 6), -0.5, 0.8,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 5 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 5 / 6), -0.5, 0.8,
	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 5 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 5 / 6), -0.5, 0.8,

	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 4 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 4 / 6), -0.4, 0.7,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 4 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 4 / 6), -0.4, 0.7,
	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 4 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 4 / 6), -0.4, 0.7,

	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 3 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 3 / 6), -0.3, 0.6,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 3 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 3 / 6), -0.3, 0.6,
	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 3 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 3 / 6), -0.3, 0.6,

	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 2 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 2 / 6), -0.2, 0.5,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 2 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 2 / 6), -0.2, 0.5,
	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 2 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 2 / 6), -0.2, 0.5,

	math.cos(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 1 / 6), math.sin(2 * math.pi * 3 / 3 + 2 * math.pi / 3 * 1 / 6), -0.1, 0.4,
	math.cos(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 1 / 6), math.sin(2 * math.pi * 2 / 3 + 2 * math.pi / 3 * 1 / 6), -0.1, 0.4,
	math.cos(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 1 / 6), math.sin(2 * math.pi * 1 / 3 + 2 * math.pi / 3 * 1 / 6), -0.1, 0.4,
]

# CTX.Context(True)
GLWindow.InitializeWindow()
GLWindow.BuildFullscreen()

GL.InitializeModernGL()

print(GL.GetInfo())

if not os.path.isdir('TestResults'):
	os.mkdir('TestResults')

# GL.BuildMipmap()

# GL.DeleteComputeShader()
# GL.DeleteFramebuffer()
# GL.DeleteIndexBuffer()
# GL.DeleteProgram()
# GL.DeleteShader()
# GL.DeleteStorageBuffer()
# GL.DeleteTexture()
# GL.DeleteUniformBuffer()
# GL.DeleteVertexArray()
# GL.DeleteVertexBuffer()

# GL.DisableAttributes()
# GL.EnableAttributes()

# GL.LineSize()
# GL.PointSize()

cs = GL.NewComputeShader('''
	#version 430

	layout (binding = 0) buffer Input {
		int A[4][4][4];
	};

	layout (binding = 1) buffer Output {
		int B[4][4][4];
	};

	layout (local_size_x = 2, local_size_y = 2, local_size_z = 2) in;

	void main() {
		B[gl_GlobalInvocationID.x][gl_GlobalInvocationID.y][gl_GlobalInvocationID.z] = A[gl_GlobalInvocationID.x][gl_GlobalInvocationID.y][gl_GlobalInvocationID.z];
	}
''')

A = GL.NewStorageBuffer(struct.pack('64i', *[1 + i for i in range(64)]))
B = GL.NewStorageBuffer(b'\x00' * 256)
C = GL.NewStorageBuffer(b'\x00' * 256)

BX = GL.NewStorageBuffer(b'\x00' * 256)
BY = GL.NewStorageBuffer(b'\x00' * 256)
BZ = GL.NewStorageBuffer(b'\x00' * 256)

GL.UseStorageBuffer(A)

GL.UseStorageBuffer(B, 1)
GL.RunComputeShader(cs)

GL.UseStorageBuffer(BX, 1)
GL.RunComputeShader(cs, x = 2)
GL.UseStorageBuffer(BY, 1)
GL.RunComputeShader(cs, y = 2)
GL.UseStorageBuffer(BZ, 1)
GL.RunComputeShader(cs, z = 2)

GL.UpdateStorageBuffer(C, 0, struct.pack('64i', *[4 for i in range(64)]))
GL.UpdateStorageBuffer(C, 64, struct.pack('32i', *[9 for i in range(32)]))

print(struct.unpack('64i', GL.ReadStorageBuffer(B)))
print(struct.unpack('64i', GL.ReadStorageBuffer(BX)))
print(struct.unpack('64i', GL.ReadStorageBuffer(BY)))
print(struct.unpack('64i', GL.ReadStorageBuffer(BZ)))
print(struct.unpack('64i', GL.ReadStorageBuffer(C)))

vert = GL.NewVertexShader('''
	#version 330

	in vec3 vert;
	in float diffuse;

	out float d;

	void main() {
		gl_Position = vec4(vert, 1.0);
		d = diffuse;
	}
''')

frag = GL.NewFragmentShader('''
	#version 330
	
	in float d;
	out vec4 color;

	void main() {
		color = vec4(0.30 * d, 0.50 * d, 1.00 * d, 0.5);
	}
''')

prog, iface = GL.NewProgram([vert, frag])

vbo = GL.NewVertexBuffer(struct.pack('72f', *verts))
vao = GL.NewVertexArray(prog, vbo, '3f1f', ['vert', 'diffuse'])

nodes = [GL.NewFramebuffer(256, 256) for i in range(6)]

enables = [
	GL.ENABLE_BLEND,
	GL.ENABLE_CULL_FACE,
	GL.ENABLE_DEPTH_TEST,
	GL.ENABLE_BLEND + GL.ENABLE_DEPTH_TEST,
	GL.ENABLE_CULL_FACE + GL.ENABLE_BLEND,
	GL.ENABLE_BLEND + GL.ENABLE_DEPTH_TEST + GL.ENABLE_CULL_FACE,
]

GL.Viewport(0, 0, 256, 256)
for i, (fbo, color, depth) in enumerate(nodes):
	GL.UseFramebuffer(fbo)
	GL.Clear(*bg[i])
	GL.EnableOnly(enables[i])
	GL.RenderTriangles(vao, 18)

for i, (fbo, color, depth) in enumerate(nodes):
	GL.UpdateTexture(color, i * 8 + 8, 8, 8, 8, b'\x00' * 256)
	GL.UpdateTexture(color, i * 8 + 8, 24, 8, 8, b'\xff' * 256)

for i, (fbo, color, depth) in enumerate(nodes):
	GL.UseFramebuffer(fbo)
	Image.frombytes('RGB', (256, 256), GL.ReadPixels(0, 0, 256, 256, 3)).save('TestResults/c_%d.png' % i)
	pixels = b''.join(struct.pack('B', int(c * 255)) for c in struct.unpack('65536f', GL.ReadDepthPixels(0, 0, 256, 256)))
	Image.frombytes('L', (256, 256), pixels).save('TestResults/d_%d.png' % i)

exit()

GL.DisableBlend()
GL.DisableCullFace()
GL.DisableDepthTest()
GL.DisableMultisample()

GL.EnableBlend()
GL.EnableCullFace()
GL.EnableDepthTest()
GL.EnableMultisample()

GL.NewAdvancedVertexArray()
GL.NewFragmentShader()
GL.NewFramebuffer()
GL.NewGeometryShader()
GL.NewIndexBuffer()
GL.NewProgram()
GL.NewTessControlShader()
GL.NewTessEvaluationShader()
GL.NewTexture()
GL.NewUniformBuffer()
GL.NewVertexArray()
GL.NewVertexBuffer()
GL.NewVertexShader()

GL.ReadPixel()
GL.ReadPixels()

GL.ReadDepthPixel()
GL.ReadDepthPixels()

GL.ReadStorageBuffer()

GL.RenderLineLoop()
GL.RenderLineStrip()
GL.RenderLines()
GL.RenderPoints()
GL.RenderTriangleFan()
GL.RenderTriangleStrip()
GL.RenderTriangles()

GL.RenderLinesAdjacency()
GL.RenderLineStripAdjacency()
GL.RenderTrianglesAdjacency()
GL.RenderTriangleStripAdjacency()

GL.SetTextureFiltered()
GL.SetTextureMipmapped()
GL.SetTexturePixelated()
GL.SetUniform()
GL.SetUniformMatrix()

# GL.UpdateIndexBuffer()
# GL.UpdateTexture()
# GL.UpdateUniformBuffer()
# GL.UpdateVertexBuffer()

GL.UseDefaultFramebuffer()
GL.UseFramebuffer()
GL.UseTexture()
GL.UseTextureAsImage()
GL.UseUniformBuffer()

GL.Viewport()
