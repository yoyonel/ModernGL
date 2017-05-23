# Change Log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/)
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Added
- Exception handling when importing the implementation.
- Standalone context on linux with fallback mechanism.
- Require version at context creation.
- Context `version_code` property.
- Framebuffer `clear()` method.

### Changed
- Context `clear()` method accepts floats.

### Removed
- Required `-std=c++11` for linux and mac.

## Fixed
- `Framebuffer` and `Texture` can have uninitialized x, y values.
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

## 1.x.x - 2016-03-03
- It was a tool for me to develop games in python

[Unreleased]: https://github.com/cprogrammer1994/ModernGL/compare/4.0.0...master
[4.0.0]: https://github.com/cprogrammer1994/ModernGL/tree/4.0.0
[3.1.5]: https://github.com/cprogrammer1994/ModernGL/compare/3.1.0...3.1.5
[3.1.0]: https://github.com/cprogrammer1994/ModernGL/tree/3.1.0
[2.4.1]: https://github.com/cprogrammer1994/ModernGL/tree/2.4.1
