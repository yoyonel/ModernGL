"""

"""
import numpy as np
import moderngl
import moderngl as mgl
from scipy import ndimage


def _raster_triangle(ctx, prog, vbo, size=(4, 4)):
    """

    :param ctx:
    :param prog:
    :param vbo:
    :param size:
    :return:
    """
    tex_depth = ctx.depth_texture(size)  # implicit -> dtype='f4', components=1
    fbo_depth = ctx.framebuffer(depth_attachment=tex_depth)
    fbo_depth.use()
    fbo_depth.clear(depth=1.0)

    # vertex array object of triangle with depth pass prog
    vao_triangle = ctx.simple_vertex_array(prog, vbo, 'in_vert')
    # Now we render a triangle in there
    vao_triangle.render()

    return fbo_depth, tex_depth


def test_depth_sampler(standalone_context, prog_render_depth_pass, prog_draw_depth, vbo_triangle, vbo_quad):
    """

    :param standalone_context:
    :param prog_render_depth_pass:
    :param prog_draw_depth:
    :param vbo_triangle:
    :param vbo_quad:
    :return:
    """
    ctx = standalone_context
    ctx.enable(mgl.DEPTH_TEST)

    size = (16, 16)
    fbo_depth, tex_depth = _raster_triangle(ctx, prog_render_depth_pass, vbo_triangle, size)

    # It should have some different values where the triangle lies.
    depth_from_dbo = np.frombuffer(tex_depth.read(), dtype=np.dtype('f4')).reshape(size[::-1])
    depth_value_from_triangle_vertices = 0.0
    # Map [-1, +1] -> [0, 1]
    depth_value_in_depthbuffer = (depth_value_from_triangle_vertices + 1)*0.5
    np_triangle_raster = np.array(
        [
            [depth_value_in_depthbuffer] * (size[0] - (j + 1)) + [1.0] * (j + 1)
            for j in range(size[1])
        ]
    )
    # some stuff should be 1s and 0.5 where the triangle lies.
    np.testing.assert_array_almost_equal(depth_from_dbo, np_triangle_raster)

    # vertex array object of (fullscreen) quad with render depth prog
    vao_quad = ctx.simple_vertex_array(prog_draw_depth, vbo_quad, 'in_vert')

    fbo_draw_depth = ctx.framebuffer(color_attachments=[ctx.renderbuffer(size, components=1, dtype='f4')])
    fbo_draw_depth.use()

    # from: https://github.com/Contraz/demosys-py/blob/master/demosys/opengl/texture.py
    depth_sampler = ctx.sampler(filter=(moderngl.NEAREST, moderngl.NEAREST), compare_func='')  # disable depth func
    depth_sampler.use(location=0)
    tex_depth.use(location=0)
    #
    vao_quad.render(moderngl.TRIANGLE_STRIP)
    #
    data = np.frombuffer(fbo_draw_depth.read(components=1, dtype='f4'), dtype=np.dtype('f4')).reshape(size[::-1])
    np.testing.assert_array_almost_equal(data, np_triangle_raster)


def test_sampler_shadow(standalone_context, prog_render_depth_pass, vbo_triangle, vbo_quad):
    """

    :param standalone_context:
    :param prog_render_depth_pass:
    :param vbo_triangle:
    :param vbo_quad:
    :return:
    """
    ctx = standalone_context
    ctx.enable(mgl.DEPTH_TEST)

    size = (4, 4)
    fbo_depth, tex_depth = _raster_triangle(ctx, prog_render_depth_pass, vbo_triangle, size)

    prog_for_shadow = ctx.program(
        vertex_shader='''
                    #version 330

                    in vec2 in_vert;
                    out vec2 uv;

                    void main() {
                        uv = in_vert;
                        gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                    }
                ''',
        fragment_shader='''
                    #version 330

                    uniform sampler2DShadow depth;

                    uniform float depth_bias;
                    uniform float depth_triangle;
                     
                    in vec2 uv;
                    out float fragColor;

                    void main() {
                        float depth_shadow_caster = depth_triangle + depth_bias;
                        vec3 shadow_coord = vec3(uv, depth_shadow_caster);
                        float visibility = texture(depth, shadow_coord);
                        fragColor = visibility;
                    }
                ''',
    )
    prog_for_shadow['depth_bias'].value = 0.00001
    prog_for_shadow['depth_triangle'].value = 0.50
    # https://www.khronos.org/opengl/wiki/Sampler_(GLSL)#Shadow_samplers
    vao_fs_shadow = ctx.simple_vertex_array(prog_for_shadow, vbo_quad, 'in_vert')

    fbo_draw_depth = ctx.framebuffer(color_attachments=[ctx.renderbuffer(size, components=1, dtype='f4')])
    fbo_draw_depth.use()

    # https://github.com/Contraz/demosys-py/blob/01f285cd3a132012e14a51bf0ae9d7aa5a489b55/demosys/opengl/texture.py#L151
    shadow_sampler = ctx.sampler(filter=(moderngl.NEAREST, moderngl.NEAREST), compare_func='>=')  # enable depth func
    shadow_sampler.use(location=0)
    tex_depth.use(location=0)

    vao_fs_shadow.render(moderngl.TRIANGLE_STRIP)

    #
    data = np.frombuffer(fbo_draw_depth.read(components=1, dtype='f4'), dtype=np.dtype('f4')).reshape(size[::-1])
    texel_shadowed = 1
    np_triangle_raster_visbility = np.array(
        [
            [texel_shadowed] * (size[0] - (j + 1)) + [1-texel_shadowed] * (j + 1)
            for j in range(size[1])
        ]
    )
    np.testing.assert_array_almost_equal(data, np_triangle_raster_visbility)


