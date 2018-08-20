import numpy as np
import moderngl
import moderngl as mgl


ctx = mgl.create_standalone_context()
ctx.enable(mgl.DEPTH_TEST)
prog = ctx.program(
    vertex_shader='''
        #version 330

        in vec3 in_vert;

        void main() {
            gl_Position = vec4(in_vert, 1.0);
        }
    ''',
    fragment_shader='''
        #version 330

        out vec3 f_color;

        void main() {
            f_color = vec3(1.0);
            gl_FragDepth = 0.1234;
        }
    ''',
)

prog_for_depth = ctx.program(
    vertex_shader='''
        #version 330

        in vec2 in_vert;
        out vec2 v_text;

        void main() {
            v_text = in_vert;
            gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
        }
    ''',
    fragment_shader='''
        #version 330

        uniform sampler2D Texture;
        
        in vec2 v_text;

        out vec3 f_color;

        void main() {
            f_color = vec3(texture(Texture, v_text).r);
        }
    ''',
)

vertices = np.array([
    [-1, 1, 0.],
    [-1, -1, 0.],
    [1, -1, 0.],
])
vbo = ctx.buffer(vertices.astype('f4').tobytes())

size = (4, 4)
cbo = ctx.renderbuffer(size)
dbo = ctx.depth_texture(size, alignment=1)  # implicit -> dtype='f4', components=1

fbo = ctx.framebuffer(color_attachments=[cbo], depth_attachment=dbo)
fbo.use()
fbo.clear(depth=1.0)

depth = np.frombuffer(dbo.read(alignment=1), dtype=np.dtype('f4')).reshape(size[::-1])
print("depth buffer - should all be 1")
print(depth)  # should all be 1

# Now we render a triangle in there
vao = ctx.simple_vertex_array(prog, vbo, 'in_vert')
vao.render()

# It should have some different values in the middle
depth_from_dbo = np.frombuffer(dbo.read(alignment=1), dtype=np.dtype('f4')).reshape(size[::-1])
print("# From dbo - some stuff should be 1s and 0.1234 where the triangle lies.")
print(depth_from_dbo)  # some stuff should be 1s and 0.5 where the triangle lies.

# lets just check the value of the fbo for safety
data = np.frombuffer(fbo.read(), dtype=np.dtype('u1')).reshape((size[1], size[0], 3))
print("From fbo - lets just check the value of the fbo for safety")
print("255 on triangle rasterisation, 0 elsewhere")
print(data[:, :, 0])

print("Show depth texture from fbo ...")
print("# some stuff should be 1s and 0.1234 where the triangle lies.")
depth_from_fbo = np.frombuffer(fbo.read(attachment=-1, dtype='f4'), dtype=np.dtype('f4')).reshape(size[::-1])
print(depth_from_fbo)

np.testing.assert_almost_equal(depth_from_dbo, depth_from_fbo)

#
canvas = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
vbo_fs = ctx.buffer(canvas.tobytes())
vao_fs = ctx.simple_vertex_array(prog_for_depth, vbo_fs, 'in_vert')
cbo_fs = ctx.renderbuffer(size)
fbo_fs = ctx.framebuffer(color_attachments=[cbo_fs])

prog_for_depth['Texture'].value = 0

fbo_fs.use()
fbo_fs.clear(depth=1.0)
dbo.use(0)
vao_fs.render(moderngl.TRIANGLE_STRIP)
#
data = np.frombuffer(fbo_fs.read(), dtype=np.dtype('u1')).reshape((size[1], size[0], 3))
print("")
print("")
print(data[:, :, 0])

fbo_fs.use()
fbo_fs.clear(depth=1.0)
texture = ctx.texture(size, 1, depth_from_dbo, dtype='f4')
texture.use(0)
vao_fs.render(moderngl.TRIANGLE_STRIP)
#
data = np.frombuffer(fbo_fs.read(), dtype=np.dtype('u1')).reshape((size[1], size[0], 3))
print("")
print("")
print(data[:, :, 0])
