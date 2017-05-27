# ModernGL

:fire: Modern OpenGL binding for Python (PyOpenGL replacement)

- [ModernGL on PyPI](https://pypi.python.org/pypi/ModernGL/)
- [Documentation](https://moderngl.readthedocs.io/)
- [Examples](https://moderngl.github.io/Examples.html)

## What is ModernGL?

ModernGL is a python3 module that encapsulates **OpenGL** in a **pythonic** way.

## Why should I use ModernGL?

If you prefer **GPU accelerated high quality graphics** then you should develop your applications using ModernGL. It is much simpler then PyOpenGL and capable of rendering with the same quality and performace.

## Why is it simpler?

With the original OpenGL API you have to write a couple of lines to achieve a **simple task** like compiling a shader or running a computation on the GPU. With ModernGL you will need just a **few lines** to achieve the same result.

## Is ModernGL faster then PyOpenGL?

In some cases **yes**, the core functions of ModernGL are written in C++, OpenGL functions are called in quick succession so these calls together count as a single python function call.

## What version of OpenGL is used?

Most of the calls only require **OpenGL 3.3** but Subroutines and Compute Shaders require **OpenGL 4.0** and **OpenGL 4.3**

## Is my old PC supported?

OpenGL 3.3 came out in February 2010. With **up to date drivers** you will be able to use the most of the ModernGL functions, even on integrated graphics cards. _(No, Compute Shaders won't work)_

## How can I install ModernGL?

```
pip install ModernGL
```

## How can I start using ModernGL?

Take a look at the [examples](https://https://github.com/cprogrammer1994/ModernGL/examples) and [docs](https://moderngl.readthedocs.io/).

## Where can I use ModernGL?

**Anywhere where OpenGL is supported.** ModernGL is capable of rendering using a [standalone_context]() as well. Rendering to a window only requires a valid OpenGL context.

## Can ModernGL createa a Window?

**NO** Window creation is up to you. You can choose from a large variety of modules that can create a window: [PyQt5](), [GLUT](), [pygame]() and many others.

## Limitations using ModernGL over PyOpenGL?

All the neccessary calls are (or can be) implemented in ModernGL. However you can interract with the ModernGL objects from PyOpenGL if you want to. If something is missing write an [issue]() or raise a [PR]().

## Supported platforms?

- [x] Windows
- [x] Linux
- [x] Mac

# Examples

## The Hello World triangle

```py

# Create a window first

ctx = ModernGL.create_context()

prog = ctx.program([
	ctx.vertex_shader('''
		#version 330
		in vec2 vert;
		void main() {
			gl_Position = vec4(vert, 0.0, 1.0);
		}
	'''),
	ctx.fragment_shader('''
		#version 330
		out vec4 color;
		void main() {
			color = vec4(0.2, 0.6, 0.9, 1.0);
		}
	'''),
])

vbo = ctx.buffer(struct.pack('6f', 0, 0, 1, 0, 0, 1))
vao = ctx.simple_vertex_array(prog, vbo, ['vert'])

# Render

vao.render(ModernGL.TRIANGLES)

```

## Installing from source

Installing on **Ubuntu** from source:

```sh
apt-get install python3-dev libgl1-mesa-dev libx11-dev
python3 setup.py install
```

Installing on **Ubuntu** from source:

```sh
python3 setup.py install
```

## Building the shinx documentation

```sh
python3 -m pip install -r docs/requirements.txt
```

## Running tests

Some of the tests may be skipped when the supported OpenGL version is below the requirements of the given test. 

```sh
python3 -m pip pytest
```

## Code quality

Code is tested with [pep8], [flake8], [prospector] and [pylint]
Examples are tested with [pep8] only
