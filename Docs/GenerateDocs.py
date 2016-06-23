import ModernGL as GL
import os, shutil, re, textwrap, html

pycode = open('../Source/Python-ModernGL.cpp').read()
ccode = open('../Source/ModernGL.cpp').read()

def func_with_name(func):
	idx = ccode.find(' %s(' % func)
	start = idx
	while ccode[start] != '\n':
		start -= 1

	par = 0
	end = idx
	while ccode[end] != '}' or par != 1:
		if ccode[end] == '{':
			par += 1
		if ccode[end] == '}':
			par -= 1
		end += 1

	return textwrap.dedent(ccode[start + 1: end + 1].replace('OpenGL::', ''))

# print(func_with_name('InitializeModernGL'))

# exit()

func = open('FunctionTemplate.html').read()
const = open('ConstantTemplate.html').read()

if not os.path.isdir('Generated'):
	os.mkdir('Generated')

objs = sorted([x for x in dir(GL) if not x.startswith('__') and x != 'ModernGL'])

for x in objs:
	if type(GL.__dict__[x]) is int:
		form = {
			'name' : x,
			'value' : str(GL.__dict__[x]),
		}
		open('Generated/%s.html' % x, 'w').write(const.format_map(form))

	else:
		form = {
			'name' : x,
			'docs' : str(GL.__dict__[x].__doc__),
			'implementation' : html.escape(func_with_name(x)),
			'function': '',
			'similar' : '',
		}
		open('Generated/%s.html' % x, 'w').write(func.format_map(form))

index = open('Generated/index.html', 'w')
index.write('<ul>')

index.write('''
<!DOCTYPE html>
<html>
<head>
	<title>ModernGL</title>
	<link rel="stylesheet" type="text/css" href="../bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="../bootstrap-theme.min.css">
</head>
<body>

<div class="container">
''')

cat = ''
for x in objs:
	if cat != x[0]:
		if cat:
			index.write('</ul>\n\n')
		cat = x[0]
		index.write('<label>{0}</label>\n'.format(cat))
		index.write('<ul>\n')
	index.write('<li><a href="{0}.html">{0}</a></li>\n'.format(x))

if cat:
	index.write('</ul>\n')

index.write('''
</div>

</body>
</html>
''')