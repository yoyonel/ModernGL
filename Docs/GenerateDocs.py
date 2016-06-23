import ModernGL as GL
import os, shutil, re, textwrap, html

pycode = open('../Source/Python-ModernGL.cpp').read()
ccode = open('../Source/ModernGL.cpp').read()

exec(open('LookupOpenGL.py').read())

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

def params_from_docs(docs, what):
	at = docs.find(what + ':\n')
	at += len(what + ':\n')

	result = []
	while docs[at] == '\t':
		end = docs.find('\n', at)
		if docs[at + 1 : end] == 'None':
			result.append(('', 'None'))
			at = end + 1
			continue

		param, rest = docs[at + 1 : end].split(' ', 1)
		default = rest.find('By default is ')
		if default >= 0:
			default += len('By default is ')
			param += ' = ' + rest[default:]
		result.append((param, docs[at + 1 : end]))
		at = end + 1

	return result

def lookup_func(m):
	return 'href="%s"' % lookup[m.group(1)]

def better_impl(code):
	code = html.escape(code)
	code = re.sub(r'([\+\*\=\-\|!\:\?]|&amp;|&lt;|&gt;)', r'<span class="token token_operator">\1</span>', code)
	code = re.sub(r'(//[^\n]+)', r'<span class="token token_comment">\1</span>', code)
	code = re.sub(r'(&quot;.+(?=(&quot;))&quot;)', r'<span class="token token_string">\1</span>', code)
	code = re.sub(r'\b(gl[a-zA-Z0-9]+)', r'<a href="\1" class="token token_glfunc">\1</a>', code)
	code = re.sub(r'\b([A-Z][a-zA-Z0-9]+)\(', r'<span class="token token_myfunc">\1</span>(', code)
	code = re.sub(r'\b(GL_[A-Z_0-9]+)\b', r'<span class="token token_glconst">\1</span>', code)
	code = re.sub(r'\b(GL[a-z]+)\b', r'<span class="token token_glkeyword">\1</span>', code)
	code = re.sub(r'\b(GL[a-z]+|bool|int|float|return|unsigned|const|char|void|if|else|for|while)\b', r'<span class="token token_mykeyword">\1</span>', code)
	code = re.sub(r'\b([0-9]+)\b', r'<span class="token token_integer">\1</span>', code)
	code = re.sub(r'([\(\)\{\}\,])', r'<span class="token token_sign">\1</span>', code)
	code = re.sub(r'href="([^"]+)"', lookup_func, code)
	return code

def parse_description(docs):
	return docs[:docs.find('Parameters:\n')].strip()

def highlight_triple(code):
	code = re.sub(r'^(\w+) (\([^\)]+\)) (.+)', r'\1 <span class="token token_operator">\2</span> <span class="token token_comment">\3</span>', code)
	if code == 'None':
		code = '<span class="token token_none">' + code + '</span>'
	return code

def parse_what_line(docs, what):
	return '\n'.join(highlight_triple(y[1]) for y in params_from_docs(docs, what))

def parse_params(docs):
	return parse_what_line(docs, 'Parameters')

def parse_returns(docs):
	return parse_what_line(docs, 'Returns')
	# return re.sub(r'^(\w+) (\([^\)]+\)) (.+)', r'\1 <span class="token token_operator">\2</span> <span class="token token_comment">\3</span>', re.search(r'Returns: (.+)', docs).group(1))

def parse_func(docs):
	code = '%s(%s)' % (x, ', '.join(y[0] for y in params_from_docs(GL.__dict__[x].__doc__, 'Parameters')))
	code = re.sub(r'\b([A-Z][a-zA-Z0-9]+)\(', r'<span class="token token_myfunc">\1</span>(', code)
	code = re.sub(r'([\(\)\{\}\,])', r'<span class="token token_sign">\1</span>', code)
	return code

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
			'docs' : parse_description(GL.__dict__[x].__doc__),
			'parameters' : parse_params(GL.__dict__[x].__doc__),
			'returns' : parse_returns(GL.__dict__[x].__doc__),
			'implementation' : better_impl(func_with_name(x)),
			'function': parse_func(GL.__dict__[x].__doc__),
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
		content += '<label style="float: left;" id="{0}">{0}</label>\n'.format(cat)
		content += '<ul class="home-ul">\n'
	content += '<li><a href="/ModernGL/{0}">{0}</a></li>\n'.format(x)

if cat:
	content += '</ul>\n'

# content = ' '.join('<a href="#{0}">{0}</a>'.format(x) for x in cats) + '<hr>' + content

os.mkdir('ModernGL/Docs')

open('ModernGL/Docs/index.html', 'w').write(page.format_map({'title' : 'ModernGL', 'subtitle': 'Docs', 'content' : content}))

import zipfile

z = zipfile.ZipFile('ModernGL-Docs.zip', 'w')

shutil.copyfile('Data/bootstrap.min.css', 'ModernGL/bootstrap.min.css')
shutil.copyfile('Data/bootstrap-theme.min.css', 'ModernGL/bootstrap-theme.min.css')
shutil.copyfile('Data/style.css', 'ModernGL/style.css')

for path, folders, files in os.walk('ModernGL'):
	for f in files:
		f = os.path.join(path, f)
		z.write(f, f[len('ModernGL/'):], zipfile.ZIP_DEFLATED)
