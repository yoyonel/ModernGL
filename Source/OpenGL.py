import json, sys, shutil, os

header_file = '''
#pragma once

#ifdef _WIN64
	typedef long long int GLsizeiptr;
	typedef long long int GLintptr;
#else
	typedef int GLsizeiptr;
	typedef int GLintptr;
#endif 

typedef char GLbyte;
typedef char GLchar;
typedef double GLclampd;
typedef double GLdouble;
typedef float GLclampf;
typedef float GLfloat;
typedef int GLint;
typedef int GLsizei;
typedef long long int GLint64;
typedef short GLshort;
typedef struct __GLsync * GLsync;
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

%(const)s

bool __stdcall Initialize() asm("_Initialize");

%(func)s
'''

asm_file_32 = '''
global _LoadCoreGL

extern _GetProcAuto
extern _NotImplemented

%(func_def)s

section .code

_LoadCoreGL:
	sub esp, 4

%(func_load)s

	add esp, 4
	mov eax, 1
	ret

%(func_decl)s

section .data

%(func_ptr)s

%(func_name)s
'''

asm_file_64 = '''
global _LoadCoreGL

extern _GetProcAuto
extern _NotImplemented

%(func_def)s

section .code

_LoadCoreGL:
	push rbp
	mov rbp, rsp
	sub rsp, 32

%(func_load)s

	add rsp, 32
	mov rax, 1
	pop rbp
	ret

%(func_decl)s

section .data

%(func_ptr)s

%(func_name)s
'''

header_const = '''
const %(type)s %(type_pad)s%(name)s%(name_pad)s = %(value)s;
'''

header_func = '''
%(type)s __stdcall %(name)s(%(params)s) asm("_%(name)s");
'''

asm_func_def_32 = '''
global _%(name)s
'''

asm_func_load_32 = '''
	mov dword [esp], _Name_%(name)s
	call _GetProcAuto
	mov [_Func_%(name)s], eax
'''

asm_func_decl_32 = '''
_%(name)s:
	jmp dword [_Func_%(name)s]
'''

asm_func_ptr_32 = '''
	_Func_%(name)s %(pad)s dd _NotImplemented
'''

asm_func_name_32 = '''
	_Name_%(name)s %(pad)s db "%(name)s", 0
'''

asm_func_def_64 = '''
global _%(name)s
'''

asm_func_load_64 = '''
	mov rcx, _Name_%(name)s
	call _GetProcAuto
	mov [_Func_%(name)s], rax
'''

asm_func_decl_64 = '''
_%(name)s:
	jmp qword [_Func_%(name)s]
'''

asm_func_ptr_64 = '''
	_Func_%(name)s %(pad)s dq _NotImplemented
'''

asm_func_name_64 = '''
	_Name_%(name)s %(pad)s db "%(name)s", 0
'''

gl = json.loads(open('Data\\OpenGL.json').read())

func_name_pad = max(len(func['name']) for func in gl['functions'])

for func in gl['functions']:
	func['pad'] = ' ' * (func_name_pad - len(func['name']))
	func['params'] = ', '.join(param['type'] + ' ' + param['name'] for param in func['parameters'])

const_type_pad = max(len(const['type']) for const in gl['constants'])
const_name_pad = max(len(const['name']) for const in gl['constants'])

for const in gl['constants']:
	const['type_pad'] = ' ' * (const_type_pad - len(const['type']))
	const['name_pad'] = ' ' * (const_name_pad - len(const['name']))

if 'asm32' in sys.argv:
	dump = open('Temp\\OpenGL32.asm', 'w')

	context = {
		'func_def' : '\n'.join(asm_func_def_32.strip('\n') % f for f in gl['functions']),
		'func_load' : '\n\n'.join(asm_func_load_32.strip('\n') % f for f in gl['functions']),
		'func_decl' : '\n\n'.join(asm_func_decl_32.strip('\n') % f for f in gl['functions']),
		'func_ptr' : '\n'.join(asm_func_ptr_32.strip('\n') % f for f in gl['functions']),
		'func_name' : '\n'.join(asm_func_name_32.strip('\n') % f for f in gl['functions']),
	}

	dump.write(asm_file_32.strip('\n') % context)
	dump.close()

if 'asm64' in sys.argv:
	dump = open('Temp\\OpenGL64.asm', 'w')

	context = {
		'func_def' : '\n'.join(asm_func_def_64.strip('\n') % f for f in gl['functions']),
		'func_load' : '\n\n'.join(asm_func_load_64.strip('\n') % f for f in gl['functions']),
		'func_decl' : '\n\n'.join(asm_func_decl_64.strip('\n') % f for f in gl['functions']),
		'func_ptr' : '\n'.join(asm_func_ptr_64.strip('\n') % f for f in gl['functions']),
		'func_name' : '\n'.join(asm_func_name_64.strip('\n') % f for f in gl['functions']),
	}

	dump.write(asm_file_64.strip('\n') % context)
	dump.close()

if 'header' in sys.argv:
	dump = open('Temp\\OpenGL.h', 'w')

	context = {
		'const' : '\n'.join(header_const.strip('\n') % c for c in gl['constants']),
		'func' : '\n'.join(header_func.strip('\n') % f for f in gl['functions']),
	}

	dump.write(header_file.strip('\n') % context)
	dump.close()
