import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

# Initialize ModernGL after creating an OpenGL context
# Remember: BuildFullscreen() will create a window and an OpenGL context
# InitializeModernGL() cannot precede the context creation

GL.InitializeModernGL()
print('ModernGL Initialized successfully!')
