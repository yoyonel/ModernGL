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

With the original OpenGL API you have to write a couple of lines to achieve a simple task like compiling a shader or running a computation on the GPU. With ModernGL you will need just a few lines to achieve the same result.

## Is ModernGL faster then PyOpenGL?

In some cases **yes**, the core functions of ModernGL are written in C++, OpenGL functions are called in quick succession so these calls together count as a single python function call.

## What version of OpenGL is used?

Most of the calls only require OpenGL 3.3 but Subroutines and Compute Shaders require OpenGL 4.0 and 4.3

## Is my old PC supports this?

OpenGL 3.3 came out in February 2010. With **up to date drivers** you will be able to use the most of the ModernGL functions, even on integrated graphics cards. _(No compute shaders won't work)_

## How can I install ModernGL?

```
pip install ModernGL
```

## How can I start using ModernGL?

Take a look at the [examples](https://https://github.com/cprogrammer1994/ModernGL/examples) and [docs](https://moderngl.readthedocs.io/)

## Where can I use ModernGL?

Anywhere where OpenGL is supported. ModernGL is capable of rendering using a [standalone_context](). Rendering to a window only requires a valid OpenGL context.

## An example with [source](https://moderngl.github.io/Examples/julia_fractal.html)

![Julia Fractal](https://moderngl.github.io/_images/julia_fractal.png)

## A short sample

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

## How to install

Installing on **Ubuntu** from source:
```
apt-get install python3-dev libgl1-mesa-dev libx11-dev
python3 setup.py install
```

...
