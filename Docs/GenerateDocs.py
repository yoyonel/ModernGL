import ModernGL as GL
import os, shutil

if not os.path.isdir('Generated'):
	os.mkdir('Generated')

for x in dir(GL):
	if x.startswith('__'):
		continue

	if type(GL.__dict__[x]) is int:
		open('Generated/%s.html' % x, 'w').write(str(GL.__dict__[x]))

	elif type(GL.__dict__[x]) is str:
		continue

	else:
		open('Generated/%s.html' % x, 'w').write(str(GL.__dict__[x].__doc__))
