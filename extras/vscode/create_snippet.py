import json
import sys

text = open(sys.argv[1], 'r').read()
lines = text.replace(' ' * 4, '\t').splitlines()
print(json.dumps(lines, indent=4))
