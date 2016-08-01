# import neccessary modules

# ModernGL will do the rendering
import ModernGL as GL

# GLWindow will create a window with a valid OpenGL context
import GLWindow as WND

# We will ned the struct module to create data for buffers
import struct

# InitializeWindow() will only initialize the GLWindow module
# The InitializeWindow() does not create a window or any OpenGL contextes
WND.InitializeWindow()

# We will need a window
# The window will have an OpenGL context
WND.BuildFullscreen()
