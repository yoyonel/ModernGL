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
BuildMipmap | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Clear | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteComputeShader | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteFramebuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteIndexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteProgram | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteShader | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteStorageBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteTexture | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteUniformBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteVertexArray | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DeleteVertexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DisableAttributes | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DisableBlend | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DisableCullFace | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DisableDepthTest | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
DisableMultisample | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableAttributes | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableBlend | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableCullFace | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableDepthTest | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableMultisample | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
EnableOnly | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ExtensionActive | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
GetDefaultFramebuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
GetInfo | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
InitializeModernGL | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
LineSize | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewAdvancedVertexArray | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewComputeShader | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
NewFragmentShader | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewFramebuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewGeometryShader | ![OpenGL-3.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.2.png)
NewIndexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewProgram | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewStorageBuffer | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
NewTessControlShader | ![OpenGL-4.0](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.0.png)
NewTessEvaluationShader | ![OpenGL-4.0](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.0.png)
NewTexture | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewUniformBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewVertexArray | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewVertexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
NewVertexShader | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
PointSize | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ReadDepthPixel | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ReadDepthPixels | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ReadPixel | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ReadPixels | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
ReadStorageBuffer | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
RenderLineLoop | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderLineStrip | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderLineStripAdjacency | ![OpenGL-3.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.2.png)
RenderLines | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderLinesAdjacency | ![OpenGL-3.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.2.png)
RenderPoints | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderTriangleFan | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderTriangleStrip | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderTriangleStripAdjacency | ![OpenGL-3.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.2.png)
RenderTriangles | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
RenderTrianglesAdjacency | ![OpenGL-3.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.2.png)
RunComputeShader | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
SetTextureFiltered | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
SetTextureMipmapped | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
SetTexturePixelated | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform1f | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform1i | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform2f | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform2i | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform3f | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform3i | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform4f | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Uniform4i | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UniformMatrix | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UpdateIndexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UpdateStorageBuffer | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
UpdateTexture | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UpdateUniformBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UpdateVertexBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UseDefaultFramebuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UseFramebuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UseStorageBuffer | ![OpenGL-4.3](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.3.png)
UseTexture | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
UseTextureAsImage | ![OpenGL-4.2](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-4.2.png)
UseUniformBuffer | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)
Viewport | ![OpenGL-3.1](https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/External/Badges/OpenGL-3.1.png)