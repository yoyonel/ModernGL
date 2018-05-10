#!/usr/bin/env python3
'''Simple example of using tesselation to render a cubic Bézier curve'''

import glfw  # https://github.com/FlorianRhiem/pyGLFW
import moderngl
import numpy as np


def main():
    if not glfw.init():
        print('Failed to initialize glfw!')
        return

    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, 4)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, 0)
    win = glfw.create_window(640, 480, 'bezier', None, None)
    if not win:
        print('Failed to create glfw window!')
        glfw.terminate()
        return

    glfw.make_context_current(win)
    ctx = moderngl.create_context()

    prog = ctx.program(
        vertex_shader='''
        #version 400 core

        in vec2 in_pos;

        void main() { gl_Position = vec4(in_pos, 0.0, 1.0); }
        ''',
        tess_control_shader='''
        #version 400 core

        layout(vertices = 4) out;

        void main() {
          // set tesselation levels, TODO compute dynamically
          gl_TessLevelOuter[0] = 1;
          gl_TessLevelOuter[1] = 32;

          // pass through vertex positions
          gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
        }
        ''',
        tess_evaluation_shader='''
        #version 400 core

        layout(isolines, fractional_even_spacing, ccw) in;

        // compute a point on a bezier curve with the points p0, p1, p2, p3
        // the parameter u is in [0, 1] and determines the position on the curve
        vec3 bezier(float u, vec3 p0, vec3 p1, vec3 p2, vec3 p3) {
          float B0 = (1.0 - u) * (1.0 - u) * (1.0 - u);
          float B1 = 3.0 * (1.0 - u) * (1.0 - u) * u;
          float B2 = 3.0 * (1.0 - u) * u * u;
          float B3 = u * u * u;

          return B0 * p0 + B1 * p1 + B2 * p2 + B3 * p3;
        }

        void main() {
          float u = gl_TessCoord.x;

          vec3 p0 = vec3(gl_in[0].gl_Position);
          vec3 p1 = vec3(gl_in[1].gl_Position);
          vec3 p2 = vec3(gl_in[2].gl_Position);
          vec3 p3 = vec3(gl_in[3].gl_Position);

          gl_Position = vec4(bezier(u, p0, p1, p2, p3), 1.0);
        }
        ''',
        fragment_shader='''
        #version 400 core

        out vec4 frag_color;

        void main() { frag_color = vec4(1.0); }
        ''')

    # four vertices define a cubic Bézier curve; has to match the shaders
    ctx.patch_vertices = 4

    ctx.line_width = 5.0
    vertices = np.array([
        [-1.0, 0.0],
        [-0.5, 1.0],
        [0.5, -1.0],
        [1.0, 0.0],
    ])

    vbo = ctx.buffer(vertices.astype('f4').tobytes())
    vao = ctx.simple_vertex_array(prog, vbo, 'in_pos')

    while not glfw.window_should_close(win):
        width, height = glfw.get_window_size(win)
        ctx.viewport = (0, 0, width, height)
        ctx.clear(0.2, 0.4, 0.7)
        vao.render(mode=moderngl.PATCHES)
        glfw.swap_buffers(win)
        glfw.poll_events()

    glfw.terminate()


if __name__ == '__main__':
    main()
