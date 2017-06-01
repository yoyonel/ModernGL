# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
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

### Changes
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

[Unreleased]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.2...master
[4.1.2]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.1...4.1.2
[4.1.1]: https://github.com/cprogrammer1994/ModernGL/compare/4.1.0...4.1.1
[4.1.0]: https://github.com/cprogrammer1994/ModernGL/compare/4.0.0...4.1.0
[4.0.0]: https://github.com/cprogrammer1994/ModernGL/tree/4.0.0
[3.1.5]: https://github.com/cprogrammer1994/ModernGL/compare/3.1.0...3.1.5
[3.1.0]: https://github.com/cprogrammer1994/ModernGL/tree/3.1.0
[2.4.1]: https://github.com/cprogrammer1994/ModernGL/tree/2.4.1
