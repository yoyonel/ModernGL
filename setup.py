from setuptools import setup, Extension
import os

def sources():
	for path, folders, files in os.walk('src'):
		for f in files:
			if f.endswith('.cpp'):
				yield os.path.join(path, f)

ModernGL = Extension(
	name = 'ModernGL.ModernGL',
	include_dirs = ['src'],
	libraries = ['gdi32', 'opengl32', 'user32'],
	sources = list(sources()),
)

setup(
	name = 'ModernGL-beta',
	version = '3.1.0',
	packages = ['ModernGL'],
	ext_modules = [ModernGL],
)
