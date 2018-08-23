# coding=utf-8
import moderngl as mgl
import numpy as np
import pytest


@pytest.fixture(autouse=True)
def standalone_context():
    return mgl.create_standalone_context()


@pytest.fixture
def prog_render_depth_pass(standalone_context):
    return standalone_context.program(
        vertex_shader='''
                #version 330

                in vec3 in_vert;

                void main() {
                    gl_Position = vec4(in_vert, 1.0);
                }
            ''',
        fragment_shader='''
                #version 330

                void main() {
                }
            ''',
    )


@pytest.fixture
def prog_draw_depth(standalone_context):
    prog = standalone_context.program(
        vertex_shader='''
                    #version 330

                    in vec2 in_vert;
                    out vec2 uv;

                    void main() {
                        uv = in_vert;
                        gl_Position = vec4(in_vert * 2.0 - 1.0, 0.0, 1.0);
                    }
                ''',
        # from `texture.py`
        fragment_shader='''
                    #version 330

                    uniform sampler2D depth;

                    in vec2 uv;
                    out float fragColor;

                    void main() {
                        float raw_depth_nonlinear = texture(depth, uv).r;
                        fragColor = raw_depth_nonlinear;
                    }
                ''',
    )
    prog['depth'].value = 0
    return prog


@pytest.fixture
def vbo_triangle(standalone_context):
    vertices = np.array([[-1, 1, 0.], [-1, -1, 0.], [1, -1, 0.], ])
    return standalone_context.buffer(vertices.astype('f4').tobytes())


@pytest.fixture
def vbo_quad(standalone_context):
    canvas_fs_quad = np.array([0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0]).astype('f4')
    return standalone_context.buffer(canvas_fs_quad.tobytes())
