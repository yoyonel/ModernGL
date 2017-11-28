#!/usr/bin/env python3.6
import itertools
import os

import glfw
import ModernGL
import pyrr
from ModernGL.ext.obj import Obj
from PIL import Image


def error_callback(error, description):
    print(f'Error: {description}')


def glfw_initialization(glsl_version=None, window_size=None, title=None):
    """Initializes GLFW, OpenGL Context and creates a Window"""
    major, minor = glsl_version or (3, 3)
    width, height = window_size or (1280, 720)
    title = title or 'ModernGL Test Window'

    if not glfw.init():
        raise RuntimeError('GLFW could not be initialized.')
    glfw.window_hint(glfw.CONTEXT_VERSION_MAJOR, major)
    glfw.window_hint(glfw.CONTEXT_VERSION_MINOR, minor)
    profile = glfw.OPENGL_CORE_PROFILE if (major, minor) > (3, 2) else glfw.GLFW_OPENGL_ANY_PROFILE
    compat = True if (major, minor) >= (3, 0) else False
    glfw.window_hint(glfw.OPENGL_PROFILE, profile)
    glfw.window_hint(glfw.OPENGL_FORWARD_COMPAT, compat)
    glfw.window_hint(glfw.VISIBLE, True)
    win = glfw.create_window(width, height, title, None, None)
    if not win:
        glfw.terminate()
        raise RuntimeError('GLFW could not create window.')
    glfw.make_context_current(win)
    glfw.swap_interval(1)

    glfw.set_error_callback(error_callback)
    glfw.set_key_callback(win, key_callback)
    return win


def key_callback(window, key, scancode, action, mods):
    global background_color
    global foreground_color
    global texture_image
    global texture_data
    global model_data
    global color
    global model
    global ctx

    # Escape or 'q' will exit
    if key in [glfw.KEY_ESCAPE, glfw.KEY_Q] and action == glfw.PRESS:
        glfw.set_window_should_close(window, True)

    elif key in [glfw.KEY_F] and action == glfw.PRESS:
        # Cycle the background color
        foreground_color = next(color)

    elif key in [glfw.KEY_B] and action == glfw.PRESS:
        # Cycle the background color
        background_color = next(color)

    elif key in [glfw.KEY_M] and action == glfw.PRESS:
        # Cycle the object model
        model_data = next(model)

    elif key in [glfw.KEY_T] and action == glfw.PRESS:
        # Cycle the texture
        texture_image = next(texture)
        texture_data = ctx.texture(texture_image.size, 3, texture_image.tobytes())
        texture_data.build_mipmaps()


def load_data(ctx, data_path=None, vertex_path=None, fragment_path=None, object_path=None, texture_path=None):
    """Loads texture data, vertex and fragment shaders and object data.

    Args:
        ctx (ModernGL.context.Context): the OpenGL context
        vertex_path (str, optional): Path to vertex shader
        fragment_path (str, optional): Path to fragment shader
        object_path (str, optional): Path to model's vertex data
        texture_path (str, optional): Path to texture file

    Updates:
        background_color
        texture_image
        model_data
        program

        texture
        model
        color


    Returns:
        tuple: opengl program, texture, vertex_data
    """
    global foreground_color
    global background_color
    global texture_image
    global texture_data
    global model_data
    global program

    global texture
    global model
    global color

    data_path = data_path or _find_data_folder()

    # Build file lists
    files = os.listdir(data_path)
    colors = list(itertools.product([0, 1], repeat=3))  # (0, 0, 0), (0, 0, 1), ... (1, 1, 1)
    models = [Obj.open(os.path.join(data_path, filename)).pack() for filename in files if filename.endswith('.obj')]
    textures = [Image.open(os.path.join(data_path, filename)) for filename in files if filename.endswith('.jpg')]
    textures = [t for t in textures if t.mode == 'RGB']

    # Setup global generators
    color = _eternal_generator(colors)
    texture = _eternal_generator(textures)
    model = _eternal_generator(models)

    # Setup keyboard control parameters
    background_color = next(color)
    foreground_color = next(color)
    texture_image = next(texture)
    model_data = next(model)

    texture_data = ctx.texture(texture_image.size, 3, texture_image.tobytes())
    texture_data.build_mipmaps()

    # Setup files
    vertex_path = vertex_path or f'{data_path}/glfw-simple-window.vert'
    fragment_path = fragment_path or f'{data_path}/glfw-simple-window.frag'
    object_path = object_path or f'{data_path}/mug.obj'

    program = _load_shaders(ctx, vertex_path, fragment_path)


