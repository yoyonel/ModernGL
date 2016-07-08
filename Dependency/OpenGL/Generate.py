import json, os, textwrap

gl = json.loads(open('OpenGL.json').read())

# if subset:
# 	subset = set(open(subset).read().split())
# 	gl['functions'] = list(filter(lambda x: x['name'] in subset, gl['functions']))
# 	gl['constants'] = list(filter(lambda x: x['name'] in subset, gl['constants']))

func_name_pad = max(len(func['name']) for func in gl['functions'])
const_type_pad = max(len(const['type']) for const in gl['constants'])
const_name_pad = max(len(const['name']) for const in gl['constants'])

for func in gl['functions']:
	func['name_pad'] = ' ' * (func_name_pad - len(func['name']))
	func['params'] = ', '.join(param['type'] + ' ' + param['name'] for param in func['parameters'])

for const in gl['constants']:
	const['type_pad'] = ' ' * (const_type_pad - len(const['type']))
	const['name_pad'] = ' ' * (const_name_pad - len(const['name']))

template = dict((name, open('Template/' + name).read()) for name in os.listdir('Template/'))

def fill(foo, iterable, tabs = 0):
	lines = '\n'.join(template[foo] % obj for obj in iterable)
	return textwrap.indent(lines, '\t' * tabs)

header_context = {
	'constants' : fill('Constant.template', gl['constants'], 1),
	'function_types' : fill('FunctionType.template', gl['functions'], 1),
	'function_exports' : fill('FunctionExport.template', gl['functions'], 1),
	'function_export_checks' : fill('FunctionExportCheck.template', gl['functions'], 1),
}

core_context = {
	'function_declare' : fill('FunctionDeclare.template', gl['functions'], 1),
	'function_check' : fill('FunctionCheck.template', gl['functions'], 1),
	'function_load' : fill('FunctionLoad.template', gl['functions'], 2),
}

if not os.path.isdir('Temp'):
	os.mkdir('Temp')

open('Temp/OpenGL.hpp', 'w').write(template['OpenGL.hpp.template'] % header_context)
open('Temp/OpenGL.cpp', 'w').write(template['OpenGL.cpp.template'] % core_context)