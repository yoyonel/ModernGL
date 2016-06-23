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

objs = sorted([x for x in dir(GL) if not x.startswith('__') and x != 'ModernGL'])

for x in objs:
	if type(GL.__dict__[x]) is int:
		form = {
			'name' : x,
			'value' : str(GL.__dict__[x]),
		}
		open('Static/%s.html' % x, 'w').write(const.format_map(form))

	if type(GL.__dict__[x]) is str:
		form = {
			'name' : x,
			'value' : '"' + GL.__dict__[x] + '"',
		}
		open('Static/%s.html' % x, 'w').write(const.format_map(form))

	else:
		form = {
			'name' : x,
			'docs' : str(GL.__dict__[x].__doc__),
			'implementation' : html.escape(func_with_name(x)),
			'function': '',
			'similar' : '',
		}
		open('Static/%s.html' % x, 'w').write(func.format_map(form))

index = open('Static/index.html', 'w')

index.write('''
<!DOCTYPE html>
<html>
<head>
	<title>ModernGL</title>
	<link rel="stylesheet" type="text/css" href="bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="bootstrap-theme.min.css">
</head>
<body>

<div class="container">

<h1>ModernGL</h1>

''')

cat = ''
for x in objs:
	if cat != x[0]:
		if cat:
			index.write('</ul>\n')
			index.write('<hr></hr>\n')

		cat = x[0]
		index.write('<label id="{0}">{0}</label>\n'.format(cat))
		index.write('<ul>\n')
	index.write('<li><a href="{0}.html">{0}</a></li>\n'.format(x))

if cat:
	index.write('</ul>\n')

index.write('''
</div>

<style>
body {
	background-color: #FAFAFA;
}

h1 {
	text-align: center;
}

.container {
	background-color: #FEFEFE;
	border: 1px solid #202020;
	padding-bottom: 90px;
	margin-bottom: 30px;
	margin-top: 30px;
}

ul {
	list-style-type: none;
}

ul {
	columns: 1;
	-webkit-columns: 1;
	-moz-columns: 1;
}

@media (min-width: 768px) {
	ul {
		columns: 2;
		-webkit-columns: 2;
		-moz-columns: 2;
	}
}

@media (min-width: 992px) {
	ul {
		columns: 3;
		-webkit-columns: 3;
		-moz-columns: 3;
	}
}

@media (min-width: 1200px) {
	ul {
		columns: 4;
		-webkit-columns: 4;
		-moz-columns: 4;
	}
}

</style>

</body>
</html>
''')

import zipfile

z = zipfile.ZipFile('ModernGL-Docs.zip', 'w')

for f in os.listdir('Static'):
	z.write(os.path.join('Static', f), f)
