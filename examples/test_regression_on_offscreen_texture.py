#!/usr/bin/python3 -B
"""

"""
import numpy as np  # pip install numpy
import moderngl as gl  # pip install moderngl
import pygame  # pip install pygame


def main():
    winsize = (4, 4)
    pygame.display.init()
    pygame.display.set_mode(winsize, pygame.OPENGL)
    ctx = gl.create_context()
    offscreen = ctx.simple_framebuffer(winsize, components=2, dtype='f1')
    offscreen.use()
    ctx.screen.use()
    ctx.clear(0.50, 0.50, 0.50, 1.0)
    pixels = ctx.screen.read(winsize, components=3, dtype='f1')
    pixels = np.frombuffer(pixels, dtype=np.uint8).reshape(4, 4, 3)
    print("EXPECTED: [127 127 127]")
    print("ACTUAL  :", pixels[0, 0])
    assert (np.all(pixels[0, 0] == [127, 127, 127]))


if __name__ == "__main__":
    main()
