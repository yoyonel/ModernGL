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

page = open('Data/PageTemplate.html').read()
func = open('Data/FunctionTemplate.html').read()
const = open('Data/ConstantTemplate.html').read()

if os.path.isdir('ModernGL'):
	shutil.rmtree('ModernGL')

os.mkdir('ModernGL')

objs = sorted([x for x in dir(GL) if not x.startswith('__') and x != 'ModernGL'])

for x in objs:
	os.mkdir('ModernGL/%s' % x)
	if type(GL.__dict__[x]) is int:
		form = {
			'name' : x,
			'value' : str(GL.__dict__[x]),
		}
		done = page.format_map({'title' : x, 'subtitle': x, 'content' : const.format_map(form)})
		open('ModernGL/%s/index.html' % x, 'w').write(done)

	elif type(GL.__dict__[x]) is str:
		form = {
			'name' : x,
			'value' : '"' + GL.__dict__[x] + '"',
		}
		done = page.format_map({'title' : x, 'subtitle': x, 'content' : const.format_map(form)})
		open('ModernGL/%s/index.html' % x, 'w').write(done)

	else:
		form = {
			'name' : x,
			'docs' : str(GL.__dict__[x].__doc__),
			'implementation' : html.escape(func_with_name(x)),
			'function': '',
			'similar' : '',
		}
		done = page.format_map({'title' : x, 'subtitle': x, 'content' : func.format_map(form)})
		open('ModernGL/%s/index.html' % x, 'w').write(done)


content = ''

cats = []

cat = ''
for x in objs:
	if cat != x[0]:
		if cat:
			content += '</ul>\n'
			content += '<hr></hr>\n'

		cat = x[0]
		cats.append(cat)
		content += '<label id="{0}">{0}</label>\n'.format(cat)
		content += '<ul class="home-ul">\n'
	content += '<li><a href="{0}">{0}</a></li>\n'.format(x)

if cat:
	content += '</ul>\n'

# content = ' '.join('<a href="#{0}">{0}</a>'.format(x) for x in cats) + '<hr>' + content

open('ModernGL/index.html', 'w').write(page.format_map({'title' : 'ModernGL', 'subtitle': 'Docs', 'content' : content}))

import zipfile

# z = zipfile.ZipFile('ModernGL-Docs.zip', 'w')

# for f in os.listdir('ModernGL'):
# 	z.write(os.path.join('ModernGL', f), f)

shutil.copyfile('Data/bootstrap.min.css', 'ModernGL/bootstrap.min.css')
shutil.copyfile('Data/bootstrap-theme.min.css', 'ModernGL/bootstrap-theme.min.css')
shutil.copyfile('Data/style.css', 'ModernGL/style.css')
