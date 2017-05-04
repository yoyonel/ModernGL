from setuptools import setup, Extension
import os, platform

target = platform.system().lower()

if target == 'linux':
	from distutils import sysconfig
	sysconfig._config_vars['OPT'] = sysconfig.get_config_vars()['OPT'].replace('-Wstrict-prototypes', '')

libraries = {
	'windows': ['gdi32', 'opengl32', 'user32'],
	'linux': ['GL', 'dl', 'X11'],
}

extra_args = {
	'windows': [],
	'linux': ['-std=c++11'],
}

def sources():
	for path, folders, files in os.walk('src'):
		for f in files:
			if f.endswith('.cpp'):
				yield os.path.join(path, f)

ModernGL = Extension(
	name = 'ModernGL.ModernGL',
	include_dirs = ['src'],
	# define_macros = [('MGL_VERBOSE', '1')],
	libraries = libraries[target],
	extra_compile_args = extra_args[target],
	sources = list(sources()),
)

short_description = 'ModernGL: Rendering made easy'

long_description = '''
'''

keywords = [
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
	'GLSL',
	'GPU',
	'GPGPU',
	'nvidia',
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
	'design',
	'video',
]

classifiers = [
	'Development Status :: 5 - Production/Stable',
	'Environment :: Win32 (MS Windows)',
	'Environment :: X11 Applications',
	'Environment :: X11 Applications :: Gnome',
	'Environment :: X11 Applications :: GTK',
	'Environment :: X11 Applications :: KDE',
	'Environment :: X11 Applications :: Qt',
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
	'Operating System :: OS Independent',
	'Operating System :: POSIX',
	'Operating System :: POSIX :: Linux',
	'Operating System :: Unix',
	'Programming Language :: C',
	'Programming Language :: C++',
	'Programming Language :: Cython',
	'Programming Language :: Python',
	'Programming Language :: Python :: 3',
	'Programming Language :: Python :: 3.4',
	'Programming Language :: Python :: 3.5',
	'Programming Language :: Python :: 3.6',
	'Programming Language :: Python :: 3 :: Only',
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

args = {
	'name' : 'ModernGL',
	'version' : '3.1.5',
	'description' : short_description,
	'long_description' : long_description.strip(),
	'url' : 'https://github.com/cprogrammer1994/ModernGL',
	'download_url' : 'https://github.com/cprogrammer1994/ModernGL/releases',
	'author' : 'Szabolcs Dombi',
	'author_email' : 'cprogrammer1994@gmail.com',
	'license' : 'MIT',
	'classifiers' : classifiers,
	'keywords' : keywords,
	'packages' : ['ModernGL'],
	'ext_modules' : [ModernGL],
	'platforms' : ['any'],
}

if target == 'windows':
	args['zip_safe'] = False

setup(**args)
