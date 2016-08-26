# ChangeLog

# 2.4.0

- Removed UseDefaultFramebuffer method.
- Removed SetDefaultFramebuffer method.
- Added SCREEN constant. `UseFramebuffer(SCREEN)`
- Framebuffer instantiation is allowed. `Framebuffer(2) # QT`

## Still missing

- NewProgram will return a single program object.
- Program objects will implement the `[]` operator.
- Transform methods have no docs.
- NewAdvancedVertexArray is not properly implemented.

# 2.3.1

- Framebuffer and Texture improvments
- UpdateTexture optional x y width height parameters
- Renamed BuildMipmap to BuildMipmaps
- Renamed InitializeModernGL to Init
- Added padding and double format to VertexArray
- Added Transform feedback methods
- Removed strict parameter from NewVertexArray
- NewVertexArray supports keyword arguments
- Added error message to DebugInfo

# 2.3.0

The version 2.3.0 is stable, all the changes made after this tag will be mentioned here.
