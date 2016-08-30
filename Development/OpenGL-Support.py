import json, os, re

gl = json.loads(open('Dependency/OpenGL/OpenGL.json').read())

version = {}

for obj in gl['constants']:
	version[obj['name']] = obj['version']

for obj in gl['functions']:
	version[obj['name']] = obj['version']

funcs = {}

for path, folders, files in os.walk('../Source'):
	for f in files:
		if f.startswith('OpenGL'):
			continue

		func = None
		lines = open(os.path.join(path, f)).read().splitlines()
		for line in lines:
			if not func:
				m = re.match(r'^PyObject \* ([A-Z][A-Za-z0-9]+)\(PyObject \* self[^\{]+\{$', line)
				if m:
					func = m.group(1)
					content = ''
			else:
				if line.startswith('}'):
					funcs[func] = content
					func = None

				else:
					content += line + '\n'

support = {}

pattern = re.compile(r'\b(gl[A-Z][A-Za-z0-9_]+|GL_[A-Z0-9_]+)\b')
for func, content in funcs.items():
	versions = [version[node.group(1)] for node in pattern.finditer(content)]
	support[func] = max(versions) if versions else '0.0'

for func in support:
	support[func] = max(support[func], support['Init'])

lst = sorted([(func, support[func]) for func in support])

def img(version):
	return 'https://raw.githubusercontent.com/cprogrammer1994/ModernGL/master/docs/Images/Badges/OpenGL-%s%s.png' % (version[0], version[2])

print('%s | %s' % ('Method', 'Version', ))
print('--- | ---')
for func, version in lst:
	print('%s | ![OpenGL-%s](%s)' % (func, version, img(version)))
