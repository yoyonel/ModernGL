# ModernGL Examples

Before running examples make sure you install the requirements:

```bash
pip install -r examples/requirements.txt
```

## Running Examples

All examples should use [moderngl_window] to make window creation and resource loading as simple
as possible and ensures all supported platforms and covered.

**Examples should work out of the box on Windows, Linux and OS X.**

## Options

```
optional arguments:
  -h, --help            show this help message and exit
  -w {pyglet,pyside2,glfw,sdl2,pyqt5}, --window {glfw,pyglet,pyqt5,sdl2}
                        Name for the window type to use
  -fs, --fullscreen     Open the window in fullscreen mode
  -vs VSYNC, --vsync VSYNC
                        Enable or disable vsync
  -s SAMPLES, --samples SAMPLES
                        Specify the desired number of samples to use for
                        multisampling
  -c CURSOR, --cursor CURSOR
                        Enable or disable displaying the mouse cursor
```

For example:

```bash
# Run example in fullscreen with 8 x MSAA, vsync and no visible mouse cursor
python 03_alpha_blending.py --fullscreen --samples 8 --cursor off --vsync on

# Run example using pygame
python 03_alpha_blending.py --window pyglet

# Run example using SDL2
python 03_alpha_blending.py --window sdl2

# Run example using PySide2
python 03_alpha_blending.py --window pyside2

# Run example using PySide2
python 03_alpha_blending.py --window pyqt5

# Run example using glfw
python 03_alpha_blending.py --window glfw

# Run example using tkinter
python 03_alpha_blending.py --window pyglet
```

## Other Examples

The examples directory also contains a **large amount of examples** contributed
by various people over time. Browse around and see what you can find :)

## Old examples

Also see the [old examples](old-examples).


[moderngl_window]: (https://github.com/moderngl/moderngl-window)