def main_loop(data_path=None, texture_path=None, vertex_path=None, fragment_path=None, object_path=None):
    global ctx

    # Loop initialization
    win = glfw_initialization()
    ctx = ModernGL.create_context()
    load_data(
        ctx,
        data_path=data_path,
        vertex_path=vertex_path,
        fragment_path=fragment_path,
        texture_path=texture_path,
        object_path=object_path,
        )

    # Display
    while not glfw.window_should_close(win):
        render_scene(win, ctx)
        glfw.swap_buffers(win)
        glfw.poll_events()

    glfw.destroy_window(win)
    glfw.terminate()


def render_scene(win, ctx):
    global fbo
    global texture_data
    global model_data
    global program
    global background_color
    global foreground_color

    # Matrices and Uniforms
    perspective = pyrr.Matrix44.perspective_projection(45.0, 1.0, 0.1, 1000.0)
    lookat = pyrr.Matrix44.look_at(
        eye=(-85, -180, 140),
        target=(0.0, 0.0, 65.0),
        up=(0.0, 0.0, 1.0),
        )
    mvp = perspective * lookat

    program.uniforms['Light'].value = (-140.0, -100.0, 350.0)
    program.uniforms['Color'].value = tuple(list(foreground_color) + [0.25])
    program.uniforms['Mvp'].write(mvp.astype('f4').tobytes())

    # Vertex Buffer and Vertex Array
    vbo = ctx.buffer(model_data)
    vao = ctx.simple_vertex_array(program, vbo, ['in_vert', 'in_text', 'in_norm'])

    ctx.disable(ModernGL.DEPTH_TEST)
    ctx.clear(*background_color)

    # Rendering
    ctx.enable(ModernGL.DEPTH_TEST)
    ctx.clear(*background_color)
    ctx.default_framebuffer.use()
    texture_data.use()
    vao.render()


def _eternal_generator(data):
    """Hack to continuously cycle across an iterable."""
    while True:
        yield from data


def _find_data_folder():
    """Searches for folder containing data"""
    starting_folder = os.path.dirname(__file__)
    if starting_folder == '.':
        starting_folder = os.getcwd()
    found = False
    data_path = ''
    while not found:
        if 'data' in os.listdir(starting_folder):
            data_path = os.path.join(starting_folder, 'data')
            if os.path.exists(data_path):
                break
        starting_folder = os.path.dirname(starting_folder)
        if starting_folder == '':
            raise RuntimeError('Could not find "data" path')
    return data_path


def _load_shaders(ctx, vertex_path, fragment_path):
    with open(vertex_path, 'r') as fd:
        vertex_source = fd.read()
    with open(fragment_path, 'r') as fd:
        fragment_source = fd.read()

    # Shaders
    vert = ctx.vertex_shader(vertex_source)
    frag = ctx.fragment_shader(fragment_source)
    prog = ctx.program([vert, frag])
    return prog


if __name__ == '__main__':
    import click

    @click.command()
    @click.option('-d', '--data-path', metavar='PATH', help='PATH to data files', default=None)
    @click.option('-f', '--fragment', metavar='PATH', help='PATH to fragment file', default=None)
    @click.option('-v', '--vertex', metavar='PATH', help='PATH to vertex file', default=None)
    @click.option('-o', '--object', metavar='PATH', help='PATH to object file', default=None)
    @click.option('-t', '--texture', metavar='PATH', help='PATH to texture file', default=None)
    def cli(data_path=None, fragment=None, vertex=None, object=None, texture=None):
        """Creates a simple window using GLFW and ModernGL

        Note: This was built for python3.6 and uses f-strings

        Keyboard Commands:

        \b
            Q: Quits program
            B: Changes the background color
            F: Changes the foreground color
            M: Changes the model
            T: Changes the texture
        """
        main_loop(
            data_path=data_path,
            fragment_path=fragment,
            vertex_path=vertex,
            object_path=object,
            texture_path=texture,
            )

    cli()
