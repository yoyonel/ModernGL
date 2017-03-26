import os, sys

here = os.path.dirname(os.path.abspath(__file__))

os.chdir('tests')

if here in sys.path:
	sys.path.remove(here)

