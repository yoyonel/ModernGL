# ModernGL

[![Chat](https://badges.gitter.im/cprogrammer1994/ModernGL.svg)](https://gitter.im/cprogrammer1994/ModernGL?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)<br>
[![PyPI](https://img.shields.io/pypi/l/ModernGL.svg)](https://pypi.python.org/pypi/ModernGL)
[![PyPI](https://img.shields.io/pypi/pyversions/ModernGL.svg)](https://pypi.python.org/pypi/ModernGL)
[![PyPI](https://img.shields.io/pypi/v/ModernGL.svg)](https://pypi.python.org/pypi/ModernGL)
[![github](https://img.shields.io/github/tag/cprogrammer1994/ModernGL.svg)](https://github.com/cprogrammer1994/ModernGL)<br>
[![PyPI](https://img.shields.io/pypi/status/ModernGL.svg)](https://pypi.python.org/pypi/ModernGL)
[![PyPI](https://img.shields.io/pypi/dm/ModernGL.svg)](https://pypi.python.org/pypi/ModernGL)

```
python -m pip install ModernGL
```

## Description

OpenGL is a great environment for developing portable, platform independent,
interactive 2D and 3D graphics applications. The API implementation in Python
is cumbersome, resulting in applications with high latency. To solve this
problem we have developed ModernGL, a wrapper over OpenGL that simplifies the
creation of simple graphics applications like scientific simulations, small
games or user interfaces. Usually, acquiring in-depth knowledge of OpenGL
requires a steep learning curve. In contrast, ModernGL is easy to learn and
use, moreover it is capable of rendering with the same performance and
quality, with less code written.

## Links

[Examples](https://github.com/cprogrammer1994/ModernGL/tree/master/Examples)<br>
[Documentation](https://pythonhosted.org/ModernGL/)<br>
[Questions](https://gitter.im/cprogrammer1994/ModernGL)<br>
[PyPI](https://pypi.python.org/pypi/ModernGL/)<br>
[Github Repository](https://github.com/cprogrammer1994/ModernGL/)<br>
[Github Page](http://cprogrammer1994.github.io/ModernGL/)<br>
[Github Docs](https://github.com/cprogrammer1994/ModernGL/wiki)<br>

# Patches are welcome

# Documentation (deprecated until a stable release)

Please follow the [Documentation](https://pythonhosted.org/ModernGL/).

# Examples

Please follow the [Examples](https://github.com/cprogrammer1994/ModernGL/tree/master/Examples).

# Linux Support

## since ModernGL 2.2.0

tested on Ubuntu 16.04

![Ubuntu](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Images/Ubuntu.png)

```
apt-get install python3-dev
apt-get install libgl1-mesa-dev
```

# Supported Versions

![OpenGL-3.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-33.png)
![OpenGL-4.0](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-40.png)
![OpenGL-4.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-41.png)
![OpenGL-4.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-42.png)
![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-43.png)
![OpenGL-4.4](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-44.png)
![OpenGL-4.5](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-45.png)

Checkout the [OpenGL Registry](https://www.opengl.org/registry/) for core specifications.

## minimum OpenGL support per method

Method | Version
--- | ---
BuildMipmap | 3.1
Clear | 3.1
DeleteComputeShader | 3.1
DeleteFramebuffer | 3.1
DeleteIndexBuffer | 3.1
DeleteProgram | 3.1
DeleteShader | 3.1
DeleteStorageBuffer | 3.1
DeleteTexture | 3.1
DeleteUniformBuffer | 3.1
DeleteVertexArray | 3.1
DeleteVertexBuffer | 3.1
DisableAttributes | 3.1
DisableBlend | 3.1
DisableCullFace | 3.1
DisableDepthTest | 3.1
DisableMultisample | 3.1
EnableAttributes | 3.1
EnableBlend | 3.1
EnableCullFace | 3.1
EnableDepthTest | 3.1
EnableMultisample | 3.1
EnableOnly | 3.1
ExtensionActive | 3.1
GetDefaultFramebuffer | 3.1
GetInfo | 3.1
InitializeModernGL | 3.1
LineSize | 3.1
NewAdvancedVertexArray | 3.1
NewComputeShader | 4.3
NewFragmentShader | 3.1
NewFramebuffer | 3.1
NewGeometryShader | 3.2
NewIndexBuffer | 3.1
NewProgram | 3.1
NewStorageBuffer | 4.3
NewTessControlShader | 4.0
NewTessEvaluationShader | 4.0
NewTexture | 3.1
NewUniformBuffer | 3.1
NewVertexArray | 3.1
NewVertexBuffer | 3.1
NewVertexShader | 3.1
PointSize | 3.1
ReadDepthPixel | 3.1
ReadDepthPixels | 3.1
ReadPixel | 3.1
ReadPixels | 3.1
ReadStorageBuffer | 4.3
RenderLineLoop | 3.1
RenderLineStrip | 3.1
RenderLineStripAdjacency | 3.2
RenderLines | 3.1
RenderLinesAdjacency | 3.2
RenderPoints | 3.1
RenderTriangleFan | 3.1
RenderTriangleStrip | 3.1
RenderTriangleStripAdjacency | 3.2
RenderTriangles | 3.1
RenderTrianglesAdjacency | 3.2
RunComputeShader | 4.3
SetTextureFiltered | 3.1
SetTextureMipmapped | 3.1
SetTexturePixelated | 3.1
Uniform1f | 3.1
Uniform1i | 3.1
Uniform2f | 3.1
Uniform2i | 3.1
Uniform3f | 3.1
Uniform3i | 3.1
Uniform4f | 3.1
Uniform4i | 3.1
UniformMatrix | 3.1
UpdateIndexBuffer | 3.1
UpdateStorageBuffer | 4.3
UpdateTexture | 3.1
UpdateUniformBuffer | 3.1
UpdateVertexBuffer | 3.1
UseDefaultFramebuffer | 3.1
UseFramebuffer | 3.1
UseStorageBuffer | 4.3
UseTexture | 3.1
UseTextureAsImage | 4.2
UseUniformBuffer | 3.1
Viewport | 3.1