def test_sampler_shadow_with_bilinear_interpolation(standalone_context, prog_render_depth_pass, vbo_triangle, vbo_quad):
    """

    :param standalone_context:
    :param prog_render_depth_pass:
    :param vbo_triangle:
    :param vbo_quad:
    :return:
    """
    ctx = standalone_context
    ctx.enable(mgl.DEPTH_TEST)

    size = (8, 8)
    fbo_depth, tex_depth = _raster_triangle(ctx, prog_render_depth_pass, vbo_triangle, size)

    prog_for_shadow = ctx.program(
        vertex_shader='''
                    #version 330

                    in vec2 in_vert;
                    out vec2 uv;

                    void main() {
                        uv = in_vert;
                        gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                    }
                ''',
        fragment_shader='''
                    #version 330

                    uniform sampler2DShadow depth;
                    
                    uniform vec2 half_pixel;
                    
                    in vec2 uv;
                    out float fragColor;

                    void main() {
                        vec3 shadow_coord = vec3(uv, 0.50 + 0.01);
                        shadow_coord += vec3(half_pixel, 0.0);
                        float visibility = texture(depth, shadow_coord);
                        fragColor = visibility;
                    }
                ''',
    )
    prog_for_shadow['half_pixel'].value = (1.0/float(size[0]) * 0.5, 1.0/float(size[1]) * 0.5)
    # https://www.khronos.org/opengl/wiki/Sampler_(GLSL)#Shadow_samplers
    vao_fs_shadow = ctx.simple_vertex_array(prog_for_shadow, vbo_quad, 'in_vert')

    fbo_draw_depth = ctx.framebuffer(color_attachments=[ctx.renderbuffer(size, components=1, dtype='f4')])
    fbo_draw_depth.use()

    # https://github.com/Contraz/demosys-py/blob/01f285cd3a132012e14a51bf0ae9d7aa5a489b55/demosys/opengl/texture.py#L151
    shadow_sampler = ctx.sampler(
        filter=(moderngl.LINEAR, moderngl.LINEAR),
        compare_func='>=',
        # # from context.py:
        # #   border_color (tuple): The (r, g, b, a) color for the texture border.
        # #                         When this value is set the ``repeat_`` values are overriden
        # #                         setting the texture wrap to return the border color when outside ``[0, 1]`` range.
        # border_color=(0, 0, 0, 0),
        repeat_x=False, repeat_y=False,
    )  # enable depth func
    shadow_sampler.use(location=0)
    tex_depth.use(location=0)

    vao_fs_shadow.render(moderngl.TRIANGLE_STRIP)

    #
    data = np.frombuffer(fbo_draw_depth.read(components=1, dtype='f4'), dtype=np.dtype('f4')).reshape(size[::-1])

    # Box filter (2x2) on triangle visibility rasterisation
    # is similar to bilinear interpolation with samplerShadow
    # https://docs.scipy.org/doc/scipy/reference/generated/scipy.ndimage.uniform_filter.html#scipy.ndimage.uniform_filter
    np_triangle_raster_visbility = np.array(
        [
            [1.0] * (size[0] - (j + 1)) + [0.0] * (j + 1)
            for j in range(size[1])
        ]
    )
    box_filter_on_triangle_raster_visibility = ndimage.uniform_filter(np_triangle_raster_visbility,
                                                                      size=2, mode='constant', cval=0, origin=-1)
    np.testing.assert_array_almost_equal(data, box_filter_on_triangle_raster_visibility)
