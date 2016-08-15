import ModernGL as GL
import GLWindow as WND
import struct

WND.InitializeWindow()
WND.BuildFullscreen()

GL.InitializeModernGL()

# Repeat until the window is destroyed
# The window can be destroyed by pressing ALT+F4 as usual
# The Update() function will call the SwapBuffers() function
while WND.Update():
	# Clear the background with RGB(240, 240, 240)
	GL.Clear(240, 240, 240)
