import json, sys, shutil, os

if not os.path.isdir('Bin'):
	os.mkdir('Bin')

if not os.path.isdir('Temp'):
	os.mkdir('Temp')

dbg = "DEBUG" in sys.argv

gl = json.loads(open('OpenGL.json').read())

for func in gl['functions']:
	func['at'] = len(func['parameters']) * 4

longest = max(len(func['name']) for func in gl['functions'])
for func in gl['functions']:
	func['pad'] = ' ' * (longest - len(func['name']))

if 'asm' in sys.argv:
	dump = open('Temp\\OpenGL.asm', 'w')

	dump.write('global _LoadCoreGL\n')
	dump.write('\n')
	dump.write('extern _wglGetProcAuto\n')
	dump.write('extern _wglNotImplementedSafe\n')
	dump.write('extern _wglNotImplemented\n')
	dump.write('\n')

	for func in gl['functions']:
		dump.write('global _%(name)s@%(at)s\n' % func)

	dump.write('\n\n')
	dump.write('section .code\n\n')
	dump.write('_LoadCoreGL:\n')
	dump.write('\tsub esp, 4\n')
	dump.write('\n')

	for func in gl['functions']:
		dump.write('\tmov [esp], dword _Name_%(name)s\n' % func);
		dump.write('\tcall _wglGetProcAuto\n');
		dump.write('\tmov [_Func_%(name)s], eax\n\n' % func)

	dump.write('\n')
	dump.write('\tadd esp, 4\n')
	dump.write('\tmov eax, 1\n')
	dump.write('\tret\n\n')

	for func in gl['functions']:
		dump.write('_%(name)s@%(at)s:\n' % func)

		if dbg:
			dump.write('\tcmp dword [_Func_%(name)s], _wglNotImplemented\n' % func)
			dump.write('\tje .no_func\n')
			dump.write('\t\tjmp dword [_Func_%(name)s]\n' % func)
			dump.write('.no_func:\n')
			dump.write('\tpush dword _Name_%(name)s\n' % func)
			dump.write('\tcall _wglNotImplementedSafe\n')
			dump.write('\tadd esp, 4\n')
			dump.write('\tret\n\n')

		else:
			dump.write('\tjmp dword [_Func_%(name)s]\n\n' % func)

	dump.write('\n\n')
	dump.write('section .data\n\n')

	for func in gl['functions']:
		dump.write('\t_Name_%(name)s %(pad)s db "%(name)s", 0\n' % func)

	dump.write('\n\n')

	for func in gl['functions']:
		dump.write('\t_Func_%(name)s %(pad)s dd _wglNotImplemented\n' % func)

	dump.write('\n\n')
	dump.close()

if 'header' in sys.argv:
	dump = open('Temp\\OpenGL.h', 'w')

	head = '''
	#pragma once

	typedef char GLbyte;
	typedef char GLchar;
	typedef double GLclampd;
	typedef double GLdouble;
	typedef float GLclampf;
	typedef float GLfloat;
	typedef int * GLintptr;
	typedef int GLint;
	typedef int GLsizei;
	typedef long long int GLint64;
	typedef short GLshort;
	typedef struct __GLsync * GLsync;
	typedef int GLsizeiptr;
	typedef unsigned char GLboolean;
	typedef unsigned char GLubyte;
	typedef unsigned int GLbitfield;
	typedef unsigned int GLenum;
	typedef unsigned int GLuint;
	typedef unsigned long long int GLuint64;
	typedef unsigned short GLhalf;
	typedef unsigned short GLushort;
	typedef void GLvoid;

	typedef void (* GLDEBUGPROC) (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar * message, const void * userParam);
	'''

	dump.write(head.strip('\n') + '\n')
	dump.write('\n\n')

	const_type_pad = max(len(const['type']) for const in gl['constants'])
	const_name_pad = max(len(const['name']) for const in gl['constants'])
	for const in gl['constants']:
		const['tpad'] = ' ' * (const_type_pad - len(const['type']))
		const['npad'] = ' ' * (const_name_pad - len(const['name']))
		dump.write('const %(type)s %(tpad)s%(name)s%(npad)s = %(value)s;\n' % const)

	dump.write('\n\n')

	dump.write('extern "C" {\n')
	dump.write('\tbool Initialize();\n')

	for func in gl['functions']:
		params = ', '.join(param['type'] + ' ' + param['name'] for param in func['parameters'])
		dump.write('\t%(type)s __stdcall %(name)s' % func)
		dump.write('(%s);\n' % params)

	dump.write('}\n\n')

	dump.close()
