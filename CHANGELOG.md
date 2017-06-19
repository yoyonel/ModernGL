# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Removed
- Unused texture's `read` method's `viewport` parameter

### Fixed
- Broken framebuffer `color_attachments` attribute
- Sigsev when creating a texture using string data by mistake

## [4.1.7] - 2017-06-13
### Added
- Uniform `read` and `write` methods
- `write_offset` parameter for the `read_into` methods
- Read framebuffer's pixels to a buffer
- Read texture's pixels to a buffer
- Write texture's from a buffer
- Pixel Buffer Object

### Fixed
- Default framebuffer wrong drawbuffers
- Framebuffer non zero viewport settings
- Uniform setter error messages

## [4.1.6] - 2017-06-12
### Fixed
- Broken uniform setter in 4.1.5

## [4.1.5] - 2017-06-09
### Fixed
- Modifying framebuffer properties has no effect unless the framebuffer is explicitly bound

## [4.1.4] - 2017-06-07
### Added
- Framebuffer `color_mask` attribute
- Framebuffer `depth_mask` attribute
- Framebuffer `viewport` attribute

### Fixed
- `copy_framebuffer` using `default_framebuffer`
- Failing `__repr__` in VertexArrays

### Changed
- Framebuffer methods do not affect the bound framebuffer

### Removed
- Invalid texture sampling parameters for multisample textures
- Invalid texture sampling parameters for depth textures

## [4.1.3] - 2017-06-04
### Added
- TextureFilter and TextureWrap classes and constants
- Texture `build_mipmaps` method
- Texture `repeat_x`, `repeat_y` and `filter` attributes
- Texture `swizzle` getter

## [4.1.2] - 2017-05-31
### Added
- Read any color attachments of the Framebuffer
-  Framebuffer, Buffer, BufferAccess and Texture `read_into` method
- `__slots__` for ModernGL classes
- Framebuffer read different color attachments
- Tkinter connector for windows using ctypes

### Fixed
- Multiple render targets
- Non-float renderbuffers are not readable
- Buffer `read` keyword only `offset` argument

### Changed
- `Context.renderbuffer` will use `floats=False` by default
- `bind_to_uniform_block` `location` parameter was renamed to `binding`
- `bind_to_storage_buffer` `location` parameter was renamed to `binding`

## [4.1.1] - 2017-05-27
### Added
- UniformBlock `binding` and `size` attribute
- Framebuffer `width`, `height` and `samples` attribute
- Texture `swizzle` attribute
- Context `error` attribute
- OpenGL objects as `glo` attributes
- Buffer `clear()` method
- Missing `release()` methods
- Iterable program member maps
- Human readable program members
- Pixel pack and unpack alignments
- Subroutines

### Removed
- UniformBlock `array_size` and `location` attribute
- VertexArrayAttribute `default` attribute

### Fixed
- BufferAccess unused `offset` parameter
- Binding buffer to a UniformBlock
- Broken RTD docs

## [4.1.0] - 2017-05-24
### Added
- Exception handling when importing the implementation
- Standalone context on **linux** and **mac** with fallback mechanism
- Require version at context creation
- Context `version_code` property
- Framebuffer `clear()` method

### Changed
- Context `clear()` method accepts floats

### Removed
- Required `-std=c++11` for **linux** and **mac**
- ModernGL `VERSION` constant

## Fixed
- `Framebuffer` and `Texture` can have uninitialized x, y values
- Uniform setters

## [4.0.0] - 2017-05-20
### Added
- Full linting support
- Restructure docs
- Examples in docs
- pep8 style
- VSCode snippets
- Changelog

### Changed
- Wrap the C/C++ module with a pure python module
- Rename internal module to avoid ambiguosity
- Rename class like members from the Context class

## [3.1.5] - 2017-05-07
### Added
- Standalone ModernGL context
- Sphinx generated docs
- Linting with pylint mock file
- Mac OSX support

## [3.1.0] - 2017-03-01
### Added
- Wrapping OpenGL objects with python types

### Changed
- Improved Linux support

### Removed
- Direct access to OpenGL objects

## [2.4.1] - 2016-08-30
### Added
- setup.py and PyPI compatible packaging
- Direct access to OpenGL objects
- Linux support

## 1.0.0 - 2016-03-03
- It was a tool for me to develop games in python

[Unreleased]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.7...master
[4.1.7]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.6...4.1.7
[4.1.6]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.5...4.1.6
[4.1.5]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.4...4.1.5
[4.1.4]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.3...4.1.4
[4.1.3]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.2...4.1.3
[4.1.2]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.1...4.1.2
[4.1.1]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.0...4.1.1
[4.1.0]: https://github.com/cprogrammer1994/ModernGL/compare/4.0.0...4.1.0
[4.0.0]: https://github.com/cprogrammer1994/ModernGL/tree/4.0.0
[3.1.5]: https://github.com/cprogrammer1994/ModernGL/compare/3.1.0...3.1.5
[3.1.0]: https://github.com/cprogrammer1994/ModernGL/tree/3.1.0
[2.4.1]: https://github.com/cprogrammer1994/ModernGL/tree/2.4.1
