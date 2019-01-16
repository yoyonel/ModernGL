
# Window Examples

ModernGL can only create an OpenGL context in headless mode and relies on other libraries
to create a context displaying a visible window. ModernGL will then load OpenGL
functions from the existing contexts instead.

This package contains examples using ModernGL with various libraries
opening a visible window.

## PyQt5

PyQt5 is a comprehensive set of Python bindings for Qt v5.
This package requires no external dependencies and works pretty much
out of the box on most platforms.

Homepage: https://www.riverbankcomputing.com/software/pyqt/intro

## pyglet

Pyglet is a cross-platform windowing and multimedia library for Python.
No external dependencies or installation requirements.
As is January 2019, pyglet is not able to open core OpenGL context causing
issues when using OpenGL versions higher than 2.1 on some platforms.
A version solving this issue is currently under development.

Homepage: https://bitbucket.org/pyglet/pyglet/wiki/Home

## py-sdl2

PySDL2 is a wrapper around the SDL2 library. It has no licensing restrictions.
In addition to the python package you need to install the shared library
from https://www.libsdl.org/download-2.0.php.

Homepage: https://github.com/marcusva/py-sdl2

## pyGLFW

Python bindings for GLFW (on GitHub: glfw/glfw). It is a ctypes wrapper which
keeps very close to the original GLFW API.
You will need to install the GLFW shared library from https://www.glfw.org/download.html.

Homepage: https://github.com/FlorianRhiem/pyGLFW
