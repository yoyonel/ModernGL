try:
	import cccompiler
except ImportError:
	pass

try:
	from setuptools import setup, Extension

except ImportError:
	from distutils.core import setup
	from distutils.extension import Extension

ShortDescription = 'modern OpenGL binding for Python'

LongDescription = '''
OpenGL is a great environment for developing portable, platform independent,
interactive 2D and 3D graphics applications. The API implementation in Python
is cumbersome, resulting in applications with high latency. To solve this
problem we have developed ModernGL, a wrapper over OpenGL that simplifies the
creation of simple graphics applications like scientific simulations, small
games or user interfaces. Usually, acquiring in-depth knowledge of OpenGL
requires a steep learning curve. In contrast, ModernGL is easy to learn and
use, moreover it is capable of rendering with the same performance and
quality, with less code written.
'''

Classifiers = [
	'Development Status :: 4 - Beta',
#	'Development Status :: 5 - Production/Stable',
#	'Development Status :: 6 - Mature',
	'Environment :: Win32 (MS Windows)',
	'Intended Audience :: Developers',
	'Intended Audience :: Education',
	'License :: Freely Distributable',
	'License :: Free For Educational Use',
	'License :: Free For Home Use',
	'License :: Freeware',
	'License :: OSI Approved',
	'License :: OSI Approved :: MIT License',
	'Natural Language :: English',
	'Operating System :: Microsoft',
	'Operating System :: Microsoft :: Windows',
	'Operating System :: Microsoft :: Windows :: Windows 7',
	'Operating System :: Microsoft :: Windows :: Windows 95/98/2000',
	'Operating System :: Microsoft :: Windows :: Windows CE',
	'Operating System :: Microsoft :: Windows :: Windows NT/2000',
	'Operating System :: Microsoft :: Windows :: Windows Server 2003',
	'Operating System :: Microsoft :: Windows :: Windows Server 2008',
	'Operating System :: Microsoft :: Windows :: Windows Vista',
	'Operating System :: Microsoft :: Windows :: Windows XP',
#	'Operating System :: OS Independent',
#	'Operating System :: POSIX',
#	'Operating System :: POSIX :: Linux',
#	'Operating System :: Unix',
	'Programming Language :: C',
	'Programming Language :: C++',
	'Programming Language :: Cython',
	'Programming Language :: Python',
	'Programming Language :: Python :: 2.7',
	'Programming Language :: Python :: 3.3',
	'Programming Language :: Python :: 3.4',
	'Programming Language :: Python :: 3.5',
	'Programming Language :: Python :: 3.6',
	'Topic :: Documentation',
	'Topic :: Desktop Environment',
	'Topic :: Education',
	'Topic :: Games/Entertainment',
	'Topic :: Multimedia',
	'Topic :: Multimedia :: Graphics',
	'Topic :: Multimedia :: Graphics :: 3D Modeling',
	'Topic :: Multimedia :: Graphics :: 3D Rendering',
	'Topic :: Multimedia :: Video',
	'Topic :: Scientific/Engineering :: Visualization',
	'Topic :: Software Development',
	'Topic :: Software Development :: Documentation',
	'Topic :: Software Development :: Libraries :: Python Modules',
	'Topic :: System :: Monitoring',
	'Topic :: Utilities',
]

Keywords = [
	'ModernGL',
	'modern OpenGL',
	'OpenGL',
	'visualization',
	'ray-tracing',
	'compute shader',
	'shader',
	'documentation',
	'documented',
	'graphics',
	'vulkan',
	'GLSL',
	'GPU',
	'GPGPU',
	'nvidia',
	'cuda',
	'amd',
	'GL',
	'GLU',
	'GLEXT',
	'WGL',
	'WGLEXT',
	'ARB',
	'GLX',
	'2D',
	'3D',
	'CAD',
	'glm',
	'design',
	'video',
]

ModernGL = Extension(
	'ModernGL.ModernGL',
	libraries = ['user32', 'gdi32'],
	sources = [
		'Source/WindowsGL.cpp',
		'Source/OpenGL.cpp',
		'Source/ModernGL.cpp',
		'Source/Python-ModernGL.cpp',
	]
)

setup(
	name = 'ModernGL',
	version = '2.0.10',
	description = ShortDescription,
	long_description = LongDescription,
	url = 'https://github.com/cprogrammer1994/ModernGL',
	author = 'Szabolcs Dombi',
	author_email = 'cprogrammer1994@gmail.com',
	license = 'MIT',
	classifiers = Classifiers,
	keywords = Keywords,
	packages = ['ModernGL'],
	ext_modules = [ModernGL],
	platforms = ['win32', 'win64'],
	zip_safe = True,
)
