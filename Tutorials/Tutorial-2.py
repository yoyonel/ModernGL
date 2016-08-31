import ModernGL as GL
import GLWindow as WND
import struct

WND.Init()

# Initialize ModernGL after creating an OpenGL context is created
# ModernGL.Init() cannot precede the context creation

GL.Init()
print('ModernGL Initialized successfully!')
